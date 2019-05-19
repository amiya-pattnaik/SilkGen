[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_WindowsDecl.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Windows declaration that are specific to SILKGEN Framework are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		03/12/09	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ] //***************************************************************
[ ] //
[ ] // MSDOSPrompt Window Declaration
[ ] 
[ ]
[+] window MainWin 	MSDOSPrompt
	[+] multitag "[DialogBox]Command Prompt*"
		[ ] "MS-DOS Prompt"
		[ ] "*COMMAND.COM"
		[ ] "[DialogBox]Command Prompt*"
		[ ] "MS-DOS Prompt[2]"
		[ ] "MS-DOS Prompt[1]"
		[ ] "*MS-DOS*"
		[ ] "*\WINOA386.MOD[2]"
		[ ] "*\WINOA386.MOD"
		[ ] "XCOPY32"
	[ ]
	[ ] const sCmdLine = "C:\WINNT\system32\COMMAND.COM"
	[ ]
	[ ]
	[+] VOID Invoke ()
		[+] if !Exists()
			[ ] Start (sCmdLine)
		[+] else
			[ ] Restore()
	[ ]
	[ ] // The command line used to invoke the application
	[ ] const sDosCmd = "C:\WINNT\system32\COMMAND.COM"
	[+] CustomWin Cmd
		[+] multitag "[ttyGrab]#1"
			[ ] "[ttyGrab]$2"
	[+] ToolBar DosToolBar
		[+] multitag "#1"
			[ ] "$1"
		[+] CheckBox Mark
			[+] multitag "#1"
				[ ] "$-8189"
		[+] PushButton Copy
			[+] multitag "#1"
				[ ] "$-8192"
		[+] CheckBox Paste
			[+] multitag "#2"
				[ ] "$-8191"
		[+] PushButton FullScreen
			[+] multitag "#2"
				[ ] "$-8177"
		[+] PushButton Properties
			[+] multitag "#3"
				[ ] "$-8179"
		[+] CheckBox Background
			[+] multitag "#3"
				[ ] "$-8175"
		[+] PushButton Font
			[+] multitag "#4"
				[ ] "$-8182"
		[+] PopupList PopSize
			[+] multitag "#1"
				[ ] "$3"
	[+] InvokeCmd (STRING sCmd)
		[+] if Exists ()
			[ ] Close ()
		[ ] Start (sDosCmd)
		[ ] TypeKeys ("{sCmd}<Enter>")
		[ ] sleep (2)
	[+] TypeCmd (STRING sCmd)
		[ ] TypeKeys ("{sCmd}<Enter>")
		[ ] sleep (1)
	[+] TypeCmdNoRtn (STRING sCmd)
		[ ] SetActive ()
		[ ] TypeKeys ("{sCmd}")
		[ ] sleep (1)
	[+] Close ()
		[ ] TypeKeys ("<Enter>exit<Enter>")
		[ ] sleep (1)
	[+] FileCopy (STRING sFrom,STRING sTo, STRING sFromPath optional, STRING sToPath optional)
		[ ] STRING sToFull = sTo
		[+] if sFromPath != NULL
			[ ] sFrom = sFromPath + "\" + sFrom
		[+] if sToPath != NULL
			[ ] sToFull = sToPath + "\" + sTo
		[ ] InvokeCmd ("xcopy {sFrom} {sToFull}")
		[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (),"(F = file, D = directory)?") != 0
			[ ] TypeCmdNoRtn ("f")
			[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (), "Overwrite {sTo} (Yes/No/All)?") != 0
			[ ] TypeCmdNoRtn ("Y")
	[+] FileRun (STRING sFile, STRING sPath optional)
		[+] if sPath != NULL
			[ ] sFile = sPath + "\" + sFile
		[ ] InvokeCmd (sFile)
		[ ] CopyWinToClip ()
	[+] FileOpen (STRING sFile, STRING sPath optional)
		[ ] STRING sCmd
		[+] if sPath != NULL
			[ ] sFile = sPath + "\" + sFile
		[ ] sCmd = "TYPE " + sFile
		[ ] InvokeCmd (sCmd)
	[+] FileMove (STRING sFrom,STRING sTo, STRING sFromPath optional)
		[ ] //FileDelete (sTo, sFromPath)
		[+] if sFromPath != NULL
			[ ] sFrom = sFromPath + "\" + sFrom
		[ ] InvokeCmd ("rename {sFrom} {sTo}")
		[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (),"(F = file, D = directory)?") != 0
			[ ] TypeCmdNoRtn ("f")
			[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (), "Overwrite {sTo} (Yes/No/All)?") != 0
			[ ] TypeCmdNoRtn ("Y")
		[ ]
	[+] FileDelete (STRING sFile, STRING sPath optional)
		[+] if sPath != NULL
			[ ] sFile = sPath + "\" + sFile
		[ ] InvokeCmd ("del {sFile}")
		[ ] CopyWinToClip ()
		[ ]
	[+] DirCopy (STRING sFrom,STRING sTo, STRING sFromPath optional, STRING sToPath optional)
		[ ] STRING sToFull = sTo
		[+] if sFromPath != NULL
			[ ] sFrom = sFromPath + "\" + sFrom
		[+] if sToPath != NULL
			[ ] sToFull = sToPath + "\" + sTo
		[ ] InvokeCmd ("xcopy {sFrom} {sToFull}")
		[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (),"(F = file, D = directory)?") != 0
			[ ] TypeCmdNoRtn ("d")
			[ ] CopyWinToClip ()
		[+] if FindOverwrite ()
			[ ] TypeCmdNoRtn ("A")
		[ ]
	[+] DirMove (STRING sFrom,STRING sTo, STRING sFromPath optional)
		[ ] DirDelete (sTo, sFromPath)
		[+] if sFromPath != NULL
			[ ] sFrom = sFromPath + "\" + sFrom
		[ ] TypeCmd ("rename {sFrom} {sTo}")
		[ ] CopyWinToClip ()
		[+] if FindOverwrite ()
			[ ] TypeCmdNoRtn ("A")
		[ ]
	[+] DirDelete (STRING sDir, STRING sPath optional)
		[+] if sPath != NULL
			[ ] sDir = sPath + "\" + sDir
		[ ] InvokeCmd ("del {sDir}\...\*.*")
		[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (),"Are you sure (Y/N)?") != 0
			[ ] TypeCmd ("Y")
		[ ] TypeCmd ("del {sDir}\*.*")
		[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (),"Are you sure (Y/N)?") != 0
			[ ] TypeCmd ("Y")
		[ ] TypeCmd ("rmdir {sDir}\*.*")
		[ ] CopyWinToClip ()
		[+] if ListFind (Clipboard.GetText (),"Are you sure (Y/N)?") != 0
			[ ] TypeCmd ("Y")
		[ ] TypeCmd ("rmdir {sDir}")
		[ ] CopyWinToClip ()
		[ ]
	[+] BOOLEAN FindOverwrite ()
		[ ] LIST OF STRING lsContents = Clipboard.GetText ()
		[ ] STRING sLine
		[+] for each sLine in lsContents
			[+] if MatchStr ("Overwrite * (Yes/No/All)?",sLine)
				[ ] return TRUE
		[ ] return FALSE
	[+] CopyWinToClip ()
		[ ] RECT rCmdSize = Cmd.GetRect ()
		[ ] DosToolBar.Mark.Check ()
		[ ] Cmd.BeginDragAt (1, 1, 1)
		[ ] Cmd.EndDragAt (rCmdSize.xSize, rCmdSize.ySize)
		[ ] DosToolBar.Copy.Click ()
	[+] VOID MatchString (STRING sToFind)
		[ ] STRING sText
		[ ] CopyWinToClip ()
		[ ] //ResPrintList ("Clipboard Contents:",Clipboard.GetText ())
		[ ]
		[+] for each sText in Clipboard.GetText ()
			[+] if MatchStr (sToFind,sText)
				[ ] Print ("Verification successful: ",sText)
				[ ] return
		[ ] RaiseError (1, "String {sToFind} not found in dos window")
[ ]
[ ] //***************************************************************
[ ] //
[ ] // MessageBox Window
[ ]
[+] window MessageBoxClass MessBox
	[ ] tag "~ActiveApp/[DialogBox]$MessageBox"
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[+] if Exists(1) && this.GetCaption() != "CogImgEdit" // cmm,11/28: added GetCaption workaround for Silk bug with MFC ImageFileEdit app
			[+] if OK.Exists ()
				[ ] OK.Click()
			[+] else
				[+] if Yes.Exists ()
					[ ] derived::Close ()
		[ ] return
	[+] PushButton OK
		[ ] tag "OK"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] PushButton Yes
		[ ] tag "Yes"
	[+] PushButton No
		[ ] tag "No"
	[+] StaticText Message
		[ ] motif tag "#2"
		[ ] tag "#1"
