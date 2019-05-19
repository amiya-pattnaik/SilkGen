[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_BrowserDecl.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Internet Explorer, FireFox related declarations are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak 
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		09/15/09	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //									INTERNET EXPLORER RELATED DECLARATIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // Used for getting size and number of objects on web pages
[+] window DialogBox SaveWebPageDialog
	[ ] //tag "Save Web Page"
	[+] multitag "Save Webpage"
		[ ] "#1"
	[ ] parent Browser
	[ ]
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] Cancel.Click ()
		[ ] return
	[ ]
	[+] explorer Invoke ()
		[ ] Browser.SetActive ()
		[ ] Browser.File.SaveAs.Pick()
		[ ]
		[ ] return
	[+] firefox  Invoke ()
		[ ] Browser.SetActive ()
		[ ] Firefox.File.SavePageAs.Pick()
		[ ]
		[ ] //Browser.File.SaveAs.Pick()
		[ ]
		[ ] return
	[ ]
	[+] VOID SaveWebComplete (STRING sPageName, STRING sSavePath, INTEGER iTimeout optional)
		[ ] // Invoke this dialog if necessary
		[+] if !Exists ()
			[ ] Invoke ()
		[ ]
		[ ] // if the trailing slash was not supplied on the destination path, add it
		[+] if SubStr (sSavePath, Len (sSavePath), 1) != "\"
			[ ] sSavePath = sSavePath + "\"
		[ ]
		[ ] // Give the timeout a default of 300 sec - this is how long to wait for the save to occur
		[+] if IsNull (iTimeout)
			[ ] iTimeout = 300
		[ ]
		[ ] explorer this.SetActive()
		[ ] explorer this.FileName.Typekeys (sSavePath + sPageName)
		[ ] firefox FF_SavePageAs.FileName.Typekeys (sSavePath + sPageName)
		[+] do
			[ ] explorer this.SetActive ()
			[ ] //SaveAsType.Select ("Web Page, complete (*.htm;*.html)")
			[ ] explorer this.SaveAsType.Select ("Webpage, complete (*.htm;*.html)")
			[ ]
			[ ] firefox FF_SavePageAs.SetActive()
			[ ] firefox FF_SavePageAs.SaveAsType1.Select ("Web Page, complete")
			[ ]
		[+] except
			[ ] // do nothing
		[ ]
		[ ] // Saving the file
		[ ] explorer Save.Click ()
		[ ] firefox FF_SavePageAs.Save.Click()
		[ ] Sleep (0.5)
		[ ]
		[ ] // Closing the Downloads dialog page of Firefox
		[+] firefox if FF_Downloads.Exists(1)
			[ ] FF_Downloads.Close(TRUE)
		[ ]
		[+] explorer if SavingWebPageDialog.Exists ()
			[ ] WaitForWindowGone (SavingWebPageDialog, iTimeout)
		[+] firefox if FF_SavePageAs.Exists()
			[ ] WaitForWindowGone (SavingWebPageDialog, iTimeout)
			[ ]
		[ ]
		[+] explorer if !Explorer.Exists ()
			[ ] Explorer.Invoke ()
		[+] firefox if !Firefox.Exists ()
			[ ] Firefox.Invoke ()
		[ ]
		[ ] return
	[ ]
	[+] StaticText SaveInText
		[+] multitag "Save in:"
			[ ] "$1091"
	[+] PopupList SaveIn3
		[+] multitag "Save in:"
			[ ] "$1137"
	[+] ListView SaveIn4
		[+] multitag "Save in:"
			[ ] "$1"
	[+] StaticText FileNameText
		[+] multitag "File name:"
			[ ] "$1090"
	[ ]
	[+] TextField FileName
		[+] multitag "[TextField]File name:"
			[ ] "[ComboBox]File name:"
		[+] // multitag "File name:"
			[ ] // "^File name:"
	[ ]
	[+] StaticText SaveAsTypeText
		[+] multitag "Save as type:"
			[ ] "$1089"
	[+] PopupList SaveAsType
		[+] multitag "Save as type:"
			[ ] "$1136"
	[+] PushButton Save
		[+] multitag "Save"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
	[+] PushButton SaveIn1
		[+] multitag "Save in:[1]"
			[ ] "$40961"
	[+] PushButton SaveIn2
		[+] multitag "Save in:[2]"
			[ ] "$40962"
	[+] RadioList SaveIn5
		[+] multitag "Save in:"
			[ ] "$40963"
	[+] DialogBox DialogBox1
		[ ] tag "$0"
		[+] StaticText EncodingText
			[+] multitag "Encoding:"
				[ ] "$65535"
		[+] PopupList Encoding
			[+] multitag "Encoding:"
				[ ] "$13146"
		[+] CustomWin NativeFontCtl1
			[ ] msw tag "[NativeFontCtl]$65535"
