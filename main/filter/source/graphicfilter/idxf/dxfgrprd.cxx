/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_filter.hxx"

#include <string.h>
#include <stdlib.h>
#include <tools/stream.hxx>
#include "dxfgrprd.hxx"

// ----------------------------------------------------------------------------

// we use an own ReadLine function, because Stream::ReadLine stops if
// a 0-sign occurs; this functions converts 0-signs to blanks and reads
// a complete line until a cr/lf is found

sal_Bool DXFReadLine( SvStream& rIStm, ByteString& rStr )
{
	char  buf[256 + 1];
	sal_Bool  bEnd = sal_False;
	sal_uLong nOldFilePos = rIStm.Tell();
	char  c = 0;

	rStr.Erase();

	while( !bEnd && !rIStm.GetError() )   // !!! nicht auf EOF testen,
										  // !!! weil wir blockweise
										  // !!! lesen
	{
		sal_uInt16 nLen = (sal_uInt16)rIStm.Read( buf, sizeof(buf)-1 );
		if( !nLen )
		{
			if( rStr.Len() == 0 )
				return sal_False;
			else
				break;
		}

		for( sal_uInt16 n = 0; n < nLen ; n++ )
		{
			c = buf[n];
			if( c != '\n' && c != '\r' )
			{
				if( !c )
					c = ' ';
				rStr += c;
			}
			else
			{
				bEnd = sal_True;
				break;
			}
		}
	}

	if( !bEnd && !rIStm.GetError() && rStr.Len() )
		bEnd = sal_True;

	nOldFilePos += rStr.Len();
	if( rIStm.Tell() > nOldFilePos )
		nOldFilePos++;
	rIStm.Seek( nOldFilePos );  // seeken wg. obigem BlockRead!

	if( bEnd && (c=='\r' || c=='\n'))  // Sonderbehandlung DOS-Dateien
	{
		char cTemp;
		rIStm.Read((char*)&cTemp , sizeof(cTemp) );
		if( cTemp == c || (cTemp != '\n' && cTemp != '\r') )
			rIStm.Seek( nOldFilePos );
	}

	return bEnd;
}

// ------------------

DXFGroupReader::DXFGroupReader(SvStream & rIStream, sal_uInt16 nminpercent, sal_uInt16 nmaxpercent ) :
	rIS(rIStream)
{
	sal_uInt16 i;

	nIBuffPos=0;
	nIBuffSize=0;
	bStatus=sal_True;
	nLastG=0;
	nGCount=0;

	nMinPercent=(sal_uLong)nminpercent;
	nMaxPercent=(sal_uLong)nmaxpercent;
	nLastPercent=nMinPercent;

	rIS.Seek(STREAM_SEEK_TO_END);
	nFileSize=rIS.Tell();
	rIS.Seek(0);

	for (i=0; i<10; i++) S0_9[i][0]=0;
    S100[ 0 ] = S102[ 0 ] = 0;
	for (i=0; i<50; i++) F10_59[i]=0.0;
	for (i=0; i<20; i++) I60_79[i]=0;
	for (i=0; i<10; i++) I90_99[i]=0;
	for (i=0; i< 8; i++) F140_147[i]=0.0;
	for (i=0; i< 6; i++) I170_175[i]=0;
	for (i=0; i<30; i++) F210_239[i]=0.0;
	for (i=0; i<11; i++) S999_1009[i][0]=0;
	for (i=0; i<50; i++) F1010_1059[i]=0.0;
	for (i=0; i<20; i++) I1060_1079[i]=0;

}


sal_uInt16 DXFGroupReader::Read()
{
	sal_uInt16 nG = 0;
	if ( bStatus )
	{
		nGCount++;
		nG = (sal_uInt16)ReadI();
		if ( bStatus )
		{
			char aTmp[ DXF_MAX_STRING_LEN + 1 ];

			if      (nG<  10) ReadS(S0_9[nG]);
			else if (nG<  60) F10_59[nG-10]=ReadF();
			else if (nG<  80) I60_79[nG-60]=ReadI();
			else if (nG<  90) ReadS( aTmp );
			else if (nG<  99) I90_99[nG-90]=ReadI();
			else if (nG==100) ReadS(S100);
			else if (nG==102) ReadS(S102);
			else if (nG==105) ReadS( aTmp );
			else if (nG< 140) ReadS( aTmp );
			else if (nG< 148) F140_147[nG-140]=ReadF();
			else if (nG< 170) ReadS( aTmp );
			else if (nG< 176) I170_175[nG-175]=ReadI();
			else if (nG< 180) ReadI();
			else if (nG< 210) ReadS( aTmp );
			else if (nG< 240) F210_239[nG-210]=ReadF();
			else if (nG<=369) ReadS( aTmp );
			else if (nG< 999) ReadS( aTmp );
			else if (nG<1010) ReadS(S999_1009[nG-999]);
			else if (nG<1060) F1010_1059[nG-1010]=ReadF();
			else if (nG<1080) I1060_1079[nG-1060]=ReadI();
			else bStatus = sal_False;
		}
	}
	if ( bStatus )
		nLastG = nG;
	else
	{
		nG = 0;
		SetS( 0, "EOF" );
		if ( nGCount != 0xffffffff )
		{
			// InfoBox(NULL,String("Fehler ab Gruppe Nr ")+String(nGCount)).Execute();
			nGCount=0xffffffff;
		}
	}
	nLastG = nG;
	return nG;
}