[ ] window MessageBox = MessBox
[ ]
[ ]
[ ] //***************************************************************
[ ] //
[ ] // Windows Explorer Window Declaration
[ ]
[+] window MainWin 		WinExplorer
	[+] multitag "Exploring*"
		[ ] "*C:\"
		[ ] "$C:\*\EXPLORER.EXE[1]"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] //msw98 const sDir = "C:\WINDOWS" // not certain if this gui specifier is correct
	[ ] const sDir = "C:\Winnt"
	[ ]
	[ ]
	[ ] // The command line used to invoke the application
	[ ] const sCmdLine = "{sDir}\EXPLORER.EXE"
	[ ]
	[ ] // The first window to appear when the application is invoked
	[ ] // const wStartup = ?
	[ ]
	[ ] // The list of windows the recovery system is to leave open
	[ ] // const lwLeaveOpen = {?}
	[ ]
	[+] VOID Invoke (LIST OF ANYTYPE laPosition optional)
		[ ] Start (sCmdLine)
		[+] if this.GetState() == WS_MAXIMIZED
			[ ] this.RestoreBox.Click()
		[+] if laPosition != NULL
			[ ] WinExplorer.Move(laPosition[1],laPosition[2])
	[+] VOID DragAndDropFromExplorer (STRING sPathFrom, STRING sItem, WINDOW wToDropAt, LIST OF INTEGER liCoord)
		[ ] WinExplorer.SetActive()
		[ ] WinExplorer.Folders.ExpandNode (sPathFrom)
		[ ] WinExplorer.Contents.Select (sItem)
		[ ] WinExplorer.Contents.BeginDrag (1, sItem)
		[ ] wToDropAt.EndDragAt (liCoord[1],liCoord[2])
		[ ]
	[+] VOID FileOpen (STRING sPath, STRING sFile)
		[ ] Folders.Select (sPath)
		[ ] Contents.DoubleSelect (sFile)
		[+] if OpenWith.Exists ()
			[ ] OpenWith.Notepad ()
		[ ]
	[+] VOID FileCopy (STRING sPath, STRING sFrom, STRING sTo)
		[ ]
	[+] VOID FileMove (STRING sPath, STRING sFrom, STRING sTo)
		[ ]
	[+] VOID FileDel (STRING sPath, STRING sFile)
		[ ]
	[+] VOID DirCopy (STRING sPath, STRING sFrom, STRING sTo)
		[ ]
	[+] VOID DirMove (STRING sPath, STRING sFrom, STRING sTo)
		[ ]
	[+] VOID DirDelete (STRING sDir, STRING sPath optional)
		[ ]
		[ ] WinExplorer.SetActive ()
		[ ] WinExplorer.Folders.Select ("/Desktop/My Computer/Prntshp (C:)/temp/new/dir1")
		[ ] WinExplorer.File.Delete.Pick ()
		[+] if MessBox.Exists (5)
			[+] MessBox.Message.VerifyProperties ({...})
				[ ] ""
				[+] {...}
					[ ] {"Text",                 "Are you sure you want to remove the folder 'dir1' and move all its contents to the Recycle Bin?"}
		[+] MainWin("Exploring*|*C:\temp\new\dir1|$C:\WINDOWS\EXPLORER.EXE").DialogBox("Confirm Folder Delete|$MessageBox").VerifyProperties ({...})
			[ ] ""
			[+] {...}
				[ ] {"Caption",              "Confirm Folder Delete"}
			[+] {...}
				[+] {'StaticText ("Are you sure you want to remove the folder ''dir1'' and move all its contents to the Recycle Bin?|$12291")', {...}}
					[ ] {"Text",                 "Are you sure you want to remove the folder 'dir1' and move all its contents to the Recycle Bin?"}
		[ ] MainWin("Exploring*|*C:\temp\new\dir1|$C:\WINDOWS\EXPLORER.EXE").DialogBox("Confirm Folder Delete|$MessageBox").SetActive ()
		[ ] MainWin("Exploring*|*C:\temp\new\dir1|$C:\WINDOWS\EXPLORER.EXE").DialogBox("Confirm Folder Delete|$MessageBox").PushButton("Yes|$6").Click ()
	[+] VOID VerNoAccess ()
		[+] if MessBox.Exists ()
			[ ] Verify (MessBox.Message.GetText (), "Access to the specified device, path, or file is denied.","That the access error was raised")
			[ ] return
		[ ] RaiseError (1,"Access error not raised as expected")
	[ ]
	[+] Menu File
		[ ] tag "File"
		[+] Menu New
			[ ] tag "New"
			[+] MenuItem Folder
				[+] multitag "Folder"
					[ ] "$29281"
			[+] MenuItem Shortcut
				[+] multitag "Shortcut"
					[ ] "$29282"
			[+] MenuItem MenuItem3
				[+] multitag "#3"
					[ ] "$29283[1]"
			[+] MenuItem MenuItem4
				[+] multitag "#4"
					[ ] "$29283[2]"
			[+] MenuItem MenuItem5
				[+] multitag "#5"
					[ ] "$29283[3]"
			[+] MenuItem MenuItem6
				[+] multitag "#6"
					[ ] "$29283[4]"
			[+] MenuItem MenuItem7
				[+] multitag "#7"
					[ ] "$29283[5]"
			[+] MenuItem MenuItem8
				[+] multitag "#8"
					[ ] "$29283[6]"
			[+] MenuItem MenuItem9
				[+] multitag "#9"
					[ ] "$29283[7]"
			[+] MenuItem MenuItem10
				[+] multitag "#10"
					[ ] "$29283[8]"
			[+] MenuItem MenuItem11
				[+] multitag "#11"
					[ ] "$29283[9]"
			[+] MenuItem MenuItem12
				[+] multitag "#12"
					[ ] "$29283[11]"
			[+] MenuItem MenuItem13
				[+] multitag "#13"
					[ ] "$29283[11]"
		[+] MenuItem CreateShortcut
			[+] multitag "Create Shortcut"
				[ ] "$28688"
		[+] MenuItem Delete
			[+] multitag "Delete"
				[ ] "$28689"
		[+] MenuItem Rename
			[+] multitag "Rename"
				[ ] "$28690"
		[+] MenuItem Properties
			[+] multitag "Properties"
				[ ] "$28691"
		[+] MenuItem Close
			[+] multitag "Close"
				[ ] "$40993"
	[+] Menu Edit
		[ ] tag "Edit"
		[+] MenuItem UndoCopy
			[+] multitag "Undo Copy"
				[ ] "$28699"
		[+] MenuItem Cut
			[+] multitag "Cut"
				[ ] "$28696"
		[+] MenuItem Copy
			[+] multitag "Copy"
				[ ] "$28697"
		[+] MenuItem Paste
			[+] multitag "Paste"
				[ ] "$28698"
		[+] MenuItem PasteShortcut
			[+] multitag "Paste Shortcut"
				[ ] "$28700"
		[+] MenuItem SelectAll
			[+] multitag "Select All"
				[ ] "$28705"
		[+] MenuItem InvertSelection
			[+] multitag "Invert Selection"
				[ ] "$28706"
	[+] Menu View
		[ ] tag "View"
		[+] MenuItem Toolbar
			[+] multitag "Toolbar"
				[ ] "$41058"
		[+] MenuItem StatusBar
			[+] multitag "Status Bar"
				[ ] "$41059"
		[+] MenuItem LargeIcons
			[+] multitag "Large Icons"
				[ ] "$28713"
		[+] MenuItem SmallIcons
			[+] multitag "Small Icons"
				[ ] "$28714"
		[+] MenuItem xList
			[+] multitag "List"
				[ ] "$28715"
		[+] MenuItem MenuItem6
			[+] multitag "#6"
				[ ] "$28716"
		[+] Menu ArrangeIcons
			[ ] tag "Arrange Icons"
			[+] MenuItem ByName
				[+] multitag "by Name"
					[ ] "$29232"
			[+] MenuItem ByType
				[+] multitag "by Type"
					[ ] "$29234"
			[+] MenuItem BySize
				[+] multitag "by Size"
					[ ] "$29233"
			[+] MenuItem ByDate
				[+] multitag "by Date"
					[ ] "$29235"
			[+] MenuItem AutoArrange
				[+] multitag "Auto Arrange"
					[ ] "$28721"
		[+] MenuItem LineUpIcons
			[+] multitag "Line up Icons"
				[ ] "$28722"
		[+] MenuItem Refresh
			[+] multitag "Refresh"
				[ ] "$41061"
		[+] MenuItem Options
			[+] multitag "Options"
				[ ] "$41060"
	[+] Menu Tools
		[ ] tag "Tools"
		[+] Menu Find
			[ ] tag "Find"
			[+] MenuItem FilesOrFolders
				[+] multitag "Files or Folders"
					[ ] "$41099"
			[+] MenuItem Computer
				[+] multitag "Computer"
					[ ] "$41100"
			[+] MenuItem UsingMicrosoftOutlook
				[+] multitag "Using Microsoft Outlook"
					[ ] "$41101"
			[+] MenuItem OnTheInternet
				[+] multitag "On the Internet"
					[ ] "$41102"
		[+] MenuItem MapNetworkDrive
			[+] multitag "Map Network Drive"
				[ ] "$41089"
		[+] MenuItem DisconnectNetworkDrive
			[+] multitag "Disconnect Network Drive"
				[ ] "$41090"
		[+] MenuItem GoTo
			[+] multitag "Go to"
				[ ] "$41092"
	[+] Menu Help
		[ ] tag "Help"
		[+] MenuItem HelpTopics
			[+] multitag "Help Topics"
				[ ] "$28737"
		[+] MenuItem AboutWindows95
			[+] multitag "About Windows 95"
				[ ] "$41218"
	[+] TreeView Folders
		[+] multitag "All Folders"
			[ ] "$40963"
		[+] VOID ExpandNode (STRING sFullPathToNode)
			[ ] LIST OF STRING lsNodes
			[ ] STRING sNode
			[ ] STRING sParents = ""
			[ ] INTEGER iLen, iLoop
			[ ]
			[ ] lsNodes = FieldsToList (sFullPathToNode, "/")
			[ ] Print (lsNodes)
			[ ]
			[ ] //throw out the first node if it is ""
			[+] if lsNodes[1] == ""
				[ ] ListDelete (lsNodes,1)
			[ ]
			[ ] iLen = ListCount(lsNodes)
			[ ]
			[ ] iLoop = 0
			[+] for each sNode in lsNodes
				[ ] iLoop++
				[ ] sParents = sParents + "/" + sNode
				[+] do
					[ ] Expand (sParents)
				[+] except
					[+] if ExceptNum() == E_ITEM_CANT_EXPAND
						[+] if iLoop == iLen
							[ ] Select (sParents) //this is a leaf node - can select but not expand
							[ ] continue
					[ ] reraise
	[ ]
	[+] ToolBar ToolBar1
		[+] multitag "#1"
			[ ] "$40960"
		[+] PushButton PushButton1
			[+] multitag "#1"
				[ ] "$40994"
		[+] PushButton PushButton2
			[+] multitag "#2"
				[ ] "$28726"
		[+] PushButton PushButton3
			[+] multitag "#3"
				[ ] "$28727"
		[+] PushButton Cut
			[+] multitag "Cut"
				[ ] "$28696"
		[+] PushButton Copy
			[+] multitag "Copy"
				[ ] "$28697"
		[+] PushButton Paste
			[+] multitag "Paste"
				[ ] "$28698"
		[+] PushButton UndoCopy
			[+] multitag "Undo Copy"
				[ ] "$28699"
		[+] PushButton Delete
			[+] multitag "Delete"
				[ ] "$28689"
		[+] PushButton Properties
			[+] multitag "Properties"
				[ ] "$28691"
		[+] PushButton LargeIcons
			[+] multitag "Large Icons"
				[ ] "$28713"
		[+] PushButton SmallIcons
			[+] multitag "Small Icons"
				[ ] "$28714"
		[+] PushButton xList
			[+] multitag "List"
				[ ] "$28715"
		[+] PushButton Details
			[+] multitag "Details"
				[ ] "$28716"
		[+] PopupList PopupList1
			[+] multitag "#1"
				[ ] "$40962"
	[+] ListView Contents
		[+] multitag "Contents of *"
			[ ] "$1"
		[+] Header Header1
			[+] multitag "#1"
				[ ] "$0"
			[+] PushButton Name
				[ ] tag "Name"
			[+] PushButton Size
				[ ] tag "Size"
			[+] PushButton Type
				[ ] tag "Type"
			[+] PushButton Modified
				[ ] tag "Modified"
