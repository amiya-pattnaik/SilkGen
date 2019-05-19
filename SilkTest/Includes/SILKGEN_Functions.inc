[ ] // //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_Functions.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Functions are specific to SILKGEN Framework are incluced here. Please do not modify it.
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		12/01/08	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[+] VOID SILKGEN_Init()
	[ ] GetPropertiesFileKeyValues(lsPROP_KEYS)
	[ ] SetRunTimeBrowserType()
[ ]
[+] VOID GetPropertiesFileKeyValues(LIST OF STRING lsPROP_KEYS)	// Reading the data from the properties file and initilize it.
	[ ]
	[ ] STRING sKey, sValue
	[ ]
	[ ] LIST OF STRING lsPROP_VALUES		= {...}
	[ ] ListRead(lsPROP_VALUES, "{HOST_GetEnv("PROJECT_HOME")}\Properties\Project.properties")
	[ ]
	[+] for each sKey in lsPROP_KEYS
		[ ]
		[-] for each sValue in lsPROP_VALUES
			[-] if MatchStr("{sKey}=*", sValue)
				[ ]
				[+] if MatchStr("TargetMachine*", sKey)
					[ ] Properties_KeyValues.sTargetMachine = Trim(GetField(sValue,"=", 2))
				[ ]
				[+] if MatchStr("DefaultBrowser*", sKey)
					[ ]
					[ ] ////commented to support any IE version. User has to provide the exact Browser specifier in the .prop file
					[+] // switch (Lower(Trim(GetField(sValue,"=", 2))))
						[ ] //
						[+] // case ""
							[ ] // Properties_KeyValues.btDefaultBrowser = NULL
							[ ] //
						[+] // case "none"
							[ ] // Properties_KeyValues.btDefaultBrowser = NULL
						[+] // case "IE 6.0"
							[ ] // Properties_KeyValues.btDefaultBrowser = explorer6_DOM
							[ ] //
						[+] // case "IE 7.0"
							[ ] // Properties_KeyValues.btDefaultBrowser = explorer7
							[ ] //
						[+] // // case "IE 8.0"
							[ ] // // Properties_KeyValues.btDefaultBrowser = explorer8_0
							[ ] // //
						[+] // case "FF 2.0"
							[ ] // Properties_KeyValues.btDefaultBrowser = firefox2_0
							[ ] // //FF2.0
						[+] // // case "FF 3.0"
							[ ] // // Properties_KeyValues.btDefaultBrowser = firefox3_0
						[+] // // case "FF 3.5"
							[ ] // // Properties_KeyValues.btDefaultBrowser = firefox3_5
						[ ] //
						[ ] //
						[ ] //
						[+] // default
							[ ] // //Properties_KeyValues.btDefaultBrowser = [BROWSERTYPE] GetField(sValue,"=", 2)
							[ ] // Properties_KeyValues.btDefaultBrowser = NULL
						[ ] //
					[ ]
					[+] if(lower(Trim(GetField(sValue,"=", 2))) == "none")
						[ ] Properties_KeyValues.btDefaultBrowser = NULL
					[+] else
						[ ] Properties_KeyValues.btDefaultBrowser = [BROWSERTYPE] Trim(GetField(sValue,"=", 2))
						[ ]
					[ ]
				[ ]
				[+] if MatchStr("LocalMachineErrorDir*", sKey)
					[ ] Properties_KeyValues.sLocalMachineErrorDir = Trim(GetField(sValue,"=", 2))
				[ ]
				[+] if MatchStr("RemoteMachineErrorDir*", sKey)
					[ ] Properties_KeyValues.sRemoteMachineErrorDir = Trim(GetField(sValue,"=", 2))
				[ ]
				[+] if MatchStr("ReportType*", sKey)
					[ ] Properties_KeyValues.sReportType = Trim(GetField(sValue,"=", 2))
				[ ]
				[+] if MatchStr("TestSetName*", sKey)
					[ ] Properties_KeyValues.sTestSetName = Trim(GetField(sValue,"=", 2))
				[ ]
				[+] if MatchStr("TestDescription*", sKey)
					[ ] Properties_KeyValues.sTestDescription = Trim(GetField(sValue,"=", 2))
				[ ]
				[+] if MatchStr("DebugMode*", sKey)
					[ ] Properties_KeyValues.iDebugMode = Val(GetField(sValue,"=", 2))
				[ ]
				[-] if MatchStr("TestFileToRun*", sKey)
					[ ] Properties_KeyValues.sTestFileToRun = Trim(GetField(sValue,"=", 2))
				[ ]
				[ ]
