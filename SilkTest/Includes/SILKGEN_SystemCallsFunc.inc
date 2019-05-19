[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_SystemCallsFunc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	System Calls related functions are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak 
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		04/06/09	Amiya Pattnayak	Created
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //									Operating System (windows) calls  RELATED FUNCTIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // function:   MakeDir (sMakeDirPath, [bAgentProcess])
[ ] // parameter:  sMakeDirPath: The fully qualified path of the directory to make. STRING.
[ ] // parameter:  bAgentProcess: TRUE if called from an agent process - default is FALSE (optional). BOOLEAN.
[ ] // returns:    void
[ ] // Action::    Makes a directory if it does not exist. Requires the parent directory to exist.
[+] VOID MakeDir (STRING sMakeDirPath, BOOLEAN bAgentProcess optional)
	[+] do
		[ ]
		[ ] // make the directory if it doesn't exist
		[ ]
		[ ] // bAgentProcess defaults to FALSE
		[+] if IsNull (bAgentProcess)
			[ ] bAgentProcess = FALSE
		[+] else
			[ ] bAgentProcess = TRUE
		[ ]
		[+] if bAgentProcess
			[+] if !SYS_DirExists(sMakeDirPath)
				[ ] SYS_MakeDir (sMakeDirPath)
		[+] else
			[+] if !hHost->SYS_DirExists(sMakeDirPath)
				[ ] hHost->SYS_MakeDir (sMakeDirPath)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: MakeDir in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: MakeDir in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
	[ ]
[ ]
[ ]
[ ] // function:  	DeleteDir (sPath, [bMakeWritable])
[ ] // parameter: 	sPath: Fully qualified path of the directory to be deleted. STRING.
[ ] // parameter: 	bMakeWritable: If TRUE, directories files will be made writable and then deleted. Default is FALSE (optional). BOOLEAN.
[ ] // returns:   	void
[ ] // Action:     	Deletes a directory and its contents.
[+] VOID DeleteDir (STRING sPath, BOOLEAN bMakeWritable optional)
	[+] do
		[ ]
		[ ] FILEINFO fiFile
		[ ] STRING sFileName
		[ ]
		[ ] // Set default value of bMakeWritable to FALSE
		[+] if IsNull (bMakeWritable)
			[ ] bMakeWritable = FALSE
		[ ]
		[ ] // if the trailing slash was not supplied on the destination path, add it
		[+] if SubStr (sPath, Len (sPath), 1) != "\"
			[ ] sPath = sPath + "\"
		[ ]
		[ ] // Delete the directory if it exists
		[+] if SYS_DirExists (sPath)
			[ ] // delete each item in the directory
			[+] for each fiFile in SYS_GetDirContents (sPath)
				[ ] sFileName = sPath + fiFile.sName
				[ ]
				[ ] // if the item is a directory, call this function to delete it and its contents
				[+] if SYS_DirExists(sFileName)
					[+] if bMakeWritable		// if desired, make directory writable
						[ ] AttribNoReadOnly (sFileName)
					[ ] DeleteDir (sFileName, bMakeWritable)
				[+] else	// otherwise its a file, so just delete it
					[+] if bMakeWritable		// if desired, make file writable
						[ ] AttribNoReadOnly (sFileName)
					[+] do
						[ ] SYS_RemoveFile (sFileName)
						[ ] Sleep (.5)
					[+] except
						[+] if StrPos ("Permission denied", ExceptData ())
							[ ] LogErrorSnapBmp ("{ExceptData ()}. Call this function with optional 'TRUE' second parameter to make writable")
						[+] else
							[ ] LogErrorSnapBmp (ExceptData ())
			[ ]
			[ ] // now the contents have been deleted, so delete the directory
			[+] if bMakeWritable		// if desired, make directory writable
				[ ] AttribNoReadOnly (Left (sPath, Len (sPath) - 1))
			[ ]
			[+] do
				[ ] SYS_RemoveDir (sPath)
				[ ] Sleep (.5)
			[+] except
				[+] if StrPos ("Permission denied", ExceptData ())
					[ ] LogErrorSnapBmp ("{ExceptData ()}. Call this function with optional 'TRUE' second parameter to make writable")
				[+] else
					[ ] LogErrorSnapBmp (ExceptData ())
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DeleteDir in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DeleteDir in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
	[ ]
[ ]
[ ]
[ ] // function:  	DeleteFile (sFile, [bMakeWritable])
[ ] // parameter: 	sFile: Fully qualified file to delete. STRING
[ ] // parameter: 	bMakeWritable: If TRUE, file will be made writable and then deleted. Default is FALSE (optional). BOOLEAN.
[ ] // returns:   	void
[ ] // Action:    	Deletes a file if it exists.
[+] VOID DeleteFile (STRING sFile, BOOLEAN bMakeWritable optional)
	[+] do
		[ ]
		[ ] // Set default value of bMakeWritable to FALSE
		[+] if IsNull (bMakeWritable)
			[ ] bMakeWritable = FALSE
		[ ]
		[ ] // check files existence before removing it
		[+] if SYS_FileExists(sFile)
			[+] if bMakeWritable		// if desired, make file writable
				[ ] AttribNoReadOnly (sFile)
			[ ] SYS_RemoveFile(sFile)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DeleteFile in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DeleteFile in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
	[ ]
[ ]
[ ]
[ ] // function:  	DeleteDirFiles (sDeletePath)
[ ] // parameter: 	sDeletePath: Fully qualified path of the directory to be cleared. STRING.
[ ] // returns:   	void
[ ] // Action:     	Deletes all files in a directory. Does not delete the directory.
[+] VOID DeleteDirFiles (STRING sDeletePath)
	[+] do
		[ ]
		[ ] LIST OF STRING lsOutput		// holds any output messages from SYS_Execute
		[ ] LIST OF FILEINFO lfFiles
		[ ] INTEGER iCount
		[ ]
		[ ] // if the trailing slash was not supplied on the destination path, add it
		[+] if SubStr (sDeletePath, Len (sDeletePath), 1) != "\"
			[ ] sDeletePath = sDeletePath + "\"
		[ ]
		[ ] // issue the delete command
		[+] if GetGUIType () == msw98
			[ ] lfFiles = SYS_GetDirContents (sDeletePath)
			[+] for iCount = 1 to ListCount (lfFiles)
				[+] do
					[ ] SYS_RemoveFile(sDeletePath + lfFiles[iCount].sName)
				[+] except
					[ ] LogWarning ("Unable to remove the file {lfFiles[iCount].sName}")
		[+] else
			[ ] SYS_Execute ("del " + sDeletePath + "*.* /Q", lsOutput)
			[ ] // If the OS returned any output, print it
			[+] if lsOutput != {}
				[ ] Print ("The following message was displayed by the operating system: {lsOutput}")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DeleteDirFiles in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DeleteDirFiles in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
	[ ]
[ ]
[ ]
[ ] // function:  	CopyOverwriteFile (sFileToCopy, sCopyToPath, [bAgentProcess])
[ ] // parameter: 	sFileToCopy: The fully qualified name of the file to copy from. STRING.
[ ] // parameter: 	sCopyToFile: The fully qualified name of the destination file. STRING.
[ ] // parameter: 	bAgentProcess: TRUE if called from an agent process - default is FALSE (optional). BOOLEAN.
[ ] // returns:		viod
[ ] // Action:     	Copies a file. If the file already exists in the destination directory, it is deleted before the copy occurs.
[+] VOID CopyOverwriteFile (STRING sFileToCopy, STRING sCopyToFile, BOOLEAN bAgentProcess optional)
	[ ] // set default to FALSE
	[+] do
		[+] if IsNull (bAgentProcess)
			[ ] bAgentProcess = FALSE
		[ ]
		[ ] // first delete the existing file if it exists
		[+] if bAgentProcess
			[+] if (SYS_FileExists (sCopyToFile))
				[ ] SYS_RemoveFile (sCopyToFile)
		[+] else
			[+] if (hHost->SYS_FileExists (sCopyToFile))
				[ ] hHost->SYS_RemoveFile (sCopyToFile)
		[ ] // then copy the file
		[+] if bAgentProcess
			[ ] SYS_CopyFile (sFileToCopy,sCopyToFile)
		[+] else
			[ ] hHost->SYS_CopyFile (sFileToCopy,sCopyToFile)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: CopyOverwriteFile in testcase: {GetTestCaseName()}	success")
		[ ] return
		[ ]
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: CopyOverwriteFile in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
	[ ]
[ ]
[ ]
[ ] // function:  	AttribNoReadOnly (sPath)
[ ] // parameter: 	sPath: Fully qualified filename to set attributes. STRING
[ ] // returns:   	void
[ ] // Action:     	Changes the attributes of the file to not be read only.
[+] VOID AttribNoReadOnly (STRING sPath)
	[+] do
		[ ]
		[ ] STRING sCmd = "attrib -r {sPath}"
		[ ]
		[ ] SYS_Execute (sCmd)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: AttribNoReadOnly in testcase: {GetTestCaseName()}	success")
		[ ] return
		[ ]
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: AttribNoReadOnly in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
[ ]
[ ]
[ ] // Function:	GetNTUser function
[ ] // Action:		Returns the current NT user name of the windows operating system.
[ ] // Syntax:		sNTUser = GetNTUser()
[ ] // Parameter:	none
[ ] // Returns:		Returns the current NT user name in which the script is running. STRING.
[+] STRING 	GetNTUser()
	[+] do
		[ ] LIST OF STRING lsOutput, lsFields
		[ ] STRING 		sLine
		[ ] INTEGER 	iFields
		[ ] SYS_Execute("net config workstation", lsOutput)
		[+] for each sLine in lsOutput
			[+] if ( MatchStr("User name*", sLine) )
				[ ] iFields = Split ( sLine, lsFields, " ")
				[ ] return lsFields[iFields]
		[ ] return ""
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetNTUser in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	GetThisComputerName function
[ ] // Action:		Returns the name of the computer of the windows operating system.
[ ] // Syntax:		sCompName = GetThisComputerName()
[ ] // Parameter:	none
[ ] // Returns:		Returns [sCompName] name of the computer in which the script is running. STRING.
[+] STRING 	GetThisComputerName()
	[+] do
			[ ]
		[ ] LIST OF STRING lsOutput, lsFields
		[ ] STRING 	sLine
		[ ] INTEGER iFields
		[ ] SYS_Execute("hostname", lsOutput)
		[ ] // SYS_Execute("net config workstation", lsOutput)
		[+] // for each sLine in lsOutput
			[+] // if ( MatchStr("Computer name*", sLine) )
				[ ] // iFields = Split ( sLine, lsFields, " ")
				[ ] // return StrTran(lsFields[iFields], "\", "" ) // remove \'s
		[ ] // return ""
		[ ] return lsOutput[1]
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetThisComputerName in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
[ ]