[ ]
[ ]
[ ] //
[ ] //***************************************************************
[ ] //
[ ] // Microsoft Notepad Window Declaration
[ ]
[+] window MainWin 		MSNotepad
	[+] multitag "*Notepad"
		[ ] "$C:\WinNT\NOTEPAD.EXE"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] // mswnt, msw2000		const sDir = "C:\WinNT"
	[ ] mswxp				const sDir = "C:\Windows"
	[ ]
	[ ] // The command line used to invoke the application
	[ ] // mswnt, msw2000		const sCmdLine = "C:\WinNT\NOTEPAD.EXE "
	[ ] mswxp,msw98			const sCmdLine = "C:\Windows\NOTEPAD.EXE "
	[ ]
	[ ] // The first window to appear when the application is invoked
	[ ] // const wStartup = ?
	[ ]
	[ ] // The list of windows the recovery system is to leave open
	[ ] // const lwLeaveOpen = {?}
	[+] VOID Invoke ()
		[+] if !MSNotepad.Exists()
			[ ] Start(sCmdLine)
	[ ] // Kelly added arguments to Close 3/25/02
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] SetActive()
		[ ] File.Exit.Pick()
		[+] if MessageBox.Exists()
			[ ] MessageBox.No.Click()
	[+] VOID DirRename ()
		[ ]
	[+] VOID FileDelete ()
		[ ]
	[+] VOID FileMove ()
		[ ]
	[+] VOID FileOpen (STRING sFile, STRING sPath optional)
		[ ] Open.Invoke ()
		[+] if sPath != NULL
			[ ] sFile = sPath + "\" + sFile
		[ ] Open.OpenViaTF (sFile)
		[ ]
	[+] VOID FileRename ()
		[ ]
	[+] VOID FileWrite (STRING sFile, STRING sPath optional, BOOLEAN bOverwrite NULL optional)
		[+] if bOverwrite != FALSE
			[ ] bOverwrite = TRUE
		[+] if sPath != NULL
			[+] if SubStr (sPath, Len (sPath), 1) == "\"
				[ ] sFile = sPath + sFile
			[+] else
				[ ] sFile = sPath + "\" + sFile
		[ ] SaveAs.Invoke ()
		[ ] SaveAs.SaveViaTF (sFile)
		[+] if SaveAs.Overwrite.Exists ()
			[+] if bOverwrite
				[ ] SaveAs.Overwrite.Yes.Click ()
			[+] else
				[ ] LogWarning ("File Exists, specify bOverwrite to overwrite")
				[ ] SaveAs.Overwrite.No.Click ()
		[ ]
	[+] VOID TypeData (LIST OF STRING lsData)
		[ ] Text.SetMultiText (lsData)
	[ ]
	[+] Menu File
		[ ] tag "File"
		[+] MenuItem New
			[+] multitag "New"
				[ ] "$9"
		[+] MenuItem Open
			[+] multitag "Open"
				[ ] "$10"
		[+] MenuItem Save
			[+] multitag "Save"
				[ ] "$1"
		[+] MenuItem SaveAs
			[+] multitag "Save As"
				[ ] "$2"
		[+] MenuItem PageSetup
			[+] multitag "Page Setup"
				[ ] "$32"
		[+] MenuItem Print
			[+] multitag "Print"
				[ ] "$14"
		[+] MenuItem Exit
			[+] multitag "Exit"
				[ ] "$28"
	[+] Menu Edit
		[ ] tag "Edit"
		[+] MenuItem Undo
			[+] multitag "Undo"
				[ ] "$25"
		[+] MenuItem Cut
			[+] multitag "Cut"
				[ ] "$768"
		[+] MenuItem Copy
			[+] multitag "Copy"
				[ ] "$769"
		[+] MenuItem Paste
			[+] multitag "Paste"
				[ ] "$770"
		[+] MenuItem Delete
			[+] multitag "Delete"
				[ ] "$771"
		[+] MenuItem SelectAll
			[+] multitag "Select All"
				[ ] "$7"
		[+] MenuItem TimeDate
			[+] multitag "Time?Date"
				[ ] "$12"
		[+] MenuItem WordWrap
			[+] multitag "Word Wrap"
				[ ] "$27"
	[+] Menu Search
		[ ] tag "Search"
		[+] MenuItem Find
			[+] multitag "Find"
				[ ] "$3"
		[+] MenuItem FindNext
			[+] multitag "Find Next"
				[ ] "$8"
	[+] Menu Help
		[ ] tag "Help"
		[+] MenuItem HelpTopics
			[+] multitag "Help Topics"
				[ ] "$5"
		[+] MenuItem AboutNotepad
			[+] multitag "About Notepad"
				[ ] "$11"
	[+] TextField Text
		[+] multitag "#1"
			[ ] "$15"
	[+] DialogBox Open
		[ ] tag "Open"
		[+] VOID Invoke ()
			[ ] File.Open.Pick ()
		[+] VOID OpenViaTF (STRING sFile)
			[ ] FileName.SetText (sFile)
			[ ] Open.Click ()
			[+] if MessBox.Exists ()
				[+] do
					[ ] RaiseError (1,"File open failed with error {MessBox.Message.GetText ()}")
				[+] except
					[ ] MSNotepad.Exit ()
					[ ] reraise
		[+] PopupList LookIn
			[+] multitag "Look in:"
				[ ] "#1"
				[ ] "$1137"
		[+] ListView LView
			[+] multitag "Look in:"
				[ ] "#1"
				[ ] "$1"
		[+] TextField FileName
			[+] multitag "File name:"
				[ ] "#1"
				[ ] "$1152"
		[+] PopupList FilesOfType
			[+] multitag "Files of type:"
				[ ] "#2"
				[ ] "$1136"
		[+] PushButton Open
			[+] multitag "Open"
				[ ] "$1"
		[+] PushButton Cancel
			[+] multitag "Cancel"
				[ ] "$2"
		[+] ToolBar TBar
			[+] multitag "Look in:"
				[ ] "#1"
				[ ] "$1"
			[+] PushButton UpOneLevel
				[+] multitag "#1"
					[ ] "$40961"
			[+] PushButton CreateNewFolder
				[+] multitag "#2"
					[ ] "$40962"
			[+] RadioList ListDetails
				[+] multitag "#1"
					[ ] "$40963"
		[+] DialogBox OpenError
			[ ] tag "Open"
			[+] PushButton OK
				[+] multitag "OK"
					[ ] "$2"
			[+] StaticText FileNotFound
				[+] multitag "*This file cannot be found.*"
					[ ] "$65535"
	[+] DialogBox SaveAs
		[ ] tag "Save As"
		[+] VOID Invoke ()
			[ ] MSNotepad.TypeKeys ("<Alt-f>")
			[ ] MSNotepad.TypeKeys ("a")
			[ ] Agent.FlushEvents ()
			[ ] //MSNotepad.File.SaveAs.Pick ()
			[ ] return
		[+] VOID SaveViaTF (STRING sFile)
			[ ] FileName.SetText (sFile)
			[ ] Save.Click ()
			[ ] return
		[+] PopupList SaveIn
			[+] multitag "Save in:"
				[ ] "#1"
				[ ] "$1137"
		[+] ListView LView
			[+] multitag "Look in:"
				[ ] "#1"
				[ ] "$1"
		[+] TextField FileName
			[+] multitag "File name:"
				[ ] "[ComboBox]File name:"
				[ ] "#1"
				[ ] "$1152"
		[+] PopupList SaveAsType
			[+] multitag "Save as type:"
				[ ] "#2"
				[ ] "$1136"
		[+] PushButton Save
			[+] multitag "Save"
				[ ] "$1"
		[+] PushButton Cancel
			[+] multitag "Cancel"
				[ ] "$2"
		[+] ToolBar TBar
			[+] multitag "Look in:"
				[ ] "#1"
				[ ] "$1"
			[+] PushButton UpOneLevel
				[+] multitag "#1"
					[ ] "$40961"
			[+] PushButton CreateNewFolder
				[+] multitag "#2"
					[ ] "$40962"
			[+] RadioList ListDetails
				[+] multitag "#1"
					[ ] "$40963"
		[+] DialogBox Overwrite
			[ ] tag "Save As"
			[+] PushButton Yes
				[+] multitag "Yes"
					[ ] "$6"
			[+] PushButton No
				[+] multitag "No"
					[ ] "$7"
			[+] CustomWin Icon1
				[+] msw multitag "[Icon]#1"
					[ ] "[Icon]$10"
			[+] StaticText FileExists
				[+] multitag "*This file already exists.??Replace existing file?"
					[ ] "$65535"
[+] window DialogBox 	OpenWith
	[+] multitag "Open With"
		[ ] "Open With[1]"
	[+] VOID Notepad ()
		[ ] ChooseTheProgram.Select ("NOTEPAD")
		[ ] AlwaysUseThis.Uncheck ()
		[ ] OK.Click ()
	[+] ListView ChooseTheProgram
		[+] multitag "Choose the program you want to use:"
			[ ] "#1"
			[ ] "$13829"
		[+] Header Header1
			[+] multitag "#1"
				[ ] "$0"
			[+] PushButton PushButton1
				[ ] tag "#1"
	[+] CheckBox AlwaysUseThis
		[+] multitag "Always use this program to open this file"
			[ ] "#1"
			[ ] "$13577"
	[+] PushButton OK
		[+] multitag "OK"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
	[+] PushButton Other
		[+] multitag "Other"
			[ ] "$13575"
[+] window DialogBox 	NotepadCannotFindFile
	[ ] tag "Notepad/[StaticText]Cannot find the */.."
	[ ] parent MSNotepad
	[+] PushButton Yes
		[ ] tag "Yes"
	[+] PushButton No
		[ ] tag "No"
	[+] CustomWin Icon1
		[ ] msw tag "[Icon]#1"
	[+] StaticText Message
		[ ] tag "Cannot find the *"
[+] // window DialogBox FNOTEPADEXE
	[+] // multitag "F:\NOTEPAD.EXE"
		[ ] // "#1"
	[ ] // parent WinExplorer
	[+] // PushButton OK
		[+] // multitag "OK"
			[ ] // "^Access to the specified device, path, or file is denied."
			[ ] // "$2"
	[+] // CustomWin Icon1
		[+] // msw multitag "[Icon]#1"
			[ ] // "[Icon]$10"
	[+] // StaticText AccessToTheSpecifiedDevice
		[+] // multitag "Access to the specified device, path, or file is denied."
			[ ] // "$65535"
[ ]
[ ] //***************************************************************
[ ] //
[ ] // Registry Editor Window Declaration
[ ]
[+] window MainWin 		RegistryEditor
	[ ] // The working directory of the application when it is invoked
	[ ] const sDir = "C:\"
	[ ]
	[ ] // The command line used to invoke the application
	[ ] const sCmdLine = "C:\WINNT\Regedit.exe "
	[+] multitag "Registry Editor"
		[ ] "$C:\WINNT\System32\regedt32.exe"
	[ ]
	[ ] // Kelly added arguments 3/25/02
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] RegistryEditor.Registry.Exit.Pick()
	[+] Menu Registry
		[ ] tag "Registry"
		[+] MenuItem ImportRegistryFile
			[ ] tag "Import Registry File"
		[+] MenuItem ExportRegistryFile
			[ ] tag "Export Registry File"
		[+] MenuItem ConnectNetworkRegistry
			[ ] tag "Connect Network Registry"
		[+] MenuItem DisconnectNetworkRegistry
			[ ] tag "Disconnect Network Registry"
		[+] MenuItem Print
			[ ] tag "Print"
		[+] MenuItem Exit
			[ ] tag "Exit"
	[+] Menu Edit
		[ ] tag "Edit"
		[+] Menu New
			[ ] tag "New"
			[+] MenuItem Key
				[ ] tag "Key"
			[+] MenuItem StringValue
				[ ] tag "String Value"
			[+] MenuItem BinaryValue
				[ ] tag "Binary Value"
			[+] MenuItem DWORDValue
				[ ] tag "DWORD Value"
		[+] MenuItem Delete
			[ ] tag "Delete"
		[+] MenuItem Rename
			[ ] tag "Rename"
		[+] MenuItem CopyKeyName
			[ ] tag "Copy Key Name"
		[+] MenuItem Find
			[ ] tag "Find"
		[+] MenuItem FindNext
			[ ] tag "Find Next"
		[+] MenuItem Modify
			[ ] tag "Modify"
		[ ]
	[+] Menu Tree
		[ ] tag "Tree"
		[+] MenuItem ExpandOneLevel
			[ ] tag "Expand One Level"
		[+] MenuItem ExpandBranch
			[ ] tag "Expand Branch"
		[+] MenuItem ExpandAll
			[ ] tag "Expand All"
		[+] MenuItem CollapseBranch
			[ ] tag "Collapse Branch"
	[+] Menu View
		[ ] tag "View"
		[+] MenuItem StatusBar
			[ ] tag "Status Bar"
		[+] MenuItem Split
			[ ] tag "Split"
		[+] MenuItem Refresh
			[ ] tag "Refresh"
	[+] Menu Security
		[ ] tag "Security"
		[+] MenuItem Permissions
			[ ] tag "Permissions"
		[+] MenuItem Auditing
			[ ] tag "Auditing"
		[+] MenuItem Owner
			[ ] tag "Owner"
	[+] Menu Options
		[ ] tag "Options"
		[+] MenuItem Font
			[ ] tag "Font"
		[+] MenuItem AutoRefresh
			[ ] tag "Auto Refresh"
		[+] MenuItem ReadOnlyMode
			[ ] tag "Read Only Mode"
		[+] MenuItem ConfirmOnDelete
			[ ] tag "Confirm on Delete"
		[+] MenuItem SaveSettingsOnExit
			[ ] tag "Save Settings on Exit"
	[+] Menu xWindow
		[ ] tag "Window"
		[+] MenuItem Cascade
			[ ] tag "Cascade"
		[+] MenuItem Tile
			[ ] tag "Tile"
		[+] MenuItem ArrangeIcons
			[ ] tag "Arrange Icons"
		[+] MenuItem N1HKEY_LOCAL_MACHINEOnLocal
			[ ] tag "1 HKEY_LOCAL_MACHINE on Local Machine"
		[+] MenuItem N2HKEY_USERSOnLocalMachine
			[ ] tag "2 HKEY_USERS on Local Machine"
		[+] MenuItem N3HKEY_CURRENT_CONFIGOnLocal
			[ ] tag "3 HKEY_CURRENT_CONFIG on Local Machine"
		[+] MenuItem N4HKEY_CLASSES_ROOTOnLocalM
			[ ] tag "4 HKEY_CLASSES_ROOT on Local Machine"
		[+] MenuItem N5HKEY_CURRENT_USEROnLocalM
			[ ] tag "5 HKEY_CURRENT_USER on Local Machine"
	[+] Menu Help
		[ ] tag "Help"
		[+] MenuItem Contents
			[ ] tag "Contents"
		[+] MenuItem SearchForHelpOn
			[ ] tag "Search for Help on"
		[+] MenuItem HowToUseHelp
			[ ] tag "How to Use Help"
		[+] MenuItem AboutRegistryEditor
			[ ] tag "About Registry Editor"
	[ ]
	[+] TreeView Keys
		[ ] tag "#1"
		[+] VOID ExpandNode (STRING sFullPathToNode)
			[ ] LIST OF STRING lsNodes
			[ ] STRING sNode
			[ ] STRING sParents = ""
			[ ] INTEGER iLen, iLoop
			[ ]
			[ ] lsNodes = FieldsToList (sFullPathToNode, "/")
			[ ]
			[ ] //throw out the first node if it is ""
			[+] if lsNodes[1] == ""
				[ ] ListDelete (lsNodes,1)
			[ ]
			[ ] iLen = ListCount(lsNodes)
			[ ]
			[ ] iLoop = 0
			[+] for each sNode in lsNodes
				[ ] iLoop++
				[ ] sParents = sParents + "/" + sNode
				[+] do
					[ ] Expand (sParents)
				[+] except
					[+] if ExceptNum() == E_ITEM_CANT_EXPAND
						[+] if iLoop == iLen
							[ ] //do nothing this is a leaf node and can not be expanded
							[ ] continue
					[ ] reraise
	[+] ListView Values
		[ ] tag "#1"
		[+] Header Header1
			[ ] tag "#1"
			[+] StaticText NameText
				[ ] tag "Name"
			[+] StaticText DataText
				[ ] tag "Data"
	[+] StatusBar StatusBar1
		[ ] tag "#1"
		[+] DynamicText DynamicText1
			[ ] tag "#1"