[ ]
[+] VOID SetRunTimeBrowserType()
	[+] if (Properties_KeyValues.btDefaultBrowser !=  NULL)
		[ ] SetBrowserType(Properties_KeyValues.btDefaultBrowser)
	[+] else
		[ ] SetBrowserType(NULL)
[ ]
[+] VOID WriteCallStackToList ()
	[ ] // Used in TestcaseExit. For tracing the error count in a testcase / function call.
	[ ] // It writes details into the XML file Under STEPS  for each testcase
	[ ]
	[ ] LIST OF CALL lcCall
	[ ] CALL Call
	[ ] lcCall = ExceptCalls ()
	[ ] lsCallStack = {}
	[+] for each Call in lcCall
		[ ] ListAppend (lsCallStack, "Module: {Call.sModule}, Function: {Call.sFunction}, Line: {Call.iLine}")
		[ ]
[ ]
[+] VOID WriteXMLStartingNode ()
	[ ] HFILE FileHandle
	[ ]
	[ ] // Open file, append line, and close
	[ ] FileHandle = FileOpen ("{HOST_GetEnv("PROJECT_HOME")}\SilkTest\Results\{sRunTimeFile}.xml", FM_APPEND)
	[ ]
	[ ] FileWriteLine (FileHandle, '<?xml version="1.0" encoding="UTF-8"?>' )
	[ ] FileWriteLine (FileHandle, '<?xml-stylesheet href="{HOST_GetEnv("SILKGEN_HOME")}\XSLT\SILKGEN_Report.xsl" type="text/xsl"?>' )
	[ ] FileWriteLine (FileHandle, '<SILKGENTD title="SilkGen, The Next Generation SilkTest Framework" copyright="Copyright &#xA9; 2009, ExGen Software. All rights reserved.">')
	[ ]
	[ ]
	[ ] FileClose (FileHandle)
	[ ]
[ ]
[+] VOID WriteXMLEndingNode ()
	[ ] HFILE FileHandle
	[ ] FileHandle = FileOpen ("{HOST_GetEnv("PROJECT_HOME")}\SilkTest\Results\{sRunTimeFile}.xml", FM_APPEND)
	[ ]
	[ ] FileWriteLine (FileHandle, '</TESTLIST>' )
	[ ] FileWriteLine (FileHandle, '</PROJECT>' )
	[ ] FileWriteLine (FileHandle, '</SILKGENTD>' )
	[ ]
	[ ] FileClose (FileHandle)
	[ ]
[ ]
[+] VOID WriteScriptInfoToXML()
	[ ] HFILE FileHandle
	[ ] FileHandle = FileOpen ("{HOST_GetEnv("PROJECT_HOME")}\SilkTest\Results\{sRunTimeFile}.xml", FM_APPEND)
	[ ]
	[ ] FileWriteLine (FileHandle, "<CREATION_DATE>{sScriptStartDateAndTime}</CREATION_DATE>" )
	[ ] FileWriteLine (FileHandle, "<OS>{SYS_GetName()}</OS>" )
	[ ] FileWriteLine (FileHandle, "<HOSTNAME>{GetThisComputerName()}</HOSTNAME>" )
	[ ] FileWriteLine (FileHandle, "<TESTUSER>{GetNTUser()}</TESTUSER>" )
	[ ]
	[ ] FileWriteLine (FileHandle, '<PROJECT name=" {Properties_KeyValues.sTestSetName}">' )
	[ ] FileWriteLine (FileHandle, '<TESTLIST name="Script Name : {GetProgramName ()}" folder="Root">' )
	[ ] FileWriteLine (FileHandle, ' ' )
	[ ] FileClose (FileHandle)
	[ ]
