[ ] //	**************************************************************************************************** //
[ ] 
[ ] //	File Name			:	SILKGEN_ErrorSnapShotFunc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	ErrorSnapShot manipulation functions are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		04/06/09	Amiya Pattnayak	Created
	[ ] //		04/11/09	Amiya Pattnayak Modified
	[ ] //					Removed the optional parameter -> STRING sBmpPath optional and modified accordingly
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //								ERROR/SNAPSHOT RELATED FUNCTIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // function:  	LogErrorSnapBmp (sErrorString, [sBmpPath,bHaltTestcase])
[ ] // parameter: 	sErrorString: Informational message to be used in logging the error. STRING.
[ ] // parameter: 	bHaltTestcase: Switch that specifies whether to halt the testcase on error. Default is FALSE (optional). BOOLEAN
[ ] // returns:   	void
[ ] // Action:    	Captures a bitmap of the entire screen in a date time stamped file, and then logs the specified error.
[ ] //			  	Default is the ProjectHome\SilkTest\ErrorBmps,
[ ] //				else it will be stored in the path specified in the Propertes setting.
[ ] //				The local machine and the remote machine's 'ErrorBmps' path should be the same in-order to view the bitmap
[ ]
[ ]
[ ]
[ ] //Original
[+] // VOID LogErrorSnapBmp (STRING sErrorString, STRING sBmpPath optional, BOOLEAN bHaltTestcase optional)
	[+] // do
		[ ] //
		[ ] // //NOTES for host->target usage:
		[ ] // //1. SCRIPTROOT must be set on both the host and target machine
		[ ] // //2. If your ErrorMode = DiffBitmaps, for the bitmap viewer to display error bitmaps in results file,
		[ ] // //   SCRIPTROOT must be set to the same path on host and target machines. This is a requirement of the
		[ ] // //   SilkTest results file
		[ ] // //3. Do not set the agent name in Runtime options to your machine name if the target machine is the local machine
		[ ] //
		[ ] // // STRING sErrorBmp, sScriptRoot, sBmpDir, sRmpFile, sTempErrorBmp, sScriptRootNoDrive, sScriptRootDrive
		[ ] // // HMACHINE hTargetMachine = GetMachine()
		[ ] // // STRING sTargetMachineName = GetMachineName ()
		[ ] // // HMACHINE hLocalMachine
		[ ] // // BOOLEAN bLocalAgent = TRUE
		[ ] // // BOOLEAN bConnectError = FALSE
		[ ] //
		[ ] // FUNCTION_DATA 	fdI
		[ ] //
		[ ] // STRING 			sErrorBmp, sErrorMsg, sBmpDir, sRmpFile, sTempErrorBmp, sScriptRoot
		[ ] // STRING			sProjectRoot, sProjectRootNoDrive, sProjectRootDrive
		[ ] //
		[ ] // BOOLEAN 		bLocalAgent 	= TRUE
		[ ] // BOOLEAN 		bConnectError 	= FALSE
		[ ] //
		[ ] // //const 			STRING sLocalMachine 	= "(local)"
		[ ] // STRING 			sTargetMachineName 		= Properties_KeyValues.sTargetMachine
		[ ] //
		[ ] // HMACHINE 		hLocalMachine	= GetMachine ()
		[ ] // HMACHINE 		hTargetMachine
		[ ] //
		[ ] //
		[ ] //
		[ ] //
		[ ] // //initialize sScriptRoot
		[ ] // sScriptRoot = PROJECT_HOME
		[ ] //
		[ ] // //determine whether the test is running a local or remote machine
		[+] // if GetMachineName () != sLocalMachine
			[ ] // bLocalAgent = FALSE
		[ ] //
		[ ] // //set bHaltTestcase to FALSE if it is not passed in
		[+] // if IsNull(bHaltTestcase)
			[ ] // bHaltTestcase = FALSE
		[ ] //
		[ ] // // if the trailing slash was not supplied on the destination path, add it
		[+] // if !IsNull (sBmpPath)
			[+] // if SubStr (sBmpPath, Len (sBmpPath), 1) != "\"
				[ ] // sBmpDir = sBmpPath + "\"
		[+] // else
			[ ] // // See if ROOT is defined, and if so store the bitmaps there
			[ ] // // if the trailing slash was not supplied on the destination path, add it
			[+] // if sScriptRoot != ""
				[+] // if SubStr (sScriptRoot, Len (sScriptRoot), 1) != "\"
					[ ] // sBmpDir = sScriptRoot + "\"
				[ ] // sBmpDir = sBmpDir + "ErrorBmps\"
				[ ] // MakeDir (sBmpDir,TRUE)
			[+] // else
				[ ] // sBmpDir = ""
		[ ] //
		[ ] // //the behavior of this function is controlled by an Enviroment variable called ErrorMode. If it is not set
		[ ] // //the first case DiffBitmaps will be executed
		[+] // switch ("{HOST_GetEnv ('ErrorMode')}")
			[ ] //
			[+] // case "DiffBitmaps", "", NULL
				[+] // if (bLocalAgent)
					[+] // withoptions
						[ ] // // Turn the bitmap match count to 0 to handle blinking cursors, etc
						[ ] // BindAgentOption (OPT_BITMAP_MATCH_COUNT, 0)
						[ ] //
						[ ] // // See if PROJECT_HOME is defined, and if so store the bitmaps there
						[ ] // sProjectRoot = PROJECT_HOME
						[ ] //
						[ ] // // Creating the 'ErrorBmps' folder in the path specified in the .properties file
						[+] // if Properties_KeyValues.sLocalMachineErrorDir != ""
							[ ] // // if the trailing slash was not supplied on the destination path, add it
							[+] // if SubStr (Properties_KeyValues.sLocalMachineErrorDir, Len (sProjectRoot), 1) != "\"
								[ ] // sBmpDir = Properties_KeyValues.sLocalMachineErrorDir + "\"
							[ ] // sBmpDir = sBmpDir + "ErrorBmps\"
							[ ] // MakeDir (sBmpDir)
						[ ] //
						[ ] // // Crating the 'ErrorBmps' folder in the default project path
						[+] // else if sProjectRoot != ""
							[ ] // // if the trailing slash was not supplied on the destination path, add it
							[+] // if SubStr (sProjectRoot, Len (sProjectRoot), 1) != "\"
								[ ] // sBmpDir = sProjectRoot + "\"
							[ ] // // Creating 'ErrorBmps' folder inside 'SilkTest' folder, which will be the default path for 'ErrorBmps'
							[ ] // sBmpDir = sBmpDir + "SilkTest\" + "ErrorBmps\"
							[ ] // MakeDir (sBmpDir)
							[ ] //
						[+] // else
							[ ] // sBmpDir = ""
						[ ] //
						[ ] // // Build a name for the error bmp using the current date time stamp
						[ ] // sTempErrorBmp = "Error{CreateCurrentDTSString ()}.bmp"
						[ ] // sErrorBmp = sBmpDir + sTempErrorBmp
						[ ] //
						[ ] // // copy the bogus bitmap to the newly created file name
						[ ] // CopyOverwriteFile ("{HOST_GetEnv("SILKGEN_HOME")}\Bmps\SILKGEN_Mock.bmp", sErrorBmp, TRUE)
						[ ] //
						[ ] // //adds the stack trace to the results file
						[ ] // ExceptPrint()
						[ ] //
						[ ] // // finally log the last error seen
						[ ] // LogWarning (ExceptData ())
						[+] // do
							[ ] // Desktop.VerifyBitmap (sErrorBmp)
						[+] // except
							[+] // // if !bLocalAgent
								[ ] // // //strip the extension from the bitmap file
								[ ] // // sRmpFile = GetField (sTempErrorBmp,".bmp", 1)
								[ ] // //
								[ ] // // //connect to the local machine to perform the copy
								[ ] // // //this is done because there may be permission problems attempting to copy from remote to local machine
								[+] // // do
									[ ] // // hLocalMachine = Connect (sLocalMachine)
								[+] // // except
									[ ] // // ExceptLog ()
									[ ] // // bConnectError = TRUE
									[ ] // // DisconnectAll()
									[ ] // // sleep(5)
									[ ] // // hLocalMachine = Connect (sLocalMachine)
								[ ] // //
								[ ] // // //separate the drive from the path
								[ ] // // sProjectRootNoDrive = GetField (PROJECT_HOME, ":",2)
								[ ] // // sProjectRootDrive = GetField (PROJECT_HOME, ":",1)
								[ ] // //
								[ ] // // //copy the files from the remote to local machine
								[ ] // // Print ("")
								[ ] // // Print ("sBmpDir is : 	{sBmpDir}")
								[ ] // // Print ("")
								[ ] // //
								[+] // // if Properties_KeyValues.sRemoteMachineErrorDir != ""
									[ ] // // Print("AMIYA")
									[ ] // // SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}$\{GetField(sBmpDir, "\", 2)}\ErrorBmps\{sTempErrorBmp}", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sTempErrorBmp}")
									[ ] // // SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}$\{GetField(sBmpDir, "\", 2)}\ErrorBmps\{sRmpFile}.rmp", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sRmpFile}.rmp")
									[ ] // // //D:\SILKGEN\ProjectWorkingFolders\SilkTest\ErrorBmps\Error121808172838.bmp
								[+] // // else
									[ ] // // Print("LITY")
									[ ] // // SYS_CopyFile ("\\{sTargetMachineName}\{sProjectRootDrive}$\{sProjectRootNoDrive}\SilkTest\ErrorBmps\{sTempErrorBmp}", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sTempErrorBmp}")
									[ ] // // SYS_CopyFile ("\\{sTargetMachineName}\{sProjectRootDrive}$\{sProjectRootNoDrive}\SilkTest\ErrorBmps\{sRmpFile}.rmp", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sRmpFile}.rmp")
								[ ] // //
								[ ] // // //disconnect from the local machine and set the target machine as the current machine
								[ ] // // Disconnect(hLocalMachine)
								[+] // // if bConnectError
									[ ] // // Connect (sTargetMachineName)
								[+] // // else
									[ ] // // SetMachine(hTargetMachine)
							[ ] // //This is temp until the color map code is implemented
							[+] // if ExceptNum () == E_BITMAPS_DIFF_COLORTABLE
								[ ] // // Add an informational message for the results file
								[ ] // sErrorMsg = ExceptData () + "; Error bitmap stored in file {sErrorBmp}"
								[ ] // sErrorMsg = GetField (sErrorMsg, "*** Error: ", 2)
								[ ] // AppError (sErrorMsg)
							[+] // else
								[ ] // reraise
				[+] // if (!bLocalAgent)
					[+] // withoptions
						[ ] // // Turn the bitmap match count to 0 to handle blinking cursors, etc
						[ ] // BindAgentOption (OPT_BITMAP_MATCH_COUNT, 0)
						[ ] //
						[ ] // sProjectRoot 				= PROJECT_HOME
						[ ] // STRING sRemoteRootDrive 	= GetField (Properties_KeyValues.sRemoteMachineErrorDir, ":",1)
						[ ] // STRING sRemoteRootNoDrive 	= GetField (Properties_KeyValues.sRemoteMachineErrorDir, ":",2)
						[ ] //
						[ ] // //Creating 'ErrorBmps' folder in the host machine if not exists since error bitmap will be copied to the Host Machine
						[+] // if Properties_KeyValues.sLocalMachineErrorDir != ""
							[+] // if !(hHost -> SYS_DirExists("{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps"))
								[ ] // hHost -> SYS_MakeDir ("{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps")
						[+] // // else
							[ ] // // //make sure that there is a bitmaps directory on the target machine specified in default location
							[+] // // if !(hHost -> SYS_DirExists("{sProjectRoot}\SilkTest\ErrorBmps"))
								[ ] // // hHost -> SYS_MakeDir ("{sProjectRoot}\SilkTest\ErrorBmps")
						[ ] //
						[ ] // // Creating the 'ErrorBmps' folder in the path specified in the .properties file
						[+] // if Properties_KeyValues.sRemoteMachineErrorDir != ""
							[ ] // // if the trailing slash was not supplied on the destination path, add it
							[+] // if SubStr (Properties_KeyValues.sRemoteMachineErrorDir, Len (sProjectRoot), 1) != "\"
								[ ] // sBmpDir = Properties_KeyValues.sRemoteMachineErrorDir + "\"
							[ ] // sBmpDir = sBmpDir + "ErrorBmps\"
							[ ] // MakeDir (sBmpDir, TRUE)
						[+] // else
							[ ] // sBmpDir = ""
						[ ] //
						[ ] // // Build a name for the error bmp using the current date time stamp
						[ ] // sTempErrorBmp 	= "Error{CreateCurrentDTSString ()}.bmp"
						[ ] // sErrorBmp 		= sBmpDir + sTempErrorBmp
						[ ] //
						[ ] // //make sure that there is a bitmaps directory on the target machine specified in .properties file
						[+] // if Properties_KeyValues.sRemoteMachineErrorDir != ""
							[+] // if !SYS_DirExists("{Properties_KeyValues.sRemoteMachineErrorDir}\ErrorBmps")
								[ ] // SYS_MakeDir ("{Properties_KeyValues.sRemoteMachineErrorDir}\ErrorBmps")
						[ ] //
						[ ] // //clean out the ErrorBmps directory if the target machine is not the local machine
						[+] // if Properties_KeyValues.sRemoteMachineErrorDir != ""
							[ ] // //delete the previously existing files on the remote machine since they will be copied to the local machine for viewing
							[ ] // DeleteDirFiles("{Properties_KeyValues.sRemoteMachineErrorDir}\ErrorBmps")
						[ ] //
						[ ] // SetMachine(hLocalMachine)
						[ ] // CopyOverwriteFile ("{HOST_GetEnv("SILKGEN_HOME")}\Bmps\SILKGEN_Mock.bmp", "\\{sTargetMachineName}\{sRemoteRootDrive}${sRemoteRootNoDrive}\ErrorBmps\{sTempErrorBmp}", TRUE)
						[ ] // Disconnect(hLocalMachine)
						[ ] //
						[ ] // //adds the stack trace to the results file
						[ ] // ExceptPrint()
						[ ] //
						[ ] // // finally log the last error seen
						[ ] // LogWarning (ExceptData ())
						[ ] //
						[+] // do
							[ ] // Desktop.VerifyBitmap (sErrorBmp)
						[+] // except
							[ ] // //strip the extension from the bitmap file
							[ ] // sRmpFile = GetField (sTempErrorBmp,".bmp", 1)
							[ ] //
							[ ] // //separate the drive from the path
							[ ] // //this is done because there may be permission problems attempting to copy from remote to local machine
							[ ] //
							[ ] // sProjectRootDrive 	= GetField (PROJECT_HOME, ":", 1)
							[ ] // sProjectRootNoDrive = GetField (PROJECT_HOME, ":", 2)
							[ ] //
							[ ] // //copy the files from the remote to local machine
							[+] // if(Properties_KeyValues.sRemoteMachineErrorDir != "")
								[+] // if (Properties_KeyValues.sLocalMachineErrorDir != "")
									[ ] // hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sTempErrorBmp}", "{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps\{sTempErrorBmp}")
									[ ] // hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sRmpFile}.rmp", "{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps\{sRmpFile}.rmp")
									[ ] //
								[+] // // else
									[ ] // // hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sTempErrorBmp}", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sTempErrorBmp}")
									[ ] // // hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sRmpFile}.rmp", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sRmpFile}.rmp")
								[ ] //
							[ ] //
						[ ] // //this is temp until the color map code is implemented
						[+] // if ExceptNum () == E_BITMAPS_DIFF_COLORTABLE
							[ ] // // Add an informational message for the results file
							[ ] // sErrorMsg = ExceptData () + "; Error bitmap stored in file {sErrorBmp}"
							[ ] // sErrorMsg = GetField (sErrorMsg, "*** Error: ", 2)
							[ ] // AppError (sErrorMsg)
						[+] // else
							[ ] // reraise
						[ ] // return
			[+] // case "PrintURL"
				[+] // withoptions
					[ ] // // Turn the bitmap match count to 0 to handle blinking cursors, etc
					[ ] // BindAgentOption (OPT_BITMAP_MATCH_COUNT, 0)
					[ ] //
					[ ] // // Build a name for the error bmp using the current date time stamp
					[ ] // sErrorBmp = "Error{CreateCurrentDTSString ()}.bmp"
					[ ] //
					[ ] // // See if PROJECT_HOME is defined, and if so store the bitmaps there
					[ ] // sProjectRoot = PROJECT_HOME
					[ ] //
					[ ] // // if the trailing slash was not supplied on the destination path, add it
					[+] // if sProjectRoot != ""
						[+] // if SubStr (sProjectRoot, Len (sProjectRoot), 1) != "\"
							[ ] // sProjectRoot = sProjectRoot + "\"
						[ ] // sProjectRoot = sProjectRoot + "ErrorBmps\"
						[ ] // MakeDir (sProjectRoot)
					[+] // else
						[ ] // sProjectRoot = "ErrorBmps\"
					[ ] //
					[ ] // // tack on the path for storing the BMPs if desired
					[ ] // sErrorBmp = sProjectRoot + sErrorBmp
					[ ] //
					[ ] // Desktop.CaptureBitmap (sErrorBmp)
					[ ] //
					[ ] // //adds the stack trace to the results file
					[ ] // ExceptPrint()
					[ ] //
					[ ] // // finally raise the last error seen
					[ ] // sErrorMsg = ExceptData () + "; Error bitmap stored in file {sErrorBmp}"
					[ ] // sErrorMsg = GetField (sErrorMsg, "*** Error: ", 2)
					[ ] // AppError (sErrorMsg)
			[+] // default
				[ ] // reraise
			[ ] //
		[ ] //
		[ ] //
		[ ] // ListAppend(laLogDetails, "Call to function: LogErrorSnapBmp in testcase: {GetTestCaseName()}	success")
		[ ] // return
	[+] // except
		[ ] //
		[ ] // ListAppend(laLogDetails, "Exception raised in Call to function: LogErrorSnapBmp in testcase: {GetTestCaseName()}")
		[ ] // ListAppend(laLogDetails, ExceptData ())
		[ ] // return
