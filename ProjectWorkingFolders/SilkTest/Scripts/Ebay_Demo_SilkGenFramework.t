[ ] //	Testcases for demo purpose, Uses ebay India website (www.ebay.in)	//
[ ] //	Below testcases internally uses SCAF functions	//
[ ] 
[ ] STRING sFileName 	= "Ebay_Data.xls"
[ ] STRING sTableName 	= "TestData1"
[ ] 
[ ] 
[+] testcase TC_01 () appstate none
	[ ] 
	[ ] //Invoking the browser and Loading the URL
	[ ] InvokeEbay ()
	[ ] 
	[ ] //Verification of Home Page
	[ ] VerifyHomePage (sFileName,sTableName,"TC_01")
[ ] 
[+] testcase TC_02 () appstate none
	[ ] 
	[ ] //Invoking the browser and Loading the URL
	[ ] InvokeEbay ()
	[ ] 
	[ ] //Fetching Data from the Table
	[ ] HeaderandFooter (sFileName,sTableName,"TC_02")
	[ ] 
	[ ] //Verification of Header Elements
	[ ] VerifyHeader ()
	[ ] 
[ ] 
[+] // testcase TC_03 () appstate none
	[ ] // //Invoking the browser and Loading the URL
	[ ] // InvokeEbay ()
	[ ] // 
	[ ] // //Fetching Data from the Table
	[ ] // HeaderandFooter (sFileName,sTableName,"TC_02")
	[ ] // 
	[ ] // //Verification of Footer Elements
	[ ] // VerifyFooter ()
	[ ] // 
[ ] // 
[+] // testcase TC_04 () appstate none
	[ ] // //Invoking the browser and Loading the URL
	[ ] // InvokeEbay ()
	[ ] // 
	[ ] // //Looging into Ebay application
	[ ] // LoginToEbay (sFileName,sTableName,"TC_04")
	[ ] // 
	[ ] // //Verification of Login Functionality
	[ ] // VerifyLoginFunctionality ()
	[ ] // 
	[ ] // //Cleanup the test case by loggin out
	[ ] // AnyEbayPage.Logout ()
[ ] // 
[+] // testcase TC_05 () appstate none
	[ ] // //Invoking the browser and Loading the URL
	[ ] // InvokeEbay ()
	[ ] // 
	[ ] // //Logging out of Ebay application
	[ ] // LogoutOfEbay (sFileName,sTableName,"TC_05")
	[ ] // 
	[ ] // //Verification of Logout functionality
	[ ] // VerifyLogoutFunctionality ()
	[ ] // 
[ ] // 
[+] // testcase TC_06 () appstate none
	[ ] // //Invoking the browser and Loading the URL
	[ ] // InvokeEbay ()
	[ ] // 
	[ ] // //Invoking Registration Page
	[ ] // InvokeRegistrationPage ()
	[ ] // 
	[ ] // 
	[ ] // //Verification of Registration Page elements
	[ ] // VerifyRegistrationPageElements (sFileName,sTableName,"TC_06")
	[ ] // 
[ ] 
