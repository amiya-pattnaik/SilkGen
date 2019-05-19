[ ] // Record Decalarion for Excel Values
[ ] 
[+] type ExcelData is record
	[ ] 
	[ ] STRING sTestCaseID
	[ ] STRING sUserName
	[ ] STRING sPassword
	[ ] LIST OF STRING lsExpectedData
[ ] 
[ ] ExcelData mExcelData
[ ] 
[ ] 
[ ] // Excel Mapping
[+] LIST OF EXCELMAP leExcelData = {...}
	[ ] {"TestCaseID",		"sTestCaseID"}
	[ ] {"UserName",		"sUserName"}
	[ ] {"Password",		"sPassword"}
	[ ] {"Expected Data",	"lsExpectedData[]"}
	[ ] 