[ ]
[+] VOID WriteScriptInfoToFile ()
	[ ] HANDLE hFile
	[ ] //hFile 	= FileOpen ("{HOST_GetEnv ("PROJECT_HOME")}\SilkTest\Results\{Properties_KeyValues.sTestSetName}.txt", FM_APPEND)
	[ ] hFile 	= FileOpen ("{HOST_GetEnv ("PROJECT_HOME")}\SilkTest\Results\{sRunTimeFile}.txt", FM_APPEND)
	[ ]
	[ ]
	[ ] FileWriteLine(hFile, "RUN SUMMARY:")
	[ ] FileWriteLine(hFile, "	")
	[ ] FileWriteLine(hFile, "Script Name:		{GetProgramName()}")
	[ ] FileWriteLine(hFile, "Operating System:	{SYS_GetName()}")
	[ ] FileWriteLine(hFile, "Host Name:		{GetThisComputerName()}")
	[ ] FileWriteLine(hFile, "Test User:		{sTestUser}")
	[ ] FileWriteLine(hFile, "******************************************************")
	[ ] FileWriteLine(hFile, "	")
	[ ] FileClose (hFile)
[ ]
[+] VOID WriteTestCaseInfoToXML ()
	[ ]
	[ ] HFILE FileHandle
	[ ] FileHandle = FileOpen ("{HOST_GetEnv("PROJECT_HOME")}\SilkTest\Results\{sRunTimeFile}.xml", FM_APPEND)
	[ ]
	[ ] FileWriteLine (FileHandle, '<TEST name="Testcase Name : {GetTestCaseName ()}" folder="{Properties_KeyValues.sTestDescription}" status= "{GetTestCaseStatus()}" creation_date=" {sTCStartDate} - {sTCStartTime}" executedtime =" {iHours}:{iMinutes}:{iSeconds}">' )
	[ ] FileWriteLine (FileHandle, '<STEP name="{lsCallStack}">' )
	[ ] FileWriteLine (FileHandle, "<STEPSTATUS>{GetTestCaseStatus()}</STEPSTATUS>" )
	[ ] FileWriteLine (FileHandle, '<OPERATION name="RunCommand">' )
	[ ] FileWriteLine (FileHandle, '<ADDITIONALDATA name="Output Details" folder="Details_{GetTestCaseName()}" ><![CDATA[{aTestcaseOutPut}]]></ADDITIONALDATA>' )
	[ ] FileWriteLine (FileHandle, "<STATUS>{GetTestCaseStatus()}</STATUS>" )
	[ ] FileWriteLine (FileHandle, "</OPERATION>" )
	[ ] FileWriteLine (FileHandle, "</STEP>" )
	[ ] FileWriteLine (FileHandle, "</TEST>" )
	[ ] FileClose (FileHandle)
	[ ]