[ ]
[-] VOID LogErrorSnapBmp (STRING sErrorString, BOOLEAN bHaltTestcase optional)
	[ ]
	[ ] //STRING sBmpPath optional,
	[ ]
	[ ] STRING 			sErrorBmp, sErrorMsg, sBmpDir, sRmpFile, sTempErrorBmp
	[ ] STRING			sProjectRoot, sProjectRootNoDrive, sProjectRootDrive
	[ ]
	[ ] STRING 			sTargetMachineName 	= Properties_KeyValues.sTargetMachine
	[ ]
	[ ] BOOLEAN 		bConnectError 		= FALSE
	[ ]
	[ ]
	[ ] //initialize sProjectRoot
	[ ] sProjectRoot = PROJECT_HOME
	[ ]
	[ ] //determine whether the test is running a local or remote machine
	[+] if GetMachineName () != sLocalMachine
		[ ] bLocalAgent = FALSE
	[ ]
	[ ] //set bHaltTestcase to FALSE if it is not passed in
	[+] if IsNull(bHaltTestcase)
		[ ] bHaltTestcase = FALSE
	[ ]
	[ ] //the behavior of this function is controlled by an Enviroment variable called ErrorMode. If it is not set
	[ ] //the first case DiffBitmaps will be executed
	[-] switch ("{HOST_GetEnv ('ErrorMode')}")
		[ ]
		[-] case "DiffBitmaps", "", NULL
			[+] if (bLocalAgent)
				[+] withoptions
					[ ] // Turn the bitmap match count to 0 to handle blinking cursors, etc
					[ ] BindAgentOption (OPT_BITMAP_MATCH_COUNT, 0)
					[ ]
					[ ] // See if PROJECT_HOME is defined, and if so store the bitmaps there
					[ ] sProjectRoot = PROJECT_HOME
					[ ]
					[ ] // Creating the 'ErrorBmps' folder in the path specified in the .properties file
					[+] if Properties_KeyValues.sLocalMachineErrorDir != ""
						[ ] // if the trailing slash was not supplied on the destination path, add it
						[+] if SubStr (Properties_KeyValues.sLocalMachineErrorDir, Len (sProjectRoot), 1) != "\"
							[ ] sBmpDir = Properties_KeyValues.sLocalMachineErrorDir + "\"
						[ ] sBmpDir = sBmpDir + "ErrorBmps\"
						[ ] MakeDir (sBmpDir)
					[ ]
					[ ] // Crating the 'ErrorBmps' folder in the default project path
					[+] else if sProjectRoot != ""
						[ ] // if the trailing slash was not supplied on the destination path, add it
						[+] if SubStr (sProjectRoot, Len (sProjectRoot), 1) != "\"
							[ ] sBmpDir = sProjectRoot + "\"
						[ ] // Creating 'ErrorBmps' folder inside 'SilkTest' folder, which will be the default path for 'ErrorBmps'
						[ ] sBmpDir = sBmpDir + "SilkTest\" + "ErrorBmps\"
						[ ] MakeDir (sBmpDir)
						[ ]
					[+] else
						[ ] sBmpDir = ""
					[ ]
					[ ] // Build a name for the error bmp using the current date time stamp
					[ ] sTempErrorBmp = "Error{CreateCurrentDTSString ()}.bmp"
					[ ] sErrorBmp = sBmpDir + sTempErrorBmp
					[ ]
					[ ] // copy the bogus bitmap to the newly created file name
					[ ] CopyOverwriteFile ("{HOST_GetEnv("SILKGEN_HOME")}\Bmps\SILKGEN_Mock.bmp", sErrorBmp, TRUE)
					[ ]
					[ ] //adds the stack trace to the results file
					[ ] ExceptPrint()
					[ ]
					[ ] // finally log the last error seen
					[+] if (ExceptData() != NULL)
						[ ] LogWarning (ExceptData ())
					[ ]
					[+] do
						[ ] Desktop.VerifyBitmap (sErrorBmp)
					[+] except
						[ ] //if bHaltTestcase is TRUE then halt the testcase after reporting the error
						[+] if bHaltTestcase
							[ ] reraise
						[ ] //otherwise report the error and let the testcase continue to execute
						[+] else
							[+] if ExceptNum () == E_BITMAPS_DIFF_COLORTABLE
								[ ] LogError (sErrorString)
								[ ] //adds the stack trace to the results file
								[ ] ExceptPrint()
							[+] else
								[ ] ExceptLog()
						[ ]
			[-] if (!bLocalAgent)
				[-] withoptions
					[ ] // Turn the bitmap match count to 0 to handle blinking cursors, etc
					[ ] BindAgentOption (OPT_BITMAP_MATCH_COUNT, 0)
					[ ]
					[ ] sProjectRoot 				= PROJECT_HOME
					[ ] STRING sRemoteRootDrive 	= GetField (Properties_KeyValues.sRemoteMachineErrorDir, ":",1)
					[ ] STRING sRemoteRootNoDrive 	= GetField (Properties_KeyValues.sRemoteMachineErrorDir, ":",2)
					[ ]
					[ ] //Creating 'ErrorBmps' folder in the host machine if not exists since error bitmap will be copied to the Host Machine
					[+] if Properties_KeyValues.sLocalMachineErrorDir != ""
						[+] if !(hHost -> SYS_DirExists("{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps"))
							[ ] hHost -> SYS_MakeDir ("{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps")
					[+] // else
						[ ] // //make sure that there is a bitmaps directory on the target machine specified in default location
						[+] // if !(hHost -> SYS_DirExists("{sProjectRoot}\SilkTest\ErrorBmps"))
							[ ] // hHost -> SYS_MakeDir ("{sProjectRoot}\SilkTest\ErrorBmps")
					[ ]
					[ ] // Creating the 'ErrorBmps' folder in the path specified in the .properties file
					[+] if Properties_KeyValues.sRemoteMachineErrorDir != ""
						[ ] // if the trailing slash was not supplied on the destination path, add it
						[+] if SubStr (Properties_KeyValues.sRemoteMachineErrorDir, Len (sProjectRoot), 1) != "\"
							[ ] sBmpDir = Properties_KeyValues.sRemoteMachineErrorDir + "\"
						[ ] sBmpDir = sBmpDir + "ErrorBmps\"
						[ ] MakeDir (sBmpDir, TRUE)
					[+] else
						[ ] sBmpDir = ""
					[ ]
					[ ] // Build a name for the error bmp using the current date time stamp
					[ ] sTempErrorBmp 	= "Error{CreateCurrentDTSString ()}.bmp"
					[ ] sErrorBmp 		= sBmpDir + sTempErrorBmp
					[ ]
					[ ] //make sure that there is a bitmaps directory on the target machine specified in .properties file
					[+] if Properties_KeyValues.sRemoteMachineErrorDir != ""
						[+] if !SYS_DirExists("{Properties_KeyValues.sRemoteMachineErrorDir}\ErrorBmps")
							[ ] SYS_MakeDir ("{Properties_KeyValues.sRemoteMachineErrorDir}\ErrorBmps")
					[ ]
					[ ] //clean out the ErrorBmps directory if the target machine is not the local machine
					[+] if Properties_KeyValues.sRemoteMachineErrorDir != ""
						[ ] //delete the previously existing files on the remote machine since they will be copied to the local machine for viewing
						[ ] DeleteDirFiles("{Properties_KeyValues.sRemoteMachineErrorDir}\ErrorBmps")
					[ ]
					[ ] SetMachine(hLocalMachine)
					[ ]
					[ ] CopyOverwriteFile ("{HOST_GetEnv("SILKGEN_HOME")}\Bmps\SILKGEN_Mock.bmp", "\\{sTargetMachineName}\{sRemoteRootDrive}${sRemoteRootNoDrive}\ErrorBmps\{sTempErrorBmp}", TRUE)
					[ ] Disconnect(hLocalMachine)
					[ ]
					[ ] //adds the stack trace to the results file
					[ ] ExceptPrint()
					[ ]
					[ ] // finally log the last error seen
					[+] if (ExceptData() != NULL)
						[ ] LogWarning (ExceptData ())
					[ ]
					[+] do
						[ ] Desktop.VerifyBitmap (sErrorBmp)
					[+] except
						[ ] //strip the extension from the bitmap file
						[ ] sRmpFile = GetField (sTempErrorBmp,".bmp", 1)
						[ ]
						[ ] //separate the drive from the path
						[ ] //this is done because there may be permission problems attempting to copy from remote to local machine
						[ ]
						[ ] sProjectRootDrive 	= GetField (PROJECT_HOME, ":", 1)
						[ ] sProjectRootNoDrive = GetField (PROJECT_HOME, ":", 2)
						[ ]
						[ ] //copy the files from the remote to local machine
						[+] if(Properties_KeyValues.sRemoteMachineErrorDir != "")
							[+] if (Properties_KeyValues.sLocalMachineErrorDir != "")
								[ ] hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sTempErrorBmp}", "{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps\{sTempErrorBmp}")
								[ ] hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sRmpFile}.rmp", "{Properties_KeyValues.sLocalMachineErrorDir}\ErrorBmps\{sRmpFile}.rmp")
								[ ]
							[+] // else
								[ ] // hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sTempErrorBmp}", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sTempErrorBmp}")
								[ ] // hHost -> SYS_CopyFile ("\\{sTargetMachineName}\{GetField(sBmpDir, ":", 1)}${GetField(sBmpDir, ":", 2)}{sRmpFile}.rmp", "{HOST_GetEnv("PROJECT_HOME")}\SilkTest\ErrorBmps\{sRmpFile}.rmp")
							[ ]
						[ ]
					[ ]
					[ ] //if bHaltTestcase is TRUE then halt the testcase after reporting the error
					[+] if bHaltTestcase
						[ ] reraise
					[ ] //otherwise report the error and let the testcase continue to execute
					[+] else
						[+] if ExceptNum () == E_BITMAPS_DIFF_COLORTABLE
							[ ] LogError (sErrorString)
							[ ] //adds the stack trace to the results file
							[ ] ExceptPrint()
						[+] else
							[ ] ExceptLog()
					[ ]
					[ ] return
		[+] case "PrintURL"
			[+] withoptions
				[ ] // Turn the bitmap match count to 0 to handle blinking cursors, etc
				[ ] BindAgentOption (OPT_BITMAP_MATCH_COUNT, 0)
				[ ]
				[ ] // Build a name for the error bmp using the current date time stamp
				[ ] sErrorBmp = "Error{CreateCurrentDTSString ()}.bmp"
				[ ]
				[ ] // See if PROJECT_HOME is defined, and if so store the bitmaps there
				[ ] sProjectRoot = PROJECT_HOME
				[ ]
				[ ] // if the trailing slash was not supplied on the destination path, add it
				[+] if sProjectRoot != ""
					[+] if SubStr (sProjectRoot, Len (sProjectRoot), 1) != "\"
						[ ] sProjectRoot = sProjectRoot + "\"
					[ ] sProjectRoot = sProjectRoot + "ErrorBmps\"
					[ ] MakeDir (sProjectRoot)
				[+] else
					[ ] sProjectRoot = "ErrorBmps\"
				[ ]
				[ ] // tack on the path for storing the BMPs if desired
				[ ] sErrorBmp = sProjectRoot + sErrorBmp
				[ ]
				[ ] Desktop.CaptureBitmap (sErrorBmp)
				[ ]
				[ ] //adds the stack trace to the results file
				[ ] ExceptPrint()
				[ ]
				[ ] // finally raise the last error seen
				[ ] sErrorMsg = ExceptData () + "; Error bitmap stored in file {sErrorBmp}"
				[ ] sErrorMsg = GetField (sErrorMsg, "*** Error: ", 2)
				[ ] AppError (sErrorMsg)
			[ ]
			[ ] //if bHaltTestcase is TRUE then halt the testcase after reporting the error
			[+] if bHaltTestcase
				[ ] AppError (sErrorString)
			[ ] //otherwise report the error and let the testcase continue to execute
			[+] else
				[ ] LogError (sErrorString)
				[ ] //adds the stack trace to the results file
				[ ] ExceptPrint()
			[ ]
		[+] default
			[ ] //if bHaltTestcase is TRUE then halt the testcase after reporting the error
			[+] if bHaltTestcase
				[ ] AppError (sErrorString)
			[ ] //otherwise report the error and let the testcase continue to execute
			[+] else
				[ ] LogError (sErrorString)
				[ ] //adds the stack trace to the results file
				[ ] ExceptPrint()
	[ ] return
