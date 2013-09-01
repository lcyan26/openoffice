#**************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
#**************************************************************



# edit to match directory level 
PRJ		= ..$/..$/..
# same for all makefiles in "helpcontent2"
PRJNAME = help_swriter

LANGUAGE_FILELIST= main0103.xhp \
main0104.xhp \
04/01020000.xhp \
02/18030700.xhp \
02/10050000.xhp \
02/08080000.xhp \
02/18120000.xhp \
02/06040000.xhp \
02/06080000.xhp \
02/18030300.xhp \
02/04090000.xhp \
02/19020000.xhp \
02/10080000.xhp \
02/06130000.xhp \
02/04250000.xhp \
02/04220000.xhp \
02/03220000.xhp \
02/10090000.xhp \
02/14010000.xhp \
02/18010000.xhp \
02/06070000.xhp \
02/18030400.xhp \
02/03210000.xhp \
02/19030000.xhp \
02/14030000.xhp \
02/14050000.xhp \
02/04100000.xhp \
02/19050000.xhp \
02/10020000.xhp \
02/08010000.xhp \
02/18030200.xhp \
02/02110000.xhp \
02/18030600.xhp \
02/14020000.xhp \
02/19010000.xhp \
02/18030100.xhp \
02/06090000.xhp \
02/06140000.xhp \
02/10030000.xhp \
02/18030500.xhp \
02/04240000.xhp \
02/04230000.xhp \
02/10010000.xhp \
02/10110000.xhp \
02/10070000.xhp \
02/18130000.xhp \
02/14040000.xhp \
02/18030000.xhp \
02/06120000.xhp \
02/19040000.xhp \
main0102.xhp \
main0213.xhp \
main0100.xhp \
main0206.xhp \
main0210.xhp \
main0000.xhp \
main0107.xhp \
main0200.xhp \
main0106.xhp \
00/00000402.xhp \
00/00000406.xhp \
00/00000404.xhp \
00/00000405.xhp \
00/00000403.xhp \
00/00000401.xhp \
00/00000004.xhp \
01/mailmerge07.xhp \
01/04090100.xhp \
01/mm_matfie.xhp \
01/04200000.xhp \
01/05140000.xhp \
01/05100300.xhp \
01/05060000.xhp \
01/mailmerge08.xhp \
01/04010000.xhp \
01/06040000.xhp \
01/05090201.xhp \
01/03140000.xhp \
01/04120213.xhp \
01/06080000.xhp \
01/05060800.xhp \
01/05090100.xhp \
01/mailmerge01.xhp \
01/04020100.xhp \
01/05150100.xhp \
01/05110000.xhp \
01/04120212.xhp \
01/04090004.xhp \
01/04090000.xhp \
01/mailmerge03.xhp \
01/04020200.xhp \
01/04120210.xhp \
01/04120300.xhp \
01/mm_seladdblo.xhp \
01/05150000.xhp \
01/05150300.xhp \
01/mailmerge04.xhp \
01/05060100.xhp \
01/03100000.xhp \
01/04120250.xhp \
01/02170000.xhp \
01/06210000.xhp \
01/03070000.xhp \
01/02130000.xhp \
01/04120200.xhp \
01/04130000.xhp \
01/04060000.xhp \
01/mm_cusaddlis.xhp \
01/06160000.xhp \
01/06060100.xhp \
01/04090007.xhp \
01/mm_newaddblo.xhp \
01/03080000.xhp \
01/05060201.xhp \
01/mailmerge02.xhp \
01/04040000.xhp \
01/04220000.xhp \
01/05030400.xhp \
01/06170000.xhp \
01/03120000.xhp \
01/06080200.xhp \
01/06220000.xhp \
01/04120225.xhp \
01/04090001.xhp \
01/05200000.xhp \
01/01150000.xhp \
01/04060100.xhp \
01/02110100.xhp \
01/03050000.xhp \
01/04030000.xhp \
01/05030200.xhp \
01/01120000.xhp \
01/05040700.xhp \
01/04120221.xhp \
01/05090200.xhp \
01/04090005.xhp \
01/05130000.xhp \
01/04120219.xhp \
01/04120214.xhp \
01/01160200.xhp \
01/03130000.xhp \
01/06100000.xhp \
01/04120100.xhp \
01/05150101.xhp \
01/04120211.xhp \
01/04120226.xhp \
01/mm_finent.xhp \
01/05110100.xhp \
01/05060700.xhp \
01/05060900.xhp \
01/04120000.xhp \
01/mailmerge06.xhp \
01/05150104.xhp \
01/05180000.xhp \
01/06030000.xhp \
01/05120500.xhp \
01/04120201.xhp \
01/05040600.xhp \
01/mm_cusaddfie.xhp \
01/mailmerge00.xhp \
01/04130100.xhp \
01/04070200.xhp \
01/05120400.xhp \
01/format_object.xhp \
01/01160100.xhp \
01/06200000.xhp \
01/05130002.xhp \
01/05120300.xhp \
01/03090000.xhp \
01/02110000.xhp \
01/04120217.xhp \
01/selection_mode.xhp \
01/04190000.xhp \
01/04090002.xhp \
01/04180400.xhp \
01/04120216.xhp \
01/05120200.xhp \
01/05100000.xhp \
01/mm_newaddlis.xhp \
01/02140000.xhp \
01/mm_seladdlis.xhp \
01/04150000.xhp \
01/05030800.xhp \
01/05170000.xhp \
01/04990000.xhp \
01/05100400.xhp \
01/04210000.xhp \
01/05090300.xhp \
01/05040500.xhp \
01/05060200.xhp \
01/02120100.xhp \
01/05130004.xhp \
01/06090000.xhp \
01/05040800.xhp \
01/04020000.xhp \
01/06080100.xhp \
01/04120227.xhp \
01/06110000.xhp \
01/05990000.xhp \
01/mm_cusgrelin.xhp \
01/04120215.xhp \
01/04230000.xhp \
01/05190000.xhp \
01/01160500.xhp \
01/05130100.xhp \
01/05110200.xhp \
01/05120100.xhp \
01/05120000.xhp \
01/05040000.xhp \
01/05040501.xhp \
01/02160000.xhp \
01/05110500.xhp \
01/06060000.xhp \
01/mm_emabod.xhp \
01/mm_copyto.xhp \
01/mm_seltab.xhp \
01/04090006.xhp \
01/mailmerge05.xhp \
01/05110300.xhp \
01/04070100.xhp \
01/02150000.xhp \
01/04120224.xhp \
01/04120229.xhp \
01/05090000.xhp \
01/04120220.xhp \
01/02120000.xhp \
01/06190000.xhp \
01/04070300.xhp \
01/01160400.xhp \
01/05080000.xhp \
01/04120223.xhp \
01/05150200.xhp \
01/04120222.xhp \
01/04090003.xhp \
01/01160300.xhp \
01/04070000.xhp \
01/05060300.xhp \
01/06120000.xhp \
01/04090200.xhp \
01/06180000.xhp \
01/06990000.xhp \
main0220.xhp \
main0203.xhp \
guide/textdoc_inframe.xhp \
guide/wrap.xhp \
guide/form_letters_main.xhp \
guide/globaldoc_howtos.xhp \
guide/shortcut_writing.xhp \
guide/indices_toc.xhp \
guide/nonprintable_text.xhp \
guide/print_small.xhp \
guide/captions.xhp \
guide/text_capital.xhp \
guide/main.xhp \
guide/autotext.xhp \
guide/table_insert.xhp \
guide/fields_userdata.xhp \
guide/removing_line_breaks.xhp \
guide/borders.xhp \
guide/pageorientation.xhp \
guide/auto_off.xhp \
guide/arrange_chapters.xhp \
guide/border_object.xhp \
guide/section_edit.xhp \
guide/text_direct_cursor.xhp \
guide/insert_graphic.xhp \
guide/text_nav_keyb.xhp \
guide/printing_order.xhp \
guide/templates_styles.xhp \
guide/calculate_intext.xhp \
guide/indices_multidoc.xhp \
guide/indices_edit.xhp \
guide/text_animation.xhp \
guide/text_centervert.xhp \
guide/indices_enter.xhp \
guide/header_with_chapter.xhp \
guide/load_styles.xhp \
guide/word_completion.xhp \
guide/table_select.xhp \
guide/insert_beforetable.xhp \
guide/indices_index.xhp \
guide/text_emphasize.xhp \
guide/table_cells.xhp \
guide/dragdroptext.xhp \
guide/change_header.xhp \
guide/footer_pagenumber.xhp \
guide/numbering_lines.xhp \
guide/insert_graphic_gallery.xhp \
guide/auto_spellcheck.xhp \
guide/fields_enter.xhp \
guide/field_convert.xhp \
guide/header_footer.xhp \
guide/section_insert.xhp \
guide/pagebackground.xhp \
guide/protection.xhp \
guide/hyperlinks.xhp \
guide/jump2statusbar.xhp \
guide/header_pagestyles.xhp \
guide/references_modify.xhp \
guide/words_count.xhp \
guide/indices_literature.xhp \
guide/template_default.xhp \
guide/send2html.xhp \
guide/captions_numbers.xhp \
guide/smarttags.xhp \
guide/calculate_clipboard.xhp \
guide/registertrue.xhp \
guide/insert_graphic_scan.xhp \
guide/table_delete.xhp \
guide/resize_navigator.xhp \
guide/anchor_object.xhp \
guide/conditional_text2.xhp \
guide/stylist_fromselect.xhp \
guide/globaldoc.xhp \
guide/insert_line.xhp \
guide/hyphen_prevent.xhp \
guide/insert_graphic_fromdraw.xhp \
guide/autocorr_except.xhp \
guide/text_rotate.xhp \
guide/footnote_usage.xhp \
guide/header_with_line.xhp \
guide/indices_delete.xhp \
guide/print_brochure.xhp \
guide/text_frame.xhp \
guide/calculate_intable.xhp \
guide/page_break.xhp \
guide/indices_userdef.xhp \
guide/table_sizing.xhp \
guide/hidden_text_display.xhp \
guide/using_numbered_lists2.xhp \
guide/navigator.xhp \
guide/pagestyles.xhp \
guide/join_numbered_lists.xhp \
guide/template_create.xhp \
guide/indices_form.xhp \
guide/tablemode.xhp \
guide/using_thesaurus.xhp \
guide/even_odd_sdw.xhp \
guide/hidden_text.xhp \
guide/chapter_numbering.xhp \
guide/insert_tab_innumbering.xhp \
guide/ruler.xhp \
guide/spellcheck_dialog.xhp \
guide/border_page.xhp \
guide/sections.xhp \
guide/number_sequence.xhp \
guide/print_preview.xhp \
guide/stylist_fillformat.xhp \
guide/number_date_conv.xhp \
guide/footer_nextpage.xhp \
guide/search_regexp.xhp \
guide/finding.xhp \
guide/calculate.xhp \
guide/insert_graphic_dialog.xhp \
guide/reset_format.xhp \
guide/indenting.xhp \
guide/pagenumbers.xhp \
guide/fields_date.xhp \
guide/references.xhp \
guide/printer_tray.xhp \
guide/auto_numbering.xhp \
guide/fields.xhp \
guide/table_repeat_multiple_headers.xhp \
guide/word_completion_adjust.xhp \
guide/using_hyphen.xhp \
guide/delete_from_dict.xhp \
guide/using_numbering.xhp \
guide/insert_graphic_fromchart.xhp \
guide/stylist_update.xhp \
guide/conditional_text.xhp \
guide/footnote_with_line.xhp \
guide/calculate_multitable.xhp \
guide/table_cellmerge.xhp \
guide/calculate_intext2.xhp \
guide/using_numbered_lists.xhp \
guide/numbering_paras.xhp \
guide/subscript.xhp \
guide/keyboard.xhp \
guide/background.xhp \
main0208.xhp \
main0205.xhp \
main0214.xhp \
main0216.xhp \
main0101.xhp \
main0204.xhp \
main0215.xhp \
main0105.xhp \
main0202.xhp \
main0110.xhp \
main0503.xhp

.IF "$(MAKETARGETS)"!="genPO"

# edit to match the current package
PACKAGE = text/swriter
# uniqe name (module wide);
# using a modified form of package should do here
TARGET  = text_swriter
# edit to match the current module
MODULE  = swriter

# --- Settings -----------------------------------------------------

.INCLUDE : settings.mk
.INCLUDE : $(PRJ)$/settings.pmk

# this list matches the *.xhp files to process
XHPFILES = \
   main0000.xhp \
   main0100.xhp \
   main0101.xhp \
   main0102.xhp \
   main0103.xhp \
   main0104.xhp \
   main0105.xhp \
   main0106.xhp \
   main0107.xhp \
   main0110.xhp \
   main0200.xhp \
   main0202.xhp \
   main0203.xhp \
   main0204.xhp \
   main0205.xhp \
   main0206.xhp \
   main0208.xhp \
   main0210.xhp \
   main0213.xhp \
   main0214.xhp \
   main0215.xhp \
   main0216.xhp \
   main0220.xhp \
   main0503.xhp 
	
# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk
.INCLUDE : tg_help.mk
.ELSE
.INCLUDE :  settings.mk
.INCLUDE :  target.mk
.ENDIF