[+] window DialogBox 	EditString
	[ ] tag "Edit String"
	[ ] parent RegistryEditor
	[+] StaticText ValueDataText
		[ ] tag "Value data:"
	[+] TextField ValueData
		[ ] tag "Value data:"
	[+] PushButton OK
		[ ] tag "OK"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] StaticText ValueNameText
		[ ] tag "Value name:"
	[+] TextField ValueName
		[ ] tag "Value name:"
[+] window DialogBox 	ExportRegistryFile
	[ ] tag "Export Registry File"
	[ ] parent RegistryEditor
	[+] VOID Invoke ()
		[ ] RegistryEditor.Registry.ExportRegistryFile.Pick()
	[+] VOID Export (STRING sPath)
		[ ] FileName.SetText(sPath)
		[ ] Save.Click()
		[ ] return
	[+] StaticText SaveInText
		[ ] tag "Save in:"
	[+] PopupList SaveIn1
		[ ] tag "Save in:"
	[+] ListView SaveIn2
		[ ] tag "Save in:"
	[+] StaticText FileNameText
		[ ] tag "File name:"
	[+] TextField FileName
		[ ] tag "File name:"
	[+] // msw2000 ComboBox FileName
		[ ] // tag "File name:"
		[ ] //
	[+] StaticText SaveAsTypeText
		[ ] tag "Save as type:"
	[+] PopupList SaveAsType
		[ ] tag "Save as type:"
	[+] PushButton Save
		[ ] tag "Save"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] ToolBar SaveIn3
		[ ] tag "Save in:"
		[+] PushButton PushButton1
			[ ] tag "#1"
		[+] PushButton PushButton2
			[ ] tag "#2"
		[+] CustomWin RadioList1
			[ ] tag "#1"
[ ]
[ ]
[ ]
[ ] //***************************************************************
[ ] //
[ ] // WordPad Window Declarations
[ ]
[+] window MainWin 		WordPad
	[+] multitag "*WordPad"
		[ ] "$C:\Program Files\Windows NT\Accessories\wordpad.exe"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] STRING sDir = "{Wordpad_sDir ()}"
	[ ]
	[ ] // The command line used to invoke the application
	[ ] STRING sCmdLine = "{Wordpad_sCmdLine ()}"
	[ ]
	[ ]
	[+] STRING Wordpad_sDir ()
		[ ] STRING sDir
		[+] do
			[ ] sDir = GetField (SYS_GetRegistryValue (HKEY_LOCAL_MACHINE,"SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\WORDPAD.EXE",""),"\WORDPAD.EXE",1)
		[+] except
			[ ] ExceptLog()
			[ ] sDir = "C:\"
			[ ] LogWarning ("WORDPAD.EXE could not be found in the registry")
		[ ] //print ("Dir is",sDir)
		[ ] return (sDir)
	[+] STRING Wordpad_sCmdLine ()
		[ ] STRING sCmdLine
		[+] do
			[ ] sCmdLine = SYS_GetRegistryValue (HKEY_LOCAL_MACHINE,"SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\WORDPAD.EXE","")
		[+] except
			[ ] ExceptLog()
			[ ] sCmdLine = ""
			[ ] LogWarning ("WORDPAD.EXE could not be found in the registry")
		[ ] return (sCmdLine)
	[ ]
	[+] VOID OpenFile (STRING sFile)
		[+] if !Exists ()
			[ ] Invoke ()
		[ ] Restore()
		[ ] File.Open.Pick ()
		[ ] WPOpen.FileName.SetText (sFile)
		[ ] WPOpen.Open.Click ()
		[ ] return
	[+] VOID FindString (STRING sToFind)
		[ ] WordTextField.TypeKeys ("<Ctrl-Home>")
		[ ] WordTextField.TypeKeys ("<Ctrl-f>")
		[ ] WPFind.FindWhat.SetText (sToFind)
		[ ] WPFind.FindNext.Click ()
		[ ] WPFind.Cancel.Click ()
		[ ] return
	[+] VOID AddToSelAndCopy (INTEGER iToAdd)
		[ ] WordPad.SetActive ()
		[ ] WordPad.WordTextField.TypeKeys ("<Shift-Right {iToAdd}>")
		[ ] WordPad.Edit.Copy.Pick ()
		[ ] return
	[+] VOID Close (BOOLEAN bConfirm optional,BOOLEAN bSetActive optional)
		[+] if MessageBox.Exists()
			[ ] MessageBox.OK.Click()
		[+] if WPOpen.Exists()
			[ ] WPOpen.Close()
		[ ] BuiltinClose()
		[ ] return
	[+] Menu File
		[ ] tag "File"
		[+] MenuItem New
			[+] multitag "New"
				[ ] "$57600"
		[+] MenuItem Open
			[+] multitag "Open"
				[ ] "$57601"
		[+] MenuItem Save
			[+] multitag "Save"
				[ ] "$57603"
		[+] MenuItem SaveAs
			[+] multitag "Save As"
				[ ] "$57604"
		[+] MenuItem Print
			[+] multitag "Print"
				[ ] "$57607"
		[+] MenuItem PrintPreview
			[+] multitag "Print Preview"
				[ ] "$57609"
		[+] MenuItem PageSetup
			[+] multitag "Page Setup"
				[ ] "$32771"
		[+] MenuItem N1TEdgeEdgeRepeatabilityL
			[+] multitag "1 T:\Edge\Edge Repeatability Log"
				[ ] "$57616"
		[+] MenuItem N2CCkptiiInitckpt2k
			[+] multitag "2 c:\ckptii\initckpt2k"
				[ ] "$57617"
		[+] MenuItem Send
			[+] multitag "Send"
				[ ] "$57612"
		[+] MenuItem Exit
			[+] multitag "Exit"
				[ ] "$57665"
	[+] Menu Edit
		[ ] tag "Edit"
		[+] MenuItem Undo
			[+] multitag "Undo"
				[ ] "$57643"
		[+] MenuItem Cut
			[+] multitag "Cut"
				[ ] "$57635"
		[+] MenuItem Copy
			[+] multitag "Copy"
				[ ] "$57634"
		[+] MenuItem Paste
			[+] multitag "Paste"
				[ ] "$57637"
		[+] MenuItem PasteSpecial
			[+] multitag "Paste Special"
				[ ] "$57639"
		[+] MenuItem Clear
			[+] multitag "Clear"
				[ ] "$57632"
		[+] MenuItem SelectAll
			[+] multitag "Select All"
				[ ] "$57642"
		[+] MenuItem Find
			[+] multitag "Find"
				[ ] "$57636"
		[+] MenuItem FindNext
			[+] multitag "Find Next"
				[ ] "$57640"
		[+] MenuItem Replace
			[+] multitag "Replace"
				[ ] "$57641"
		[+] MenuItem Links
			[+] multitag "Links"
				[ ] "$57857"
		[+] MenuItem ObjectProperties
			[+] multitag "Object Properties"
				[ ] "$57860"
		[+] MenuItem Object
			[+] multitag "Object"
				[ ] "$57872"
	[+] Menu View
		[ ] tag "View"
		[+] MenuItem Toolbar
			[+] multitag "Toolbar"
				[ ] "$59392"
		[+] MenuItem FormatBar
			[+] multitag "Format Bar"
				[ ] "$59396"
		[+] MenuItem Ruler
			[+] multitag "Ruler"
				[ ] "$59397"
		[+] MenuItem StatusBar
			[+] multitag "Status Bar"
				[ ] "$59393"
		[+] MenuItem Options
			[+] multitag "Options"
				[ ] "$32776"
	[+] Menu Insert
		[ ] tag "Insert"
		[+] MenuItem DateAndTime
			[+] multitag "Date and Time"
				[ ] "$32778"
		[+] MenuItem Object
			[+] multitag "Object"
				[ ] "$57856"
	[+] Menu Format
		[ ] tag "Format"
		[+] MenuItem Font
			[+] multitag "Font"
				[ ] "$57696"
		[+] MenuItem BulletStyle
			[+] multitag "Bullet Style"
				[ ] "$32777"
		[+] MenuItem Paragraph
			[+] multitag "Paragraph"
				[ ] "$32780"
		[+] MenuItem Tabs
			[+] multitag "Tabs"
				[ ] "$32781"
	[+] Menu Help
		[ ] tag "Help"
		[+] MenuItem HelpTopics
			[+] multitag "Help Topics"
				[ ] "$57666"
		[+] MenuItem AboutWordPad
			[+] multitag "About WordPad"
				[ ] "$57664"
	[+] StatusBar StatusBar1
		[ ] tag "$59393"
		[+] DynamicText DynamicText1
			[ ] tag "#1"
		[+] DynamicText DynamicText2
			[ ] tag "#2"
		[+] DynamicText DynamicText3
			[ ] tag "#3"
	[+] TextField WordTextField
		[ ] tag "$59648"
[+] window DialogBox 	WPOpen
	[ ] tag "Open"
	[ ] parent WordPad
	[+] StaticText LookInText
		[+] multitag "Look in:"
			[ ] "$1091"
	[+] PopupList LookIn1
		[+] multitag "Look in:"
			[ ] "$1137"
	[+] ListView LookIn2
		[+] multitag "Look in:"
			[ ] "$1"
	[+] StaticText FileNameText
		[+] multitag "File name:"
			[ ] "$1090"
	[+] TextField FileName
		[+] multitag "File name:"
			[ ] "$1152"
	[+] StaticText FilesOfTypeText
		[+] multitag "Files of type:"
			[ ] "$1089"
	[+] PopupList FilesOfType
		[+] multitag "Files of type:"
			[ ] "$1136"
	[+] PushButton Open
		[+] multitag "Open"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
	[+] ToolBar LookIn3
		[+] multitag "Look in:"
			[ ] "$1"
		[+] PushButton PushButton1
			[ ] tag "$40961"
		[+] PushButton PushButton2
			[ ] tag "$40962"
		[+] RadioList RadioList1
			[ ] tag "$40963"
