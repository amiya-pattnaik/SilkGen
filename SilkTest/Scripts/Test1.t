[ ] 
[+] testcase T100(STRING sNmae, INTEGER sNmae1)
	[ ] //LIST OF ANYTYPE lsArgs = GetArgs()
	[ ] Print ("First Name is :- {sNmae} ")
	[ ] 
	[ ] Print ("Second value is :- {sNmae1} ")
	[ ] 
	[ ] //Print ("Total is :- {val(sNmae1) + 10}")
	[ ] 
	[ ] //Print ("Argument Passed is {lsArgs}")
	[ ] //Print ("")
	[ ] 
[ ] 
[+] testcase T2(STRING sNmae) appstate none
	[ ] Print ("Last Name is :- {sNmae}")
	[ ] 
[ ] 
[+] testcase T3(STRING sNmae) appstate none
	[ ] Print ("Last Name is :- {sNmae}")
	[ ] 
[ ] 
[+] // testcase IF () appstate none
	[ ] // 
	[ ] // CloseAllBrowsers()						//Yes
	[ ] // //DeleteCookies								//yes
	[ ] // //DeleteCookiesRestartBrowser()				//Yes
	[ ] // //DeleteTempInternetFiles()					//yes
	[ ] // //FindBadImages("D:\Amiya\Test\URL.txt")	//yes
	[ ] // //IE_FindOnPage("Search")					//yes
	[ ] // //PrintPage()								//yes
	[ ] // 
	[ ] // //LIST OF STRING lsLink =	{"Sign in", "Create an account now", "Learn More"}
	[ ] // //NavigateLinks(lsLink)						//yes
	[ ] // 
	[ ] // //PageLoadTimes("www.google.com", 4)		//yes
	[ ] // 
	[ ] // //SaveAndVerifyPageSize("Google", "D:\Amiya\Test", "PageSize1.csv", "PageSize2.csv" )  //no
	[ ] // 
	[ ] // 
[ ] 
[+] testcase FF () appstate none
	[ ] //CloseAllBrowsers()						//Yes						
	[ ] 
	[ ] //DeleteCookies()							//yes					
	[ ] //DeleteCookiesRestartBrowser()				//no
	[ ] //DeleteTempInternetFiles()					//yes		
	[ ] //FindBadImages("D:\Amiya\Test\URL.txt")	//yes
	[ ] //IE_FindOnPage("Search")					//yes
	[ ] //PrintPage()									
	[ ] 
	[ ] // LIST OF STRING lsLink =	{"Sign in", "Create an account now", "Learn More"}
	[ ] // NavigateLinks(lsLink)					//yes					
	[ ] 
	[ ] //PageLoadTimes("www.google.com", 4)		//yes
	[ ] 
	[ ] //SaveAndVerifyPageSize("HDFC", "D:\Amiya\Test", "PageSize1.csv", "PageSize2.csv" ) // complete
	[ ] 
	[ ] Print("Amiya")
	[ ] 
	[ ] //Print (DB_Connect ("DSN=TestSqlScript;SRVR=LOCALMACHINE;UID=;PWD="))
	[ ] 
	[ ] //DB_ExecuteSQLScript("DSN=TestSqlScript", "C:\CSI_1.1\SilkTest\Scripts\Test.sql")
[ ] 
[+] testcase TestConcurrently2 ()
	[ ] STRING client1 = "10.229.43.116"
	[ ] //STRING client2 = "10.229.43.98"
	[ ] //STRING client2 = "local"
	[ ] 
	[ ] SetAgentTrace (TRUE)
	[ ] 
	[ ] Connect (client1)
	[ ] //Connect (client2)
	[ ] 
	[+] parallel
		[ ] DoSomething (client1) // thread for client1
		[ ] //DoSomething (client2) // thread for client2
	[ ]                         // automatic synchronization
	[ ] Disconnect (client1)
	[ ] //Disconnect (client2)
	[ ] 
[ ] 
[+] DoSomething (STRING sMachine)
	[ ] HTIMER hTimer
	[ ] hTimer = TimerCreate ()
	[ ] TimerStart (hTimer)
	[ ] SetMachine (sMachine)
	[ ] 
	[ ] // code to update database goes here
	[ ] LIST OF STRING ls = {}
	[ ] SYS_Execute("ipconfig", ls)
	[ ] ListPrint(ls)
	[ ] 
	[ ] TimerStop (hTimer)
	[ ] Print ("Time on {sMachine} is: {TimerStr (hTimer)}")
	[ ] TimerDestroy (hTimer)
	[ ] 