[+] window DialogBox SavingWebPageDialog
	[ ] tag "Save Web Page/[StaticText]*complete./.."
	[ ] parent Browser
	[+] CustomWin SysAnimate321
		[ ] msw tag "[SysAnimate32]#1"
	[+] StaticText StaticText1
		[ ] tag "#1"
	[+] CustomWin Msctls_progress321
		[ ] msw tag "[msctls_progress32]#1"
	[+] StaticText CompleteText
		[ ] tag "*complete."
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] CustomWin NativeFontCtl1
		[ ] msw tag "[NativeFontCtl]#1"
[ ]
[ ]
[ ] // Browser Dialogs
[+] window BrowserChild PageNotFound
	[ ] tag "The page cannot be found"
	[ ] parent Browser
[+] window BrowserChild HTTP400BadRequest
	[ ] tag "HTTP 400 - Bad Request"
	[ ] parent Browser
[+] window BrowserChild HTTP403Forbidden
	[+] multitag "HTTP 403 (Forbidden)"
		[ ] "403 Forbidden"
	[ ] parent Browser
[+] window BrowserChild HTTP500InternalServerError
	[ ] tag "HTTP 500 Internal server error"
	[ ] parent Browser
[+] window BrowserChild PageLoad
	[ ] parent Browser
	[ ]
	[ ] STRING sURL
	[+] VOID OnLoadPage (STRING sLocation, STRING sUser null, STRING sPassword null)
		[ ] return
[+] window BrowserChild AnyWebPage
	[ ] STRING sURL
	[ ]
	[+] VOID OnLoadPage ()
		[ ] return