[ ]
[+] VOID WriteTestCaseInfoToFile (STRING sTestStatus, STRING sTestDescription, ANYTYPE aMessages optional)
	[ ] HANDLE hFile
	[ ] //hFile = FileOpen ("{HOST_GetEnv ("PROJECT_HOME")}\SilkTest\Results\{Properties_KeyValues.sTestSetName}.txt", FM_APPEND)
	[ ] hFile = FileOpen ("{HOST_GetEnv ("PROJECT_HOME")}\SilkTest\Results\{sRunTimeFile}.txt", FM_APPEND)
	[ ]
	[ ] FileWriteLine(hFile, "Testcase Name:		{GetTestCaseName()}")
	[ ] FileWriteLine(hFile, "Started:		{sTCStartDate} - {sTCStartTime}")
	[ ] FileWriteLine(hFile, "Execution Time:		{iHours}:{iMinutes}:{iSeconds}")
	[ ] FileWriteLine(hFile, "Status:			{sTestStatus}")
	[ ] FileWriteLine(hFile, "TestSetName:		{Properties_KeyValues.sTestSetName}")
	[ ] FileWriteLine(hFile, "TestDescription:	{sTestDescription}")
	[ ] FileWriteLine(hFile, "Testcase Output:	{aMessages}")
	[ ] FileWriteLine(hFile, "------------------------------------------------------")
	[ ] FileWriteLine(hFile, "	")
	[ ] FileClose (hFile)
	[ ]
[ ]
[+] VOID WriteLogDetailsToLogFile()		// Only for generating log file for SILKGEN functions/methods
	[ ] STRING sLogFile = "{HOST_GetEnv ("PROJECT_HOME")}\SilkTest\Log\{sRunTimeFile}_Log.txt"
	[ ]
	[ ] SYS_ListWrite(laLogDetails, sLogFile)
	[ ]
[ ]
[+] STRING 	GetTestCaseStatus()
	[ ] STRING sTCStatus
	[+] if (GetTestCaseErrorCount() > 0 || ExceptData() != NULL)
		[ ] //PrintResToFile(rToken, "Failed", sTestDescription,{ExceptData()})
		[ ] sTCStatus = "Failed"
	[+] else
		[ ] sTCStatus = "Passed"
		[ ]
	[ ]
	[ ] return sTCStatus
[ ]
[+] INTEGER Split (STRING str, out LIST OF STRING arr, STRING fs optional)
	[ ] // split.inc
	[ ] //**	Split
	[ ] //**
	[ ] //**	Action:	Split separates a string by the given delimiter and stores
	[ ] //**			the newly creted fields in a list of strings.
	[ ] //**
	[ ] //**	Syntax:	Split (sStr, lsNewList, sDelimiter)
	[ ] //**			sStr		The string to be parsed
	[ ] //**			lsNewList	The output list of fields
	[ ] //**			sDelimiter	The delimiter, if omitted, defaults to whitespace
	[ ] //**
	[ ] //**  Notes:	Split returns the number of fields in list lsNewList
	[ ] //**
	[ ] //**  Example: Split ("window.recover", ls, ".") => 2, ls =
	[ ] //**				   ("window", "recover")
	[ ] //**
	[ ] arr = {}
	[ ] INTEGER i // number of fields
	[ ] STRING sField
	[ ] INTEGER x // location of next field separator
	[ ]
	[+] if (fs != NULL)
		[ ] INTEGER fslen = Len (fs)
		[ ] i = 1 // number of fields
		[+] while TRUE
			[ ] x = StrPos (fs, str)
			[+] if x == 0
				[ ] ListAppend (arr, str)
				[ ] return i
			[+] else
				[ ] sField = SubStr (str, 1, x - 1)
				[ ] ListAppend (arr, sField)
				[ ] i += 1
				[ ] str = SubStr (str, x + fslen)
	[+] else // field separator is whitespace (spaces, tabs, etc)
		[ ] // 1. Check for either type of field separator.
		[ ] // 2. Allow multiple field separators to separate adjacent fields.
		[ ] // 3. Ignore initial and trailing whitespace.
		[ ] // THEREFORE, use this strategy:
		[ ] // First, strip initial whitespace
		[ ] // Then, if there is anything left,
		[ ] //    add the chunk to the next whitespace/eol to the array.
		[ ] //    send the remainder through the loop again.
		[ ] i = 0
		[+] while TRUE
			[ ] // Remove initial whitespace
			[ ] str = Ltrim (str)
			[ ]
			[ ] // If there's nothing left, we're done.
			[+] if (str == "")
				[ ] return i
			[ ]
			[ ] // Find next field
			[+] for (x = 1; ! IsSpace (str[x]); ++x)
				[+] if (x == Len (str))
					[ ] x = 0
					[ ] break
			[ ]
			[ ] // Place field in array and continue
			[+] if (x == 0)
				[ ] ListAppend (arr, str)
				[ ] return ++i
			[+] else
				[ ] sField = SubStr (str, 1, x - 1)
				[ ] ListAppend (arr, sField)
				[ ] i += 1
				[ ] str = SubStr (str, x + 1)
		[ ]
