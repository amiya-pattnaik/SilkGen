[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_Browser.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Internet Explorer related functions are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		03/11/09	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //									BROWSER RELATED FUNCTIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // function:  IE_CloseAllBrowsers ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Close All Open Browsers
[+] VOID SG_CloseAllBrowsers ()
	[+] do
		[ ] //Closes all instances of browser
		[ ] Browser.CloseOthers ()
		[+] if (Browser.Exists(1))
			[ ] Browser.SetActive()
			[ ] Browser.Close( TRUE)
			[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_CloseAllBrowsers in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_CloseAllBrowsers in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
[ ]
[ ]
[ ] // function:  SG_DeleteCookies ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Deletes temporary internet files and cookies.
[+] explorer SG_DeleteCookies ()
	[+] do
		[ ] BROWSERTYPE bt = GetBrowserType()
		[ ] // //Delete the Files
		[ ] // Open the Explorer options dialog and delete files
		[ ] // Browser.ClearCache ()
		[ ]
		[ ] //Invokeing the Browser if not currently available
		[+] if !Browser.Exists(1)
			[ ] Browser.Invoke()
		[ ]
		[ ] //Deletes the Cookies for Internet Explorer
		[+] if MatchStr("Internet Explorer*","{bt}")
			[ ]
			[ ] // Invoke the options dialog
			[ ] Browser.SetActive()
			[ ] Browser.TypeKeys("<Alt-T>o")
			[ ] sleep(0.5)
			[ ]
			[ ] //Delete Cookies for IE 6
			[+] if IE_Options.General.PushButton("Delete Cookies").Exists()
				[ ] IE_Options.General.PushButton("Delete Cookies").Click()
				[ ] BrowserMessage.OK.Click()
			[ ]
			[ ] //Delete Cookies for IE 7
			[+] if IE_Options.General.PushButton("Delete").Exists()
				[ ] IE_Options.General.PushButton("Delete").Click()
				[ ] IE_Options.DialogBox("Delete Browsing History").PushButton("Delete Cookies").Click()
				[ ] BrowserMessage.Yes.Click()
				[ ] IE_Options.DialogBox("Delete Browsing History").SetActive()
				[ ] Sleep(0.5)
				[ ] IE_Options.DialogBox("Delete Browsing History").PushButton("Close|$5536").SetFocus()
				[ ] IE_Options.DialogBox("Delete Browsing History").PushButton("Close|$5536").Click()
			[ ]
			[+] // if IE_Options.General.PushButton("Delete Files").Exists()
				[ ] // IE_Options.General.PushButton("Delete Files").Click()
				[ ] // Browser.TypeKeys("<ENTER>")
				[ ] // //BrowserMessage.OK.Click()
			[ ]
			[+] if (IE_Options.Exists())
				[ ] IE_Options.OK.Click()
			[ ]
		[ ]
		[ ] //Deletes the Cookies for FireFox
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_DeleteCookies in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_DeleteCookies in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[+] firefox  SG_DeleteCookies ()
	[+] do
		[ ]
		[+] if Firefox.Exists (1)
			[ ] Firefox.SetActive()
		[+] else
			[ ] Firefox.Invoke ()
		[ ]
		[ ] Firefox.Tools.Options.Pick()
		[ ] Sleep(0.5)
		[ ] FF_Options.SetActive ()
		[ ] //Clicking on Privacy options
		[ ] FF_Options.Click (1, 255, 25)
		[ ] Sleep(0.5)
		[ ] FF_Options.ShowCookies.Click()
		[ ] FF_Cookies.SetActive ()
		[ ] Sleep(0.5)
		[ ] //Clicking on Remove All Cookies button on Cookies window
		[ ] FF_Cookies.DoubleClick (1, 160, 290)
		[ ] Sleep(1)
		[ ] FF_Cookies.Close()
		[ ] Sleep(1)
		[+] if(FF_Options.Exists())
			[ ] FF_Options.OK.Click()
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_DeleteCookies in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_DeleteCookies in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
	[ ]
[ ]
[ ] // function:  SG_DeleteCookiesRestartBrowser ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Deletes temporary internet files and cookies and takes the browser down and back up (for IE 6.x only).
[+] explorer SG_DeleteCookiesRestartBrowser ()
	[ ]
	[+] do
		[ ] // Delete cookies and files
		[ ] SG_DeleteCookies()
		[ ]
		[ ] // Restart the Browser
		[ ] Browser.Close ()
		[ ] Browser.Invoke ()
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_DeleteCookiesRestartBrowser in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_DeleteCookiesRestartBrowser in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
		[ ]
[+] firefox  SG_DeleteCookiesRestartBrowser ()
	[ ]
	[+] do
		[ ] // Delete cookies and files
		[ ] SG_DeleteCookies()
		[ ]
		[ ] // Restart the Browser
		[ ] Browser.Close ()
		[ ] Firefox.Invoke ()
		[+] if(FF_RestorePrevSession.Exists(1))
			[ ] FF_RestorePrevSession.Close()
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_DeleteCookiesRestartBrowser in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_DeleteCookiesRestartBrowser in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
		[ ]
[ ]
[ ]
[ ] // function:  SG_DeleteTempInternetFiles ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Deletes temporary internet files and cookies (for IE 6.x only).
[+] explorer SG_DeleteTempInternetFiles ()
	[+] do
		[ ]
		[+] if Browser.Exists ()
			[ ] Browser.SetActive ()
		[+] else
			[ ] Browser.Invoke ()
		[ ]
		[ ] Browser.ClearCache ()
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_DeleteTempInternetFiles in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_DeleteTempInternetFiles in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
		[ ]
[+] firefox  SG_DeleteTempInternetFiles ()
	[+] do
		[ ]
		[+] if Firefox.Exists (1)
			[ ] Firefox.SetActive()
		[+] else
			[ ] Firefox.Invoke ()
		[ ] Firefox.ClearCache ()
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_DeleteTempInternetFiles in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_DeleteTempInternetFiles in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
		[ ]
[ ]
[ ] // function:  SG_FindBadImages (sURLListInFile)
[ ] // parameter: sURLList: The text file containing the list of URLs to check. STRING.
[ ] // returns:	  void
[ ] // notes:     Errors with URL and Image info for bad images found on any of the URLs in sURLLIst.
[+] VOID SG_FindBadImages (STRING sURLListInFile)
	[+] do
		[ ]
		[ ] HFILE hIn
		[ ] STRING sURL
		[ ] STRING 			sErrorBmp
		[ ] LIST OF WINDOW lwImages = {}
		[ ] WINDOW wImage
		[ ] INTEGER i = 0
		[ ]
		[ ] hIn = FileOpen (sURLListInFile, FM_READ)
		[ ]
		[+] while (FileReadLine (hIn, sURL))
			[ ] BrowserPage.SetActive ()
			[ ] Browser.LoadPage (sURL)
			[ ]
			[ ] lwImages = ReturnObjectsOfClassX (BrowserPage, HtmlImage)
			[+] for each wImage in lwImages
				[+] do
					[+] if (wImage.GetRect().xSize >= 46 && wImage.GetRect ().ySize >= 37)
						[ ] sErrorBmp = "badimage{CreateCurrentDTSString ()}.bmp"
						[ ] CopyOverwriteFile ("{PROJECT_HOME}\badimage.bmp", sErrorBmp)
						[ ] wImage.VerifyBitmap (sErrorBmp,{0, 0, 46, 37})
						[ ] LogError ("INVALID BITMAP >>>>>> URL: {sURL}  >>>>>>  IMAGE: {wImage}")
						[ ] Print ()
				[+] except
					[ ]
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_FindBadImages in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_FindBadImages in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  bFound = IE_FindOnPage (sFind)
[ ] // parameter: sFind: The string to search for. STRING.
[ ] // returns:	  bFound: TRUE if sFind is found on the current IE page, FALSE otherwise.
[ ] // notes:     Tests whether a string is present on the Internet Explorer page.
[+] BOOLEAN IE_FindOnPage (STRING sFind)
	[+] do
		[ ] Browser.SetActive()
		[ ] IE_Find.Invoke ()
		[ ] IE_Find.Find.SetText (sFind)
		[ ] IE_Find.FindNext.Click ()
		[ ]
		[+] if BrowserMessage.Exists (1)
			[ ] // for IE 6
			[+] if BrowserMessage.Message.GetText () == "Finished searching the document."
				[ ] BrowserMessage.OK.Click()
				[ ] IE_Find.Cancel.Click()
				[ ]
				[ ] ListAppend(laLogDetails, "Call to function: IE_FindOnPage in testcase: {GetTestCaseName()}	success")
				[ ] return (FALSE)
			[ ] // // for IE 7
			[+] if BrowserMessage.Message.GetText () == "Text not found."
				[ ] BrowserMessage.OK.Click()
				[ ] IE_Find.Cancel.Click()
				[ ]
				[ ] ListAppend(laLogDetails, "Call to function: IE_FindOnPage in testcase: {GetTestCaseName()}	success")
				[ ] return (FALSE)
			[ ]
			[+] else
				[ ] LogErrorSnapBmp ("***Error: IEFindOnPage- Unexpected browser message: {BrowserMessage.Message.GetText ()}")
				[ ] BrowserMessage.Close(TRUE, TRUE)
				[ ] IE_Find.Cancel.Click()
				[ ] // BrowserMessage.Accept ()
				[ ] // IE_Find.Dismiss ()
				[ ] return (FALSE)
		[+] else
			[ ] IE_Find.Cancel.Click()
			[ ]
			[ ] ListAppend(laLogDetails, "Call to function: IE_FindOnPage in testcase: {GetTestCaseName()}	success")
			[ ] return (TRUE)
		[ ]
		[ ]
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: IE_FindOnPage in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return FALSE
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_PrintPage ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Prints the current web page.
[+] explorer VOID SG_PrintPage ()
	[+] do
		[ ] Browser.SetActive()
		[ ] Browser.File.Print.Pick()
		[+] if(Print.Exists(10))
			[ ]
			[ ] // //For IE 6
			[+] // if (Print.PushButton("OK").Exists())
				[ ] // Print.PushButton("OK").Click()
				[ ] //
			[ ]
			[ ] //For both IE 6 and IE 7
			[+] if (Print.PushButton("Print|$1").Exists())
				[ ] Print.PushButton("Print|$1").Click()
				[ ]
			[ ]
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_PrintPage in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_PrintPage in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return
		[ ]
	[ ]
[+] firefox  VOID SG_PrintPage ()
	[+] do
		[ ] Browser.SetActive()
		[ ] Browser.File.Print.Pick()
		[ ] //For FF 2.0
		[+] if(FF_Print.Exists(10))
			[ ] FF_Print.SetActive()
			[+] withoptions
				[ ] BindAgentOption(OPT_SHOW_OUT_OF_VIEW, FALSE)
				[ ] BindAgentOption(OPT_SCROLL_INTO_VIEW, FALSE)
				[ ] FF_Print.OK.Click()
			[ ]
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_PrintPage in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_PrintPage in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ]
[ ] // function:  SG_NavigateLinks (lsLinks, [wStarting, laInvokeArgs])
[ ] // parameter: lsLinks: The list of link captions to click. LIST OF STRING.
[ ] // parameter: wStarting: Starting window for clicking links, will be invoked if does not exist (optional). WINDOW.
[ ] // parameter: laInvokeArgs: Arguments for invoking wStarting, if needed (optional). LIST OF ANYTYPE.
[ ] // returns:	  void
[ ] // notes:     Navigates web pages by clicking links specified in a list.
[+] VOID SG_NavigateLinks (LIST OF STRING lsLinks, WINDOW wStarting optional, LIST OF ANYTYPE laInvokeArgs optional)
	[+] do
		[ ]
		[ ] INTEGER			iCount
		[ ] LIST OF WINDOW	lwWindows
		[ ] LIST OF STRING	lsCaptions
		[ ] STRING 		  	sCaption, sLink
		[ ] STRING			sExtension = BrowserPage.GetExtension()
		[ ]
		[ ] // Set wStarting to BrowserPage if not supplied
		[+] if IsNull (wStarting)
			[ ] wStarting = BrowserPage
		[ ]
		[ ] // Set laInvokeArgs to empty list if not supplied
		[+] if IsNull (laInvokeArgs)
			[ ] laInvokeArgs = {}
		[ ]
		[ ] // start at the home page
		[+] if !wStarting.Exists ()
			[ ] wStarting.ArgListCall ("Invoke", laInvokeArgs)
		[ ]
		[ ] // Click each link in the list
		[+] for each sLink in lsLinks
			[ ] sLink = Trim(sLink)
			[ ] lwWindows = ReturnObjectsOfClassX (BrowserPage, HtmlLink, 3)
			[ ] lsCaptions = {}
			[ ]
			[+] for iCount = 1 to ListCount (lwWindows)
				[+] do
					[ ] sCaption = Trim(lwWindows[iCount].sFullCaption)
				[+] except
					[ ] ListAppend (lsCaptions, "")
					[ ] continue //added to skip links where sFullCaption is NULL and to avoid runtime error
				[ ] ListAppend (lsCaptions, sCaption)
				[+] if sCaption == sLink
					[+] if sExtension == "domex.dll"
						[ ] lwWindows[iCount].Click (1,2,2) //added to hit link
						[ ] Sleep (1)
					[+] else
						[ ] lwWindows[iCount].Click ()
						[+] do
							[ ] SG_TurnTablesOff (BrowserPage)
						[+] except
							[ ] ExceptLog ()
					[ ] break
			[+] if iCount == ListCount (lwWindows) && lsCaptions[iCount] != sLink
				[ ] LogError ("***Error: Could not find link with caption '{sLink}'")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_NavigateLinks in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_NavigateLinks in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_PageLoadTimes (sPage, iCount, bDetail)
[ ] // parameter: sPage: The URL of the web page to be timed. STRING
[ ] // parameter: iCount: Number of times to time the page in order to calculate the average. Default is 1 (optional). INTEGER
[ ] // parameter: bDetail: Whether or not to print out times for each iteration. Default is FALSE (optional). BOOLEAN
[ ] // returns:	  void
[ ] // notes: 	  Loads sPage iCount times and calculates the average page load time.
[+] VOID SG_PageLoadTimes (STRING sPage, INTEGER iCount optional, BOOLEAN bDetail optional)
	[+] do
		[ ]
		[ ] DATETIME 	dtTime1, dtTime2
		[ ] STRING 		sTime1, sTime2
		[ ] INTEGER 	iDiff, iHours, iMins, iSecs, iMicSecs
		[ ] INTEGER 	iLoop
		[ ] REAL 		rTotal = 0.0
		[ ] REAL 		rAvg
		[ ] REAL		rDiff
		[ ] BOOLEAN 	bPrintHeader = TRUE
		[ ]
		[+] if IsNull(bDetail)
			[ ] bDetail = FALSE
		[ ]
		[+] if IsNull(iCount)
			[ ] iCount = 1
		[ ]
		[+] if !Browser.Exists ()
			[ ] Browser.Invoke ()
		[ ]
		[ ] print ()
		[ ] print ("Page: ""{sPage}"" - {iCount} Iterations:")
		[ ]
		[+] for iLoop = 1 to iCount
			[ ] AnyWebPage.sURL = sPage
			[ ] Browser.LoadPage ("about:blank")
			[ ]
			[ ] dtTime1 = GetDateTime ()
			[ ] sTime1 = GetField([STRING]dtTime1, " ", 2)
			[ ]
			[ ] Browser.LoadPage (AnyWebPage.sURL)
			[ ]
			[ ] dtTime2 = GetDateTime ()
			[ ] sTime2 = GetField([STRING]dtTime2, " ", 2)
			[ ]
			[ ] iDiff = DiffDateTime (dtTime2, dtTime1, iHours, iMins, iSecs, iMicSecs)
			[ ] rDiff = ((iHours * 3600.0) + (iMins * 60.0) + (iSecs) + iMicSecs / 1000000.0)
			[ ]
			[ ] rTotal = rTotal + rDiff
			[ ]
			[+] if bDetail
				[+] if bPrintHeader
					[ ] print ("	Page Time Details:")
					[ ] bPrintHeader = FALSE
				[ ] print ("		Page Time {iLoop}: {rDiff}")
		[ ]
		[ ] rAvg = rTotal / iCount
		[ ]
		[ ] print ("	Average Page Time: {rAvg}")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_PageLoadTimes in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_PageLoadTimes in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_SaveAndVerifyPageSize (sPageName, sSavePath, sSizeCSVFile, sDetailCSVFile, [nMaxKB, iMaxObjects])
[ ] // parameter: sPageName: Name to use when saving the page files. STRING.
[ ] // parameter: sSavePath: Directory to use when saving the page files. STRING.
[ ] // parameter: sSizeCSVFile: Comma Separated Value file where lines are written containing page size information and verification results. STRING.
[ ] // parameter: sDetailCSVFile: CSV file to store detailed page information such as the size of each object. STRING.
[ ] // parameter: iMaxObjects: Threshold for maximum objects that should be on the page. Default is 30 (optional). INTEGER.
[ ] // parameter: nMaxKB: Threshold for maximum page size (KB). Default is 50 (optional). NUMBER.
[ ] // returns:	  void
[ ] // notes:     Saves the page size and number of objects on the current web page and verifies them against the specified maximums.
[ ] // notes:  	  This function will work for both IE and Firefox. Inside the function implementation is different for IE and Firefox.
[ ] // Example:   SaveAndVerifyPageSize ("HDFC", "D:\Amiya\Test", "PageSize1.csv", "PageSize2.csv")
[+] VOID SG_SaveAndVerifyPageSize (STRING sPageName, STRING sSavePath, STRING sSizeCSVFile, STRING sDetailCSVFile, NUMBER nMaxKB optional, INTEGER iMaxObjects optional)
	[+] do
		[ ]
		[ ] FILEINFO			fFile
		[ ] INTEGER				iTotal 				= 0
		[ ] LIST OF FILEINFO 	lfInfo
		[ ] LIST OF STRING		lsCSVIn 			= {}
		[ ] LIST OF STRING		lsDetailLines		= {}
		[ ] LIST OF STRING		lsSizeDetail
		[ ] REAL				rKb
		[ ] STRING				sExceededObjects	= ""
		[ ] STRING				sExceededSize 		= ""
		[ ] STRING				sFormatted			= ""
		[ ] STRING				sURL 				= ""
		[ ] STRING				sURLPage			= ""
		[ ] WEB_PAGE_SIZE 		wpsPage
		[ ]
		[ ] Browser.SetActive()
		[ ] sURL 		= Browser.Location.GetText ()
		[ ] sURLPage	= GetFieldReverse (sURL, "/", 1)
		[ ]
		[ ] Print ("URL: {sURL}")
		[ ] // strip commas from the sURLPage to maintain the CSV format
		[ ] sURLPage = StrTran (sURLPage, ',', '%44')
		[ ]
		[ ] // if the trailing slash was not supplied on the destination path, add it
		[+] if SubStr (sSavePath, Len (sSavePath), 1) != "\"
			[ ] sSavePath = sSavePath + "\"
		[ ]
		[ ] // Get the lines in the existing CSV file
		[+] do
			[ ] ListRead (lsCSVIn, "{sSavePath}\{sSizeCSVFile}")
		[+] except
			[ ] // do nothing
		[ ]
		[ ] // nMaxKB defaults to 50
		[+] if IsNull (nMaxKB)
			[ ] nMaxKB = 50
		[ ]
		[ ] // iMaxObjects defaults to 30
		[+] if IsNull (iMaxObjects)
			[ ] iMaxObjects = 30
		[ ]
		[ ] // if no lines in the file, add the title line
		[+] if lsCSVIn == {}
			[ ] lsCSVIn = {"Size (KB),> {nMaxKB} KB,Objects,> {iMaxObjects},URL"}
		[ ]
		[ ] // Get the lines in the existing Detail CSV file
		[+] do
			[ ] ListRead (lsDetailLines, "{sSavePath}\{sDetailCSVFile}")
		[+] except
			[ ] // do nothing
		[ ]
		[ ] // if no lines in the detail file, add the title line
		[+] if lsDetailLines == {}
			[ ] lsDetailLines = {"Page, Object, Size"}
		[ ]
		[ ] // Save the page to the specified directory
		[ ] // SaveWebPageDialog.Invoke()
		[ ] Sleep(1)
		[ ] SaveWebPageDialog.SaveWebComplete (sPageName, sSavePath)
		[ ]
		[ ] // Save the page source
		[+] if(Browser.Exists(1))
			[ ] Browser.SetActive ()
		[ ] Sleep (1)
		[+] if MSNotepad.Exists ()
			[ ] MSNotepad.Exit ()
		[ ] Browser.View.Source.Pick ()
		[ ]
		[+] explorer if NotepadCannotFindFile.Exists (2)
			[ ] LogWarning ("***Warning: View Source - {NotepadCannotFindFile.Message.GetText()} - URL '{sURL}'")
			[ ] MessBox.No.Click ()
			[ ] MSNotepad.Exit ()
			[ ] Sleep (2)
			[ ] Browser.View.Source.Pick ()
		[ ]
		[+] explorer if MSNotepad.Exists (2)
			[ ] MSNotepad.SetActive ()
			[ ] MSNotepad.FileWrite (sPageName, sSavePath, TRUE)
			[ ] MSNotepad.Close ()
		[+] else
			[ ] Browser.Reload.Click ()
			[ ] Browser.View.Source.Pick ()
			[+] if MSNotepad.Exists (2)
				[ ] MSNotepad.SetActive ()
				[ ] MSNotepad.FileWrite (sPageName, sSavePath, TRUE)
				[ ] MSNotepad.Close ()
			[+] else
				[ ] LogError ("***Error: No source available for page '{sURL}'")
				[ ] SYS_CopyFile(sSavePath + sPageName + ".htm", sSavePath + sPageName + ".txt")
		[ ]
		[+] firefox if FF_SourcePage.Exists(2)
			[ ] FF_SourcePage.SetActive()
			[ ] FF_SourcePage.TypeKeys("<Ctrl-s>")
			[ ] FF_SavePageAs.FileName.Typekeys (sSavePath + sPageName)
			[ ] FF_SavePageAs.Save.Click()
			[ ] Sleep (0.5)
			[+] if SaveAsOverwrite.Exists(2)
				[ ] SaveAs.SetActive ()
				[ ] SaveAs.Yes.Click ()
			[ ]
			[ ]
			[ ] // Closing the Downloads dialog page of Firefox
			[+] if FF_Downloads.Exists(2)
				[ ] FF_Downloads.Close(TRUE)
			[ ] FF_SourcePage.Close(TRUE)
			[ ]
		[+] else
			[ ] Browser.Reload.Click ()
			[ ] Browser.View.Source.Pick ()
			[+] if FF_SourcePage.Exists(2)
				[ ] FF_SourcePage.SetActive()
				[ ] FF_SourcePage.TypeKeys("<Ctrl-s>")
				[ ] FF_SavePageAs.FileName.Typekeys (sSavePath + sPageName)
				[ ] FF_SavePageAs.Save.Click()
				[ ] Sleep (0.5)
				[+] if SaveAsOverwrite.Exists(2)
					[ ] SaveAs.SetActive ()
					[ ] SaveAs.Yes.Click ()
				[ ]
				[ ]
				[ ] // Closing the Downloads dialog page of Firefox
				[+] if FF_Downloads.Exists(2)
					[ ] FF_Downloads.Close(TRUE)
				[ ] FF_SourcePage.Close(TRUE)
				[ ]
			[+] else
				[ ] LogError ("***Error: No source available for page '{sURL}'")
				[ ] SYS_CopyFile(sSavePath + sPageName + ".htm", sSavePath + sPageName + ".txt")
		[ ]
		[ ] // delete  the htm file
		[ ] DeleteFile (sSavePath + sPageName + ".htm")
		[ ]
		[ ] // Get the size and convert to KB
		[ ] lfInfo = SYS_GetDirContents (sSavePath)
		[ ]
		[ ] // find the file sPageName.txt and start with its size
		[+] for each fFile in lfInfo
			[+] if fFile.sName == sPageName + ".txt"
				[ ] iTotal = fFile.iSize
				[ ] ListAppend (lsDetailLines, "{sURLPage},.txt file (View Source),{iTotal}")
				[ ] break
		[ ]
		[ ] // get a list of the child objects from the page
		[+] do
			[ ] lfInfo = SYS_GetDirContents (sSavePath + sPageName + "_files")
		[+] except
			[ ] lfInfo = {}
		[ ]
		[ ] // add the size of each object to the page total
		[+] for each fFile in lfInfo
			[ ] iTotal = iTotal + fFile.iSize
			[ ] ListAppend (lsDetailLines, "{sURLPage},{fFile.sName},{fFile.iSize}")
		[ ]
		[ ] wpsPage.iPageSize 	= iTotal					// page size
		[ ] rKb					= iTotal
		[ ] wpsPage.nKB 		= rKb / 1024				// converted to KB
		[ ] wpsPage.iNumObjects	= ListCount (lfInfo) + 1	// number of page objects
		[ ]
		[ ] // Set flag if page size exceeded
		[+] if wpsPage.nKB > nMaxKB
			[ ] sExceededSize = "Yes"
		[ ]
		[ ] // Set flag if number of page objects exceeded
		[+] if wpsPage.iNumObjects > iMaxObjects
			[ ] sExceededObjects = "Yes"
		[ ]
		[ ] // strip commas from the URL to maintain the CSV format
		[ ] sURL = StrTran (sURL, ',', '%44')
		[ ]
		[ ] sFormatted = FormatPrecision ([STRING]wpsPage.nKB, 1)
		[ ]
		[ ] // now append the current page data
		[ ] ListAppend (lsCSVIn, "{sFormatted},{sExceededSize},{wpsPage.iNumObjects},{sExceededObjects},{sURL}")
		[ ]
		[ ] // and write to the file
		[ ] ListWrite (lsCSVIn, "{sSavePath}\{sSizeCSVFile}")
		[ ]
		[ ] // write to the detail file
		[ ] ListWrite (lsDetailLines, "{sSavePath}\{sDetailCSVFile}")
		[ ]
		[ ] // //delete the folder and the htm file
		[ ] DeleteFile (sSavePath + sPageName + ".txt")
		[ ] DeleteDir (sSavePath + sPageName + "_files")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_SaveAndVerifyPageSize in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_SaveAndVerifyPageSize in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog()
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //									HTML TABLE RELATED FUNCTIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // function:  SG_SetHtmlTableRecognition (NUMBER nStrength)
[ ] // parameter: nStrength: The strength from 0 to 1. NUMBER.
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Turns on recognition of tables and sets strength in DOM browser extensions.
[+] VOID SG_SetHtmlTableRecognition (NUMBER nStrength)
	[+] do
		[ ]
		[ ] BrowserPage.SetUserOption ("ShowHtmlTable",TRUE,USEROPT_DEFAULT)
		[ ] BrowserPage.SetUserOption ("ShowBorderlessTables",nStrength,USEROPT_DEFAULT)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_SetHtmlTableRecognition in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_SetHtmlTableRecognition in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_TurnHtmlTablesOff ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Turns off recognition of tables in DOM browser extensions.
[+] VOID SG_TurnHtmlTablesOff ()
	[+] do
		[ ]
		[ ] BrowserPage.SetUserOption ("ShowHtmlTable",FALSE,USEROPT_DEFAULT)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_TurnHtmlTablesOff in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_TurnHtmlTablesOff in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_TurnHtmlTablesOn ()
[ ] // parameter: none
[ ] // returns:	  void
[ ] // notes:     Turns on recognition of tables in DOM browser extensions.
[+] VOID SG_TurnHtmlTablesOn ()
	[+] do
		[ ]
		[ ] BrowserPage.SetUserOption ("ShowHtmlTable",TRUE,USEROPT_DEFAULT)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_TurnHtmlTablesOn in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_TurnHtmlTablesOn in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_TurnTablesOff (wWindow)
[ ] // parameter: wWindow: Window to address the turn off command to. WINDOW.
[ ] // returns:	  void
[ ] // notes:     Turns off recognition of tables in Virtual Objects browser extensions.
[+] VOID SG_TurnTablesOff (WINDOW wWindow)
	[+] do
		[ ] wWindow.SetUserOption ("GroupTables",FALSE,USEROPT_DEFAULT)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_TurnTablesOff in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_TurnTablesOff in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
		[ ]
	[ ]
[ ]
[ ]
[ ] // function:  SG_TurnTablesOn (wWindow)
[ ] // parameter: wWindow: Window to address the turn on command to. WINDOW.
[ ] // returns:	  void
[ ] // notes:     Turns on recognition of tables in Virtual Objects browser extensions.
[+] VOID SG_TurnTablesOn (WINDOW wWindow)
	[+] do
		[ ] wWindow.SetUserOption ("GroupTables",TRUE,USEROPT_DEFAULT)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SG_TurnTablesOn in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SG_TurnTablesOn in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
		[ ]
[ ]
[ ]