[ ]
[+] // window DialogBox 	Print
	[ ] // tag "Print[1]"
	[ ] // parent Browser
	[ ] //
	[ ] // ////////////////
	[ ] // Declarations //
	[ ] // ////////////////
	[+] // CheckBox Collate
		[+] // multitag "Collate"
			[ ] // "^Copies"
			[ ] // "#2"
			[ ] // "$1041"
			[ ] // "@(387,217)"
	[+] // CheckBox PrintAllLinkedDocuments
		[+] // multitag "Print all linked documents"
			[ ] // "^Print frames[1]"
			[ ] // "#3"
			[ ] // "$8140"
			[ ] // "@(105,360)"
	[+] // CheckBox PrintTableOfLinks
		[+] // multitag "Print table of links"
			[ ] // "^Print frames[2]"
			[ ] // "#4"
			[ ] // "$8142"
			[ ] // "@(312,360)"
	[+] // CheckBox PrintToFile
		[+] // multitag "Print to file"
			[ ] // "^\\Fraprnt2\e2b5si1"
			[ ] // "#1"
			[ ] // "$1040"
			[ ] // "@(366,120)"
	[+] // CustomWin Copies1
		[+] // msw multitag "[Icon]Copies"
			[ ] // "[Icon]^Copies"
			[ ] // "[Icon]#1"
			[ ] // "[Icon]$1086"
			[ ] // "[Icon]@(300,221)"
	[+] // CustomWin NativeFontCtl1
		[+] // msw multitag "[NativeFontCtl]#1"
			[ ] // "[NativeFontCtl]$65535"
			[ ] // "[NativeFontCtl]@(0,0)"
	[+] // CustomWin PrintFrames2
		[+] // msw multitag "[BitMap]Print frames"
			[ ] // "[BitMap]^Print frames"
			[ ] // "[BitMap]#1"
			[ ] // "[BitMap]$8141"
			[ ] // "[BitMap]@(94,301)"
	[+] // RadioList PrintRange
		[+] // multitag "Print range"
			[ ] // "^Print range"
			[ ] // "#1"
			[ ] // "$1056"
			[ ] // "@(72,201)"
	[+] // PopupList Name
		[+] // multitag "Name:"
			[ ] // "^Name:"
			[ ] // "#1"
			[ ] // "$1139"
			[ ] // "@(192,39)"
	[+] // PushButton Cancel
		[ ] // tag "Cancel"
	[+] // PushButton OK
		[+] // multitag "OK"
			[ ] // "^Print frames[1]"
			[ ] // "#2"
			[ ] // "$1"
			[ ] // "@(308,391)"
	[+] // PushButton Properties
		[+] // multitag "Properties"
			[ ] // "^Printer"
			[ ] // "#1"
			[ ] // "$1025"
			[ ] // "@(363,39)"
	[+] // RadioList PrintFrames1
		[+] // multitag "Print frames"
			[ ] // "^Print frames"
			[ ] // "#2"
			[ ] // "$1059"
			[ ] // "@(301,299)"
	[+] // StaticText CommentText
		[+] // multitag "Comment:"
			[ ] // "^Where:[2]"
			[ ] // "#9"
			[ ] // "$1096"
			[ ] // "@(51,125)"
	[+] // StaticText CopiesText
		[+] // multitag "Copies"
			[ ] // "^Printer[4]"
			[ ] // "#12"
			[ ] // "$1073"
			[ ] // "@(330,197)"
	[+] // StaticText CubeE2251BText
		[+] // multitag "Cube E2251B"
			[ ] // "^Comment:"
			[ ] // "#10"
			[ ] // "$1100"
			[ ] // "@(192,125)"
	[+] // StaticText DefaultPrinterReadyText
		[+] // multitag "Default printer; Ready"
			[ ] // "^Status:[1]"
			[ ] // "#4"
			[ ] // "$1099"
			[ ] // "@(246,67)"
	[+] // StaticText Fraprnt2E2b5si1Text
		[+] // multitag "\\Fraprnt2\e2b5si1"
			[ ] // "^Where:[1]"
			[ ] // "#8"
			[ ] // "$1101"
			[ ] // "@(246,106)"
	[+] // StaticText HPLaserJet5SiText
		[+] // multitag "HP LaserJet 5Si"
			[ ] // "^Type:[1]"
			[ ] // "#6"
			[ ] // "$1098"
			[ ] // "@(246,86)"
	[+] // StaticText FromText
		[+] // multitag "from:"
			[ ] // "^Print range[1]"
			[ ] // "#14"
			[ ] // "$1089"
			[ ] // "@(92,198)"
	[+] // StaticText NameText
		[+] // multitag "Name:"
			[ ] // "^Printer[1]"
			[ ] // "#2"
			[ ] // "$1093"
			[ ] // "@(51,39)"
	[+] // StaticText NumberOfCopiesText
		[+] // multitag "Number of copies:"
			[ ] // "^Copies"
			[ ] // "#13"
			[ ] // "$1092"
			[ ] // "@(303,182)"
	[+] // StaticText PrintRangeText
		[+] // multitag "Print range"
			[ ] // "^Printer[3]"
			[ ] // "#11"
			[ ] // "$1072"
			[ ] // "@(120,197)"
	[+] // StaticText PrintFramesText
		[+] // multitag "Print frames"
			[ ] // "^Print range[3]"
			[ ] // "#16"
			[ ] // "$65535"
			[ ] // "@(216,297)"
	[+] // StaticText PrinterText
		[+] // multitag "Printer"
			[ ] // "#1"
			[ ] // "$1075"
			[ ] // "@(216,75)"
	[+] // StaticText StatusText
		[+] // multitag "Status:"
			[ ] // "^Printer[2]"
			[ ] // "#3"
			[ ] // "$1095"
			[ ] // "@(51,67)"
	[+] // StaticText ToText
		[+] // multitag "to:"
			[ ] // "^Print range[2]"
			[ ] // "#15"
			[ ] // "$1090"
			[ ] // "@(161,198)"
	[+] // StaticText TypeText
		[+] // multitag "Type:"
			[ ] // "^Status:[2]"
			[ ] // "#5"
			[ ] // "$1094"
			[ ] // "@(51,86)"
	[+] // StaticText WhereText
		[+] // multitag "Where:"
			[ ] // "^Type:[2]"
			[ ] // "#7"
			[ ] // "$1097"
			[ ] // "@(51,106)"
	[+] // TextField From
		[+] // multitag "from:"
			[ ] // "^from:"
			[ ] // "#2"
			[ ] // "$1152"
			[ ] // "@(129,197)"
	[+] // TextField To
		[+] // multitag "to:"
			[ ] // "^to:"
			[ ] // "#3"
			[ ] // "$1153"
			[ ] // "@(195,197)"
	[+] // TextField NumberOfCopies
		[+] // multitag "Number of copies:"
			[ ] // "^Number of copies:"
			[ ] // "#1"
			[ ] // "$1154"
			[ ] // "@(376,182)"
	[+] // UpDown Copies2
		[+] // multitag "Copies"
			[ ] // "^Copies"
			[ ] // "#1"
			[ ] // "$9999"
			[ ] // "@(399,182)"
	[ ] //