[ ]
[+] // VOID RunTestsFromCommandLine()				//To run selected testcases from a single script file
	[ ]
	[ ] ////// This is same as RunTestsFromSingleScriptFile(). It is just a name change
	[ ]
	[ ] // ANYTYPE			aPassArg 	= ""
	[ ] // INTEGER 		iTemp 		= 0
	[ ] // LIST OF ANYTYPE	laTestArgs 	= GetArgs()
	[ ] //
	[ ] // //Converting all the argument into a singe string
	[+] // for (iTemp = 1; iTemp <= ListCount(laTestArgs); iTemp++)
		[ ] // laTestArgs[iTemp] = Ltrim(Rtrim(laTestArgs[iTemp]))
		[ ] //
		[ ] // aPassArg = aPassArg + " {laTestArgs[iTemp]}"
	[ ] //
	[ ] // //Converting individual testcase and its corresponing argument into a List
	[ ] // LIST OF ANYTYPE laTestCases = ParseStringToListOfAnytype(aPassArg, "/")
	[ ] // INTEGER j = 0
	[ ] //
	[ ] // //Executing each individual testcase with its argument
	[+] // for (iTemp = 1; iTemp <= ListCount(laTestCases); iTemp++)
		[+] // do
			[ ] //
			[ ] // LIST OF ANYTYPE laTCData 	= ParseStringToListOfAnytype(laTestCases[iTemp], " ")
			[ ] // STRING sTestcaseName 		= laTCData[1]
			[ ] //
			[ ] // ListDelete(laTCData, 1)		//To Get rid of the testcase name
			[ ] //
			[ ] // // Converting If an argument is more than one word to singe string
			[ ] // INTEGER iStart = 0, iEnd = 0, k = 0, i = 0
			[+] // for (i = 1; i <= ListCount(laTCData); i++)
				[ ] //
				[+] // if(laTCData[i][1] == "'")
					[ ] // laTCData[i] = Stuff(laTCData[i], 1, 1, "")
					[ ] // iStart = i
					[ ] //
				[+] // if(laTCData[i][StrLen(laTCData[i])] == "'")
					[ ] // laTCData[i] = Stuff(laTCData[i], StrLen(laTCData[i]), 1, "")
					[ ] // iEnd = i
					[ ] //
				[ ] // k = 0
				[+] // for (k = iStart; k < iEnd; k++)
					[ ] // laTCData[iStart] = laTCData[iStart] + " "+ laTCData[iStart + 1]
					[ ] // ListDelete(laTCData, iStart + 1)
			[ ] //
			[ ] // // If passed value is an INTEGER, then Converting it to INTEGER.
			[+] // for (j = 1; j <= ListCount(laTCData); j++)
				[+] // if (Val(laTCData[j]) > 0)
					[ ] // laTCData[j] = Val(laTCData[j])
					[ ] //
			[ ] //
			[ ] // //Finally  executing the testcase along with its arguments
			[ ] // ArgListCall(sTestcaseName, laTCData)
		[+] // except
			[+] // if(ExceptData() != NULL)
				[ ] // LogWarning("{ExceptData()}")
				[ ] // continue
		[ ] //
		[ ] //
	[ ] //
	[ ] //
