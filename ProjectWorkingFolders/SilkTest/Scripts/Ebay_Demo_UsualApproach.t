[ ] //	Testcases for demo purpose, Uses ebay India website (www.ebay.in)	//
[ ] //	Below testcases are developed using Conventional SilkTest approach	//
[ ] 
[ ] 
[ ] STRING sFileName 	= "Ebay_Data.xls"
[ ] STRING sTableName 	= "TestData1"
[ ] 
[+] type ExcelTable is record
	[ ] STRING sTestCaseID
	[ ] STRING sUserName
	[ ] STRING sPassword
	[ ] STRING sExpectedData
	[ ] 
[ ] ExcelTable MyExcelTable
[ ] 
[+] VOID LoadTestCaseData(STRING sFileName, STRING sTableName, STRING sTestCase)
	[ ] STRING 		sConnection
	[ ] HSQL 		hstmnt
	[ ] HDATABASE 	hdbc
	[ ] 
	[ ] sConnection = "DRIVER=Microsoft Excel Driver (*.xls);FIRSTROWHASNAMES=1;READONLY=TRUE;DRIVERID=790;" + "DBQ={PROJECT_HOME}\SilkTest\Data\{sFileName}"
	[ ] 
	[ ] hdbc 		= DB_Connect(sConnection)
	[ ] 
	[ ] hstmnt 		= DB_Executesql(hdbc, "SELECT * FROM [{sTableName}$] where TestCaseID = '{sTestCase}'")
	[ ] 
	[+] while (DB_FetchNext(hstmnt, MyExcelTable))
		[ ] 
	[ ] DB_FinishSQL(hstmnt)
	[ ] DB_Disconnect(hdbc)
	[ ] 
	[ ] 
[ ] 
[+] testcase TC_01 () appstate none
	[ ] //Fetching the data from the Spreadsheet
	[ ] LoadTestCaseData(sFileName, sTableName, "TC_01")
	[ ] 
	[ ] //Invoking the browser and Loading the URL
	[ ] InvokeEbay ()
	[ ] 
	[ ] //Verification of Home Page
	[+] do
		[ ] VerifyExists(@(MyExcelTable.sExpectedData), TRUE)
		[ ] RES.Print ("EBay Home page is displayed")
	[+] except
		[ ] RES.LogError ("** Could not find EBay Home Pag **")
	[ ] 
[ ] 
[+] testcase TC_02 () appstate none
	[ ] 
	[ ] //***** Invoking the browser and Loading the URL *****//
	[ ] InvokeEbay ()
	[ ] 
	[ ] //*****	Fetching Data from the Table *****//
	[ ] LoadTestCaseData(sFileName, sTableName, "TC_02")
	[ ] 
	[ ] LIST OF STRING lsExpData = ParseStringList(MyExcelTable.sExpectedData, Chr(10))//Note: ParseStringList is SCAF Function
	[ ] 
	[ ] 
	[ ] //***** Verification of Header/Footer Elements *****//
	[ ] LIST OF WINDOW lwWindows
	[ ] STRING sExpectedData
	[ ] WINDOW wWin
	[ ] 
	[+] for each sExpectedData in lsExpData
		[ ] wWin = EBayHome.@(sExpectedData)
		[ ] ListAppend (lwWindows,wWin)
	[ ] VerifyWindowsExist (lwWindows)
	[ ] VerifyHeader ()
	[ ] 
[ ] 
[+] testcase TC_03 () appstate none
	[ ] 
	[ ] //***** Invoking the browser and Loading the URL *****//
	[ ] InvokeEbay ()
	[ ] 
	[ ] //*****	Fetching Data from the Table *****//
	[ ] LoadTestCaseData(sFileName, sTableName, "TC_03")
	[ ] 
	[ ] 
	[ ] LIST OF STRING lsExpData = ParseStringList(MyExcelTable.sExpectedData, Chr(10))//Note: ParseStringList is SCAF Function
	[ ] 
	[ ] //***** Verification of Header/Footer Elements *****//
	[ ] LIST OF WINDOW lwWindows
	[ ] STRING sExpectedData
	[ ] WINDOW wWin
	[ ] 
	[+] for each sExpectedData in lsExpData
		[ ] wWin = EBayHome.@(sExpectedData)
		[ ] ListAppend (lwWindows,wWin)
	[ ] VerifyWindowsExist (lwWindows)
	[ ] VerifyHeader ()
	[ ] 