[+] window DialogBox 	FileDownload
	[ ] tag "File Download"
	[ ] parent FileDownloadMain
	[ ]
	[+] CheckBox AlwaysAskBeforeOpeningThis
		[ ] tag "Always ask before opening this type of file"
	[+] PushButton OK
		[ ] tag "OK"
	[+] PushButton Open
		[ ] tag "Open"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] PushButton MoreInfo
		[ ] tag "More Info"
	[+] RadioList WhatWouldYouLikeToDoWith3
		[ ] tag "What would you like to do with this file?"
	[ ]
	[+] StaticText WhatWouldYouLikeToDoWith1
		[ ] tag "What would you like to do with this file?"
	[+] StaticText YouHaveChosenToDownloadA
		[ ] tag "You have chosen to download a file from this location."
	[ ]
	[+] CustomWin BitMap1
		[ ] msw tag "[BitMap]#1"
	[+] CustomWin WhatWouldYouLikeToDoWith2
		[ ] msw tag "[EtchedHorz]What would you like to do with this file?"
[+] window DialogBox 	FileDownloadMain
	[ ] tag "File Download"
[+] // window DialogBox 	TemporaryInternetFiles
	[+] // multitag "*\Temporary Internet Files"
		[ ] // "*\Temp Files"
		[ ] // "Temporary Internet Files"
		[ ] // "Temp Files"
	[ ] //
	[+] // VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] // // close the dialog box
		[+] // while exists (2)
			[ ] // SetActive ()
			[ ] // TypeKeys ("<Alt-F4>")
		[ ] //
		[ ] // // then close the Internet Options dialogs
		[ ] // // IE_CacheSettings.OK.Click ()		//Amiya
		[ ] // IE_Options.OK.Click ()
		[ ] //
		[ ] // return
	[+] // VOID Invoke ()
		[ ] // // Make sure browser is open
		[+] // if Browser.Exists ()
			[ ] // Browser.SetActive ()
		[+] // else
			[ ] // Browser.Invoke ()
		[ ] //
		[ ] // // Invoke the options dialog
		[ ] // Browser.TypeKeys("<Alt-T>o")
		[ ] //
		[ ] // // View files
		[ ] // // IE_Options.General.Settings.Click ()		//Amiya
		[ ] // // IE_CacheSettings.ViewFiles.Click ()		//Amiya
		[ ] //
		[ ] // return
	[+] // VOID SaveTempFiles (STRING sSavePath)
		[ ] // // invoke the dialog or set it active
		[+] // if !Exists (3)
			[ ] // Invoke ()
		[+] // else
			[ ] // SetActive ()
		[ ] //
		[ ] // // select all files
		[ ] // TypeKeys("<Ctrl-a>")
		[ ] //
		[ ] // // copy to clipboard
		[ ] // TypeKeys("<Ctrl-c>")
		[ ] //
		[ ] // // type the save location
		[ ] //
		[ ] // Address.SetText (sSavePath)
		[ ] // Address.TypeKeys ("<Enter>")
		[ ] //
		[ ] // // click in the files area
		[+] // do
			[ ] // ClickCenter (TemporaryInternetFiles)
		[+] // except
			[ ] // TemporaryInternetFiles.FileTree.Files1.Files2.FilesListView.Click ()
		[ ] //
		[ ] // // paste from clipboard
		[ ] // TypeKeys("<Ctrl-v>")
		[ ] //
		[ ] // // deal with any confirmation dialogs
		[+] // while MessBox.No.Exists (2)
			[ ] // MessBox.No.Click ()
		[ ] //
		[ ] // Sleep (1)
		[ ] //
		[ ] // return
	[ ] //
	[+] // ComboBox Address
		[ ] // tag "#1"
	[+] // PushButton Back
		[ ] // tag "Back"
	[+] // PushButton Forward
		[ ] // tag "Forward"
	[+] // PushButton Up
		[ ] // tag "Up"
	[+] // PushButton MapDrive
		[ ] // tag "Map Drive"
	[+] // PushButton Disconnect
		[ ] // tag "Disconnect"
	[+] // PushButton Search
		[ ] // tag "Search"
	[+] // PushButton Folders
		[ ] // tag "Folders"
	[+] // PushButton Views
		[ ] // tag "Views"
	[+] // PushButton File
		[ ] // tag "File"
	[+] // PushButton Edit
		[ ] // tag "Edit"
	[+] // PushButton View
		[ ] // tag "View"
	[+] // PushButton Favorites
		[ ] // tag "Favorites"
	[+] // PushButton Tools
		[ ] // tag "Tools"
	[+] // PushButton Help
		[ ] // tag "Help"
	[+] // CustomWin FileTree
		[ ] // msw tag "[DUIViewWndClassName]$0"
		[+] // CustomWin Files1
			[ ] // msw tag "[DirectUIHWND]$0"
			[+] // CustomWin Files2
				[ ] // msw tag "[CtrlNotifySink]$0"
				[+] // ListView FilesListView
					[ ] // tag "$1"
					[+] // Header Header1
						[ ] // tag "$0"
						[+] // PushButton Name
							[ ] // tag "Name"
						[+] // PushButton InternetAddress
							[ ] // tag "Internet Address"
						[+] // PushButton Type
							[ ] // tag "Type"
						[+] // PushButton Size
							[ ] // tag "Size"
						[+] // PushButton Expires
							[ ] // tag "Expires"
						[+] // PushButton LastModified
							[ ] // tag "Last Modified"
						[+] // PushButton LastAccessed
							[ ] // tag "Last Accessed"
						[+] // PushButton LastChecked
							[ ] // tag "Last Checked"
