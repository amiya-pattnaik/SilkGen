[ ]
[ ] //	**************************************************************************************************** //
[ ] 
[ ] //	File Name			:	SILKGEN_Defaults.inc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Functions specific to SILKGEN Framework are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		12/01/08	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[+] // TestPlanEnter()
	[ ] // // Creating a Plan File against the ScriptName, TestcaseName & its respective TestData from the .txt file
	[ ] // SILKGEN_Init()
	[+] // if(Properties_KeyValues.sTestFileToRun != "")
		[ ] // RunTestsFromFile_Plan("{Properties_KeyValues.sTestFileToRun}")
		[ ] //
[ ]
[+] ScriptEnter ()
	[ ] SILKGEN_Init()
	[ ] sScriptStartDateAndTime = FormatDateTime (GetDateTime(), "ddd mmmm dd yyyy - hh:nn:ss AM/PM")
	[ ]
	[+] switch(Lower(Properties_KeyValues.sReportType))
		[+] case ""
			[ ] //no customized reports
		[+] case "none"
			[ ] //no customized reports
		[+] case "xml"
			[ ] WriteXMLStartingNode()
			[ ] WriteScriptInfoToXML()
			[ ]
		[+] case "text"
			[ ] WriteScriptInfoToFile()
		[+] case "res"
			[ ] //no customized reports
		[ ]
		[+] default
			[ ] Print ("Invalid report type")
		[ ]
	[ ]
	[ ] //Getting ScriptName, TestcaseName & its respective TestData from the .txt file -
	[ ] //- and storing it in the record 'Script_Tc_TData'
	[+] if(Properties_KeyValues.sTestFileToRun != "")
		[ ] GetTestsFromFile("{Properties_KeyValues.sTestFileToRun}")
		[ ]
		[ ]
	[ ]
	[ ]
	[ ] //Connecting to the remote machine
	[ ] ConnectTargetMachine(Properties_KeyValues.sTargetMachine)
	[ ]
[ ]
[+] ScriptExit(Boolean bException)
	[-] switch(Lower(Trim(Properties_KeyValues.sReportType)))
		[+] case ""
			[ ] //no customized reports
		[+] case "none"
			[ ] //no customized reports
		[+] case "xml"
			[ ] WriteXMLEndingNode()
		[+] case "text"
			[ ] //not adding any footer information in test file report generation
		[-] case "res"
			[ ] //no customized reports
		[ ]
		[+] default
			[ ] Print ("Invalid report type")
		[ ]
	[ ]
	[ ] //Disonnecting to the remote machine
	[+] if !(GetMachineName(GetMachine ()) == sLocalMachine)
		[ ] DisconnectTargetMachine(Properties_KeyValues.sTargetMachine)
	[ ]
	[ ]
[ ]
[+] TestCaseEnter()
	[ ] dTestcaseStartTime = GetDateTime()
	[ ] sTCStartDate = FormatDateTime (dTestcaseStartTime, "ddd mmmm dd yyyy")
	[ ] sTCStartTime = FormatDateTime (dTestcaseStartTime, "hh:nn:ss AM/PM")
	[ ]
[ ]
[+] TestCaseExit(Boolean bException)
	[ ] dTestcaseEndTime = GetDateTime ()
	[ ] DiffDateTime (dTestcaseEndTime, dTestcaseStartTime, iHours, iMinutes, iSeconds)
	[ ] aTestcaseOutPut = ExceptData()
	[ ]
	[+] if(GetTestCaseStatus() == "Passed")
		[ ] aTestcaseOutPut = "!!! Testcase executed without any error !!!"
		[ ] lsCallStack		= {"!!! All the steps in the testcase are executed without any error !!!"}
	[+] else if(aTestcaseOutPut == NULL)
			[ ] aTestcaseOutPut = "!!! Error: in the testcase. For more details please check the SilkTest result file !!!"
			[ ] lsCallStack		= {"!!! Error in the steps. For more details please check the SilkTest result file !!!"}
	[+] else
		[ ] aTestcaseOutPut = ExceptData()
		[ ] WriteCallStackToList()
	[ ]
	[+] switch(Lower(Trim(Properties_KeyValues.sReportType)))
		[+] case ""
			[ ] //no customized reports
		[+] case "none"
			[ ] //no customized reports
		[+] case "xml"
			[ ] WriteTestCaseInfoToXML()
		[+] case "text"
			[ ] WriteTestCaseInfoToFile (GetTestCaseStatus(), "{Properties_KeyValues.sTestDescription}", "{aTestcaseOutPut}")
		[+] case "res"
			[ ] //no customized reports
		[ ]
		[+] default
			[ ] Print ("Invalid report type")
		[ ]
	[ ]
	[+] if(Properties_KeyValues.iDebugMode != 0)
		[ ] WriteLogDetailsToLogFile()
	[ ]
	[-] if (bException)
		[ ] ExceptLog ()
		[ ] //DefaultTestCaseExit(bException)
		[ ]
[ ]
[ ] //	**************************************************************************************************** //
[ ]