[ ]
[+] VOID RunTestsFromSingleScriptFile()				//To run selected testcases from a single script file
	[ ] ANYTYPE			aPassArg 	= ""
	[ ] INTEGER 		iTemp 		= 0
	[ ] LIST OF ANYTYPE	laTestArgs 	= GetArgs()
	[ ]
	[ ] //Converting all the argument into a singe string
	[+] for (iTemp = 1; iTemp <= ListCount(laTestArgs); iTemp++)
		[ ] laTestArgs[iTemp] = Ltrim(Rtrim(laTestArgs[iTemp]))
		[ ]
		[ ] aPassArg = aPassArg + " {laTestArgs[iTemp]}"
	[ ]
	[ ] //Converting individual testcase and its corresponing argument into a List
	[ ] LIST OF ANYTYPE laTestCases = ParseStringToListOfAnytype(aPassArg, "/")
	[ ] INTEGER j = 0
	[ ]
	[ ] //Executing each individual testcase with its argument
	[+] for (iTemp = 1; iTemp <= ListCount(laTestCases); iTemp++)
		[+] do
			[ ]
			[ ] LIST OF ANYTYPE laTCData 	= ParseStringToListOfAnytype(laTestCases[iTemp], " ")
			[ ] STRING sTestcaseName 		= laTCData[1]
			[ ]
			[ ] ListDelete(laTCData, 1)		//To Get rid of the testcase name
			[ ]
			[ ] // Converting If an argument is more than one word to singe string
			[ ] INTEGER iStart = 0, iEnd = 0, k = 0, i = 0
			[+] for (i = 1; i <= ListCount(laTCData); i++)
				[ ]
				[+] if(laTCData[i][1] == "'")
					[ ] laTCData[i] = Stuff(laTCData[i], 1, 1, "")
					[ ] iStart = i
					[ ]
				[+] if(laTCData[i][StrLen(laTCData[i])] == "'")
					[ ] laTCData[i] = Stuff(laTCData[i], StrLen(laTCData[i]), 1, "")
					[ ] iEnd = i
					[ ]
				[ ] k = 0
				[+] for (k = iStart; k < iEnd; k++)
					[ ] laTCData[iStart] = laTCData[iStart] + " "+ laTCData[iStart + 1]
					[ ] ListDelete(laTCData, iStart + 1)
			[ ]
			[ ] // If passed value is an INTEGER, then Converting it to INTEGER.
			[+] for (j = 1; j <= ListCount(laTCData); j++)
				[+] if (Val(laTCData[j]) > 0)
					[ ] laTCData[j] = Val(laTCData[j])
					[ ]
			[ ]
			[ ] //Finally  executing the testcase along with its arguments
			[ ] ArgListCall(sTestcaseName, laTCData)
		[+] except
			[+] if(ExceptData() != NULL)
				[ ] LogWarning("{ExceptData()}")
				[ ] continue
		[ ]
		[ ]
	[ ]
	[ ]
[ ]
[+] VOID GetTestsFromFile(STRING sInputFile)	// To read the test FILE and store the values in the record before test execution
	[ ]
	[ ] INTEGER iTemp = 0 					//Temp variable
	[ ]
	[ ] LIST OF ANYTYPE laFileInfo 	= {}	//Contains entire file data
	[ ]
	[ ] // Reading the text file into a LIST
	[ ] ListRead(laFileInfo, sInputFile)
	[ ]
	[ ] // Getting the position of SCRIPT_NAME, Tescase and its TestData from the text file
	[+] for (iTemp = 1; iTemp <= ListCount(laFileInfo) ; iTemp++)
		[ ] laFileInfo[iTemp] = Ltrim(Rtrim(laFileInfo[iTemp]))
		[ ]
		[-] if( MatchStr("*FILE_NAME*", laFileInfo[iTemp]))
			[ ] laFileInfo[iTemp] = GetField(laFileInfo[iTemp], "=", 2)
			[ ] ListAppend(Script_Tc_TData.lsScriptName, laFileInfo[iTemp])
			[ ]
		[-] else
			[-] if(laFileInfo[iTemp] != "")
				[ ] ListAppend(Script_Tc_TData.laTestCaseTestData, LTrim(Rtrim(laFileInfo[iTemp])))
	[ ]
	[ ] // Writting run time script's name from .txt file to .inc file
	[ ] HFILE FileHandle
	[ ] FileHandle = FileOpen ("{HOST_GetEnv ("SILKGEN_HOME")}\SilkTest\Includes\SILKGEN_RunTimeScripts.inc", FM_WRITE)
	[+] for (iTemp = 1; iTemp <= ListCount(Script_Tc_TData.lsScriptName) ; iTemp++)
		[ ] // Open file, append line, and close
		[ ] FileWriteLine (FileHandle, '[ ] use "{Script_Tc_TData.lsScriptName[iTemp]}"')
	[ ] FileClose (FileHandle)
