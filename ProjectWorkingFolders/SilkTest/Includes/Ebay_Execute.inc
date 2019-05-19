[ ] //	Executable Functions that are directly used either in TestCases/TestPlan
[ ] //	Below executable functions internally uses SCAF functions.
[ ] 
[ ] 
[+] //Function Info:
	[ ] // function  	: InvokeEbay()
	[ ] // returns   	: VOID
	[ ] // parameter 	: None
	[ ] // notes		: Invoke the application's Home page.
	[ ] 							
[+] VOID InvokeEbay ()
	[ ] 
	[+] if(!Browser.Exists(1))
		[ ] Browser.Invoke()
	[ ] Browser.SetActive()
	[ ] // Loading the Application URL
	[ ] Browser.LoadPage(sURL)
	[ ] Browser.WaitForReady(180)
	[ ] Browser.Maximize()
	[ ] 
	[ ] //Browser.WaitForReady(300)
	[ ] Sleep(10)
	[ ] 
[ ] 
[ ] //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
[ ] // 							Test Functions
[ ] //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
[+] VOID HeaderandFooter (STRING sSpreadsheet, STRING sTable, STRING sTestCase) 
	[ ] //Fetching the data from the Spreadsheet
	[ ] Excel_LoadTableRow (mExcelData, sSpreadsheet, sTable, leExcelData,"TestCaseID = '{sTestCase}'")
[ ] 
[+] VOID LoginToEbay (STRING sSpreadsheet, STRING sTable, STRING sTestCase )
	[ ] //Fetching the data from the Spreadsheet
	[ ] Excel_LoadTableRow (mExcelData, sSpreadsheet, sTable, leExcelData,"TestCaseID = '{sTestCase}'")
	[ ] EBayHome.Login ()
	[ ] 
[ ] 
[+] VOID LogoutOfEbay (STRING sSpreadsheet, STRING sTable, STRING sTestCase)  
	[ ] 
	[ ] //Logging into Ebay
	[ ] LoginToEbay (sSpreadsheet,sTable,sTestCase)
	[ ] 
	[ ] //Logging out
	[ ] AnyEbayPage.Logout ()
[ ] 
[+] VOID InvokeRegistrationPage ()
	[ ] //Invoking Home Page
	[ ] RegisterPage.Invoke ()
	[ ] 
[ ] 
[ ] //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
[ ] //							Verification functions
[ ] //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
[+] VOID VerifyHomePage (STRING sSpreadsheet, STRING sTable, STRING sTestCase) 
	[ ] 
	[ ] 
	[ ] //Fetching the data from the Spreadsheet
	[ ] Excel_LoadTableRow (mExcelData, sSpreadsheet, sTable, leExcelData,"TestCaseID = '{sTestCase}'")
	[ ] 
	[ ] //Verification of the Home Page
	[+] do
		[ ] VerifyExists(@(mExcelData.lsExpectedData[1]), TRUE)								
		[ ] RES.Print ("EBay Home page is displayed")
	[+] except
		[ ] RES.LogError ("** Could not find EBay Home Pag **")
	[ ] 
[ ] 
[+] VOID VerifyHeader ()
	[ ] LIST OF WINDOW lwWindows
	[ ] STRING sExpectedData
	[ ] WINDOW wWin
	[ ] 
	[ ] //Verification of Header and Footer
	[+] for each sExpectedData in mExcelData.lsExpectedData
		[ ] wWin = EBayHome.@(sExpectedData)
		[ ] ListAppend (lwWindows,wWin)
	[ ] VerifyWindowsExist (lwWindows)
[ ] 
[+] VOID VerifyFooter ()
	[ ] LIST OF WINDOW lwWindows
	[ ] STRING sExpectedData
	[ ] WINDOW wWin
	[ ] 
	[ ] //Verification of Header and Footer
	[+] for each sExpectedData in mExcelData.lsExpectedData
		[ ] wWin = EBayHome.@(sExpectedData)
		[ ] ListAppend (lwWindows,wWin)
	[ ] VerifyWindowsExist (lwWindows)
[ ] 
[+] VOID VerifyLoginFunctionality ()
	[ ] 
	[ ] //Verify Logged in
	[ ] AnyEbayPage.VerifyLogin(mExcelData.sUserName)
	[ ] 
[ ] 
[+] VOID VerifyLogoutFunctionality ()
	[ ] 
	[ ] //Check for Logging out working fine
	[+] do
		[ ] VerifyExists (AnyEbayPage.HtmlText (mExcelData.lsExpectedData[1]),TRUE)
		[ ] RES.Print ("EBay logout page is displayed")
	[+] except
		[ ] RES.LogError ("**Logout page is not displayed **")
[ ] 
[+] VOID VerifyRegistrationPageElements (STRING sSpreadsheet, STRING sTable, STRING sTestCase )  
	[ ] LIST OF WINDOW lwVerify
	[ ] 
	[ ] //Fetching the data from the Spreadsheet
	[ ] Excel_LoadTableRow (mExcelData, sSpreadsheet, sTable, leExcelData,"TestCaseID = '{sTestCase}'")
	[ ] 
	[ ] lwVerify = RegisterPage.@ (mExcelData.lsExpectedData[1])
	[ ] 
	[ ] //Verification of Registatretion Fields
	[ ] VerifyWindowsExist (lwVerify, 6)
	[ ] 
[ ] 
[ ] //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
[ ] //							Cleanup functions
[ ] //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
[-] VOID LogoutEbay ()
	[ ] //Logging out
	[ ] AnyEbayPage.Logout ()
	[ ] 
	[ ] //Closing the Browsers
	[ ] SG_CloseAllBrowsers ()