[+] window DialogBox 	WPFind
	[ ] tag "Find"
	[ ] parent WordPad
	[+] StaticText FindWhatText
		[+] multitag "Find what:"
			[ ] "$65535"
	[+] TextField FindWhat
		[+] multitag "Find what:"
			[ ] "$1152"
	[+] CheckBox MatchWholeWordOnly
		[+] multitag "Match whole word only"
			[ ] "$1040"
	[+] CheckBox MatchCase
		[+] multitag "Match case"
			[ ] "$1041"
	[+] PushButton FindNext
		[+] multitag "Find Next"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
[ ]
[ ]
[ ] //*****************************************************************
[ ] //
[ ] // Control Panel Devices
[ ]
[+] type DEVICE_DATA is record
	[ ] STRING 	sDevice
	[ ] BOOLEAN bStatus //Started is TRUE
	[ ] STRING	sStartupType
	[ ] BOOLEAN bExists
[ ]
[ ]
[+] window MainWin 		Devices
	[ ] mswnt 	tag "[DialogBox]Devices"
	[ ] msw2000 tag "[DialogBox]Device Manager"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] const sDir = "C:\"
	[ ]
	[ ] // The command line used to invoke the application
	[ ] const sCmdLine = "C:\WINNT\system32\rundll32.exe shell32,Control_RunDLL ""C:\WINNT\System32\srvmgr.cpl"",Devices"
	[ ] // mswnt40 const sCmdLine = "C:\WINNT\system32\rundll32.exe shell32,Control_RunDLL ""C:\WINNT\System32\srvmgr.cpl"",Devices"
	[ ] // msw2000 const sCmdLine = "C:\WINNT\System32\mmc.exe C:\WINNT\system32\devmgmt.msc /s "
	[ ] // The first window to appear when the application is invoked
	[ ] // const wStartup = ?
	[ ]
	[ ] // The list of windows the recovery system is to leave open
	[ ] // const lwLeaveOpen = {?}
	[+] VOID Invoke ()
		[ ] Start (sCmdLine)
	[ ] // Kelly added arguments 3/25/02:
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[+] if (GetGUIType() == msw2000)
			[ ] derived::Close()
		[+] else
			[ ] Close.Click()
	[ ] // Kelly 3/25/02 Commented out the following due to Cognex window references
	[+] // VOID VerifyDevices (LIST OF DEVICE_DATA lsDevices)
		[ ] // DEVICE_DATA ddDevice
		[ ] // INTEGER iLoop
		[ ] // STRING sCurrentDevice
		[ ] // STRING sCurrentStartupType
		[ ] // STRING sDeviceStatus
		[ ] //
		[+] // if !Exists()
			[ ] // Invoke()
		[ ] //
		[+] // if (GetGUIType() == msw2000)
			[ ] // Integer i = 0
			[ ] //
			[+] // for each ddDevice in lsDevices
				[ ] // i = DeviceManagerWindow.AfxFrameOrView42u1.AfxFrameOrView42u1.DeviceList.FindItem(ddDevice.sDevice)
				[+] // if (i > 0)
					[ ] // DeviceManagerWindow.AfxFrameOrView42u1.AfxFrameOrView42u1.DeviceList.Select(ddDevice.sDevice)
					[ ] // DeviceManagerWindow.SizeableRebar1.ReBarWindow321.ToolBar3.Action.Click()
					[ ] // ActionMenu.Properties.Click()
					[ ] // //CognexFrameGrabberDeviceProp.SetActive()
					[ ] // sDeviceStatus = CognexFrameGrabberDeviceProp.General.DeviceStatus.GetText()
					[ ] // //Verify the device status
					[+] // do
						[+] // if (ddDevice.bStatus)
							[ ] // Verify(sDeviceStatus,"This device is working properly.")
						[+] // else
							[ ] // Verify(sDeviceStatus,"This device cannot start. (Code 10)")
					[+] // except
						[ ] // ExceptLog()
					[ ] // CognexFrameGrabberDeviceProp.SetActive()
					[ ] // CognexFrameGrabberDeviceProp.Cancel.Click()
					[ ] // Devices.SetActive()
				[+] // else
					[+] // if ddDevice.bExists == TRUE
							[ ] // LogError ("The device {ddDevice.sDevice} was not found in the Devices list")
		[+] // else
			[ ] //
			[+] // for each ddDevice in lsDevices
				[+] // for iLoop = 1 to Devices.Device.GetItemCount()
					[ ] // Devices.Device.Select (iLoop)
					[ ] // Devices.Startup.Click()
					[ ] // sCurrentDevice = DeviceDescription.Device.GetText()
					[ ] // sCurrentStartupType = DeviceDescription.StartupType.GetSelText()
					[ ] // DeviceDescription.OK.Click()
					[+] // if sCurrentDevice == ddDevice.sDevice
						[ ] // //Verify the device status
						[+] // do
							[+] // if ddDevice.sStartupType == "Disabled"
								[ ] // Verify (Device.Start.IsEnabled(),ddDevice.bStatus,"the device status of {ddDevice.sDevice}")
							[+] // else
								[ ] // Verify (!Device.Start.IsEnabled(),ddDevice.bStatus,"the device status of {ddDevice.sDevice}")
						[+] // except
							[ ] // ExceptLog()
						[ ] // //Verify the device startup type
						[+] // do
							[ ] // Verify (sCurrentStartupType,ddDevice.sStartupType,"the device startup type for {ddDevice.sDevice}")
						[+] // except
							[ ] // ExceptLog()
						[ ] // break
					[+] // if sCurrentDevice > ddDevice.sDevice
						[+] // if ddDevice.bExists == TRUE
							[ ] // LogError ("The device {ddDevice.sDevice} was not found in the Devices list")
						[ ] // break
		[ ] // Close ()
		[ ] // return
	[+] StaticText DeviceText
		[ ] tag "Device"
	[+] StaticText StatusText
		[ ] tag "Status"
	[+] StaticText StartupText
		[ ] tag "Startup"
	[+] ListBox Device
		[ ] tag "Device"
	[+] PushButton Close
		[ ] tag "Close"
	[+] PushButton Start
		[ ] tag "Start"
	[+] PushButton Stop
		[ ] tag "Stop"
	[+] PushButton Startup
		[ ] tag "Startup"
	[+] PushButton HWProfiles
		[ ] tag "HW Profiles"
	[+] PushButton Help
		[ ] tag "Help"
	[ ]
[+] window ChildWin 	DeviceManagerWindow
	[ ] tag "Device Manager on local computer"
	[ ] parent Devices
	[+] CustomWin AfxFrameOrView42u1
		[ ] msw tag "[AfxFrameOrView42u]#1"
		[+] CustomWin AfxFrameOrView42u1
			[ ] msw tag "[AfxFrameOrView42u]#1"
			[+] TreeView DeviceList
				[ ] tag "#1"
	[+] StatusBar StatusBar1
		[ ] tag "#1"
		[+] DynamicText DynamicText1
			[ ] tag "#1"
		[+] DynamicText DynamicText2
			[ ] tag "#2"
		[+] DynamicText DynamicText3
			[ ] tag "#3"
		[+] StaticText StaticText1
			[ ] tag "#1"
	[+] CustomWin SizeableRebar1
		[ ] msw tag "[SizeableRebar]#1"
		[+] CustomWin ReBarWindow321
			[ ] msw tag "[ReBarWindow32]#1"
			[+] ToolBar ToolBar2
				[ ] tag "#2"
				[+] PushButton PushButton1
					[ ] tag "#1"
			[+] ToolBar ToolBar1
				[ ] tag "#1"
				[+] PushButton PushButton1
					[ ] tag "#1"
				[+] PushButton PushButton2
					[ ] tag "#2"
				[+] PushButton PushButton3
					[ ] tag "#3"
				[+] PushButton PushButton4
					[ ] tag "#4"
				[+] PushButton PushButton5
					[ ] tag "#5"
			[+] ToolBar ToolBar3
				[ ] tag "#3"
				[+] PushButton Action
					[ ] tag "Action"
				[+] PushButton View
					[ ] tag "View"
[ ]
[ ] // Kelly 3/25/02 Commented out the following due to Cognex window references
[+] // window DialogBox CognexFrameGrabberDeviceProp
	[ ] // tag "Cognex Frame Grabber * Properties"
	[+] // DialogBox General
		[ ] // tag "General"
		[+] // CustomWin Icon1
			[ ] // msw tag "[Icon]#1"
		[+] // StaticText CognexFrameGrabber8100Text
			[ ] // tag "Cognex Frame Grabber 8100"
		[+] // StaticText DeviceTypeText
			[ ] // tag "Device type:"
		[+] // TextField DeviceType
			[ ] // tag "Device type:"
		[+] // StaticText ManufacturerText
			[ ] // tag "Manufacturer:"
		[+] // TextField Manufacturer
			[ ] // tag "Manufacturer:"
		[+] // StaticText LocationText
			[ ] // tag "Location:"
		[+] // TextField Location
			[ ] // tag "Location:"
		[+] // StaticText DeviceStatusText
			[ ] // tag "Device status"
		[+] // TextField DeviceStatus
			[ ] // tag "Device status"
		[+] // PushButton Troubleshooter
			[ ] // tag "Troubleshooter"
		[+] // StaticText DeviceUsageText
			[ ] // tag "Device usage:"
		[+] // PopupList DeviceUsage
			[ ] // tag "Device usage:"
	[+] // PushButton OK
		[ ] // tag "OK"
	[+] // PushButton Cancel
		[ ] // tag "Cancel"
	[+] // PageList PageList1
		[ ] // tag "#1"
[ ]
[+] window DialogBox 	ActionMenu
	[ ] //tag "#1"
	[ ] tag "bogus tag" //bl 3/15/02 - we need to find a specific tag for this since record ID wants to resolve it all the time
	[ ]
	[+] CustomWin Disable
		[ ] tag "(1:1, 2:6)"
	[+] CustomWin Uninstall
		[ ] tag "(1:1, 3:6)"
	[+] CustomWin ScanForHardwareChanges
		[ ] tag "(1:1, 3:6)"
	[+] CustomWin Properties
		[ ] tag "(1:1, 4:6)"
	[+] CustomWin Help
		[ ] tag "(1:1, 5:6)"
[+] window DialogBox 	DeviceDescription
	[ ] tag "Device"
	[ ] parent Devices
	[+] StaticText DeviceText
		[ ] tag "Device:"
	[+] StaticText Device
		[ ] tag "#2"
	[+] StaticText StartupTypeText
		[ ] tag "Startup Type"
	[+] RadioList StartupType
		[ ] tag "Startup Type"
	[+] PushButton OK
		[ ] tag "OK"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] PushButton Help
		[ ] tag "Help"