[ ] 
[+] testcase TestDBFunctions () appstate none
	[ ] 
	[ ] STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] HDATABASE hdbc = DB_Connect (sCon_string)
	[ ] //print(hdbc)
	[ ] LIST OF ANYTYPE	 laQueryOutPut = {}
	[ ] LIST OF STRING	 lsQueryOutPut = {}
	[ ] 
	[ ] LIST OF LIST OF ANYTYPE llaQueryOutPut = {}
	[ ] LIST OF LIST OF STRING  llsQueryOutPut = {}
	[ ] 
	[ ] ANYTYPE aOut
	[ ] STRING sOut
	[ ] 
	[ ] LIST OF STRING lsQuery = {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] // LIST OF STRING lsQuery = {"select *from XCUSTOMERS"}
	[ ] 
	[+] // LIST OF STRING lsQuery = {...}
		[ ] // "select * from Persons where P_Id = 901"
		[ ] // "select * from Persons where P_Id = 101"
		[ ] // "select *from Employee"
	[ ] 
	[ ] // //DB_Execute(hdbc, lsQuery)
	[ ] 
	[ ] // //SET Address='Nissestien 67', City='Sandnes'
	[+] // LIST OF SQLCOLUMNVALUE lsqlUpdate = {...}
		[ ] // {"P_Id",101,0}
		[ ] // {"FirstName","Amiya",0}
		[ ] // 
	[ ] 
	[ ] 
	[ ] //DB_Update (hdbc, "Persons", lsqlUpdate, "P_Id = 111")
	[ ] // HFILE OutputFileHandle
	[ ] // OutputFileHandle = FileOpen ("C:\CSI_1.1\SilkTest\Scripts\Test.sql", FM_READ )
	[ ] // print(OutputFileHandle)
	[ ] // //FileOpen(
	[ ] //DB_ExecuteSQLScript(sCon_string, "C:\CSI_1.1\SilkTest\Scripts\Test.sql")
	[ ] 
	[ ] // DB_QueryAll_Any( hdbc, lsQuery, laQueryOutPut)
	[ ] // Print(laQueryOutPut)
	[ ] // 
	[ ] // 
	[ ] // // DB_QueryAll_Str( hdbc, lsQuery, lsQueryOutPut)
	[ ] // // Print(lsQueryOutPut)
	[ ] // 
	[ ] // 
	[ ] // DB_QueryAll_ListAny( hdbc, lsQuery, llaQueryOutPut)
	[ ] // Print(llaQueryOutPut)
	[ ] 
	[ ] 
	[ ] // DB_QueryAll_ListStr( hdbc, lsQuery, llsQueryOutPut)
	[ ] // Print(llsQueryOutPut)
	[ ] 
	[ ] // DB_QueryFirst_Any(hdbc, lsQuery, aOut)
	[ ] // Print (aOut)
	[ ] // 
	[ ] // DB_QueryFirst_Str(hdbc, lsQuery, sOut)
	[ ] // Print (sOut)
	[ ] 
	[ ] // DB_QueryFirst_ListAny ( hdbc, lsQuery, laQueryOutPut)
	[ ] // Print(laQueryOutPut)
	[ ] 
	[ ] // DB_QueryFirst_ListStr ( hdbc, lsQuery, lsQueryOutPut)
	[ ] // Print(lsQueryOutPut)
	[ ] // Print (SQL_FormatList(lsQuery))
	[ ] // Print(SQL_ListToStr(lsQuery))
	[ ] // SQL_Translate(lsQuery, "Persons", "Employee")
	[ ] // Print (lsQuery)
	[ ] 
	[+] // SQLCOLUMNVALUE ColValue = {...}
		[ ] // "P_Id"	//Column Name
		[ ] // 901		//Column value
		[ ] // 3		//number of decimal point. This is only applicable if your Column value is REAL. This is optional.
	[ ] 
	[+] // LIST OF SQLCOLUMNVALUE lColValue = {...}
		[ ] // {"CUSTNO", 100, 3}
		[ ] // {"SALARY", 25000.40, 2}
		[ ] // 
		[ ] // 
	[ ] // 
	[ ] // 
	[ ] // // Print (SQL_ColumnValue_Format (ColValue))
	[ ] // // 
	[ ] // // Print (TypeOf(SQL_ColumnValue_Format (ColValue)))
	[ ] // 
	[ ] // listPrint(SQL_FormatUpdate("Employee", lColValue))
	[ ] 
	[ ] 
	[ ] 