[ ]
[ ] //----------------------------------------------------------------------------------------//
[ ] //									FIREFOX RELATED DECLARATIONS
[ ] //----------------------------------------------------------------------------------------//
[+] window FF_XulTemplateDlg FF_Print
	[ ] tag "#1"
	[ ] parent Browser
	[ ] const wInvoke = Firefox.File.Print
	[ ] const wDismissButton = Cancel
	[ ]
	[ ]
	[+] CheckBox 	PrintToFile
		[+] multitag "Print to file"
			[ ] "$1040"
	[+] RadioList 	PrintRange
		[+] multitag "Print range"
			[ ] "$1056"
	[ ]
	[+] StaticText 	PrintRangeText
		[+] multitag "Print range"
			[ ] "$1072"
	[+] StaticText 	FromText
		[+] multitag "from:"
			[ ] "$1089"
	[+] StaticText 	ToText
		[+] multitag "to:"
			[ ] "$1090"
	[+] StaticText 	CopiesText
		[+] multitag "Copies"
			[ ] "$1073"
	[+] StaticText 	NumberOfCopiesText
		[+] multitag "Number of copies:"
			[ ] "$1092"
	[ ]
	[+] TextField 	From
		[+] multitag "from:"
			[ ] "$1152"
	[+] TextField 	To
		[+] multitag "to:"
			[ ] "$1153"
	[+] TextField 	NumberOfCopies
		[+] multitag "Number of copies:"
			[ ] "$1154"
	[ ]
	[+] PushButton OK
		[+] multitag "OK|$1"
			[ ] "^Print Frames"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