[+] window DialogBox 	WelcomeToNetscapeQualityFeedback
	[ ] tag "Welcome to Netscape Quality Feedback Agent - Step 1 of 3"
	[+] PushButton Next
		[+] multitag "Next >"
			[ ] "#2"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "#3"
	[+] PushButton Help
		[+] multitag "Help"
			[ ] "#4"
	[+] StaticText TheNetscapeQualityFeedback
		[+] multitag "The Netscape Quality Feedback Agent is a feature that gathers predefined technical information about Communicator and sends i*"
			[ ] "#1"
	[+] StaticText ClickNextToContinueIfYou
		[+] multitag "Click Next to continue. If you do not want to run the agent right now, click Cancel. You can run this setup wizard by clickin*"
			[ ] "#3"
	[+] CustomWin TalkbackIsATrademarkOf
		[+] msw multitag "[BlackFrame]Talkback is a Trademark of"
			[ ] "[BlackFrame]#2"
	[+] PushButton Back
		[+] multitag "< Back"
			[ ] "#1"
	[+] CustomWin BlackFrame1
		[ ] msw tag "[BlackFrame]#1"
	[+] StaticText UsingTheAgentIsSimpleJu
		[+] multitag "Using the agent is simple - just use this setup wizard to initialize the agent. No information is sent until you can examine e*"
			[ ] "#2"
	[+] StaticText TalkbackIsATrademarkOfText
		[+] multitag "Talkback is a Trademark of"
			[ ] "#5"
	[+] StaticText NetscapeQualityFeedbackAgen
		[+] multitag "Netscape Quality Feedback Agent is based on Full Circle Talkback."
			[ ] "#4"
	[+] StaticText FullCircleSoftwareIncText
		[+] multitag "Full Circle Software, Inc."
			[ ] "#6"
[ ]
[ ]
[ ] //*******************************************************************
[ ] //
[ ] // Display Settings
[+] window MainWin 		DisplayProperties
	[ ] tag "[DialogBox]Display Properties"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] const sDir = "C:\"
	[ ]
	[ ] // The command line used to invoke the application
	[ ] mswnt	const sCmdLine = "C:\WINNT\system32\rundll32.exe shell32,Control_RunDLL ""C:\WINNT\System32\DESK.CPL"",Display"
	[ ] msw2000 const sCmdLine = "C:\WINNT\system32\rundll32.exe shell32.dll,Control_RunDLL ""C:\WINNT\System32\desk.cpl"",Display"
	[ ] // The first window to appear when the application is invoked
	[ ] // const wStartup = ?
	[ ]
	[ ] // The list of windows the recovery system is to leave open
	[ ] // const lwLeaveOpen = {?}
	[+] VOID SetColorSettings (STRING sColorSetting)
		[ ] //this could easily be extended to change the resolution as well
		[+] if !this.Exists ()
			[ ] Invoke ()
		[ ] PageSelector.Select("Settings")
		[+] switch sColorSetting
			[+] case "8 bit"
				[ ] Settings.ColorPalette.Select("256 Colors")
			[+] case "16 bit"
				[ ] mswnt Settings.ColorPalette.Select("65536 Colors")
				[ ] msw2000 Settings.ColorPalette.Select("High Color (16 bit)")
			[+] case "32 bit"
				[ ] mswnt	Settings.ColorPalette.Select("True Color")
				[ ] msw2000 Settings.ColorPalette.Select("True Color (32 bit)")
		[ ] OK.Click()
		[+] switch GetGuiType ()
			[+] case mswnt
				[+] if DisplayPropertiesMessageBox.OK.Exists(3)
					[ ] DisplayPropertiesMessageBox.OK.Click()
			[+] case msw2000
				[+] if DisplayPropertiesMessageBox.OK.Exists(3)
					[ ] DisplayPropertiesMessageBox.OK.Click()
				[+] if MonitorSettings.Yes.Exists(3)
					[ ] MonitorSettings.Yes.Click()
		[ ] return
		[ ]
		[ ]
	[+] DialogBox Settings
		[ ] tag "Settings"
		[+] PopupList ColorPalette
			[+] multitag "Color Palette"
				[ ] "Colors"
		[ ]
		[ ]
		[+] CustomWin BitMap1
			[ ] msw tag "[BitMap]#1"
		[+] StaticText ColorPaletteText
			[ ] tag "Color Palette"
		[+] CustomWin ColorPalette2
			[ ] msw tag "[BitMap]Color Palette"
		[+] StaticText DesktopAreaText
			[ ] tag "Desktop Area"
		[+] StaticText LessText
			[ ] tag "Less"
		[+] Scale Less
			[ ] tag "Less"
		[+] StaticText MoreText
			[ ] tag "More"
		[+] StaticText N1024By768PixelsText
			[ ] tag "1024 by 768 pixels"
		[+] StaticText FontSizeText
			[ ] tag "Font Size"
		[+] PopupList FontSize
			[ ] tag "Font Size"
		[+] StaticText RefreshFrequencyText
			[ ] tag "Refresh Frequency"
		[+] PopupList RefreshFrequency
			[ ] tag "Refresh Frequency"
		[+] PushButton ListAllModes
			[ ] tag "List All Modes"
		[+] PushButton Test
			[ ] tag "Test"
		[+] PushButton DisplayType
			[ ] tag "Display Type"
	[+] PushButton OK
		[ ] tag "OK"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] PushButton Apply
		[ ] tag "Apply"
	[+] PageList PageSelector
		[ ] tag "#1"
[+] window DialogBox 	MonitorSettings
	[ ] tag "Monitor Settings"
	[ ] parent DisplayProperties
	[+] PushButton Yes
		[+] multitag "Yes"
			[ ] "$6"
	[+] PushButton No
		[+] multitag "No"
			[ ] "$7"
	[+] StaticText YourDesktopHasBeenReconfig
		[+] multitag "Your desktop has been reconfigured.  Do you want to keep these settings?"
			[ ] "$-1"
	[+] CustomWin Icon1
		[ ] msw tag "[Icon]$1002"
	[+] StaticText RevertingIn11SecondsText
		[+] multitag "Reverting in 11 seconds"
			[ ] "$1217"
[+] window DialogBox 	DisplayPropertiesMessageBox
	[+] multitag "Display Properties"
		[ ] "Display Settings"
	[ ] parent DisplayProperties
	[+] PushButton OK
		[+] multitag "OK"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
	[+] CustomWin Icon1
		[ ] msw tag "[Icon]$20"
	[+] StaticText WindowsWillNowApplyYourNe
		[+] multitag "Windows will now apply your new desktop settings. This will take a few seconds, during which time your screen may flicker.????*"
			[ ] "$65535"
[ ]
[ ]
[ ] //*******************************************************************
[ ] //
[ ] // Microsoft Outlook window declarations
[ ]
[+] window MainWin 		Outlook
	[ ] tag "[DialogBox]*Microsoft Outlook"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] const sDir = "C:\TEMP"
	[ ]
	[ ] // The command line used to invoke the application
	[ ] const sCmdLine = "C:\Program Files\Microsoft Office\Office\OUTLOOK.EXE "
	[ ]
	[ ] // The first window to appear when the application is invoked
	[ ] // const wStartup = ?
	[ ]
	[ ] // The list of windows the recovery system is to leave open
	[ ] // const lwLeaveOpen = {?}
	[ ]
	[+] VOID Invoke (STRING sProfile optional)
		[ ] STRING sErrorMsg
		[ ]
		[+] if !IsNull (sProfile)
			[+] do
				[ ] Start (sCmdLine + '/profile "{sProfile}"')
			[+] except
				[+] if MessBox.Exists ()
					[ ] sErrorMsg =  MessBox.Message.GetText()
					[ ] MessBox.OK.Click()
					[ ] AppError ("Could not start MicroSoft Outlook - the following message was received: {sErrorMsg}")
				[+] else
					[ ] AppError ("Could not start MicroSoft Outlook")
		[+] else
			[+] do
				[ ] Start (sCmdLine)
			[+] except
				[+] if MessBox.Exists ()
					[ ] sErrorMsg =  MessBox.Message.GetText()
					[ ] MessBox.OK.Click()
					[ ] AppError ("Could not start MicroSoft Outlook - the following message was received: {sErrorMsg}")
				[+] else
					[ ] AppError ("Could not start MicroSoft Outlook")
		[ ] return
	[+] VOID Close(BOOLEAN bSetActive optional, BOOLEAN bConfirm optional)
		[ ] CloseBox.Click()
	[ ]
	[+] CustomWin MsoDockTop
		[+] msw multitag "[MsoCommandBarDock]MsoDockTop"
			[ ] "[MsoCommandBarDock]$0"
		[+] CustomWin Standard
			[+] msw multitag "[MsoCommandBar]Standard"
				[ ] "[MsoCommandBar]$0[2]"
			[+] TextField TextField1
				[ ] tag "$24579444"
		[+] CustomWin MenuBar
			[+] msw multitag "[MsoCommandBar]Menu Bar"
				[ ] "[MsoCommandBar]$0[1]"
	[+] StatusBar StatusBar1
		[ ] tag "$101"
		[+] DynamicText DynamicText1
			[ ] tag "#1"
	[+] CustomWin AfxWnd2
		[ ] msw tag "[AfxWnd]$104"
	[+] CustomWin TreeViewContainer
		[ ] msw tag "[rctrl_renwnd32]#1"
		[+] CustomWin SUPERGRID1
			[ ] msw tag "[SUPERGRID]$101"
			[+] ScrollBar ScrollBar1
				[ ] tag "$4693"
		[+] TreeView Folders
			[ ] tag "#1"
	[+] CustomWin ListViewContainer
		[ ] msw tag "[AfxWnd]$103"
		[+] CustomWin ShortcutBar
			[+] msw multitag "[rctrl_renwnd32]ShortcutBar"
				[ ] "[rctrl_renwnd32]$1"
			[+] CustomWin FIScrollWnd
				[+] msw multitag "[rctrl_renwnd32]FIScrollWnd"
					[ ] "[rctrl_renwnd32]$0"
				[+] ListView Navigator
					[ ] tag "$0"
