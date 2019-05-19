[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_MainFunction.inc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	It contains only main() function specific to SILKGEN Framework are incluced here.
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		18/05/09	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ] //	This main () function is used to run selected testcases from a script file
[ ]
[+] main()		//Comment or uncomment this main() or its sub-functions when ever required by your project
	[ ]
	[ ] //RunTestsFromCommandLine()	// This is to run testcases from command line from SILKGEN GUI. comment or uncomment whenever required.
	[ ] RunTestsFromSingleScriptFile()
	[ ]
[ ]
[ ]
[ ] //	This main() function is for running selected testcases/functions from different script/include files (more than one file)
[ ] // 	For this options the script, include files names and the testcase names hould be provided in a .txt file
[ ] // 	The path of the .txt file is assigned in the .properties file against the "field TestFileToRun=Pathof the .txt file"
[ ]
[+] // main()
	[ ] // RunTestsFromFile_ToScript()
	[ ] //