[ ]
[+] VOID RunTestsFromFile_ToScript()				//To run tests from FILE as a SCRIPT. This is being call in the main() of SILKGEN_RunFromFile.t
	[ ]
	[ ] INTEGER iTemp = 0, j = 0//Temp variable
	[ ]
	[ ] // Executing each individual testcase with its argument
	[+] for (iTemp = 1; iTemp <= ListCount(Script_Tc_TData.laTestCaseTestData); iTemp++)
		[-] do
			[ ] LIST  of ANYTYPE laTCData 	= ParseStringToListOfAnytype(Script_Tc_TData.laTestCaseTestData[iTemp], " ")
			[ ] j = 0
			[ ]
			[ ] STRING sTestcaseName 		= laTCData[1]
			[ ] ListDelete(laTCData, 1)		//To Get rid of the testcase name
			[ ]
			[ ] // Conerting If an argument is more than one word to singe string
			[ ] INTEGER iStart = 0, iEnd = 0, k = 0, i = 0
			[+] for (i = 1; i <= ListCount(laTCData); i++)
				[ ]
				[+] if(laTCData[i][1] == '"')
					[ ] laTCData[i] = Stuff(laTCData[i], 1, 1, "")
					[ ] iStart = i
					[ ]
				[+] if(laTCData[i][StrLen(laTCData[i])] == '"')
					[ ] laTCData[i] = Stuff(laTCData[i], StrLen(laTCData[i]), 1, "")
					[ ] iEnd = i
					[ ]
				[ ] k = 0
				[+] for (k = iStart; k < iEnd; k++)
					[ ] laTCData[iStart] = laTCData[iStart] + " "+ laTCData[iStart + 1]
					[ ] ListDelete(laTCData, iStart + 1)
			[ ]
			[ ]
			[ ] // If passed value is an INTEGER, then Converting it to INTEGER.
			[-] for (j = 1; j <= ListCount(laTCData); j++)
				[-] if (Val(laTCData[j]) > 0)
					[ ] laTCData[j] = Val(laTCData[j])
					[ ]
			[ ] ArgListCall(sTestcaseName, laTCData)
			[ ]
		[+] except
			[+] if(ExceptData() != NULL)
				[ ] LogWarning(ExceptData())
				[ ] continue
