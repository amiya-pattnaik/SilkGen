[ ]
[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_DriverScript.t
[ ] 
[ ] //	**************************************************************************************************** //
[ ]
[ ] // 	SILKGEN -				:	This is the Driver Script specific to SILKGEN Framework are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		12/01/08	Amiya Pattnayak	Created
	[ ] //
[ ]
[ ] //	**************************************************************************************************** //
[ ]
[+] // testcase DriverTest (LIST OF FUNCTION_DATA lfSetup, LIST OF FUNCTION_DATA lfTest, LIST OF FUNCTION_DATA lfVerify, LIST OF FUNCTION_DATA lfCleanup) //appstate none
	[ ] //
	[ ] // FUNCTION_DATA fdI
	[ ] // INTEGER iNumSetup 	= ListCount (lfSetup)
	[ ] // INTEGER iNumTest 	= ListCount (lfTest)
	[ ] // INTEGER iNumVerify 	= ListCount (lfVerify)
	[ ] // INTEGER iNumCleanup = ListCount (lfCleanup)
	[ ] //
	[ ] // // run setup functions
	[+] // if iNumSetup > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Setup Functions:")
			[ ] // RunFuncsVerbose (lfSetup)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfSetup
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
	[ ] //
	[ ] // // run test functions
	[+] // if iNumTest > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Test Functions:")
			[ ] // RunFuncsVerbose (lfTest)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfTest
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
	[ ] //
	[ ] // // run verify functions
	[+] // if iNumVerify > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Verify Functions:")
			[ ] // RunFuncsVerbose (lfVerify)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfVerify
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
	[ ] //
	[ ] // // run cleanup functions
	[+] // if iNumCleanup > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Cleanup Functions:")
			[ ] // RunFuncsVerbose (lfCleanup)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfCleanup
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
[ ]
[+] // DriverTest (LIST OF FUNCTION_DATA lfSetup, LIST OF FUNCTION_DATA lfTest, LIST OF FUNCTION_DATA lfVerify, LIST OF FUNCTION_DATA lfCleanup) //appstate none
	[ ] //
	[ ] // FUNCTION_DATA fdI
	[ ] // INTEGER iNumSetup 	= ListCount (lfSetup)
	[ ] // INTEGER iNumTest 	= ListCount (lfTest)
	[ ] // INTEGER iNumVerify 	= ListCount (lfVerify)
	[ ] // INTEGER iNumCleanup = ListCount (lfCleanup)
	[ ] //
	[ ] // // run setup functions
	[+] // if iNumSetup > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Setup Functions:")
			[ ] // RunFuncsVerbose (lfSetup)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfSetup
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
	[ ] //
	[ ] // // run test functions
	[+] // if iNumTest > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Test Functions:")
			[ ] // RunFuncsVerbose (lfTest)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfTest
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
	[ ] //
	[ ] // // run verify functions
	[+] // if iNumVerify > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Verify Functions:")
			[ ] // RunFuncsVerbose (lfVerify)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfVerify
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
	[ ] //
	[ ] // // run cleanup functions
	[+] // if iNumCleanup > 0
		[+] // if VERBOSE
			[ ] // ResOpenList ("Cleanup Functions:")
			[ ] // RunFuncsVerbose (lfCleanup)
			[ ] // ResCloseList ()
		[+] // else
			[+] // for each fdI in lfCleanup
				[ ] // ArgListCall (fdI.sFuncName, fdI.laArgs)
[ ]
