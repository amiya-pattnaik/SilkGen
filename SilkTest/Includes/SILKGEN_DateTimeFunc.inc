[ ] //	**************************************************************************************************** //
[ ] 
[ ] //	File Name			:	SILKGEN_DateTimeFunc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Date-Time manipulation functions are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		04/06/09	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ]
[ ] // //  ---------------------------------------------------------------------------------------------------- //
[ ] //									DATE/TIME RELATED FUNCTIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // function:  sDateTime = CreateCurrentDTSString ()
[ ] // parameter: 	none
[ ] // returns:   	sDateTime: The 12-character date time stamp in mmddyyhhnnss format. STRING.
[ ] // Action:     	Returns a string based on current date time stamp for use in creating unique data.
[+] STRING CreateCurrentDTSString ()
	[+] do
		[ ]
		[ ] STRING sDate
		[ ]
		[ ] sDate = FormatDateTime (GetDateTime (),"mmddyyhhnnss")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: CreateCurrentDTSString in testcase: {GetTestCaseName()}	success")
		[ ] return (sDate)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: CreateCurrentDTSString in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