long DXFGroupReader::GetI(sal_uInt16 nG)
{
	sal_Int32 nRetValue = 0;
	if ( ( nG >= 60 ) && ( nG <= 79 ) )
		nRetValue = I60_79[ nG - 60 ];
	else if ( ( nG >= 90 ) && ( nG <= 99 ) )
		nRetValue = I90_99[ nG - 90 ];
	else if ( ( nG >= 170 ) && ( nG <= 175 ) )
		nRetValue = I170_175[ nG - 170 ];
	else if ( ( nG >= 1060 ) && ( nG <= 1079 ) )
		nRetValue = I1060_1079[ nG - 1060 ];
	return nRetValue;
}

double DXFGroupReader::GetF(sal_uInt16 nG)
{
	nG-=10;
	if (nG<50) return F10_59[nG];
	else {
		nG-=130;
		if (nG<8) return F140_147[nG];
		else {
			nG-=70;
			if (nG<30) return F210_239[nG];
			else {
				nG-=800;
				if (nG<50) return F1010_1059[nG];
				else return 0;
			}
		}
	}
}

const char * DXFGroupReader::GetS(sal_uInt16 nG)
{
	if (nG<10) return S0_9[nG];
	else if ( nG == 100 )
        return S100;    
    else if ( nG == 102 )
        return S102;
    else
    {
		nG-=999;
		if (nG<11) return S999_1009[nG];
		else return NULL;
	}
}

void DXFGroupReader::SetF(sal_uInt16 nG, double fF)
{
	nG-=10;
	if (nG<50) F10_59[nG]=fF;
	else {
		nG-=130;
		if (nG<8) F140_147[nG]=fF;
		else {
			nG-=70;
			if (nG<30) F210_239[nG]=fF;
			else {
				nG-=800;
				if (nG<50) F1010_1059[nG]=fF;
			}
		}
	}
}


void DXFGroupReader::SetS(sal_uInt16 nG, const char * sS)
{
    char* pPtr = NULL;
	if ( nG < 10 )
        pPtr = S0_9[ nG ];
	else if ( nG == 100 )
        pPtr = S100;
    else if ( nG == 102 )
        pPtr = S102;
    else
    {
		nG -= 999;
		if ( nG < 11 )
            pPtr = S999_1009[ nG ];
	}
    if ( pPtr )
        strncpy( pPtr, sS, DXF_MAX_STRING_LEN + 1 );
}


void DXFGroupReader::ReadLine(char * ptgt)
{
	ByteString	aStr;
	sal_uLong		nLen;
	
	DXFReadLine( rIS, aStr );

	nLen = aStr.Len();
	if ( nLen > DXF_MAX_STRING_LEN )
		nLen = DXF_MAX_STRING_LEN;

	memcpy( ptgt, aStr.GetBuffer(), nLen );
	ptgt[ nLen ] = 0x00;
/*
	if ( pCallback )
	{
		const sal_uLong nPercent= nMinPercent + (nMaxPercent-nMinPercent)*rIS.Tell() / nFileSize;

		if ( nPercent >= nLastPercent + 4 )
		{
			nLastPercent=nPercent;
			if (((*pCallback)(pCallerData,(sal_uInt16)nPercent))==sal_True)
				bStatus=sal_False;
		}
	}
*/
}


long DXFGroupReader::ReadI()
{
	char sl[DXF_MAX_STRING_LEN+1],*p;

	ReadLine(sl);

	p=sl;

	while(*p==0x20) p++;

	if ((*p<'0' || *p>'9') && *p!='-') {
		bStatus=sal_False;
		return 0;
	}

	char *start = p;
	if (*p=='-') {
		p++;
	}
	while (*p>='0' && *p<='9') {
		p++;
	}

	char prev = *p;
	*p = '\0';
	char *end;
	long res = strtol(start, &end, 10);
	*p = prev;
	if (end != p) {
		bStatus=sal_False;
		return 0;
	}

	while (*p==0x20) p++;
	if (*p!=0) {
		bStatus=sal_False;
		return 0;
	}

	return res;
}


double DXFGroupReader::ReadF()
{
	char sl[DXF_MAX_STRING_LEN+1],*p;

	ReadLine(sl);
	p=sl;
	while(*p==0x20) p++;
	if ((*p<'0' || *p>'9') && *p!='.' && *p!='-') {
		bStatus=sal_False;
		return 0.0;
	}
	return atof(p);
}


void DXFGroupReader::ReadS(char * ptgt)
{
	ReadLine(ptgt);
}