[ ]
[ ]
[ ] //*******************************************************************
[ ] //
[ ] // System Properties Dialog
[ ] // contains method to set Environment variables using GUI
[+] window MainWin 	SystemProperties
	[ ] tag "[DialogBox]System Properties"
	[ ]
	[ ] // The working directory of the application when it is invoked
	[ ] //const sDir = "C:\WINNT\Profiles\*\Desktop" //this may be different on each machine bl 0625/02
	[ ]
	[ ] // The command line used to invoke the application
	[ ] //this should be the same on 32 bit systems
	[ ] const sCmdLine = "C:\WINNT\system32\rundll32.exe shell32,Control_RunDLL SYSDM.CPL,System"
	[ ]
	[ ] // The first window to appear when the application is invoked
	[ ] // const wStartup = ?
	[ ]
	[ ] // The list of windows the recovery system is to leave open
	[ ] // const lwLeaveOpen = {?}
	[ ]
	[ ]
	[+] DialogBox General
		[ ] tag "General"
		[ ]
		[+] CustomWin BitMap1
			[ ] msw tag "[BitMap]#1"
		[+] StaticText SystemText
			[ ] tag "System:"
		[+] StaticText MicrosoftWindowsNTText
			[ ] tag "Microsoft Windows NT"
		[+] StaticText N4001381Text
			[ ] tag "4.00.1381"
		[+] StaticText IE550031050106Text
			[ ] tag "IE 5 5.00.3105.0106"
		[+] StaticText RegisteredToText
			[ ] tag "Registered to:"
		[+] TextField RegisteredTo1
			[ ] tag "Registered to:[1]"
		[+] TextField RegisteredTo2
			[ ] tag "Registered to:[2]"
		[+] TextField RegisteredTo3
			[ ] tag "Registered to:[3]"
		[+] TextField RegisteredTo4
			[ ] tag "Registered to:[4]"
		[+] StaticText ComputerText
			[ ] tag "Computer:"
		[+] CustomWin BitMap2
			[ ] msw tag "[BitMap]#2"
		[+] StaticText X86Family6Model8Stepping
			[ ] tag "x86 Family 6 Model 8 Stepping 6"
		[+] StaticText ATATCOMPATIBLEText
			[ ] tag "AT?AT COMPATIBLE"
		[+] StaticText N391540KBRAM1Text
			[ ] tag "391,540 KB RAM[1]"
		[+] StaticText N391540KBRAM2Text
			[ ] tag "391,540 KB RAM[2]"
		[+] StaticText StaticText11
			[ ] tag "#11"
	[+] DialogBox Environment
		[ ] tag "Environment"
		[+] VOID Invoke ()
			[ ] SystemProperties.Invoke ()
			[ ] PageList1.Select ("Environment")
			[ ] return
		[ ] // function:  UpdateEnvVariable (sVariable, sValue, vtVariableType)
		[ ] // parameter: sVariable: Name of the Environment Variable to set. STRING.
		[ ] // parameter: sValue: The value of the Environment Variable to set. STRING.
		[ ] // parameter: vtVariableType: The type of Environment Variable to set: Systm or User. ENV_VARIABLE_TYPE (Enum).
		[ ] // notes:     Sets an Environment Variable via the Windows GUI.
		[+] VOID UpdateEnvVariable (STRING sVariable, STRING sValue, ENV_VARIABLE_TYPE vtVariableType optional)
			[ ]
			[ ] //Invoke the SystemProperties dialog
			[ ] Invoke ()
			[ ]
			[ ] //Set the Variable Type to System if it is not specified
			[+] if IsNull (vtVariableType)
				[ ] vtVariableType = System
			[ ]
			[ ] //Set the focus to the desired Variable Type
			[+] if vtVariableType == System
				[ ] SystemProperties.Environment.SystemVariables.Select(1)
			[+] else
				[ ] SystemProperties.Environment.UserVariables.Select(1)
			[ ]
			[ ] //Set the value of the Environment Variable
			[ ] SystemProperties.Environment.Variable.SetText (sVariable)
			[ ] SystemProperties.Environment.Value.SetText(sValue)
			[ ] SystemProperties.Environment.Set.Click()
			[ ]
			[ ] //Dismiss the dialog
			[ ] SystemProperties.OK.Click()
			[ ]
			[ ] return
			[ ]
		[+] StaticText SystemVariablesText
			[ ] tag "System Variables:"
		[+] ListView SystemVariables
			[ ] tag "System Variables:"
			[+] Header Header1
				[ ] tag "#1"
				[+] StaticText VariableText
					[ ] tag "Variable"
				[+] StaticText ValueText
					[ ] tag "Value"
		[+] StaticText UserVariablesLabel
			[ ] tag "User Variables for LeSuerB:"
		[+] ListView UserVariables
			[ ] tag "User Variables for*"
			[+] Header Header1
				[ ] tag "#1"
				[+] StaticText VariableText
					[ ] tag "Variable"
				[+] StaticText ValueText
					[ ] tag "Value"
		[+] StaticText VariableText
			[ ] tag "Variable:"
		[+] TextField Variable
			[ ] tag "Variable:"
		[+] StaticText ValueText
			[ ] tag "Value:"
		[+] TextField Value
			[ ] tag "Value:"
		[+] PushButton Set
			[ ] tag "Set"
		[+] PushButton Delete
			[ ] tag "Delete"
	[+] PushButton OK
		[ ] tag "OK"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] PushButton Apply
		[ ] tag "Apply"
	[+] PageList PageList1
		[ ] tag "#1"
[ ]
[ ]
[ ] //*******************************************************************
[ ] //
[ ] // Program Manager Declaration
[+] window DialogBox 	ProgramManager
	[ ] tag "Program Manager"
	[ ]
	[ ] //methods
	[+] BOOLEAN ShortCutExists(STRING sShortCut)
		[+] if Desktop.FindItem(sShortCut) == 0
			[ ] return (FALSE)
		[+] else
			[ ] return (TRUE)
	[+] VOID VerifyShortCutExists(STRING sShortCut, BOOLEAN bExpectExists)
		[ ]
		[+] do
			[ ] Verify (ShortCutExists(sShortCut), bExpectExists,"the ShortCut {sShortCut} exists on the Desktop")
			[+] if bExpectExists
				[ ] print ("Verified the ShortCut {sShortCut} is displayed on the Desktop")
			[+] else
				[ ] print ("Verified the ShortCut {sShortCut} is not displayed on the Desktop")
		[+] except
			[ ] ExceptLog()
		[ ]
		[ ] return
	[ ]
	[ ]
	[+] ListView Desktop
		[ ] tag "#1"
	[ ]
[ ]
[ ]
[ ]
[ ] // MS Excel declarations and methods
[+] window DialogBox 	MicrosoftExcel
	[ ] tag "Microsoft Excel*.xls"
	[ ]
	[+] VOID AddColumns (STRING sStartingColumn, INTEGER iNumColumns)
		[ ] INTEGER iLoop
		[ ] SetFocusCell (sStartingColumn)
		[ ]
		[+] for iLoop = 1 to iNumColumns
			[ ] MicrosoftExcel.TypeKeys ("<ALT-i>c")
		[ ]
		[ ] return
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] INTEGER iMessage
		[ ] iMessage = 1
		[ ]
		[ ] SetActive ()
		[ ] sleep (1)
		[ ] TypeKeys ("<Alt-f>x")
		[ ] sleep (1)
		[ ]
		[+] while (MicrosoftExcelMessageBox.No.Exists (3)) && (iMessage < 5)
			[ ] MicrosoftExcelMessageBox.No.Click ()
			[ ] iMessage++
		[ ]
		[ ]
		[ ]
		[ ] return
	[+] VOID Copy ()
		[ ] TypeKeys ("<Alt-e>c")
		[ ] return
	[+] VOID CopySheet ()
		[ ] SelectAll ()
		[ ] MicrosoftExcel.TypeKeys ("<Ctrl-c>")
		[ ] return
	[+] VOID CopySheetToSheet (STRING sSheetToCopy, STRING sSheetToPaste)
		[ ] GoToSheet (sSheetToCopy)
		[ ]
		[ ] CopySheet ()
		[ ]
		[ ] GoToSheet (sSheetToPaste)
		[ ]
		[ ] SelectAll ()
		[ ]
		[ ] Paste ()
		[ ]
		[ ] return
	[+] VOID CreateNewSheet()
		[ ] TypeKeys ("<Alt-i>w")
		[ ]
		[ ] return
	[+] VOID Find (STRING sFindWhat, BOOLEAN bEntireCells)
		[ ] ExcelFind.Invoke ()
		[ ] ExcelFind.FindWhat.TypeKeys (sFindWhat)
		[ ]
		[+] if bEntireCells
			[ ] ExcelFind.TypeKeys("<ALT-t>")
			[ ] ExcelFind.TypeKeys("<ALT-o>")
		[ ]
		[ ] ExcelFind.TypeKeys("<ENTER>")
		[ ] ExcelFind.Close ()
		[ ] return
	[+] STRING GetFocusCell ()
		[ ] STRING sCell
		[ ] sCell = MicrosoftExcel.EditCell.SelectCell.GetText()
		[ ] return (sCell)
	[+] STRING GetCellValue (STRING sCell)
		[ ] SetFocusCell(sCell)
		[ ] sleep(1)
		[ ] TypeKeys ("<Alt-e><c>")
		[ ] sleep(5)
		[ ] return (Clipboard.GetText()[1])
	[+] VOID GoToA1 ()
		[ ] MicrosoftExcel.TypeKeys ("<Ctrl-Home>")
		[ ] return
	[+] VOID GoToSheet (STRING sReference)
		[ ] ExcelGoTo.Invoke ()
		[ ] ExcelGoTo.Reference.TypeKeys (sReference)
		[ ] ExcelGoTo.TypeKeys ("<ENTER>")
		[ ] return
	[+] VOID Paste ()
		[ ] TypeKeys ("<Alt-e>p")
		[ ] return
	[+] VOID PasteAll ()
		[ ] SelectAll ()
		[ ] TypeKeys ("<CTRL-v>")
		[ ] return
	[+] VOID PasteSpecialValues ()
		[ ] TypeKeys ("<Alt-e>s")
		[ ] ExcelPasteSpecial.Exists (3)
		[ ]
		[ ] ExcelPasteSpecial.TypeKeys ("<Alt-v>")
		[ ] ExcelPasteSpecial.TypeKeys ("<ENTER>")
		[ ] return
	[+] VOID ParsePage (STRING sIniFile,STRING sIniTag,LIST OF STRING lsCells)
		[ ]
		[ ] HINIFILE		hiPageValues = IniFileOpen (sIniFile)
		[ ] STRING 			sCell
		[ ]
		[+] for each sCell in lsCells
			[ ] IniFileSetValue (hiPageValues, sIniTag, sCell, GetCellValue(sCell))
		[ ]
		[ ] IniFileClose (hiPageValues)
		[ ] return
	[+] VOID SaveAs (STRING sWorksheetName)
		[ ] ExcelSaveAs.Invoke ()
		[ ] ExcelSaveAs.SaveFile (sWorksheetName)
		[ ] return
		[ ]
	[+] VOID SelectCellRowToEnd (STRING sStartingCell)
		[ ]
		[ ] SetFocusCell (sStartingCell)
		[ ] PressKeys ("<SHIFT>")
		[ ] PressKeys ("<END>")
		[ ] ReleaseKeys ("<END>")
		[ ] PressKeys ("<RIGHT>")
		[ ] ReleaseKeys ("<RIGHT>")
		[ ] ReleaseKeys ("<SHIFT>")
		[ ]
		[ ] return
	[+] VOID SetFocusCell (STRING sCell)
		[ ] MicrosoftExcel.EditCell.SelectCell.SetText (sCell)
		[ ] MicrosoftExcel.EditCell.SelectCell.TypeKeys ("<ENTER>")
		[ ]
		[ ] return
	[+] VOID SetCellValue (STRING sCell, STRING sValue)
		[ ] SetFocusCell(sCell)
		[ ]
		[ ] TypeKeys (sValue)
		[ ]
		[ ] EditCell.AcceptCellEntry.Click()
		[ ]
		[ ] return
	[+] VOID SelectAll ()
		[ ] MicrosoftExcel.TypeKeys ("<Ctrl-a>")
		[ ]
		[ ] //bl: 7/30/04 - original approached saved in case we need to revert to it
		[ ] // POINT p
		[ ] //
		[ ] // MicrosoftExcel.EditCell.SelectCell.MoveMouse()
		[ ] //
		[ ] // p = Cursor.GetPosition()
		[ ] //
		[ ] // p.y = p.y - 25
		[ ] // p.x = p.x - 40
		[ ] //
		[ ] // Click (1, p.x, p.y)
		[ ] //
		[ ] // sleep (3)
		[ ]
		[ ] return
	[ ]
	[+] CustomWin EnterCellValue
		[ ] msw tag "[EXCEL<]#1"
	[+] CustomWin EditCell
		[ ] msw tag "[EXCEL;]#1"
		[+] ComboBox SelectCell
			[ ] tag "#1"
			[ ]
			[+] STRING GetText ()
				[ ] STRING sText
				[ ]
				[ ] Click (1,10,8)
				[ ] sleep(1)
				[ ] TypeKeys ("<CTRL-c>")
				[ ] sText = Clipboard.GetText ()[1]
				[ ]
				[ ] return (sText)
		[+] Control CancelCellEntry
			[ ] tag "(2:2,1:1)"
		[+] Control AcceptCellEntry
			[ ] tag "(4:4,1:1)"
	[+] CustomWin ToolBarContainer
		[ ] msw tag "[EXCEL2]#1"
		[+] CustomWin MainMenu
			[ ] msw tag "[MsoCommandBar]Worksheet Menu Bar"
		[+] CustomWin StandardTools
			[ ] msw tag "[MsoCommandBar]Standard"
			[+] TextField Zoom
				[ ] tag "#1"
		[+] CustomWin FormattingTools
			[ ] msw tag "[MsoCommandBar]Formatting"
			[+] TextField PointSize
				[ ] tag "#2"
			[+] TextField Font
				[ ] tag "#1"
	[+] CustomWin StatusBar
		[ ] msw tag "[EXCEL4]#1"
