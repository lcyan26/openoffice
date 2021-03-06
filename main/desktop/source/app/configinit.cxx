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
#include "precompiled_desktop.hxx"

#include "configinit.hxx"

#include "desktop.hrc"
#include "app.hxx"
#include <comphelper/processfactory.hxx>
#include <uno/current_context.hxx>
#include <cppuhelper/implbase1.hxx>
#include <rtl/ustrbuf.hxx>
#include <osl/diagnose.h>
#include <stdio.h>
#include <map>
#include <com/sun/star/lang/ServiceNotRegisteredException.hpp>
#include <com/sun/star/configuration/CannotLoadConfigurationException.hpp>
#include <com/sun/star/configuration/InvalidBootstrapFileException.hpp>
#include <com/sun/star/configuration/backend/BackendSetupException.hpp>
#include <com/sun/star/configuration/backend/CannotConnectException.hpp>

// ----------------------------------------------------------------------------

namespace uno           = ::com::sun::star::uno;
namespace lang          = ::com::sun::star::lang;
namespace configuration = ::com::sun::star::configuration;
namespace backend       = ::com::sun::star::configuration::backend;
using rtl::OUString;
using uno::UNO_QUERY;
using desktop::Desktop;

// ----------------------------------------------------------------------------
static char const CONFIGURATION_PROVIDER[]  = "com.sun.star.configuration.ConfigurationProvider";

static char const CONFIGURATION_ERROR_HANDLER[]  = "com.sun.star.configuration.backend.InteractionHandler";

// must be aligned with configmgr/source/misc/configinteractionhandler
static char const CONFIG_ERROR_HANDLER[] = "configuration.interaction-handler";
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
#define arraysize( arr ) ( sizeof (arr)/sizeof *(arr) )

typedef uno::Reference< lang::XMultiServiceFactory > ConfigurationProvider;

#define OUSTRING( constascii ) OUString( RTL_CONSTASCII_USTRINGPARAM( constascii ) )

#define OU2O( ustr, enc ) rtl::OUStringToOString( (ustr), RTL_TEXTENCODING_ ## enc )

#define k_PROVIDER OUSTRING( CONFIGURATION_PROVIDER )
#define k_ERRORHANDLER OUSTRING( CONFIGURATION_ERROR_HANDLER )
// ----------------------------------------------------------------------------
// Get a message string securely. There is a fallback string if the resource
// is not available. Adapted from Desktop::GetMsgString()

OUString getMsgString( sal_uInt16 nId, char const * aFallBackMsg )
{
    ResMgr* pResMgr = Desktop::GetDesktopResManager();
    if ( !pResMgr || !nId )
        return OUString::createFromAscii(aFallBackMsg);
    else
        return OUString( String(ResId( nId, *pResMgr )));
}
// ----------------------------------------------------------------------------
/** Creates the normal configuration provider.

*/
static
ConfigurationProvider createDefaultConfigurationProvider( )
{
    uno::Reference< lang::XMultiServiceFactory > xServiceManager = ::comphelper::getProcessServiceFactory();

    OSL_ENSURE( xServiceManager.is(),"No ServiceManager set for CreateApplicationConfigurationProvider");

    ConfigurationProvider xProvider;

    if (xServiceManager.is())
    {
   
            xProvider.set( xServiceManager->createInstance(k_PROVIDER),  UNO_QUERY);
    }

    if (!xProvider.is())
    {
        OUString const sMsg = OUSTRING("Service \"") + k_PROVIDER + 
                                OUSTRING("\" is not available at the service manager.");

        throw lang::ServiceNotRegisteredException(sMsg, xServiceManager);
    }

    return xProvider;
}
// ----------------------------------------------------------------------------
/// @attention this method must be called from a catch statement!
static void handleGeneralException(uno::Exception& aException,
                                   const rtl::OUString& aMessage)
{
    aException.Message = aMessage ;
    throw ;
}
// ----------------------------------------------------------------------------