[ ] 
[+] testcase TestSQL () appstate none
	[ ] 
	[ ] STRING sCon_string 	= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] STRING lsQuery 		= "select * from Persons"
	[ ] LIST OF ANYTYPE 	 laQueryOutPut = {}
	[ ] LIST OF ANYTYPE 	 laData 
	[ ] 
	[ ] HDATABASE hdbc 		= DB_Connect (sCon_string)
	[ ] HSQL hstmnt 		= DB_ExecuteSql (hdbc, lsQuery) 
	[ ] 
	[+] while (DB_FetchNext (hstmnt, laData))
		[ ] ListAppend(laQueryOutPut, laData)
	[ ] 
	[ ] Print(laQueryOutPut)
	[ ] DB_FinishSQL (hstmnt)
	[ ] DB_Disconnect (hdbc)
[ ] 
[ ] 
[ ] 
[ ] 
[+] type SQLColumn is record					// Used to store the column's values of the original SQL Table			 
	[ ] STRING sCUSTNO
	[ ] STRING sCUSTNAME
	[ ] STRING sCUSTCITY
[+] LIST OF SQLQUERYMAP lSqlQueryMap = {...}	// Used to map the original SQL column name against the user defined record (ANYTYPE aRecord)
	[ ] {"CUSTNO",			"sCUSTNO"}
	[ ] {"CUSTNAME",		"sCUSTNAME"}
	[ ] {"CUSTCITY",		"sCUSTCITY"}
	[ ] 
	[ ] // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
	[ ] // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
	[ ] 
[ ] 
[+] testcase DBQueryFirstRecord () appstate none
	[ ] STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] LIST OF STRING lsQuery = {"select * from XCUSTOMERS where CUSTNO = 900", "select * from XCUSTOMERS where CUSTNO = 1006", "select *from XCUSTOMERS"}
	[ ] 
	[ ] HDATABASE hdbc = DB_Connect (sCon_string)
	[ ] //print(hdbc)
	[ ] 
	[ ] SQLColumn SQLColumnData
	[ ] DB_QueryFirst_Record (hdbc, lsQuery, lSqlQueryMap, SQLColumnData)
	[ ] 
	[ ] Print (SQLColumnData.sCUSTNO)
	[ ] Print (SQLColumnData.sCUSTNAME)
	[ ] Print (SQLColumnData.sCUSTCITY)
	[ ] 