[+] window FF_XulTemplateDlg FF_Options
	[+] multitag "Options"
		[ ] "$"
	[ ] parent Browser
	[ ]
	[+] XulTextField HistoryDays
		[+] multitag "historyDays"
			[ ] "$xul_textbox"
			[ ] "&id='historyDays';name='historyBox'"
	[ ]
	[+] XulCheckBox RememberVisitedPagesForThe
		[+] multitag "Remember visited pages for the last"
			[ ] "$rememberHistoryDays"
			[ ] "&id='rememberHistoryDays';name='Remember visited pages for the last'"
	[+] XulCheckBox RememberWhatIEnterInForms
		[+] multitag "Remember what I enter in forms and the search bar"
			[ ] "$rememberForms"
			[ ] "&id='rememberForms';name='Remember what I enter in forms and the search bar'"
	[+] XulCheckBox RememberWhatIVeDownloaded
		[+] multitag "Remember what I've downloaded"
			[ ] "$rememberDownloads"
			[ ] "&id='rememberDownloads';name='Remember what I've downloaded'"
	[+] XulCheckBox AcceptCookiesFromSites
		[+] multitag "Accept cookies from sites"
			[ ] "$acceptCookies"
			[ ] "&id='acceptCookies';name='Accept cookies from sites'"
	[ ]
	[+] XulText EepUntil
		[+] multitag "eep until:"
			[ ] "$xul_label[1]"
			[ ] "&id='keepUntil'"
	[ ]
	[+] XulPopupList KeepCookiesUntil
		[+] multitag "keepCookiesUntil"
			[ ] "$xul_menulist"
			[ ] "&id='keepCookiesUntil';name='they expire'"
	[ ]
	[+] MenuItem TheyExpire
		[+] multitag "they expire"
			[ ] "&id='they expire';name='they expire'"
	[+] MenuItem ICloseFirefox
		[+] multitag "I close Firefox"
			[ ] "&id='I close Firefox';name='I close Firefox'"
	[+] MenuItem AskMeEveryTime
		[+] multitag "ask me every time"
			[ ] "&id='ask me every time';name='ask me every time'"
	[ ]
	[+] XulCheckBox AlwaysClearMyPrivateDataW
		[+] multitag "Always clear my private data when I close Firefox"
			[ ] "$alwaysClear"
			[ ] "&id='alwaysClear';name='Always clear my private data when I close Firefox'"
	[+] XulCheckBox AskMeBeforeClearingPrivate
		[+] multitag "Ask me before clearing private data"
			[ ] "$askBeforeClear"
			[ ] "&id='askBeforeClear';name='Ask me before clearing private data'"
	[+] XulRadioList XulRadioList1
		[ ] tag "&id='Main';name='Main'"
	[ ]
	[+] XulPushButton Exceptions
		[+] multitag "Exceptions"
			[ ] "$cookieExceptions"
			[ ] "&id='cookieExceptions';name='Exceptions...'"
	[+] XulPushButton ClearNow
		[+] multitag "Clear Now"
			[ ] "$clearDataNow"
			[ ] "&id='clearDataNow';name='Clear Now...'"
	[+] XulPushButton Settings
		[+] multitag "Settings"
			[ ] "$clearDataSettings"
			[ ] "&id='clearDataSettings';name='Settings...'"
	[+] XulPushButton ShowCookies
		[+] multitag "Show Cookies"
			[ ] "$showCookiesButton"
			[ ] "&id='showCookiesButton';name='Show Cookies...'"
	[+] XulPushButton XulPushButton1
		[ ] tag "#1"
	[+] XulPushButton OK
		[+] multitag "OK"
			[ ] "&id='OK';name='OK'"
	[+] XulPushButton XulPushButton3
		[ ] tag "#3"
	[+] XulPushButton Cancel
		[+] multitag "Cancel"
			[ ] "&id='Cancel';name='Cancel'"
	[+] XulPushButton Help
		[+] multitag "Help"
			[ ] "&id='Help';name='Help'"
	[+] XulPushButton MoreInfo
		[+] multitag "More Info"
			[ ] "&id='More Info';name='More Info'"
[+] window FF_XulTemplateDlg SaveAsOverwrite
	[+] multitag "Save As"
		[ ] "$firefox2_0"
		[ ] "#1"
	[ ] parent FF_SourcePage
	[ ]
[+] window FF_XulTemplateDlg SaveAs
	[+] multitag "Save As"
		[ ] "$firefox2_0"
	[ ] parent SaveAsOverwrite
	[+] PushButton Yes
		[+] multitag "Yes"
			[ ] "$6"
[+] window MainWin FF_Cookies
	[+] multitag "Cookies"
		[ ] "$firefox2_0[1]"
	[+] PushButton CloseButton
		[+] multitag "$close-button"
			[ ] "&id='close-button'"
	[ ]
[+] window MainWin FF_RestorePrevSession
	[+] multitag "Firefox*"
		[ ] "*Restore Previous Session"
		[ ] "$firefox2_0"
		[ ]