uno::Reference< lang::XMultiServiceFactory > CreateApplicationConfigurationProvider( )
{
    uno::Reference< lang::XMultiServiceFactory > xProvider;
    
    try
    {
        xProvider = createDefaultConfigurationProvider( );
    }
    catch (configuration::InvalidBootstrapFileException & exception)
    {
        handleGeneralException(exception,
                getMsgString( STR_CONFIG_ERR_SETTINGS_INCOMPLETE,
                            "The startup settings for your configuration settings are incomplete. "));
    }
     catch (backend::CannotConnectException & exception)
    {
        handleGeneralException(exception,
                getMsgString( STR_CONFIG_ERR_CANNOT_CONNECT, 
                            "A connection to your configuration settings could not be established. "));
    }
    catch (backend::BackendSetupException & exception)
    {
        handleGeneralException(exception,
                getMsgString( STR_CONFIG_ERR_CANNOT_CONNECT, 
                            "A connection to your configuration settings could not be established. "));
    }
    catch (configuration::CannotLoadConfigurationException & exception)
    {
        handleGeneralException(exception,
                getMsgString( STR_CONFIG_ERR_CANNOT_CONNECT, 
                            "A connection to your configuration settings could not be established. "));
    }
    catch (uno::Exception & exception)
    {
        handleGeneralException(exception,
                getMsgString( STR_CONFIG_ERR_ACCESS_GENERAL, 
                            "A general error occurred while accessing your configuration settings."));
    }


    return xProvider ;
}
// ----------------------------------------------------------------------------




// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ConfigurationErrorHandler
// ----------------------------------------------------------------------------

namespace
{
    typedef uno::Reference< uno::XCurrentContext > CurrentContext;
    class SimpleCurrentContext : public cppu::WeakImplHelper1< uno::XCurrentContext >
    {
        CurrentContext m_xChainedContext;
    public:
        explicit
        SimpleCurrentContext(const CurrentContext & xChainedContext)
        : m_xChainedContext(xChainedContext)
        {}

        void install()      { uno::setCurrentContext(this); }
        void deinstall()    { uno::setCurrentContext(m_xChainedContext); }

        uno::Any getChainedValueByName( OUString const & aName) const
        { 
            return m_xChainedContext.is() 
                            ? m_xChainedContext->getValueByName(aName) 
                            : uno::Any(); 
        }

        // XCurrentContext
        virtual uno::Any SAL_CALL
            getValueByName( OUString const & aName) 
                throw (uno::RuntimeException);
    };
    
    uno::Any SAL_CALL
        SimpleCurrentContext::getValueByName( OUString const & aName) 
            throw (uno::RuntimeException)
    {
        return getChainedValueByName(aName);
    }

}

// ----------------------------------------------------------------------------
class ConfigurationErrorHandler::Context : public SimpleCurrentContext
{
public:
    Context()
    : SimpleCurrentContext( uno::getCurrentContext() )
    {
    }

    ~Context()
    {
    }

    // XCurrentContext
    virtual uno::Any SAL_CALL
        getValueByName( OUString const & aName) 
            throw (uno::RuntimeException);

private:
    InteractionHandler  m_xHandler;
};

//------------------------------------------------------------------------------
uno::Any SAL_CALL ConfigurationErrorHandler::Context::getValueByName( OUString const & aName) 
        throw (uno::RuntimeException)
{
    if ( aName.equalsAscii( CONFIG_ERROR_HANDLER ) )
    {
        if ( !m_xHandler.is() )
            m_xHandler = ConfigurationErrorHandler::getDefaultInteractionHandler();
        return uno::Any( m_xHandler );
    }
    return SimpleCurrentContext::getValueByName( aName );
}

//------------------------------------------------------------------------------
ConfigurationErrorHandler::~ConfigurationErrorHandler()
{
    deactivate();
}

//------------------------------------------------------------------------------
/// installs the handler into the current context
void ConfigurationErrorHandler::activate()
{
    if (!m_pContext) 
    {
        m_pContext = new Context;
        m_pContext->acquire();
    }
    m_pContext->install();
}

//------------------------------------------------------------------------------
/// deinstalls the handler from the current context, restoring the previous context
void ConfigurationErrorHandler::deactivate()
{
    if (m_pContext) 
    {
        m_pContext->deinstall();
        m_pContext->release();
        m_pContext = 0;
    }
}
//------------------------------------------------------------------------------

ConfigurationErrorHandler::InteractionHandler ConfigurationErrorHandler::getDefaultInteractionHandler()
{
    uno::Reference< lang::XMultiServiceFactory > xServiceManager = ::comphelper::getProcessServiceFactory();

    OSL_ENSURE( xServiceManager.is(),"No ServiceManager set for ConfigurationErrorHandler");

    InteractionHandler xHandler;

    if (xServiceManager.is())
    {
        xHandler.set( xServiceManager->createInstance(k_ERRORHANDLER), UNO_QUERY );
    }

    return xHandler;
}
//------------------------------------------------------------------------------