[ ] 
[+] testcase TC_04 () appstate none
	[ ] 
	[ ] //Fetching the data from the Spreadsheet
	[ ] LoadTestCaseData(sFileName, sTableName, "TC_04")
	[ ] 
	[ ] //Invoking the browser and Loading the URL
	[ ] InvokeEbay ()
	[ ] 
	[ ] //Looging into Ebay application
	[ ] 
	[ ] //Clicking the Sighin link to get the required loging page
	[ ] EBayHome.SetActive( )
	[ ] EBayHome.SignIn.Click ()
	[ ] Browser.WaitForReady(300)
	[ ] //Sleep(10)
	[ ] 
	[+] if (!WelcomeToEBay.Exists(30))
		[ ] Browser.WaitForReady(300)
		[ ] //Sleep(2)
		[ ] 
	[ ] 
	[ ] WelcomeToEBay.SetActive()
	[ ] WelcomeToEBay.UserID.ClearText()
	[ ] WelcomeToEBay.UserID.SetText(MyExcelTable.sUserName)
	[ ] WelcomeToEBay.Password.SetText(MyExcelTable.sPassword)
	[ ] WelcomeToEBay.SignedIn.Click ()
	[ ] 
	[ ] 
	[ ] //Verification of Login Functionality
	[+] if (Upper(EBayMessage.User.GetText()) == "HI, ({Upper(MyExcelTable.sUserName)})!")  //Hi, (test_ctsuser)!
		[ ] Print ("You have successfully Loged in with user {MyExcelTable.sUserName}")
	[+] else
		[ ] LogError("You are not successfully Loged in")
		[ ] 
	[ ] 
	[ ] //Cleanup the test case by loggin out
	[ ] AnyEbayPage.Logout ()
	[ ] Browser.WaitForReady(180)
[ ] 
[+] testcase TC_05 () appstate none
	[ ] //Fetching the data from the Spreadsheet
	[ ] LoadTestCaseData(sFileName, sTableName, "TC_05")
	[ ] 
	[ ] //Invoking the browser and Loading the URL
	[ ] InvokeEbay ()
	[ ] 
	[ ] //Looging into Ebay application
	[ ] 
	[ ] //Clicking the Sighin link to get the required loging page
	[ ] EBayHome.SetActive( )
	[ ] EBayHome.SignIn.Click ()
	[ ] Browser.WaitForReady(300)
	[ ] //Sleep(10)
	[ ] 
	[+] if (!WelcomeToEBay.Exists(30))
		[ ] Browser.WaitForReady(300)
		[ ] //Sleep(2)
		[ ] 
	[ ] 
	[ ] WelcomeToEBay.SetActive()
	[ ] WelcomeToEBay.UserID.ClearText()
	[ ] WelcomeToEBay.UserID.SetText(MyExcelTable.sUserName)
	[ ] WelcomeToEBay.Password.SetText(MyExcelTable.sPassword)
	[ ] WelcomeToEBay.SignedIn.Click ()
	[ ] 
	[ ] 
	[ ] //Logging out of Ebay application
	[ ] AnyEbayPage.Logout ()
	[ ] Browser.WaitForReady(180)
	[ ] 
	[ ] //Verification of Logout functionality
	[ ] //Check for Logging out working fine
	[+] do
		[ ] VerifyExists (AnyEbayPage.HtmlText (MyExcelTable.sExpectedData),TRUE)
		[ ] RES.Print ("EBay logout page is displayed")
	[+] except
		[ ] RES.LogError ("**Logout page is not displayed **")
	[ ] 
[ ] 
[+] testcase TC_06 () appstate none
	[ ] //Fetching the data from the Spreadsheet
	[ ] LoadTestCaseData(sFileName, sTableName, "TC_06")
	[ ] 
	[ ] //Invoking the browser and Loading the URL
	[ ] InvokeEbay ()
	[ ] 
	[ ] //Invoking Registration Page
	[ ] InvokeRegistrationPage ()
	[ ] 
	[ ] 
	[ ] //Verification of Registration Page elements
	[ ] LIST OF WINDOW 	lwVerify
	[ ] WINDOW			wToVerify
	[ ] 
	[ ] 
	[ ] lwVerify = RegisterPage.@ (MyExcelTable.sExpectedData)
	[ ] 
	[ ] //Verification of Registatretion Fields
	[+] for each wToVerify in lwVerify
		[+] if (!wToVerify.Exists (5))
			[ ] LogErrorSnapBmp ("***Error: VerifyWindowsExist - Window {wToVerify} did not exist")
		[+] else
			[ ] Print ("VerifyWindowsExist - Verified that window {wToVerify} exists")
			[ ] 
[ ] 
[ ] 