[+] window MainWin FF_Downloads
	[+] multitag "Downloads"
		[ ] "$firefox2_0[1]"
[+] window MainWin FF_SourcePage
	[+] multitag "Source of: http:*"
		[ ] "*Mozilla Firefox"
		[ ] "$firefox2_0[1]"
	[+] Menu File
		[+] multitag "File"
			[ ] "$file-menu"
			[ ] "&id='file-menu';name='File'"
		[+] MenuItem SavePageAs
			[+] multitag "Save Page As"
				[ ] "&id='Save Page As...';name='Save Page As...'"
		[+] MenuItem PageSetup
			[+] multitag "Page Setup"
				[ ] "&id='Page Setup...';name='Page Setup...'"
		[+] MenuItem PrintPreview
			[+] multitag "Print Preview"
				[ ] "&id='Print Preview';name='Print Preview'"
		[+] MenuItem Print
			[+] multitag "Print"
				[ ] "&id='Print...';name='Print...'"
		[+] MenuItem Close
			[+] multitag "Close"
				[ ] "$menu_close"
				[ ] "&id='menu_close';name='Close'"
		[+] MenuItem Exit
			[+] multitag "Exit"
				[ ] "$menu_FileQuitItem"
				[ ] "&id='menu_FileQuitItem';name='Exit'"
	[+] Menu Edit
		[+] multitag "Edit"
			[ ] "$edit-menu"
			[ ] "&id='edit-menu';name='Edit'"
		[+] MenuItem Undo
			[+] multitag "Undo"
				[ ] "&id='Undo';name='Undo'"
		[+] MenuItem Redo
			[+] multitag "Redo"
				[ ] "&id='Redo';name='Redo'"
		[+] MenuItem Cut
			[+] multitag "Cut"
				[ ] "&id='Cut';name='Cut'"
		[+] MenuItem Copy
			[+] multitag "Copy"
				[ ] "&id='Copy';name='Copy'"
		[+] MenuItem Paste
			[+] multitag "Paste"
				[ ] "&id='Paste';name='Paste'"
		[+] MenuItem Delete
			[+] multitag "Delete"
				[ ] "&id='Delete';name='Delete'"
		[+] MenuItem SelectAll
			[+] multitag "Select All"
				[ ] "&id='Select All';name='Select All'"
		[+] MenuItem FindInThisPage
			[+] multitag "Find in This Page"
				[ ] "$menu_find"
				[ ] "&id='menu_find';name='Find in This Page...'"
		[+] MenuItem FindAgain
			[+] multitag "Find Again"
				[ ] "&id='Find Again';name='Find Again'"
		[+] MenuItem SwitchTextDirection
			[+] multitag "Switch Text Direction"
				[ ] "$textfieldDirection-swap"
				[ ] "&id='textfieldDirection-swap';name='Switch Text Direction'"
	[+] Menu View
		[+] multitag "View"
			[ ] "$view-menu"
			[ ] "&id='view-menu';name='View'"
		[+] Menu Toolbars
			[+] multitag "Toolbars"
				[ ] "$viewToolbarsMenu"
				[ ] "&id='viewToolbarsMenu';name='Toolbars'"
			[+] MenuItem Customize
				[+] multitag "Customize"
					[ ] "&id='Customize...';name='Customize...'"
		[+] MenuItem StatusBar
			[+] multitag "Status Bar"
				[ ] "$toggle_taskbar"
				[ ] "&id='toggle_taskbar';name='Status Bar'"
		[+] Menu Sidebar
			[+] multitag "Sidebar"
				[ ] "$viewSidebarMenuMenu"
				[ ] "&id='viewSidebarMenuMenu';name='Sidebar'"
			[+] MenuItem Bookmarks
				[+] multitag "Bookmarks"
					[ ] "&id='Bookmarks';name='Bookmarks'"
			[+] MenuItem History
				[+] multitag "History"
					[ ] "&id='History';name='History'"
		[+] MenuItem Stop
			[+] multitag "Stop"
				[ ] "&id='Stop';name='Stop'"
		[+] MenuItem Reload
			[+] multitag "Reload"
				[ ] "&id='Reload';name='Reload'"
		[+] Menu TextSize
			[+] multitag "Text Size"
				[ ] "$viewTextZoomMenu"
				[ ] "&id='viewTextZoomMenu';name='Text Size'"
			[+] MenuItem Increase
				[+] multitag "Increase"
					[ ] "&id='Increase';name='Increase'"
			[+] MenuItem Decrease
				[+] multitag "Decrease"
					[ ] "&id='Decrease';name='Decrease'"
			[+] MenuItem Normal
				[+] multitag "Normal"
					[ ] "&id='Normal';name='Normal'"
		[+] Menu PageStyle
			[+] multitag "Page Style"
				[ ] "$pageStyleMenu"
				[ ] "&id='pageStyleMenu';name='Page Style'"
			[+] MenuItem NoStyle
				[+] multitag "No Style"
					[ ] "&id='No Style';name='No Style'"
			[+] MenuItem BasicPageStyle
				[+] multitag "Basic Page Style"
					[ ] "&id='Basic Page Style';name='Basic Page Style'"
		[+] Menu CharacterEncoding
			[+] multitag "Character Encoding"
				[ ] "$charsetMenu"
				[ ] "&id='charsetMenu';name='Character Encoding'"
			[+] MenuItem RdfHttpHomeNetscapeComN
				[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
					[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='charsetGroup'"
			[+] Menu AutoDetect
				[+] multitag "Auto-Detect"
					[ ] "&id='Auto-Detect';name='Auto-Detect'"
				[+] MenuItem RdfHttpHomeNetscapeComN
					[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
						[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='detectorGroup'"
			[+] Menu MoreEncodings
				[+] multitag "More Encodings"
					[ ] "&id='More Encodings';name='More Encodings'"
				[+] MenuItem RdfHttpHomeNetscapeComN
					[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
						[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
				[+] Menu WestEuropean
					[+] multitag "West European"
						[ ] "&id='West European';name='West European'"
					[+] MenuItem RdfHttpHomeNetscapeComN
						[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
							[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
				[+] Menu EastEuropean
					[+] multitag "East European"
						[ ] "&id='East European';name='East European'"
					[+] MenuItem RdfHttpHomeNetscapeComN
						[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
							[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
				[+] Menu EastAsian
					[+] multitag "East Asian"
						[ ] "&id='East Asian';name='East Asian'"
					[+] MenuItem RdfHttpHomeNetscapeComN
						[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
							[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
				[+] Menu SESWAsian
					[+] multitag "SE  SW Asian"
						[ ] "&id='SE & SW Asian';name='SE & SW Asian'"
					[+] MenuItem RdfHttpHomeNetscapeComN
						[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
							[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
				[+] Menu MiddleEastern
					[+] multitag "Middle Eastern"
						[ ] "&id='Middle Eastern';name='Middle Eastern'"
					[+] MenuItem RdfHttpHomeNetscapeComN
						[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
							[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
				[+] Menu Unicode
					[+] multitag "Unicode"
						[ ] "&id='Unicode';name='Unicode'"
					[+] MenuItem RdfHttpHomeNetscapeComN
						[+] multitag "rdf:http:??home.netscape.com?NC-rdf#Name"
							[ ] "&id='rdf:http:??home.netscape.com?NC-rdf#Name';name='rdf:http:??home.netscape.com?NC-rdf#Name'"
			[+] MenuItem CustomizeList
				[+] multitag "Customize List"
					[ ] "&id='Customize List...';name='charsetCustomize'"
			[+] MenuItem WesternISO88591
				[+] multitag "Western (ISO-8859-1)"
					[ ] "$charset.ISO-8859-1"
					[ ] "&id='charset.ISO-8859-1';name='charsetGroup'"
			[+] MenuItem UnicodeUTF8
				[+] multitag "Unicode (UTF-8)"
					[ ] "$charset.UTF-8"
					[ ] "&id='charset.UTF-8';name='charsetGroup'"
		[+] MenuItem PageSource
			[+] multitag "Page Source"
				[ ] "&id='Page Source';name='Page Source'"
		[+] MenuItem FullScreen
			[+] multitag "Full Screen"
				[ ] "$fullScreenItem"
				[ ] "&id='fullScreenItem';name='Full Screen'"
		[+] MenuItem SwitchPageDirection
			[+] multitag "Switch Page Direction"
				[ ] "$documentDirection-swap"
				[ ] "&id='documentDirection-swap';name='Switch Page Direction'"
[ ]
[ ]
