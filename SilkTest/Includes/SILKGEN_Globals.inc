[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_Globals.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -			:	All Global declarations that are specific to SILKGEN Framework are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		12/01/08	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ] ANYTYPE 	aTestcaseOutPut 	= ""			//Used to hold testcase output if any error in the testcase
[ ] LIST OF ANYTYPE laLogDetails 	= {}			//Used to hold all error details (used in writting log files)
[ ]
[ ]
[ ] DATETIME 	dTestcaseStartTime					//testcase start time
[ ] DATETIME 	dTestcaseEndTime					//testcase end time
[ ]
[ ] INTEGER 	iDaysDiff, iHours, iMinutes, iSeconds
[ ] BOOLEAN 	VERBOSE 	= TRUE
[ ] BOOLEAN 	bLocalAgent = TRUE
[ ]
[ ] LIST OF STRING lsCallStack = {}					//used to write TestCaseInfoToXML file
[+] LIST OF STRING lsPROP_KEYS = {...}				//Contains KEYS name of the properties file
	[ ] "TargetMachine"
	[ ] "DefaultBrowser"
	[ ] "LocalMachineErrorDir"
	[ ] "RemoteMachineErrorDir"
	[ ] "ReportType"
	[ ] "DebugMode"
	[ ] "TestSetName"
	[ ] "TestDescription"
	[ ] "TestFileToRun"
	[ ]
[ ]
[ ] STRING	sScriptStartDateAndTime 	= "" 		//Script start date and time
[ ] STRING	sTCStartDate							//testcase start date
[ ] STRING	sTCStartTime							//testcase start time
[ ] STRING	sRunTimeFile 				= FormatDateTime (GetDateTime(), "ddmmyy_hhnnss")	//to create file based on the time stamp
[ ] STRING	sTestUser 					= GetNTUser()			//the user who loged in to the computer
[ ] STRING	sHost						= GetThisComputerName()	//the name of the computer in which test is running
[ ]
[ ] const	STRING	sLocalMachine 		= "(local)"	//local machine
[ ] const	STRING	SILKGEN_HOME		= "{HOST_GetEnv ("SILKGEN_HOME")}"	//framework working folder
[ ] const	STRING	PROJECT_HOME		= "{HOST_GetEnv ("PROJECT_HOME")}"	//project working folder
[ ]
[ ] HMACHINE 	hTargetMachine
[ ] HMACHINE 	hLocalMachine			= GetMachine ()
[ ]
[ ]