[ ]
[+] VOID CreatePlanFromTestFile(STRING sInputFile, STRING sOutputPlanFile)	//To run tests from FILE as a PLAN. This is being call in the main() of
	[ ]
	[ ] INTEGER iTemp = 0 					//Temp variable
	[ ]
	[ ] LIST OF ANYTYPE laFileInfo 	= {}	//Contains entire file data
	[ ]
	[ ] HFILE FileHandle
	[ ]
	[ ] FileHandle = FileOpen (sOutputPlanFile, FM_WRITE)
	[ ]
	[ ] // Reading the text file into a LIST
	[ ] ListRead(laFileInfo, sInputFile)
	[ ]
	[ ] // Getting the position of SCRIPT_NAME, Tescase and its TestData from the text file
	[+] for (iTemp = 1; iTemp <= ListCount(laFileInfo); iTemp++)
		[ ] laFileInfo[iTemp] = Ltrim(Rtrim(laFileInfo[iTemp]))
		[ ]
		[ ] // Writting Script's name to Plan File
		[+] if( MatchStr("*FILE_NAME*", laFileInfo[iTemp]))
			[ ] laFileInfo[iTemp] = GetField(laFileInfo[iTemp], "=", 2)
			[ ] FileWriteLine (FileHandle, '[+] EXECUTING TEST FROM FILE : {laFileInfo[iTemp]}')
			[ ] FileWriteLine (FileHandle, '	[ ] script: {laFileInfo[iTemp]}')
		[ ]
		[ ] // Writting TestCase's name, TestData to Plan File against the FileName
		[+] else
			[+] if(laFileInfo[iTemp] != "")
				[ ]
				[ ] LIST OF ANYTYPE laTC_TCData = ParseStringToListOfAnytype(laFileInfo[iTemp], " ")
				[ ]
				[ ] STRING sTestcaseName 		= laTC_TCData[1]
				[ ] ANYTYPE aTestData			= ""
				[ ] INTEGER i = 0
				[ ] ListDelete(laTC_TCData, 1)		//To Get rid of the testcase name
				[ ]
				[ ] FileWriteLine (FileHandle, '	[+] TestCase : {sTestcaseName}')
				[ ] FileWriteLine (FileHandle, '		[ ] testcase: {sTestcaseName}')
				[ ]
				[ ] // Writting test data to plan file
				[+] if (ListCount(laTC_TCData) > 0)
					[ ]
					[ ] // Conerting If an argument is more than one word, enclose it with quotation marks.
					[ ] INTEGER iStart = 0, iEnd = 0, k = 0
					[+] for (i = 1; i <= ListCount(laTC_TCData); i++)
						[ ]
						[+] if(laTC_TCData[i][1] == '"')
							[ ] laTC_TCData[i] = Stuff(laTC_TCData[i], 1, 1, "")
							[ ] iStart = i
							[ ]
						[+] if(laTC_TCData[i][StrLen(laTC_TCData[i])] == '"')
							[ ] laTC_TCData[i] = Stuff(laTC_TCData[i], StrLen(laTC_TCData[i]), 1, "")
							[ ] iEnd = i
							[ ]
						[ ] k = 0
						[+] for (k = iStart; k < iEnd; k++)
							[ ] laTC_TCData[iStart] = laTC_TCData[iStart] + " "+ laTC_TCData[iStart + 1]
							[ ] ListDelete(laTC_TCData, iStart + 1)
					[ ]
					[ ] //Writting test data to plan file
					[+] for (i = 1; i <= ListCount(laTC_TCData); i++)
						[+] if(i == 1)
							[+] if(Val(laTC_TCData[i]) > 0)	//Checking the type of data being passed and converting it based on its type.
								[ ] aTestData = laTC_TCData[i]
							[+] else
								[ ] aTestData = '"{laTC_TCData[i]}"' //converting to STRING
						[+] else
							[+] if(Val(laTC_TCData[i]) > 0) //Checking the type of data being passed and converting it based on its type.
								[ ] aTestData = '{aTestData}, {laTC_TCData[i]}'
							[+] else
								[ ] aTestData = '{aTestData}, "{laTC_TCData[i]}"' //converting to STRING
					[ ] FileWriteLine (FileHandle, '		[ ] testdata: {aTestData}')
					[ ]
				[ ]
	[ ]
	[ ] FileClose (FileHandle)
	[ ]
[ ]
[+] // testcase A11() appstate none
	[ ] // // RunTestsFromFile_Script()
	[ ] // CreatePlanFromTestFile("D:\SILKGEN\SilkTest\Scripts\TestFile.txt", "D:\SILKGEN\SilkTest\Scripts\SILKGEN_RunFromFile.pln")
	[ ] // //Print(Val("Amiya Ranjan Pattnayak"))
	[ ] //