[+] window DialogBox 	ExcelFind
	[+] multitag "Find"
		[ ] "Find and Replace"
	[ ] parent MicrosoftExcel
	[ ]
	[ ] //methods
	[+] VOID Invoke ()
		[ ] MicrosoftExcel.TypeKeys("<Esc>")
		[+] if !Exists()
			[ ] MicrosoftExcel.TypeKeys ("<Ctrl-f>")
		[ ] return
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] TypeKeys("<ALT-F4>")
		[ ] return
	[ ]
	[+] CustomWin FindWhat
		[ ] tag "[EDTBX]#1"
[+] window DialogBox 	ExcelReplace
	[+] multitag "Replace"
		[ ] "Find and Replace"
	[ ] parent MicrosoftExcel
	[ ]
	[+] VOID Close (BOOLEAN bConfirm optional, BOOLEAN bSetActive optional)
		[ ] SetActive ()
		[ ] TypeKeys ("<ALT-F4>")
		[ ] return
	[+] VOID Invoke ()
		[ ] MicrosoftExcel.TypeKeys ("<Ctrl-h>")
		[ ] return
	[+] VOID SearchAndReplace (STRING sTarget, STRING sReplaceWith, BOOLEAN bAllOccurrences)
		[ ]
		[+] if !Exists()
			[ ] Invoke ()
		[ ]
		[ ] FindWhat.TypeKeys (sTarget)
		[ ] ReplaceWith.TypeKeys(sReplaceWith)
		[ ]
		[ ]
		[+] if bAllOccurrences
			[ ] TypeKeys ("<Alt-a>")
		[+] else
			[ ] TypeKeys ("<Alt-f>")
			[ ] TypeKeys ("<Alt-r>")
		[ ]
		[+] if ExcelMessageBox.Exists(2)
			[ ] LogWarning("MessageBox displayed")
			[ ] ExcelMessageBox.OK.Click()
		[ ]
		[+] if Exists (1)
			[ ] Close ()
		[ ]
		[ ] return
	[ ]
	[+] CustomWin FindWhat
		[ ] tag "[EDTBX]#1"
	[+] CustomWin ReplaceWith
		[ ] tag "[EDTBX]#2"
[+] window DialogBox 	ExcelMessageBox
	[ ] tag "Microsoft Excel"
	[ ] parent ExcelReplace
	[+] PushButton OK
		[+] multitag "OK"
			[ ] "$2"
	[+] CustomWin Icon1
		[ ] msw tag "[Icon]$-1"
	[+] CustomWin Message
		[+] msw multitag "[MSOUNISTAT]Microsoft Excel cannot find matching data to replace.*"
			[ ] "[MSOUNISTAT]$-1"
[+] window DialogBox 	ExcelGoTo
	[ ] tag "Go To"
	[ ] parent MicrosoftExcel
	[ ]
	[+] VOID Invoke ()
		[ ] MicrosoftExcel.TypeKeys ("<Ctrl-g>")
		[ ] return
	[ ]
	[+] CustomWin Reference
		[ ] tag "[EDTBX]#1"
	[+] ScrollBar ScrollBar1
		[ ] tag "$20"
[+] window DialogBox 	ExcelInsert
	[ ] tag "Insert"
	[ ] parent MicrosoftExcel
	[+] ListView Items
		[ ] tag "$1000"
	[+] PushButton OK
		[+] multitag "OK"
			[ ] "$1"
	[+] StaticText PreviewText
		[+] multitag "Preview"
			[ ] "$1002"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
	[+] ToolBar ToolBar1
		[ ] tag "$102"
		[+] RadioList RadioList1
			[ ] tag "$1007"
	[+] PageList PageList1
		[ ] tag "$1004"
[+] window DialogBox 	ExcelNew
	[ ] tag "New"
	[ ] parent MicrosoftExcel
	[+] VOID Invoke ()
		[ ] MicrosoftExcel.TypeKeys ("<Alt-f>n")
		[ ] return
	[+] ListView Items
		[ ] tag "$1000"
	[+] StaticText PreviewText
		[+] multitag "Preview"
			[ ] "$1002"
	[+] PushButton OK
		[+] multitag "OK"
			[ ] "$1"
	[+] PushButton Cancel
		[+] multitag "Cancel"
			[ ] "$2"
	[+] ToolBar ToolBar1
		[ ] tag "$102"
		[+] RadioList RadioList1
			[ ] tag "$1007"
	[+] PageList PageList1
		[ ] tag "$1004"
[+] window DialogBox 	ExcelPasteSpecial
	[ ] tag "Paste Special"
	[ ] parent MicrosoftExcel
	[ ]
[+] window DialogBox 	ExcelFileOpen
	[ ] tag "../Open"
	[ ]
	[ ] //methods
	[+] VOID Invoke ()
		[ ] MicrosoftExcel.TypeKeys ("<ALT-f>o")
		[ ] return
	[+] VOID OpenFile (STRING sFileName)
		[+] if !Exists()
			[ ] Invoke ()
		[ ] FileName.TypeKeys (sFileName)
		[ ] TypeKeys ("<ENTER>")
		[ ]
		[ ] return
	[ ]
	[+] CustomWin CSnakeList
		[ ] msw tag "[Snake List]CSnakeList"
		[+] CustomWin OpenListView1
			[ ] msw tag "[OpenListView]#1"
	[+] CustomWin FOToolbarWindow1
		[ ] msw tag "[FO Toolbar Window]#1"
		[+] ToolBar ToolBar1
			[ ] tag "#1"
			[+] PushButton PushButton1
				[ ] tag "#1"
			[+] PushButton PushButton2
				[ ] tag "#2"
			[+] PushButton PushButton3
				[ ] tag "#3"
			[+] PushButton PushButton4
				[ ] tag "#4"
			[+] RadioList RadioList1
				[ ] tag "#1"
			[+] PushButton PushButton5
				[ ] tag "#5"
	[+] CustomWin FileName
		[ ] msw tag "[RichEdit20W]#1"
	[+] CustomWin RichEdit20W2
		[ ] msw tag "[RichEdit20W]#2"
[+] window DialogBox 	ExcelSaveAs
	[ ] tag "../Save As"
	[ ]
	[ ] //methods
	[ ]
	[+] VOID Invoke ()
		[ ] MicrosoftExcel.TypeKeys("<ALT-f>a")
		[ ] return
	[+] VOID SaveFile (STRING sFileName)
		[+] if !Exists()
			[ ] Invoke ()
		[ ] FileName.TypeKeys (sFileName)
		[ ] TypeKeys ("<ENTER>")
		[ ]
		[ ] return
	[ ]
	[+] CustomWin CSnakeList
		[ ] msw tag "[Snake List]CSnakeList"
		[+] CustomWin OpenListView1
			[ ] msw tag "[OpenListView]#1"
	[+] CustomWin FOToolbarWindow1
		[ ] msw tag "[FO Toolbar Window]#1"
		[+] ToolBar ToolBar1
			[ ] tag "#1"
			[+] PushButton PushButton1
				[ ] tag "#1"
			[+] PushButton PushButton2
				[ ] tag "#2"
			[+] PushButton PushButton3
				[ ] tag "#3"
			[+] RadioList RadioList1
				[ ] tag "#1"
			[+] PushButton PushButton4
				[ ] tag "#4"
	[+] CustomWin FileName
		[ ] tag "[RichEdit20W]#1"
[+] window ChildWin 	ExcelWorksheet
	[ ] tag "*.xls"
	[ ] parent MicrosoftExcel
	[+] ScrollBar ScrollBar1
		[ ] tag "#1"
	[+] ScrollBar ScrollBar2
		[ ] tag "#2"
	[+] CustomWin XLCTL3
		[ ] msw tag "[XLCTL]#3"
	[+] CustomWin XLCTL1
		[ ] msw tag "[XLCTL]#1"
	[+] CustomWin XLCTL2
		[ ] msw tag "[XLCTL]#2"
[+] window DialogBox 	MicrosoftExcelMessageBox
	[ ] tag "Microsoft Excel"
	[ ] parent MicrosoftExcel
	[+] PushButton Yes
		[ ] tag "Yes"
	[+] PushButton No
		[ ] tag "No"
	[+] PushButton Cancel
		[ ] tag "Cancel"
	[+] CustomWin Icon1
		[ ] msw tag "[Icon]#1"
	[+] CustomWin DoYouWantToSaveTheChange
		[ ] msw tag "[MSOUNISTAT]Do you want to save the changes you made to 'Book1'"
[ ]
[ ] //*******************************************************************
[ ] //
[ ]
[ ] // // testcase to generate help file
[-] // testcase GenHelp () appstate none
	[ ] // INTEGER 		iParams = 0
	[ ] // LIST OF STRING 	lsFuncs, lsHelp
	[ ] // STRING			sLine
	[ ] //
	[ ] // // first do funcs
	[ ] // // ListRead (lsFuncs, "C:\SILKGEN\SilkTest\Includes\SILKGEN_Functions.inc")
	[ ] // //
	[ ] // // lsHelp = {"#********************************************"}
	[ ] // // ListAppend (lsHelp, "")
	[ ] // // ListAppend (lsHelp, "group:     Star Quality functions")
	[ ] // //
	[+] // // for each sLine in lsFuncs
		[ ] // // Ltrim (sLine)
		[+] // // if StrPos ("// function:", sLine)
			[ ] // // ListAppend (lsHelp, "")  		// add a blank line
			[ ] // // ListAppend (lsHelp, "function:"+ GetField (sLine, "function:", 2))
			[ ] // // iParams = 0
		[+] // // else
			[+] // // if StrPos ("// returns:", sLine)
				[ ] // // ListAppend (lsHelp, "returns:"+ GetField (sLine, "returns:", 2))
			[+] // // else
				[+] // // if StrPos ("// parameter:", sLine)
					[ ] // // iParams = iParams + 1
					[+] // // if iParams <= 8			// help chokes if > 8 parameters
						[ ] // // ListAppend (lsHelp, "parameter:"+ GetField (sLine, "parameter:", 2))
				[+] // // else
					[+] // // if StrPos ("// notes:", sLine)
						[ ] // // ListAppend (lsHelp, "notes:"+ GetField (sLine, "notes:", 2))
	[ ] // //
	[ ] // // ListWrite (lsHelp, "C:\SILKGEN\SilkTest\Includes\help.txt")
	[ ] //
	[ ] //
	[ ] //
	[ ] // // add on the browser functions
	[ ] //
	[ ] // ListAppend (lsHelp, "")
	[ ] // ListAppend (lsHelp, "#********************************************")
	[ ] // ListAppend (lsHelp, "")
	[ ] // ListAppend (lsHelp, "group:     Star Quality Browser functions")
	[ ] //
	[ ] //
	[ ] // ListRead (lsFuncs, "C:\SILKGEN\SilkTest\Includes\SILKGEN_Browser.inc")
	[ ] //
	[+] // for each sLine in lsFuncs
		[ ] // Ltrim (sLine)
		[+] // if StrPos ("// function:", sLine)
			[ ] // ListAppend (lsHelp, "")  		// add a blank line
			[ ] // ListAppend (lsHelp, "function:"+ GetField (sLine, "function:", 2))
			[ ] // iParams = 0
		[+] // else
			[+] // if StrPos ("// returns:", sLine)
				[ ] // ListAppend (lsHelp, "returns:"+ GetField (sLine, "returns:", 2))
			[+] // else
				[+] // if StrPos ("// parameter:", sLine)
					[ ] // iParams = iParams + 1
					[+] // if iParams <= 8			// help chokes if > 8 parameters
						[ ] // ListAppend (lsHelp, "parameter:"+ GetField (sLine, "parameter:", 2))
				[+] // else
					[+] // if StrPos ("// notes:", sLine)
						[ ] // ListAppend (lsHelp, "notes:"+ GetField (sLine, "notes:", 2))
	[ ] //
	[ ] // ListWrite (lsHelp, "C:\SILKGEN\SilkTest\Includes\SILKGEN_help.txt")
	[ ] // //
	[ ] //
	[ ] // return
[ ]