[+] testcase DBQueryAllRecord () appstate none
	[ ] STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] LIST OF STRING lsQuery 	= {"select * from XCUSTOMERS where CUSTNO = 1002","select *from XCUSTOMERS", "select * from XCUSTOMERS where CUSTNO = 1005"}
	[ ] LIST OF SQLColumn lSQLColumnData = {...}
	[ ] INTEGER iRows 			= 0
	[ ] 
	[ ] HDATABASE hdbc = DB_Connect (sCon_string)
	[ ] 
	[ ] DB_QueryAll_Record (hdbc, lsQuery, lSqlQueryMap, lSQLColumnData)
	[ ] 
	[-] for iRows = 1 to ListCount(lSQLColumnData)
		[ ] Print(lSQLColumnData[iRows].sCUSTNO)
	[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[+] type ExcelColumn is record					// Used to store the column's values of the original SQL Table			 
	[ ] STRING sCUSTNO
	[ ] STRING sCUSTNAME
	[ ] STRING sCUSTCITY
	[ ] 
	[ ] 
[+] LIST OF EXCELMAP lExcelMap = {...}			// Used to map the original SQL column name against the user defined record (ANYTYPE aRecord)
	[ ] {"CUSTNO",			"sCUSTNO"}
	[ ] {"CUSTNAME",		"sCUSTNAME"}
	[ ] {"CUSTCITY",		"sCUSTCITY"}
	[ ] 
	[ ] 
	[ ] // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
	[ ] // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
	[ ] 
[ ] 
[+] type ExcelColumnEx is record					// Used to store the column's values of the original SQL Table			 
	[ ] STRING sCUSTNO
	[ ] STRING sCUSTNAME
	[ ] STRING sCUSTDEPT
	[ ] STRING sCUSTJOINDATE
	[ ] 
[+] LIST OF EXCELMAP lExcelMapEx = {...}			// Used to map the original SQL column name against the user defined record (ANYTYPE aRecord)
	[ ] {"Employee$.CUSTNO",			"sCUSTNO"}
	[ ] {"Employee$.CUSTNAME",		"sCUSTNAME"}
	[ ] {"XEmployee$.CUSTDEPT",		"sCUSTDEPT"}
	[ ] {"XEmployee$.CUSTJOINDATE",	"sCUSTJOINDATE"}
	[ ] 
	[ ] // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
	[ ] // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
	[ ] 
[ ] 
[ ] 
[+] testcase TestExcelFunction () appstate none
	[ ] STRING sFileName 	= "C:\CSI_1.1\SilkTest\Scripts\TestExcelTable.xls"
	[ ] STRING sQuery 		= "select * from Employee where CUSTNO = 1001"
	[ ] STRING sSheet		= "Employee"
	[ ] HDATABASE hdbc 		= Excel_Connect(sFileName)
	[ ] Print ("The Excel Handle is : {hdbc}")
	[ ] 
	[ ] 
	[ ] 
	[ ] //Print(Excel_Select(hdbc, sFileName, sSheet, "[CUSTNO],[1000]"))
	[ ] 
	[ ] // ExcelColumn ExcelColumnData 
	[ ] // Excel_LoadNameValue (ExcelColumnData, sFileName, sSheet, lExcelMap)	//Not working
	[ ] // Print(ExcelColumnData)
	[ ] 
	[ ] // ExcelColumn ExcelColumnData 
	[ ] // Excel_LoadTableRow (ExcelColumnData, sFileName, sSheet, lExcelMap, "CUSTNO = 1001")
	[ ] // Print(ExcelColumnData)
	[ ] 
	[ ] // LIST OF ExcelColumn lExcelColumnData
	[ ] // Excel_LoadTableRows (lExcelColumnData, sFileName, sSheet, lExcelMap, "CUSTCITY = 'London'", 2)
	[ ] // ListPrint(lExcelColumnData)
	[ ] // Print(lExcelColumnData[1].sCUSTNO)
	[ ] // Print(lExcelColumnData[1].sCUSTNAME)
	[ ] // Print(lExcelColumnData[1].sCUSTCITY)
	[ ] 
	[ ] // LIST OF ExcelColumn lExcelColumnData
	[ ] // Excel_LoadTableRowsEx (lExcelColumnData, sFileName, "Employee", "XEmployee", lExcelMap, "[Employee$].CUSTNO = [XEmployee$].CUSTNO", 2)
	[ ] // 
	[ ] // ListPrint(lExcelColumnData)
	[ ] // Print(lExcelColumnData[1].sCUSTNO)
	[ ] // Print(lExcelColumnData[1].sCUSTNAME)
	[ ] // Print(lExcelColumnData[1].sCUSTCITY)
	[ ] 
	[ ] // STRING sJoin = "INNER JOIN [XEmployee$] ON [Employee$].CUSTNO = [XEmployee$].CUSTNO"
	[ ] // //STRING sJoin = "[XEmployee$]"
	[ ] // // Print(Excel_SelectEx (hdbc, sFileName, "[Employee$].CUSTNO", "[Employee$]", sJoin, "[XEmployee$].CUSTNO = 1000"))
	[ ] // //Print(Excel_SelectEx (hdbc, sFileName, "[Employee$].CUSTNO", "[Employee$]"))//, sJoin ))
	[ ] // Print(Excel_SelectEx (hdbc, sFileName, "[Employee$.CUSTNO]", "[Employee$]", NULL))//, "[XEmployee$.CUSTNO] = 1000" ))
	[ ] 
	[ ] 
	[ ] // STRING sJoin = "INNER JOIN [XEmployee$] ON [Employee$].CUSTNO = [XEmployee$].CUSTNO"
	[ ] // LIST OF ExcelColumnEx lExcelColumnDataEx
	[ ] // Excel_LoadTableRowsEx (lExcelColumnDataEx, sFileName, "[Employee$]", sJoin, lExcelMapEx, "[Employee$].CUSTNO = 1001", 4)
	[ ] // ListPrint(lExcelColumnDataEx)
	[ ] 
	[ ] 
	[ ] ExcelColumn ExcelColumnData 
	[ ] Excel_LoadTestCase (ExcelColumnData, sFileName, sSheet, lExcelMap, "CUSTNO", "1000")
	[ ] Print(ExcelColumnData)
	[ ] 
