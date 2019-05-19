[ ] //	**************************************************************************************************** //
[ ] 
[ ] //	File Name			:	SILKGEN_DataBase.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -			:	All Database related functions provided by SILKGEN are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		03/30/09	Amiya Pattnayak	Created
	[ ] //		04/11/09	Amiya Pattnayak	Modified
	[ ] //		04/28/09	Amiya Pattnayak	Modified
	[ ] //		07/22/09	Amiya Pattnayak	Modified
	[ ] //		11/12/09	Amiya Pattnayak	Modified
	[ ] //		12/01/09	Amiya Pattnayak	Modified
	[ ]
	[ ]
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 											Excel Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] const	STRING	EXCEL_LIST_DELIM 	= Chr (10)
[ ] const	STRING	EXCEL_SET_DELIM  	= ","
[ ] const	STRING	EXCEL_PROP_DELIM 	= ","
[ ]
[ ]
[ ]
[+] type EXCELRUNFLAGS is set
	[ ] ExcelRunFlags_Optional
[ ]
[+] type EXCELLOADFLAGS is set
	[ ] ExcelLoadFlags_NullIfNotFound
[ ]
[+] STRING ExcelMap_FormatSelect (LIST OF EXCELMAP lExcelMap)						// Internal function
	[+] do
		[ ]
		[ ] STRING sSelect = ""
		[ ]
		[ ] INTEGER nCount = ListCount (lExcelMap)
		[ ] INTEGER nIndex
		[ ]
		[+] for nIndex = 1 to nCount
			[+] if (nIndex > 1)
				[ ] sSelect += ","
			[ ]
			[+] if (Right (lExcelMap[nIndex].sColumnName,1) == "]")
				[ ] sSelect += lExcelMap[nIndex].sColumnName
			[+] else
				[ ] sSelect += "[{lExcelMap[nIndex].sColumnName}]"
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ExcelMap_FormatSelect in testcase: {GetTestCaseName()}	success")
		[ ] return (sSelect)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ExcelMap_FormatSelect in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[+] INTEGER ExcelMap_FindByName (LIST OF EXCELMAP lExcelMap, STRING sColumnName)	// Internal function
	[+] do
		[ ]
		[ ] INTEGER nCount = ListCount (lExcelMap)
		[ ] INTEGER nIndex
		[ ]
		[+] for nIndex = 1 to nCount
			[+] if (lExcelMap[nIndex].sColumnName == sColumnName)
				[ ] return (nIndex)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ExcelMap_FindByName in testcase: {GetTestCaseName()}	success")
		[ ] return (0)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ExcelMap_FindByName in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return (0)
	[ ]
[ ]
[+] INTEGER ExcelMap_Compile (inout LIST OF EXCELMAP lExcelMap)						// Internal function
	[+] do
		[ ]
		[ ] INTEGER nKeyIndex = NULL
		[ ]
		[ ] INTEGER nIndex
		[+] for nIndex = 1 to ListCount (lExcelMap)
			[ ] lExcelMap[nIndex].RunFlags = {}
			[ ]
			[+] if ((lExcelMap[nIndex].sMember != NULL) && (Left (lExcelMap[nIndex].sMember, 1) == "<") && (Right (lExcelMap[nIndex].sMember, 1) == ">"))
				[+] if (nKeyIndex != NULL)
					[ ] RES.AppError ("Only one key member is allowed")
				[ ]
				[ ] lExcelMap[nIndex].sMember = SubStr (lExcelMap[nIndex].sMember, 2, Len (lExcelMap[nIndex].sMember) - 2)
				[ ] nKeyIndex = nIndex
			[ ]
			[ ] STRING sTransform = StrTrim (lExcelMap[nIndex].sTransform)
			[+] if (sTransform == NULL)
				[ ] sTransform = ""
			[ ]
			[+] if (Left (sTransform, 1) == "[")
				[ ] INTEGER nPos = StrPos ("]", sTransform)
				[+] if (nPos == 0)
					[ ] RES.AppError ("Invalid option syntax")
				[ ]
				[ ] STRING sOptions = SubStr (sTransform, 2, nPos - 2)
				[ ] sTransform = Trim (SubStr (sTransform, nPos + 1))
				[ ]
				[ ] STRING sEach
				[+] for each sEach in ParseStringList (sOptions, ",")
					[ ] sEach = Upper (Trim (sEach))
					[ ]
					[+] switch (sEach)
						[+] case "OPTIONAL"
							[ ] lExcelMap[nIndex].RunFlags += ExcelRunFlags_Optional
						[+] default
							[ ] RES.AppError ("{sEach} is not a valid option")
			[ ]
			[ ] TransInfo_ParseFunc (lExcelMap[nIndex].TransInfo, sTransform)
			[ ]
			[+] if (ExcelRunFlags_Optional in lExcelMap[nIndex].RunFlags)
				[ ] lExcelMap[nIndex].TransInfo.Flags += TransFlags_Optional
			[ ]
			[+] if (lExcelMap[nIndex].lPropMap != NULL)
				[ ] ExcelMap_Compile (lExcelMap[nIndex].lPropMap)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ExcelMap_Compile in testcase: {GetTestCaseName()}	success")
		[ ] return (nKeyIndex)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ExcelMap_Compile in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return (0)
[ ]
[+] // INTEGER ExcelMap_Compile (inout LIST OF EXCELMAP lExcelMap)
	[ ] // INTEGER nKeyIndex = NULL
	[ ] //
	[ ] // INTEGER nIndex
	[+] // for nIndex = 1 to ListCount (lExcelMap)
		[ ] // lExcelMap[nIndex].RunFlags = {}
		[ ] //
		[+] // if ((lExcelMap[nIndex].sMember != NULL) && (Left (lExcelMap[nIndex].sMember, 1) == "<") && (Right (lExcelMap[nIndex].sMember, 1) == ">"))
			[+] // if (nKeyIndex != NULL)
				[ ] // RES.AppError ("Only one key member is allowed")
			[ ] //
			[ ] // lExcelMap[nIndex].sMember = SubStr (lExcelMap[nIndex].sMember, 2, Len (lExcelMap[nIndex].sMember) - 2)
			[ ] // nKeyIndex = nIndex
		[ ] //
		[ ] // STRING sTransform = StrTrim (lExcelMap[nIndex].sTransform)
		[+] // if (sTransform == NULL)
			[ ] // sTransform = ""
		[ ] //
		[+] // if (Left (sTransform, 1) == "[")
			[ ] // INTEGER nPos = StrPos ("]", sTransform)
			[+] // if (nPos == 0)
				[ ] // RES.AppError ("Invalid option syntax")
			[ ] //
			[ ] // STRING sOptions = SubStr (sTransform, 2, nPos - 2)
			[ ] // sTransform = Trim (SubStr (sTransform, nPos + 1))
			[ ] //
			[ ] // STRING sEach
			[+] // for each sEach in ParseStringList (sOptions, ",")
				[ ] // sEach = Upper (Trim (sEach))
				[ ] //
				[+] // switch (sEach)
					[+] // case "OPTIONAL"
						[ ] // lExcelMap[nIndex].RunFlags += ExcelRunFlags_Optional
					[+] // default
						[ ] // RES.AppError ("{sEach} is not a valid option")
		[ ] //
		[ ] // TransInfo_ParseFunc (lExcelMap[nIndex].TransInfo, sTransform)
		[ ] //
		[+] // if (ExcelRunFlags_Optional in lExcelMap[nIndex].RunFlags)
			[ ] // lExcelMap[nIndex].TransInfo.Flags += TransFlags_Optional
		[ ] //
		[+] // if (lExcelMap[nIndex].lPropMap != NULL)
			[ ] // ExcelMap_Compile (lExcelMap[nIndex].lPropMap)
	[ ] //
	[ ] // return (nKeyIndex)
[ ]
[ ]
[ ]
[ ] // Function:	Excel_Connect function
[ ] // Action:		connects to the Excel sheet which is used as a database
[ ] // Syntax:		HDATABASE Excel_Connect (sFileName)
[ ] // Parameter:	sFileName: the Excel file to be connected. STRING.
[ ] // Returns:		returns the handle of excel sheet. HDATABASE.
[+] HDATABASE Excel_Connect (STRING sFileName)
	[+] do
		[ ]
		[ ] HDATABASE hdb = NULL
		[ ]
		[ ] BOOLEAN bFullPath = (IsAlpha (sFileName[1]) && (sFileName[2] == ":")) ||
                        (sFileName[1] == "\") || (sFileName[1] == "/")
		[ ]
		[ ] STRING sFullPath = (bFullPath ? sFileName : "{"{PROJECT_HOME}\SilkTest\Data"}\{sFileName}")
		[ ] STRING sConnect = "DSN=Excel Files;DBQ={sFullPath}"
		[ ]
		[+] do
			[+] if (! hHost->SYS_FileExists (sFullPath))
				[ ] raise 1, "File not found"
			[ ]
			[ ] hdb = DB_Connect (sConnect)
		[+] except
			[ ] RES.AppError ("Unable to connect to '{sFullPath}' -- {ExceptData()}")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: Excel_Connect in testcase: {GetTestCaseName()}	success")
		[ ] return (hdb)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_Connect in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return hdb
	[ ]
[ ]
[ ]
[ ] // Function:	Excel_Select function
[ ] // Action: 		Select the required values "sSelect" from the sheet in the Excel file
[ ] // Syntax:		Excel_Select (hdb, sFileName, sSheetName, sSelect, sWhere)
[ ] // Parameter: 	hdb  : Handle to connect to the Spreadsheet
[ ] // Parameter: 	sFileName : The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING.
[ ] // Parameter: 	sSheetName : The Sheet name which is the table from which the value needs to be fetched. STRING.
[ ] // Parameter: 	sSelect : The Column names whose values need to be selected. STRING.
[ ] // Parameter: 	sWhere : [Optional] Where condition for the query if required. STRING.
[ ] // Returns:		returns a HSQL handle. HANDLE
[+] HSQL Excel_Select (HDATABASE hdb, STRING sFileName, STRING sSheetName, STRING sSelect, STRING sWhere optional)	//Internal function
	[+] do
		[ ]
		[ ] HSQL hsql = NULL
		[ ] HSQL hsqlTry1 = NULL
		[ ] HSQL hsqlTry2 = NULL
		[ ]
		[ ] STRING sFrom = "[{sSheetName}$]"
		[ ]
		[+] if (sWhere == NULL)
			[ ] sWhere = "true"
		[+] do
			[ ] hsql = DB_ExecuteSql (hdb, "select {sSelect} from {sFrom} where {sWhere}")
		[+] except
			[ ] //ExceptLog ()
			[ ]
			[+] do
				[ ] hsqlTry1 = DB_ExecuteSql (hdb, "select * from {sFrom}")
				[ ] hsqlTry2 = DB_ExecuteSql (hdb, "select {sSelect} from {sFrom}")
			[ ] except
			[ ]
			[ ] STRING sError
			[ ]
			[+] select
				[+] case (hsqlTry2 != NULL)
					[ ] sError = "Invalid where clause ({sWhere})"
				[+] case (hsqlTry1 != NULL)
					[ ] sError = "Invalid select clause ({sSelect})"
				[+] default
					[ ] sError = "Unable to open spreasheet {sFileName}, worksheet [{sSheetName}]"
			[ ]
			[+] if (hsqlTry1 != NULL)
				[ ] DB_FinishSql (hsqlTry1)
			[ ]
			[+] if (hsqlTry2 != NULL)
				[ ] DB_FinishSql (hsqlTry2)
			[ ]
			[ ] RES.AppError (sError)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: Excel_Select in testcase: {GetTestCaseName()}	success")
		[ ] return (hsql)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_Select in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return hsql
	[ ]
[ ]
[ ]
[ ] // Function:	Excel_SelectEx function
[ ] // Action: 		Selects the required values "sSelect" from the two sheets in the Excel file
[ ] //             	{Ex: "SELECT suppliers.supplier_id, suppliers.supplier_name, orders.order_date FROM suppliers, orders WHERE suppliers.supplier_id = orders.supplier_id;"}
[ ] // Syntax:		Excel_SelectEx (hdb, sFileName, sSelect, sFrom, sJoin , sWhere )
[ ] // Parameter: 	hdb: 		Handle to connect to the Spreadsheet. HDATABASE.
[ ] // Parameter: 	sFileName: 	The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING.
[ ] // Parameter: 	sSelect:	The Column names whose values need to be selected. STRING.
[ ] // Parameter: 	sFrom:		The First Sheet name which is the table from which the value needs to be fetched. STRING.
[ ] // Parameter: 	sJoin:		[Optional] The Second Sheet name which is the table from which the value needs to be fetched. STRING.
[ ] // Parameter: 	sWhere:		[Optional] Where condition for the query if required. STRING.
[ ] //             	{Ex : For "sWhere"  Correct format is: [Students$].Name = [Dept$].Name and Wrong format is: Students.Name = Dept.Name}
[ ] //             	Here 'Students' and 'Dept' are the table names and 'Name' is the Column name
[ ] // Returns:		returns a HSQL handle. HANDLE.
[ ]
[+] // Example:
	[ ] //
	[+] // // type ExcelColumn is record					// Used to store the column's values of the original SQL Table
		[ ] // // STRING sCUSTNO
		[ ] // // STRING sCUSTNAME
		[ ] // // STRING sCUSTCITY
		[ ] // // STRING sCUSTDEPT
		[ ] // //
		[ ] // //
	[+] // // LIST OF EXCELMAP lExcelMap = {...}			// Used to map the original SQL column name against the user defined record (ANYTYPE aRecord)
		[ ] // // {"CUSTNO",			"sCUSTNO"}
		[ ] // // {"CUSTNAME",		"sCUSTNAME"}
		[ ] // // {"CUSTCITY",		"sCUSTCITY"}
		[ ] // // {"CUSTJOINDATE",	"sCUSTJOINDATE"}
		[ ] // //
		[ ] // //
		[ ] // // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] // //
	[ ] // //
	[ ] // // STRING sFileName 	= "C:\Test_1.1\SilkTest\Scripts\TestExcelTable.xls"
	[ ] // // STRING sSelect		= "[Employee$.CUSTNO], [XEmployee$.CUSTDEPT]"
	[ ] // // STRING sJoin 		= "INNER JOIN [XEmployee$] ON [Employee$].CUSTNO = [XEmployee$].CUSTNO"
	[ ] // // STRING sWhere		= "[XEmployee$.CUSTNO] = 1000"
	[ ] // //
	[ ] // // Print(Excel_SelectEx (hdbc, sFileName, sSelect, "[Employee$]", sJoin, sWhere ))
	[ ] //
	[ ] //
[+] HSQL Excel_SelectEx (HDATABASE hdb, STRING sFileName, STRING sSelect, STRING sFrom, STRING sJoin optional, STRING sWhere optional)	//Internal function
	[+] do
		[ ]
		[ ] HSQL hsql 		= NULL
		[ ] HSQL hsqlTry1 	= NULL
		[ ] HSQL hsqlTry2 	= NULL
		[ ] STRING sError	= ""
		[ ]
		[+] if (sJoin == NULL)
			[ ] sJoin = ""
		[ ]
		[+] if (sWhere == NULL)
			[ ] sWhere = "true"
			[ ] //sWhere = ''
		[ ]
		[+] do
			[ ] hsql = DB_ExecuteSql (hdb, "select {sSelect} from {sFrom} {sJoin} where {sWhere}")
		[+] except
			[+] do
				[ ] hsqlTry1 = DB_ExecuteSql (hdb, "select {sSelect} from {sFrom} {sJoin}")
			[+] except
				[+] do
					[ ] hsqlTry2 = DB_ExecuteSql (hdb, "select {sSelect} from {sFrom}")
				[+] except
					[ ] ExceptLog ()
				[ ]
			[ ]
			[+] select
				[+] case (hsqlTry1 != NULL)
					[ ] //sError = "Invalid where clause ({sWhere})"
					[ ] hsql = hsqlTry1
					[ ]
				[+] case (hsqlTry2 != NULL)
					[ ] //sError = "Invalid select clause ({sSelect})"
					[ ] hsql = hsqlTry2
				[+] default
					[ ] sError = "Unable to open spreasheet {sFileName}, from {sFrom}"
				[ ]
			[ ]
			[+] if (hsqlTry1 != NULL)
				[ ] DB_FinishSql (hsqlTry1)
			[+] if (hsqlTry2 != NULL)
				[ ] DB_FinishSql (hsqlTry2)
				[ ]
			[ ] RES.AppError (sError)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: Excel_SelectEx in testcase: {GetTestCaseName()}	success")
		[ ] return (hsql)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_SelectEx in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return hsql
[ ]
[ ]
[ ] // Function:	Excel_LoadNameValue function
[ ] // Action: 		Load the Name and Value from the table to the record using ExcelMapping
[ ] // Syntax:		Excel_LoadNameValue (aRecord, sFileName, sSheetName, lExcelMap)
[ ] // Parameter: 	sFileName  : The Spreadsheet name along with location {Ex: C:\Sample.xls}
[ ] // Parameter: 	sSheetName : The Sheet name which is the table from which the value needs to be fetched
[ ] // Parameter: 	aRecord    : The Record in which the name and value are stored after fetching
[ ] // Parameter: 	lExcelMap  : ExcelMapping of the Column with the Record values
[ ] //             	{Ex: lExcelMap = {...}
[ ] //                     {"Name", "sName"}   Here 'Name' is the Column name in the table and 'sName' is the variable in the record
[ ] //                     {"Value","sValue"}  Here 'Value' is the Column name in the table and 'sValue' is the variable in the record
[ ] // Returns:		void
[+] // void Excel_LoadNameValue (inout ANYTYPE aRecord, STRING sFileName, STRING sSheetName, LIST OF EXCELMAP lExcelMap) //Need to check
	[+] // do
		[ ] //
		[ ] // ExcelMap_Compile (lExcelMap)
		[ ] //
		[ ] // HDATABASE hdb = Excel_Connect (sFileName)
		[ ] //
		[+] // do
			[ ] // STRING sSelect = "[Name],[Value]"
			[ ] // //STRING sSelect = "[CUSTNO]"
			[ ] // HSQL hsql = Excel_Select (hdb, sFileName, sSheetName, sSelect)
			[ ] // Print ("The value of hsql = {hsql}")
		[+] // except
			[ ] // DB_Disconnect (hdb)
			[ ] // reraise
		[ ] //
		[ ] // STRING sName	= ""
		[ ] // STRING sValue  	= ""
		[ ] //
		[ ] // INTEGER nNumErrors = 0
		[ ] //
		[+] // while (DB_FetchNext (hsql, sName, sValue))
			[ ] // sName = Trim (sName)
			[ ] // sValue = StrTrim (sValue)
			[ ] //
			[ ] // Print (sName)
			[ ] // Print (sValue)
			[ ] //
			[+] // if (sName == "")
				[ ] // continue
			[ ] //
			[ ] // INTEGER nFind = ExcelMap_FindByName (lExcelMap, sName)
			[ ] //
			[+] // if (nFind == 0)
				[ ] // RES.LogError ("Column {sName} is not defined in ExcelMap for {TypeOf(aRecord)}")
				[ ] // nNumErrors += 1
				[ ] // continue
			[ ] //
			[ ] // EXCELMAP ExcelMap = lExcelMap[nFind]
			[ ] //
			[+] // do
				[ ] // Record_SetValueStr (aRecord, ExcelMap.sMember, sValue, ExcelMap.TransInfo)
			[+] // except
				[ ] // RES.LogError (ExceptData())
				[ ] // nNumErrors += 1
		[ ] //
		[ ] // DB_FinishSql (hsql)
		[ ] // DB_Disconnect (hdb)
		[ ] //
		[+] // if (nNumErrors > 0)
			[ ] // RES.AppError ("{nNumErrors} error(s) occurred storing data into {TypeOf(aRecord)}")
		[+] // else
			[ ] // ListAppend(laLogDetails, "Call to function: Excel_LoadNameValue in testcase: {GetTestCaseName()}	success")
			[ ] // return
	[+] // except
		[ ] // ListAppend(laLogDetails, "Exception raised in Call to function: Excel_LoadNameValue in testcase: {GetTestCaseName()}")
		[ ] // ListAppend(laLogDetails, ExceptData ())
		[ ] // reraise
		[ ] // return
[ ]
[ ]
[ ]
[ ]
[ ] // Function:	Excel_LoadTableRow function
[ ] // Action:		Load the particular row value from the table according to the where clause to the record using ExcelMapping
[ ] // Syntax:		Excel_LoadTableRow (aRecord, sFileName, sSheetName, lExcelMap, sWhere )
[ ] // Parameter: 	sFileName  : The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING
[ ] // Parameter: 	sSheetName : The Sheet name which is the table from which the value needs to be fetched. STRING
[ ] // Parameter: 	sWhere     : The where clause against which the value will be fetched from the table. STRING
[ ] // Parameter: 	aRecord    : The Record in which the values are stored after fetching. ANYTYPE
[ ] // Parameter: 	lExcelMap  : ExcelMapping of the Column with the Record variables. EXCELMAP
[ ] // Returns:		void
[ ]
[+] //Example:
	[ ]
	[+] // type ExcelColumn is record					// Used to store the column's values of the original Excel Table
		[ ] // STRING sCUSTNO
		[ ] // STRING sCUSTNAME
		[ ] // STRING sCUSTCITY
		[ ] // STRING sCUSTDEPT
		[ ] // // //Note:- This record should be declared outside of the function call
		[ ] //
	[+] // LIST OF EXCELMAP lExcelMap = {...}			// Used to map the original Excel column name against the user defined record (ANYTYPE aRecord)
		[ ] // {"CUSTNO",			"sCUSTNO"}
		[ ] // {"CUSTNAME",		"sCUSTNAME"}
		[ ] // {"CUSTCITY",		"sCUSTCITY"}
		[ ] // {"CUSTJOINDATE",	"sCUSTJOINDATE"}
		[ ] //
		[ ] //
		[ ] // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] //
	[ ] //
	[ ] // STRING sFileName 	= "C:\Test_1.1\SilkTest\Scripts\TestExcelTable.xls"
	[ ] // ExcelColumn ExcelColumnData
	[ ] // Excel_LoadTableRow (ExcelColumnData, sFileName, sSheet, lExcelMap, "CUSTNO = 1001")
	[ ]
	[ ] // Print(ExcelColumnData)
	[ ]
[+] void Excel_LoadTableRow (inout ANYTYPE aRecord, STRING sFileName, STRING sSheetName, LIST OF EXCELMAP lExcelMap, STRING sWhere )
	[+] do
		[ ]
		[ ] INTEGER nKeyIndex = ExcelMap_Compile (lExcelMap)
		[ ] BOOLEAN bKeyWhere = (nKeyIndex != NULL) && (sWhere != NULL) && (sWhere != "")
		[ ] HDATABASE hdb = Excel_Connect (sFileName)
		[+] do
			[ ] STRING sSelect = ExcelMap_FormatSelect (lExcelMap)
			[ ] STRING sWhere2
			[+] if (bKeyWhere)
				[ ] sSelect += ", {sWhere}"
				[ ] sWhere2 = NULL
			[+] else
				[ ] sWhere2 = sWhere
			[ ]
			[ ] HSQL hsql = Excel_Select (hdb, sFileName, sSheetName, sSelect, sWhere2)
		[+] except
			[ ] DB_Disconnect (hdb)
			[ ] reraise
		[ ]
		[ ] INTEGER nNumErrors = 0
		[ ] INTEGER nNumRows = 0
		[ ]
		[ ] BOOLEAN bNewRow
		[ ] BOOLEAN bSkipRow = FALSE
		[ ]
		[+] while (TRUE)
			[ ] LIST OF STRING lsValues
			[ ]
			[+] if (! DB_FetchNext (hsql, lsValues))
				[ ] break
			[ ]
			[+] if (nKeyIndex == NULL)
				[ ] bNewRow = TRUE
			[+] else
				[ ]
				[ ] bNewRow = (lsValues[nKeyIndex] != NULL) && (lsValues[nKeyIndex] != "")
				[ ]
				[+] if ((! bNewRow) && (nNumRows == 0))
					[ ] continue
				[ ]
				[+] if (bNewRow && bKeyWhere)
					[ ] bSkipRow = (Val (lsValues[ListCount (lsValues)]) == 0)
			[ ]
			[+] if (bSkipRow)
				[ ] continue
			[ ]
			[+] if (bNewRow)
				[+] if (nNumRows == 0)
					[ ] nNumRows = 1
				[+] else
					[ ] break
			[ ]
			[ ] INTEGER nCount = ListCount (lExcelMap)
			[ ] INTEGER nIndex
			[ ]
			[+] for nIndex = 1 to nCount
				[+] if ((nIndex == nKeyIndex) && (! bNewRow))
					[ ] continue
				[ ]
				[+] do
					[+] if (lExcelMap[nIndex].lPropMap != NULL)
						[ ] Record_SetProperties (aRecord, lExcelMap[nIndex], lsValues[nIndex])
					[+] else
						[ ] Record_SetValueStr (aRecord, lExcelMap[nIndex].sMember, lsValues[nIndex], lExcelMap[nIndex].TransInfo)
				[+] except
					[ ] RES.LogError (ExceptData ())
					[ ] nNumErrors += 1
		[ ]
		[ ] DB_FinishSql (hsql)
		[ ] DB_Disconnect (hdb)
		[ ]
		[+] if (nNumRows == 0)
			[ ] RES.AppError ("No row returned where {sWhere}")
		[ ]
		[+] if (nNumErrors > 0)
			[ ] RES.AppError ("{nNumErrors} error(s) occurred storing data into {TypeOf(aRecord)} where {sWhere}")
		[+] else
			[ ] ListAppend(laLogDetails, "Call to function: Excel_LoadTableRow in testcase: {GetTestCaseName()}	success")
			[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_LoadTableRow in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[ ]
[ ] // Function:	Excel_LoadTableRows function
[ ] // Action:		Load all the row values from the table according to the where clause which is optional to the list of record using ExcelMapping
[ ] // Syntax:		Excel_LoadTableRows (laRecord, sFileName, sSheetName, lExcelMap, sWhere, nMaxRows)
[ ] // Parameter: 	sFileName  : The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING
[ ] // Parameter: 	sSheetName : The Sheet name which is the table from which the value needs to be fetched. STRING
[ ] // Parameter: 	sWhere     : [Optional] The where clause against which the value will be fetched from the table. STRING
[ ] // Parameter: 	laRecord   : The List of Records in which the values are stored after fetching. LIST OF ANYTYPE
[ ] // Parameter: 	nMaxRows   : [Optional] The maximum number of rows to be fetched. If omitted all the rows will be selected. INTEGER
[ ] // Parameter: 	lExcelMap  : ExcelMapping of the Column with the Record variables. EXCELMAP
[ ] // Returns:		void
[ ]
[+] //Example:
	[+] // type ExcelColumn is record					// Used to store the column's values of the original Excel Table
		[ ] // STRING sCUSTNO
		[ ] // STRING sCUSTNAME
		[ ] // STRING sCUSTCITY
		[ ] // STRING sCUSTDEPT
		[ ] // // //Note:- This record should be declared outside of the function call
		[ ] //
	[+] // LIST OF EXCELMAP lExcelMap = {...}			// Used to map the original Excel column name against the user defined record (ANYTYPE aRecord)
		[ ] // {"CUSTNO",			"sCUSTNO"}
		[ ] // {"CUSTNAME",		"sCUSTNAME"}
		[ ] // {"CUSTCITY",		"sCUSTCITY"}
		[ ] // {"CUSTJOINDATE",	"sCUSTJOINDATE"}
		[ ] //
		[ ] //
		[ ] // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] //
	[ ]
	[ ] // STRING sFileName 	= "C:\Test_1.1\SilkTest\Scripts\TestExcelTable.xls"
	[ ] // LIST OF ExcelColumn lExcelColumnData
	[ ] // Excel_LoadTableRows (lExcelColumnData, sFileName, sSheet, lExcelMap, "CUSTCITY = 'London'", 2)
	[ ]
	[ ] // ListPrint(lExcelColumnData)
	[ ] // Print(lExcelColumnData[1].sCUSTNO)
	[ ] // Print(lExcelColumnData[1].sCUSTNAME)
	[ ] // Print(lExcelColumnData[1].sCUSTCITY)
	[ ]
[+] void Excel_LoadTableRows (inout LIST OF ANYTYPE laRecord, STRING sFileName, STRING sSheetName, LIST OF EXCELMAP lExcelMap, STRING sWhere optional, INTEGER nMaxRows optional)
	[+] do
		[ ]
		[ ] INTEGER nKeyIndex = ExcelMap_Compile (lExcelMap)
		[ ] BOOLEAN bKeyWhere = (nKeyIndex != NULL) && (sWhere != NULL) && (sWhere != "")
		[ ]
		[ ] HDATABASE hdb = Excel_Connect (sFileName)
		[ ]
		[+] do
			[ ] STRING sSelect = ExcelMap_FormatSelect (lExcelMap)
			[ ]
			[+] if (bKeyWhere)
				[ ] sSelect += ", {sWhere}"
				[ ] sWhere = NULL
			[ ]
			[ ] HSQL hsql = Excel_Select (hdb, sFileName, sSheetName, sSelect, sWhere)
		[+] except
			[ ] DB_Disconnect (hdb)
			[ ] reraise
		[ ]
		[ ] laRecord = {}
		[ ]
		[ ] LIST OF STRING lsValues
		[ ] INTEGER nNumErrors = 0
		[ ] INTEGER nNumRows = 0
		[ ] INTEGER nExcelRow = 1
		[ ]
		[ ] BOOLEAN bNewRow
		[ ] BOOLEAN bSkipRow = FALSE
		[ ]
		[+] while (TRUE)
			[+] do
				[ ] nExcelRow += 1
				[+] if (! DB_FetchNext (hsql, lsValues))
					[ ] break
			[+] except
				[ ] STRING sError = ExceptError()
				[ ]
				[+] if (MatchStr ("*Numeric field overflow*", sError))
					[ ] sError = "Data inconsistancy error"
				[ ]
				[ ] RES.LogError ("[Row {nExcelRow}] {sError}")
				[ ] nNumErrors += 1
				[ ] continue
			[ ]
			[+] if (nKeyIndex == NULL)
				[ ] bNewRow = TRUE
			[+] else
				[ ] bNewRow = (lsValues[nKeyIndex] != NULL) && (lsValues[nKeyIndex] != "")
				[ ]
				[+] if ((! bNewRow) && (nNumRows == 0))
					[ ] continue
				[ ]
				[+] if (bNewRow && bKeyWhere)
					[ ] bSkipRow = (Val (lsValues[ListCount (lsValues)]) == 0)
			[ ]
			[+] if (bNewRow && (nMaxRows != NULL) && (nNumRows == nMaxRows))
				[ ] break
			[ ]
			[+] if (bSkipRow)
				[ ] continue
			[ ]
			[+] if (bNewRow)
				[ ] nNumRows += 1
				[ ] ListAppend (laRecord, {})
				[ ]
				[ ] Record_Initialize (laRecord[nNumRows])
			[ ]
			[ ] INTEGER nCount = ListCount (lExcelMap)
			[ ] INTEGER nIndex
			[ ]
			[+] for nIndex = 1 to nCount
				[+] if ((nIndex == nKeyIndex) && (! bNewRow))
					[ ] continue
				[ ]
				[+] do
					[+] if (lExcelMap[nIndex].lPropMap != NULL)
						[ ] Record_SetProperties (laRecord[nNumRows], lExcelMap[nIndex], lsValues[nIndex])
					[+] else
						[ ] Record_SetValueStr (laRecord[nNumRows], lExcelMap[nIndex].sMember, lsValues[nIndex], lExcelMap[nIndex].TransInfo)
				[+] except
					[ ] RES.LogError ("[Row {nExcelRow}] {ExceptError ()}")
					[ ] nNumErrors += 1
		[ ]
		[ ] DB_FinishSql (hsql)
		[ ] DB_Disconnect (hdb)
		[ ]
		[+] if (nNumErrors > 0)
			[ ] RES.AppError ("{nNumErrors} error(s) occurred storing data into {TypeOf(laRecord[1])}" + ((sWhere != NULL) ? " where {sWhere}" : ""))
		[+] else
			[ ] ListAppend(laLogDetails, "Call to function: Excel_LoadTableRows in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_LoadTableRows in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[ ]
[ ] // Function:	Excel_LoadTableRowsEx function
[ ] // Action:		Load all the row values from more than one table (External tables) based on the SQL JOIN and the where clause (which is optional) -
[ ] // 				-  The result set is stored into the list of record using ExcelMapping.
[ ] //				Note:- If sJoin is set to NULL, then you should not select any of the columns of the second table.i.e. in the Excel Mapping you you should not have any entries of the table's Column.
[ ] // Syntax:		Excel_LoadTableRowsEx (laRecord, sFileName, sFrom, sJoin null, lExcelMap, sWhere, nMaxRows)
[ ] // Parameter: 	sFileName  : The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING
[ ] // Parameter: 	sFrom      : The First Sheet name which is the table from which the value needs to be fetched. STRING
[ ] // Parameter: 	sJoin      : The SQL JOIN statement. STRING
[ ] // Parameter: 	sWhere     : [Optional] The where clause based on which the value will be fetched from the table. STRING
[ ] //             	{Ex : For "sWhere"  Correct format: [Students$].Name = [Dept$].Name and Wrong format : Students.Name = Dept.Name}
[ ] //             	Here 'Students' and 'Dept' are the table names and 'Name' is the Column name
[ ] // Parameter: 	laRecord   : The List of Records in which the values are stored after fetching. LIST OF ANYTYPE
[ ] // Parameter: 	nMaxRows   : [Optional] The maximum number of rows to be fetched. If omitted all the rows will be selected. INTEGER
[ ] // Parameter: 	lExcelMap  : ExcelMapping of the Column with the Record values
[ ] // Returns:		void
[ ]
[+] // Example:
	[ ]
	[+] // type ExcelColumnEx is record					// Used to store the column's values of the original Excel Table
		[ ] // STRING sCUSTNO			//First table column
		[ ] // STRING sCUSTNAME		//First table column
		[ ] // STRING sCUSTDEPT		//Second table column
		[ ] // STRING sCUSTJOINDATE	//Second table column
		[ ] // // //Note:- This record should be declared outside of the function call
		[ ] //
	[+] // LIST OF EXCELMAP lExcelMapEx = {...}			// Used to map the original Excel column name against the user defined record (ANYTYPE aRecord)
		[ ] // {"Employee$.CUSTNO",		"sCUSTNO"}			//First table column mapping to sCUSTNO
		[ ] // {"Employee$.CUSTNAME",		"sCUSTNAME"}		//First table column mapping to sCUSTNAME
		[ ] // {"XEmployee$.CUSTDEPT",		"sCUSTDEPT"}		//Second table column mapping to sCUSTDEPT
		[ ] // {"XEmployee$.CUSTJOINDATE",	"sCUSTJOINDATE"}	//Second table column mapping to sCUSTJOINDATE
		[ ] //
		[ ] // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] //
	[ ] //
	[ ] // STRING sFileName 	= "C:\Test_1.1\SilkTest\Scripts\TestExcelTable.xls"
	[ ] // STRING sFrom		= "[Employee$]"
	[ ] // STRING sJoin 		= "INNER JOIN [XEmployee$] ON [Employee$].CUSTNO = [XEmployee$].CUSTNO"
	[ ] // STRING sWhere		= "[Employee$].CUSTNO = 1001"
	[ ] // LIST OF ExcelColumnEx lExcelColumnDataEx
	[ ] // Excel_LoadTableRowsEx (lExcelColumnDataEx, sFileName, sFrom, sJoin, lExcelMapEx, sWhere, 4)
	[ ]
	[+] //Output
		[ ] // ListPrint(lExcelColumnDataEx)
		[ ] // Print(lExcelColumnDataEx[1].sCUSTNO)
		[ ] // Print(lExcelColumnDataEx[1].sCUSTNAME)
		[ ] // Print(lExcelColumnDataEx[1].sCUSTDEPT)
		[ ] // Print(lExcelColumnDataEx[1].sCUSTJOINDATE)
	[ ]
	[ ]
[+] void Excel_LoadTableRowsEx (inout LIST OF ANYTYPE laRecord, STRING sFileName, STRING sFrom, STRING sJoin null, LIST OF EXCELMAP lExcelMap, STRING sWhere optional, INTEGER nMaxRows optional)
	[+] do
		[ ]
		[ ] INTEGER nKeyIndex = ExcelMap_Compile (lExcelMap)
		[ ] BOOLEAN bKeyWhere = (nKeyIndex != NULL) && (sWhere != NULL) && (sWhere != "")
		[ ] STRING sSelect = ""
		[ ]
		[ ] HDATABASE hdb = Excel_Connect (sFileName)
		[ ]
		[+] do
			[ ] sSelect = ExcelMap_FormatSelect (lExcelMap)
			[ ]
			[+] if (bKeyWhere)
				[ ] sSelect += ", {sWhere}"
				[ ] sWhere = NULL
			[ ]
			[ ] HSQL hsql = Excel_SelectEx (hdb, sFileName, sSelect, sFrom, sJoin, sWhere)
		[+] except
			[ ] DB_Disconnect (hdb)
			[ ] reraise
		[ ]
		[ ] laRecord = {}
		[ ]
		[ ] LIST OF STRING lsValues
		[ ] INTEGER nNumErrors 	= 0
		[ ] INTEGER nNumRows 	= 0
		[ ] INTEGER nExcelRow 	= 1
		[ ]
		[ ] BOOLEAN bNewRow
		[ ] BOOLEAN bSkipRow = FALSE
		[ ]
		[+] while (TRUE)
			[+] do
				[ ] nExcelRow += 1
				[+] if (! DB_FetchNext (hsql, lsValues))
					[ ] break
			[+] except
				[ ] STRING sError = ExceptError()
				[ ]
				[+] if (MatchStr ("*Numeric field overflow*", sError))
					[ ] sError = "Data inconsistancy error"
				[ ]
				[ ] RES.LogError ("[Row {nExcelRow}] {sError}")
				[ ] nNumErrors += 1
				[ ] continue
			[ ]
			[+] if (nKeyIndex == NULL)
				[ ] bNewRow = TRUE
			[+] else
				[ ] bNewRow = (lsValues[nKeyIndex] != NULL) && (lsValues[nKeyIndex] != "")
				[ ]
				[+] if ((! bNewRow) && (nNumRows == 0))
					[ ] continue
				[ ]
				[+] if (bNewRow && bKeyWhere)
					[ ] bSkipRow = (Val (lsValues[ListCount (lsValues)]) == 0)
			[ ]
			[+] if (bNewRow && (nMaxRows != NULL) && (nNumRows == nMaxRows))
				[ ] break
			[ ]
			[+] if (bSkipRow)
				[ ] continue
			[ ]
			[+] if (bNewRow)
				[ ] nNumRows += 1
				[ ] ListAppend (laRecord, {})
				[ ]
				[ ] Record_Initialize (laRecord[nNumRows])
			[ ]
			[ ] INTEGER nCount = ListCount (lExcelMap)
			[ ] INTEGER nIndex
			[ ]
			[+] for nIndex = 1 to nCount
				[+] if ((nIndex == nKeyIndex) && (! bNewRow))
					[ ] continue
				[ ]
				[+] do
					[+] if (lExcelMap[nIndex].lPropMap != NULL)
						[ ] Record_SetProperties (laRecord[nNumRows], lExcelMap[nIndex], lsValues[nIndex])
					[+] else
						[ ] Record_SetValueStr (laRecord[nNumRows], lExcelMap[nIndex].sMember, lsValues[nIndex], lExcelMap[nIndex].TransInfo)
				[+] except
					[ ] RES.LogError ("[Row {nExcelRow}] {ExceptError ()}")
					[ ] nNumErrors += 1
		[ ]
		[ ] DB_FinishSql (hsql)
		[ ] DB_Disconnect (hdb)
		[ ]
		[+] if (nNumErrors > 0)
			[ ] RES.AppError ("{nNumErrors} error(s) occurred storing data into {TypeOf(laRecord[1])}" + ((sWhere != NULL) ? " where {sWhere}" : ""))
		[+] else
			[ ] ListAppend(laLogDetails, "Call to function: Excel_LoadTableRowsEx in testcase: {GetTestCaseName()}	success")
			[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_LoadTableRowsEx in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[ ]
[ ] // Function:	Excel_LoadTestCase function
[ ] // Action:		Load the particular row value from the table according to the Test case ID to the record using ExcelMapping
[ ] // Syntax:		Excel_LoadTestCase (aRecord, sFileName, sSheetName, lExcelMap, sTestCaseID)
[ ] // Parameter: 	aRecord    : The Record in which the values are stored after fetching. ANYTYPE.
[ ] // Parameter: 	sFileName  : The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING.
[ ] // Parameter: 	sSheetName : The Sheet name which is the table from which the value needs to be fetched. STRING.
[ ] // Parameter: 	lExcelMap  : ExcelMapping of the Column with the Record variables. EXCELMAP.
[ ] // Parameter: 	sTestCaseID: The Test case ID against which the  row will be fetched from the table
[ ] // Parameter: 	sColumnName: The column name, used for 'SQL where condition' against the 'sTestCaseID'. STRING.
[ ] // Returns:		void
[ ]
[+] //Example:
	[ ]
	[+] // type ExcelColumn is record					// Used to store the column's values of the original Excel Table
		[ ] // STRING sCUSTNO
		[ ] // STRING sCUSTNAME
		[ ] // STRING sCUSTCITY
		[ ] // // //Note:- This record should be declared outside of the function call
		[ ] //
	[+] // LIST OF EXCELMAP lExcelMap = {...}			// Used to map the original Excel column name against the user defined record (ANYTYPE aRecord)
		[ ] // {"CUSTNO",			"sCUSTNO"}
		[ ] // {"CUSTNAME",		"sCUSTNAME"}
		[ ] // {"CUSTCITY",		"sCUSTCITY"}
		[ ] //
		[ ] //
		[ ] // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] //
	[ ] // STRING sFileName 	= "C:\Test_1.1\SilkTest\Scripts\TestExcelTable.xls"
	[ ]
	[ ] // ExcelColumn ExcelColumnData
	[ ] // Excel_LoadTestCase (ExcelColumnData, sFileName, sSheet, lExcelMap, "CUSTNO", "1000")
	[ ] // Print(ExcelColumnData)
	[ ] //Note:- where "CUSTNO" refers to the Excel Column's name and "1000" refers to the row's value
[+] void Excel_LoadTestCase (inout ANYTYPE aRecord, STRING sFileName, STRING sSheetName, LIST OF EXCELMAP lExcelMap, STRING sColumnName, STRING sTestCaseID )
	[+] do
		[ ] //	Newly added a parameter 'sColumnName'
		[ ] // 	STRING sWhere = "([Test Case ID] = '{sTestCaseID}')"
		[ ]
		[ ] STRING sWhere = "({sColumnName} = {sTestCaseID})"
		[ ] Excel_LoadTableRow (aRecord, sFileName, sSheetName, lExcelMap, sWhere)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: Excel_LoadTestCase in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Excel_LoadTestCase in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
[ ]
[ ]
[ ] // Function:	Excel_TableRowCount function
[ ] // Action:		Returns the number of rows in excel sheet based on the Pattern
[ ] // Syntax:		iCount = Excel_TableRowCount (sFileName, sSheetName, sColumnName, sPattern)
[ ] // Parameter: 	sFileName  : The Spreadsheet name along with location {Ex: C:\Sample.xls}. STRING.
[ ] // Parameter: 	sSheetName : The Sheet name which is the table from which the value needs to be fetched. STRING.
[ ] // Parameter: 	sColumnName : The column name of spread sheet/excel table. STRING.
[ ] // Parameter: 	sPattern : To search for a specified pattern in a column. STRING
[ ] // Returns:		Returns the number of rows in excel sheet. INTEGER.
[ ]
[+] //Example:
	[ ] // Print(Excel_TableRowCount("{HOST_GetEnv("PROJECT")}\Data\OrderCreation.xls",  "Order", "Test Case ID", "TC_"))
[+] INTEGER Excel_TableRowCount (STRING sFileName, STRING sSheetName, STRING sColumnName, STRING sPattern)
	[ ] INTEGER iRows = 0
	[ ] HSQL hstmnt = DB_ExecuteSql (Excel_Connect(sFileName), "Select Count (*) from [{sSheetName}$] where [{sColumnName}] like '{sPattern}%'")
	[+] while (DB_FetchNext (hstmnt, iRows))
		[ ] //Do nothing
	[ ] return (iRows)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 											SQL Formatting Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] VOID SQL_QueryMap_Compile (inout LIST OF SQLQUERYMAP lQueryMap)		// Internal function
	[+] do
		[ ]
		[ ] INTEGER i
		[+] for i = 1 to ListCount (lQueryMap)
			[ ] TransInfo_ParseFunc (lQueryMap[i].TransInfo, lQueryMap[i].sTrans)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_QueryMap_Compile in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_QueryMap_Compile in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[+] STRING SQL_QueryMap_GetSelect (LIST OF SQLQUERYMAP lQueryMap)		// Internal function
	[+] do
		[ ]
		[ ] STRING sSelect = ""
		[ ]
		[ ] INTEGER nCount = ListCount (lQueryMap)
		[ ] INTEGER nIndex
		[ ]
		[+] for nIndex = 1 to nCount
			[+] if (nIndex > 1)
				[ ] sSelect += ","
			[ ]
			[ ] sSelect += lQueryMap[nIndex].sExpr
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_QueryMap_GetSelect in testcase: {GetTestCaseName()}	success")
		[ ] return (sSelect)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_QueryMap_GetSelect in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return ""
	[ ]
[ ]
[+] void SQL_QueryMap_SetRecord (LIST OF SQLQUERYMAP lQueryMap, LIST OF STRING lsValues, inout ANYTYPE aRecord)	// Internal function
	[+] do
		[ ]
		[ ] Record_Initialize (aRecord)
		[ ]
		[ ] INTEGER nCount = ListCount (lQueryMap)
		[ ] INTEGER nIndex
		[ ]
		[+] for nIndex = 1 to nCount
			[ ] Record_SetValueStr (aRecord, lQueryMap[nIndex].sMember, lsValues[nIndex], lQueryMap[nIndex].TransInfo)
		[ ] ListAppend(laLogDetails, "Call to function: SQL_QueryMap_SetRecord in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_QueryMap_SetRecord in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
[ ]
[ ]
[ ]
[ ] // Function:	SQL_Translate function
[ ] // Action:		SQL_Translate searches lsSQL list for the query sFrom. When it finds a match, it replaces sFrom with sTo.
[ ] //				All instances of sFrom in lsSQL list are replaced, and the new list is modifies with lsSQL
[ ] // Syntax:		SQL_Translate (lsSQL, sFrom, sTo)
[ ] // Parameter:	lsSQL	: The original list of SQL query. LIST OF STRING
[ ] // Parameter:	sFrom	: The SQL query to search from the original list (lsSQL). STRING.
[ ] // Parameter:	sTo		: The SQL query to be replaced against the  sFrom. STRING.
[ ] // Returns:		void
[ ]
[+] // Example:
	[+] // LIST OF STRING lsQuery = {...}
		[ ] // "select * from Persons where P_Id = 901"
		[ ] // "select * from Persons where P_Id = 101"
		[ ] // "select *from Employee"
		[ ]
	[ ] // SQL_Translate(lsQuery, "Persons", "Employee")
	[ ] // Print (lsQuery)
	[+] // Output
		[ ] // The output of lsQuery will be
		[ ] // select * from Employee where P_Id = 901, select * from Employee where P_Id = 101, select *from Employee
[+] void SQL_Translate (inout LIST OF STRING lsSQL, STRING sFrom, STRING sTo)
	[+] do
		[ ]
		[ ] INTEGER nIndex
		[+] for nIndex = 1 to ListCount (lsSQL)
			[+] if (StrPos (sFrom, lsSQL[nIndex]) > 0)
				[ ] lsSQL[nIndex] = StrTran (lsSQL[nIndex], sFrom, sTo)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_Translate in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_Translate in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[ ]
[ ] // Function:	SQL_ListToStr function
[ ] // Action:		Convert LIST OF SQL queries into a single query of type STRING.
[ ] // Syntax:		sQuery = SQL_ListToStr (lsSQL)
[ ] // Parameter:	lsSQL : LIST OF SQL queries. LIST OF STRING.
[ ] // Returns:		It returns a single query of type STRING.
[ ]
[+] // Example:
	[+] // LIST OF STRING lsQuery = {...}
		[ ] // "select * from Persons where P_Id = 901"
		[ ] // "select * from Persons where P_Id = 101"
		[ ] // "select *from Employee"
		[ ]
	[ ] // sQuery = SQL_ListToStr (lsSQL)
	[+] // Output
		[ ]
		[ ] // The output of squery will be
		[ ] // select * from Persons where P_Id = 901 select * from Persons where P_Id = 101 select *from Employee
[+] STRING SQL_ListToStr (LIST OF STRING lsSQL)
	[+] do
		[ ]
		[ ] STRING sSQL = ""
		[ ]
		[ ] INTEGER i
		[+] for i = 1 to Listcount (lsSQL)
			[+] if (i > 1)
				[ ] sSQL += " "
			[ ] sSQL += Trim (lsSQL[i])
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_ListToStr in testcase: {GetTestCaseName()}	success")
		[ ] return (sSQL)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_ListToStr in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	SQL_FormatList function
[ ] // Action:		Convert each item of lsItems queries with single quotes and places a comma seprater in between each item and -
[ ] //				- returns it as a single string.
[ ] // Syntax:		sQuery = SQL_FormatList (lsItems)
[ ] // Parameter:	lsItems : LIST OF SQL queries / Items. LIST OF STRING.
[ ] // Returns:		It returns a single query of type STRING.
[ ]
[+] // Example:
	[+] // LIST OF STRING lsQuery = {...}
		[ ] // "select * from Persons where P_Id = 901"
		[ ] // "select * from Persons where P_Id = 101"
		[ ] // "select *from Employee"
		[ ]
	[ ] // sQuery = SQL_FormatList (lsSQL)
	[+] // Output
		[ ] // The output of squery will be
		[ ] // 'select * from Persons where P_Id = 901','select * from Persons where P_Id = 101','select *from Employee'
[+] STRING SQL_FormatList (LIST OF STRING lsItems)
	[+] do
		[ ]
		[ ] STRING sList = ""
		[ ]
		[ ] STRING sItem
		[+] for each sItem in lsItems
			[+] if (sList != "")
				[ ] sList += ","
			[ ] sList += "'{sItem}'"
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_FormatList in testcase: {GetTestCaseName()}	success")
		[ ] return (sList)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_FormatList in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return ""
	[ ]
[ ]
[ ]
[ ]
[ ] // Function:	SQL_ColumnValue_Format  function
[ ] // Action:		It converts the Column's Value to STRING datatype.
[ ] // Syntax:		sColValue = SQL_ColumnValue_Format (ColumnValue)
[ ] // Parameter:	ColumnValue : The SQL table Column's information. SQLCOLUMNVALUE.
[ ] // Returns:		Returns the column's value which is of type STRING
[ ]
[+] // Example:
	[+] // SQLCOLUMNVALUE ColValue = {...}
		[ ] // "P_Id"	//Column Name
		[ ] // 901		//Column value
		[ ] // 3		//number of decimal point. This is only applicable if your Column value is REAL. This is optional.
	[ ] // sColValue = SQL_ColumnValue_Format (ColValue)
	[+] // output
		[ ] // The output of sColValue will be always of Type STRING irrespective of any datatype.
[+] STRING SQL_ColumnValue_Format (SQLCOLUMNVALUE ColumnValue)
	[+] do
		[ ]
		[+] if (ColumnValue.aValue == NULL)
			[ ] return ("DEFAULT")
		[ ]
		[ ] DATATYPE ColumnType = TypeOf (ColumnValue.aValue)
		[ ] STRING sValue
		[ ]
		[+] select
			[+] case (ColumnType == STRING)
				[ ] sValue = "'{ColumnValue.aValue}'" //todo: Escape quotes
			[+] case (ColumnType == INTEGER)
				[ ] sValue = Str (ColumnValue.aValue)
			[+] case (ColumnType == REAL)
				[ ] INTEGER nDecimal = (ColumnValue.nDecimal != NULL) ? ColumnValue.nDecimal : 6
				[ ] sValue = Str (ColumnValue.aValue, 1, nDecimal)
			[+] default
				[ ] sValue = [STRING] ColumnValue.aValue
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_ColumnValue_Format in testcase: {GetTestCaseName()}	success")
		[ ] return (sValue)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_ColumnValue_Format in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	SQL_FormatInsert function
[ ] // Action:		It converts the list of Column Value of a table to a SQL INSERT INTO Statement.
[ ] // Syntax:		lsInsertQuery = SQL_FormatInsert (sTable, lColumnValue)
[ ] // Parameter:	sTable : the table name of the SQL database
[ ] // Parameter: 	lColumnValue : The list of cloumn information of sTable for which INSERT will be done. SQLCOLUMNVALUE.
[ ] // Returns:		It returns the SQL INSERT INTO Statement. LIST OF STRING.
[ ]
[+] // Example:
	[+] // LIST OF SQLCOLUMNVALUE lColValue = {...}
		[ ] // {"CUSTNO", 100, 3}
		[ ] // {"SALARY", 25000.40, 2}
		[ ] //
		[ ] //
	[ ] // LIST OF STRING lsInsertQuery = SQL_FormatInsert ("Employee", lColValue)
	[ ] // ListPrint(lsInsertQuery)
	[+] // output
		[ ] // The output of lsInsertQuery will be
		[ ]
		[ ] // INSERT INTO Employee (CUSTNO, SALARY)
		[ ] // VALUES (100, 25000.40)
[+] LIST OF STRING SQL_FormatInsert (STRING sTable, LIST OF SQLCOLUMNVALUE lColumnValue)
	[+] do
			[ ]
		[ ] INTEGER nIndex
		[ ] INTEGER nCount = ListCount (lColumnValue)
		[ ]
		[ ] STRING sInsertColumns = ""
		[ ] STRING sInsertValues  = ""
		[ ]
		[+] for nIndex = 1 to nCount
			[ ] STRING sComma = (nIndex > 1) ? ", " : ""
			[ ]
			[ ] STRING sColumn = lColumnValue[nIndex].sColumn
			[ ] STRING sValue  = SQL_ColumnValue_Format (lColumnValue[nIndex])
			[ ]
			[ ] sInsertColumns += "{sComma}{sColumn}"
			[ ] sInsertValues  += "{sComma}{sValue}"
		[ ]
		[+] LIST OF STRING lsSQL = {...}
			[ ] "INSERT INTO {sTable} ({sInsertColumns})"
			[ ] "VALUES ({sInsertValues})"
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_FormatInsert in testcase: {GetTestCaseName()}	success")
		[ ] return (lsSQL)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_FormatInsert in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return NULL
		[ ]
[ ]
[ ] // Function:	SQL_FormatUpdate function
[ ] // Action:		It converts the list of Column Value of a table to a SQL UPDATE Statement.
[ ] // Syntax:		lsInsertQuery = SQL_FormatUpdate (sTable, lColumnValue)
[ ] // Parameter:	sTable : the table name of the SQL database
[ ] // Parameter: 	lColumnValue : The list of cloumn information of sTable for which UPDATE will be done. SQLCOLUMNVALUE.
[ ] // Returns:		It returns the SQL UPDATE Statement. LIST OF STRING.
[ ]
[+] // Example:
	[+] // LIST OF SQLCOLUMNVALUE lColValue = {...}
		[ ] // {"CUSTNO", 100, 3}
		[ ] // {"SALARY", 25000.40, 2}
		[ ] //
		[ ] //
	[ ] // LIST OF STRING lsInsertQuery = SQL_FormatUpdate ("Employee", lColValue)
	[ ] // ListPrint(lsInsertQuery)
	[+] // output
		[ ] // The output of lsInsertQuery will be
		[ ]
		[ ] // UPDATE Employee
		[ ] // SET CUSTNO=100, SALARY=25000.40
[+] LIST OF STRING SQL_FormatUpdate (STRING sTable, LIST OF SQLCOLUMNVALUE lColumnValue)
	[+] do
		[ ]
		[ ] INTEGER nIndex
		[ ] INTEGER nCount = ListCount (lColumnValue)
		[ ]
		[ ] STRING sUpdateList = ""
		[ ]
		[+] for nIndex = 1 to nCount
			[ ] STRING sComma  = (nIndex > 1) ? ", " : ""
			[ ] STRING sColumn = lColumnValue[nIndex].sColumn
			[ ] STRING sValue  = SQL_ColumnValue_Format (lColumnValue[nIndex])
			[ ]
			[ ] sUpdateList += "{sComma}{sColumn}={sValue}"
		[ ]
		[+] LIST OF STRING lsSQL = {...}
			[ ] "UPDATE {sTable}"
			[ ] "SET {sUpdateList}"
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: SQL_FormatUpdate in testcase: {GetTestCaseName()}	success")
		[ ] return (lsSQL)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: SQL_FormatUpdate in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return NULL
		[ ]
	[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 											Database Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // Function: 	DB_QueryAll_Any function
[ ] // Action: 		Executes all the valid query on the given database -
[ ] //				The output of the Queries that are executed successfully are stored in the LIST OF ANYTYPE.
[ ] //				Note:-  The output will only contain the records of the First column of the Table, which is of type LIST OF ANYTYPE.
[ ] // Syntax:  	iCount = DB_QueryAll_Any (hdb, lsSQL, laValues)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in LIST OF STRING format
[ ] // Parameter:  	laValues: [inout] List of values of type ANYTYPE returned by SQL query
[ ] // Returns:  	Returns the count of SQL query result. INTEGER
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // LIST OF ANYTYPE	 laQueryOutPut = {}
	[ ] //
	[ ] // DB_QueryAll_Any( hdbc, lsQuery, laQueryOutPut)
	[ ] // Print(laQueryOutPut)
	[ ]
	[ ] ////output
	[ ] //The output will only contain the records of the First column of the Table, which is of type LIST OF ANYTYPE.
	[ ]
	[ ]
[+] INTEGER DB_QueryAll_Any (HDATABASE hdb, LIST OF STRING lsSQL,  inout LIST OF ANYTYPE laValues)
	[+] do
		[ ]
		[ ] HSQL hsql 		= NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ] INTEGER iNum 	= 1
		[ ] laValues 		= {}
		[ ]
		[+] do
			[ ] // executing each sql queries in the list
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ]
				[ ] ANYTYPE aData
				[+] while (DB_FetchNext (hsql, aData))
					[ ] ListAppend (laValues, aData)
					[ ]
		[+] except
			[ ] bExcept = TRUE
			[ ]
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryAll_Any in testcase: {GetTestCaseName()}	success")
		[ ] return (ListCount (laValues))
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryAll_Any in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return 0
	[ ]
[ ]
[ ]
[ ] // Function: 	DB_QueryAll_Str function
[ ] // Action: 		Executes all the valid query on the given database -
[ ] //				The output of the Queries that are executed successfully are stored in the LIST OF ANYTYPE.
[ ] //				Note:-  The output will only contain the records of the First column of the Table, which is of type LIST OF STRING.
[ ] // Syntax:  	iCount = DB_QueryAll_Str (hdb, lsSQL, lsValues)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in LIST OF STRING format
[ ] // Parameter:  	lsValues: [inout] List of values of type STRING returned by SQL query
[ ] // Returns:  	Returns the count of SQL query result. INTEGER
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // LIST OF STRING	 lsQueryOutPut = {}
	[ ] //
	[ ] // DB_QueryAll_Str( hdbc, lsQuery, lsQueryOutPut)
	[ ] // Print(lsQueryOutPut)
	[ ]
	[ ] ////output
	[ ] //The output will only contain the records of the First column of the Table, which is of type LIST OF STRING.
	[ ]
	[ ]
[+] INTEGER DB_QueryAll_Str (HDATABASE hdb, LIST OF STRING lsSQL, inout LIST OF STRING lsValues)
	[+] do
		[ ]
		[ ] HSQL hsql 		= NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ] INTEGER iNum 	= 1
		[ ] lsValues 		= {}
		[ ]
		[+] do
			[ ] // executing each sql queries in the list
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ]
				[ ] STRING sData
				[+] while (DB_FetchNext (hsql, sData))
					[ ] ListAppend (lsValues, sData)
					[ ]
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryAll_Str in testcase: {GetTestCaseName()}	success")
		[ ] return (ListCount (lsValues))
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryAll_Str in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return 0
[ ]
[ ]
[ ] // Function: 	DB_QueryAll_ListAny function
[ ] // Action: 		Executes all the valid query on the given database -
[ ] //				The output of the Queries that are executed successfully are stored in the LIST OF LIST OF ANYTYPE.
[ ] //				Note:-  The output will contain the records of all columns of the Table, which is of type LIST OF LIST OF ANYTYPE.
[ ] // Syntax:  	iCount = DB_QueryAll_ListAny (hdb, lsSQL, llaValues)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in LIST OF STRING format
[ ] // Parameter:  	llaValues: [inout] List of values of type LIST OF ANYTYPE returned by SQL query
[ ] // Returns:  	Returns the count of SQL query result. INTEGER
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // LIST OF LIST OF ANYTYPE llaQueryOutPut = {}
	[ ] //
	[ ] // DB_QueryAll_ListAny( hdbc, lsQuery, llaQueryOutPut)
	[ ] // Print(llaQueryOutPut)
	[ ]
	[ ] ////output
	[ ] //Prints the output that will contain the records of all columns of the Table, which is of type LIST OF LIST OF ANYTYPE.
	[ ]
	[ ]
[+] INTEGER DB_QueryAll_ListAny (HDATABASE hdb, LIST OF STRING lsSQL, inout LIST OF LIST OF ANYTYPE llaValues)
	[+] do
		[ ]
		[ ] HSQL hsql 		= NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ] INTEGER iNum 	= 1
		[ ] llaValues 		= {}
		[ ]
		[+] do
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ]
				[ ] LIST OF ANYTYPE laValues
				[+] while (DB_FetchNext (hsql, laValues))
					[ ] ListAppend (llaValues, laValues)
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryAll_ListAny in testcase: {GetTestCaseName()}	success")
		[ ] return (ListCount (llaValues))
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryAll_ListAny in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return 0
	[ ]
[ ]
[ ]
[ ] // Function: 	DB_QueryAll_ListStr function
[ ] // Action: 		Executes all the valid query on the given database -
[ ] //				The output of the Queries that are executed successfully are stored in the LIST OF ANYTYPE.
[ ] //				Note:-  The output will contain the records of all columns of the Table, which is of type LIST OF LIST OF STRING.
[ ] // Syntax:  	iCount = DB_QueryAll_ListStr (hdb, lsSQL, llsValues)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in LIST OF STRING format
[ ] // Parameter:  	llsValues: [inout] List of values of type LIST OF STRING returned by SQL query
[ ] // Returns:  	Returns the count of SQL query result. INTEGER
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // LIST OF LIST OF STRING  llsQueryOutPut = {}
	[ ] //
	[ ] // DB_QueryAll_ListStr( hdbc, lsQuery, llsQueryOutPut)
	[ ] // Print(llsQueryOutPut)
	[ ]
	[ ] ////output
	[ ] //Prints the output that will contain the records of all columns of the Table, which is of type LIST OF LIST OF STRING.
	[ ]
	[ ]
[+] INTEGER DB_QueryAll_ListStr (HDATABASE hdb, LIST OF STRING lsSQL, inout LIST OF LIST OF STRING llsValues)
	[+] do
		[ ]
		[ ] HSQL hsql 		= NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ] INTEGER iNum 	= 1
		[ ] llsValues 		= {}
		[ ]
		[+] do
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ]
				[ ] LIST OF STRING lsValues
				[+] while (DB_FetchNext (hsql, lsValues))
					[ ] ListAppend (llsValues, lsValues)
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryAll_ListStr in testcase: {GetTestCaseName()}	success")
		[ ] return (ListCount (llsValues))
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryAll_ListStr in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return 0
[ ]
[ ]
[ ] // Function: 	DB_QueryFirst_Any function
[ ] // Action: 		Executes only the first valid query from lsSQL on the given database -
[ ] //				The output of the Query that is executed successfully is stored in aValue.
[ ] //				Note:-  The output will contain the first row's first column's value in aValue. ANYTYPE.
[ ] // Syntax: 		bStatus = DB_QueryFirst_Any (hdb, lsSQL, aValue)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in List of STRING format. LIST OF STRING lsSQL
[ ] // Parameter:  	aValue: Value of returned by SQL query. ANYTYPE
[ ] // Returns:  	bStatus : Returns FALSE when the query does not returs any value or there are no more rows. -
[ ] // 				- If the specified handle (hstmnt) is invalid, the function returns FALSE and an error. Otherwise TRUE. BOOLEAN.
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // ANYTYPE aOut
	[ ] //
	[ ] // DB_QueryFirst_Any(hdbc, lsQuery, aOut)
	[ ] // Print (aOut)
	[ ]
	[ ] ////output
	[ ] //Prints the output that will contain the first row's first column's value in aValue. ANYTYPE.
	[ ]
	[ ]
[+] BOOLEAN DB_QueryFirst_Any (HDATABASE hdb, LIST OF STRING lsSQL, inout ANYTYPE aValue)
	[+] do
		[ ]
		[ ] HSQL hsql 			= NULL
		[ ] BOOLEAN bExcept 	= FALSE
		[ ] BOOLEAN bFetched 	= FALSE
		[ ] INTEGER iNum		= 1
		[ ]
		[+] do
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ] bFetched = DB_FetchNext (hsql, aValue)
				[+] if (bFetched)
					[ ] break
			[ ]
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryFirst_Any in testcase: {GetTestCaseName()}	success")
		[ ] return (bFetched)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryFirst_Any in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return FALSE
[ ]
[ ]
[ ] // Function: 	DB_QueryFirst_Str function
[ ] // Action: 		Executes only the first valid query from lsSQL on the given database -
[ ] //				The output of the Query that is executed successfully is stored in sValue.
[ ] //				Note:-  The output will contain the first row's first column's value in sValue. STRING.
[ ] // Syntax: 		bStatus = DB_QueryFirst_Str (hdb, lsSQL, sValue)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in List of STRING format. LIST OF STRING lsSQL
[ ] // Parameter:  	sValue: Value of returned by SQL query. STRING.
[ ] // Returns:  	bStatus : Returns FALSE when the query does not returs any value or there are no more rows. -
[ ] // 				- If the specified handle (hstmnt) is invalid, the function returns FALSE and an error. Otherwise TRUE. BOOLEAN.
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // STRING sOut
	[ ] //
	[ ] // DB_QueryFirst_Str(hdbc, lsQuery, sOut)
	[ ] // Print (sOut)
	[ ]
	[ ] ////output
	[ ] //Prints output will contain the first row's first column's value in sValue. STRING.
	[ ]
	[ ]
[+] BOOLEAN DB_QueryFirst_Str (HDATABASE hdb, LIST OF STRING lsSQL, inout STRING sValue)
	[+] do
		[ ]
		[ ] HSQL hsql 			= NULL
		[ ] BOOLEAN bExcept 	= FALSE
		[ ] BOOLEAN bFetched 	= FALSE
		[ ] INTEGER iNum		= 1
		[ ]
		[+] do
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ] bFetched = DB_FetchNext (hsql, sValue)
				[+] if (bFetched)
					[ ] break
			[ ]
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryFirst_Str in testcase: {GetTestCaseName()}	success")
		[ ] return (bFetched)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryFirst_Str in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return FALSE
[ ]
[ ]
[ ] // Function: 	DB_QueryFirst_ListAny function
[ ] // Action: 		Executes only the first valid query from lsSQL on the given database -
[ ] //				The output of the Queries that are executed successfully are stored in the laValue.
[ ] //				Note:-  The output will only contain the first row's values of the Table, which is of type LIST OF ANYTYPE.
[ ] // Syntax:  	bStatus = DB_QueryFirst_ListAny (hdb, lsSQL, laValues)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in LIST OF STRING format
[ ] // Parameter:  	laValues: [inout] List of values of type ANYTYPE returned by SQL query
[ ] // Returns:  	bStatus : Returns FALSE when the query does not returs any value or there are no more rows. -
[ ] // 				- If the specified handle (hstmnt) is invalid, the function returns FALSE and an error. Otherwise TRUE. BOOLEAN.
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // LIST OF ANYTYPE	 laQueryOutPut = {}
	[ ] //
	[ ] // DB_QueryFirst_ListAny ( hdbc, lsQuery, laQueryOutPut)
	[ ] // Print(laQueryOutPut)
	[ ]
	[ ] ////output
	[ ] //Prints The output will only contain the first row's values of the Table, which is of type LIST OF ANYTYPE.
	[ ]
	[ ]
[+] BOOLEAN DB_QueryFirst_ListAny (HDATABASE hdb, LIST OF STRING lsSQL, inout LIST OF ANYTYPE laValue)
	[+] do
		[ ]
		[ ] HSQL hsql 			= NULL
		[ ] BOOLEAN bExcept 	= FALSE
		[ ] BOOLEAN bFetched 	= FALSE
		[ ] INTEGER iNum		= 1
		[ ]
		[ ]
		[+] do
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ] bFetched = DB_FetchNext (hsql, laValue)
				[+] if (bFetched)
					[ ] break
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryFirst_ListAny in testcase: {GetTestCaseName()}	success")
		[ ] return (bFetched)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryFirst_ListAny in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return FALSE
[ ]
[ ]
[ ] // Function: 	DB_QueryFirst_ListStr function
[ ] // Action: 		Executes only the first valid query from lsSQL on the given database -
[ ] //				The output of the Queries that are executed successfully are stored in the laValue.
[ ] //				Note:-  The output will only contain the first row's values of the Table, which is of type LIST OF STRING.
[ ] // Syntax:  	bStatus = DB_QueryFirst_ListStr (hdb, lsSQL, lsValues)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in LIST OF STRING format
[ ] // Parameter:  	lsValues: [inout] List of values of type ANYTYPE returned by SQL query
[ ] // Returns:  	bStatus : Returns FALSE when the query does not returs any value or there are no more rows. -
[ ] // 				- If the specified handle (hstmnt) is invalid, the function returns FALSE and an error. Otherwise TRUE. BOOLEAN.
[+] // Example:
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc 			= DB_Connect (sCon_string)
	[ ] // LIST OF STRING lsQuery 	= {"select * from Persons where P_Id = 100", "select * from Persons where P_Id = 800", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // LIST OF STRING	 lsQueryOutPut = {}
	[ ] //
	[ ] // DB_QueryFirst_ListStr ( hdbc, lsQuery, lsQueryOutPut)
	[ ] // Print(lsQueryOutPut)
	[ ]
	[ ] ////output
	[ ] //Prints The output will only contain the first row's values of the Table, which is of type LIST OF STRING.
	[ ]
	[ ]
[+] BOOLEAN DB_QueryFirst_ListStr (HDATABASE hdb, LIST OF STRING lsSQL, inout LIST OF STRING lsValue)
	[+] do
		[ ]
		[ ] HSQL hsql 			= NULL
		[ ] BOOLEAN bExcept 	= FALSE
		[ ] BOOLEAN bFetched 	= FALSE
		[ ] INTEGER iNum		= 1
		[ ]
		[+] do
			[+] for (iNum = 1; iNum <= ListCount(lsSQL); iNum++)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ] bFetched = DB_FetchNext (hsql, lsValue)
				[+] if (bFetched)
					[ ] break
			[ ]
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryFirst_ListStr in testcase: {GetTestCaseName()}	success")
		[ ] return (bFetched)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryFirst_ListStr in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return FALSE
	[ ]
[ ]
[ ]
[ ] // Function: 	DB_QueryFirst_Record function
[ ] // Action: 		Executes only the first valid query from lsSQL on the given database -
[ ] //				The output of the Query that is executed successfully is stored in aRecord.
[ ] //				Note:-  The output will contain the first row's first column's value in aRecord. ANYTYPE.
[ ] // Syntax: 		iCount = DB_QueryFirst_Record (hdb, lsSQL, lQueryMap, aRecord, bUpdateRecord)
[ ]
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in List of STRING format. LIST OF STRING lsSQL
[ ] // Parameter:  	lQueryMap: SQL Mapping of the Column with the Record values, SQLQUERYMAP. LIST OF SQLQUERYMAP
[ ] // Parameter:  	aRecord: Value of returned by SQL query. ANYTYPE Record.
[ ] // Parameter: 	bUpdateRecord: [Optional] If TRUE, then the Record i.e. aRecord will be Initialize, else not.
[ ] // Returns:  	iCount : Returns the count of SQL query result. INTEGER
[+] // Example:
	[+] // type SQLColumn is record					// Used to store the column's values of the original SQL Table
		[ ] // STRING sCUSTNO
		[ ] // STRING sCUSTNAME
		[ ] // STRING sCUSTCITY
		[ ] // // Note:- This record should be declared outside of the function call
	[ ]
	[+] // LIST OF SQLQUERYMAP lSqlQueryMap = {...}	// Used to map the original SQL column name against the user defined record (ANYTYPE aRecord)
		[ ] // {"CUSTNO",			"sCUSTNO"}
		[ ] // {"CUSTNAME",		"sCUSTNAME"}
		[ ] // {"CUSTCITY",		"sCUSTCITY"}
		[ ] //
		[ ] // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] //
	[ ] //
	[ ]
	[ ] // STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // LIST OF STRING lsQuery = {"select * from XCUSTOMERS where CUSTNO = 900", "select * from XCUSTOMERS where CUSTNO = 1006", "select *from XCUSTOMERS"}
	[ ] //
	[ ] // HDATABASE hdbc = DB_Connect (sCon_string)
	[ ] // //print(hdbc)
	[ ] //
	[ ] // SQLColumn SQLColumnData
	[ ] // DB_QueryFirst_Record (hdbc, lsQuery, lSqlQueryMap, SQLColumnData)
	[ ]
	[ ] // Print (SQLColumnData.sCUSTNO)
	[ ] // Print (SQLColumnData.sCUSTNAME)
	[ ] // Print (SQLColumnData.sCUSTCITY)
	[ ]
	[+] // Output:
		[ ] // Prints the CUSTNO of first record
		[ ] //
[+] BOOLEAN DB_QueryFirst_Record (HDATABASE hdb, LIST OF STRING lsSQL, LIST OF SQLQUERYMAP lQueryMap, inout ANYTYPE aRecord, BOOLEAN bUpdateRecord optional)
	[+] do
		[ ]
		[+] if (bUpdateRecord == NULL)
			[ ] bUpdateRecord = FALSE
		[ ]
		[ ] SQL_QueryMap_Compile (lQueryMap)
		[ ]
		[ ] SQL_Translate (lsSQL, "<*>", SQL_QueryMap_GetSelect (lQueryMap))
		[ ]
		[ ] HSQL hsql = NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ] BOOLEAN bFetched = FALSE
		[ ]
		[ ] LIST OF STRING lsValues
		[ ] INTEGER iNum = 0
		[ ]
		[+] do
			[+] for iNum = 1 to ListCount(lsSQL)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ] bFetched = DB_FetchNext (hsql, lsValues)
				[+] if (bFetched)
					[ ] break
			[ ] // hsql = DB_ExecuteSQL (hdb, SQL_ListToStr (lsSQL))
			[ ] // bFetched = DB_FetchNext (hsql, lsValues)
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[+] if (bFetched)
			[+] if (! bUpdateRecord)
				[ ] Record_Initialize (aRecord)
			[ ]
			[ ] SQL_QueryMap_SetRecord (lQueryMap, lsValues, aRecord)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryFirst_Record in testcase: {GetTestCaseName()}	success")
		[ ] return (bFetched)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryFirst_Record in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return FALSE
	[ ]
[ ]
[ ]
[ ] // Function: 	DB_QueryAll_Record function
[ ] // Action: 		Executes all the valid query from lsSQL on the given database -
[ ] //				The output of the Query that are executed successfully are stored in laRecords.
[ ] // Syntax: 		iCount = DB_QueryAll_Record(hdb, lsSQL, lQueryMap, laRecords)
[ ]
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:  	lsSQL: SQL query statement in List of STRING format. LIST OF STRING lsSQL
[ ] // Parameter:  	lQueryMap: SQL Mapping of the Column with the Record values, SQLQUERYMAP. LIST OF SQLQUERYMAP
[ ] // Parameter:  	laRecords: List of Values/records returned by SQL query. LIST OF ANYTYPE Record.
[ ] // Returns:  	iCount : Returns the counts of SQL query result. INTEGER
[+] // Example:
	[+] // type SQLColumn is record					// Used to store the column's values of the original SQL Table
		[ ] // STRING sCUSTNO
		[ ] // STRING sCUSTNAME
		[ ] // STRING sCUSTCITY
		[ ] // // Note:- This record should be declared outside of the function call
	[ ]
	[+] // LIST OF SQLQUERYMAP lSqlQueryMap = {...}	// Used to map the original SQL column name against the user defined record (ANYTYPE aRecord)
		[ ] // {"CUSTNO",			"sCUSTNO"}
		[ ] // {"CUSTNAME",		"sCUSTNAME"}
		[ ] // {"CUSTCITY",		"sCUSTCITY"}
		[ ] //
		[ ] // // where CUSTNO, CUSTNAME, CUSTCITY etc are the Columns name of the SQL Table
		[ ] // // where sCUSTNO, sCUSTNAME, sCUSTCITY etc are used to map these above Columns of the SQL Table
		[ ] //
	[ ] //
	[ ]
	[ ] // STRING sCon_string 		= "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // LIST OF STRING lsQuery 	= {"select * from XCUSTOMERS where CUSTNO = 1002","select *from XCUSTOMERS", "select * from XCUSTOMERS where CUSTNO = 1005"}
	[ ] // LIST OF SQLColumn lSQLColumnData = {...}
	[ ] // INTEGER iRows 			= 0
	[ ] //
	[ ] // HDATABASE hdbc = DB_Connect (sCon_string)
	[ ] //
	[ ] // DB_QueryAll_Record (hdbc, lsQuery, lSqlQueryMap, lSQLColumnData)
	[ ]
	[+] // for iRows = 1 to ListCount(lSQLColumnData)
		[ ] // Print(lSQLColumnData[iRows].sCUSTNO)
	[ ]
	[+] // Output:
		[ ] // Prints the CUSTNO of each record
[+] INTEGER DB_QueryAll_Record (HDATABASE hdb, LIST OF STRING lsSQL, LIST OF SQLQUERYMAP lQueryMap, inout LIST OF ANYTYPE laRecords)
	[+] do
		[ ]
		[ ] SQL_QueryMap_Compile (lQueryMap)
		[ ]
		[ ] SQL_Translate (lsSQL, "<*>", SQL_QueryMap_GetSelect (lQueryMap))
		[ ]
		[ ] HSQL hsql = NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ]
		[ ] laRecords = {}
		[ ] INTEGER nNumRows = 0, iNum = 0
		[ ]
		[+] do
			[+] for iNum = 1 to ListCount(lsSQL)
				[ ] hsql = DB_ExecuteSQL (hdb, lsSQL[iNum])
				[ ] //hsql = DB_ExecuteSQL (hdb, SQL_ListToStr (lsSQL))
				[ ]
				[ ] LIST OF STRING lsValues
				[ ]
				[+] while (DB_FetchNext (hsql, lsValues))
					[ ] nNumRows += 1
					[ ] ListAppend (laRecords, {})
					[ ]
					[ ] Record_Initialize (laRecords[nNumRows])
					[ ] SQL_QueryMap_SetRecord (lQueryMap, lsValues, laRecords[nNumRows])
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_QueryAll_Record in testcase: {GetTestCaseName()}	success")
		[ ] return (nNumRows)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_QueryAll_Record in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return 0
	[ ]
[ ]
[ ]
[ ]
[ ] // Function:	DB_Insert function
[ ] // Action:		Insert a new row or rows in a table
[ ] // Syntax:		DB_Insert (hdb, sTable, lColumnValue)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:	sTable : the name of the database table. STRING.
[ ] // Parameter:	lColumnValue : the list of column's value to be inserted. SQLCOLUMNVALUE
[ ] // Returns:		void
[ ]
[+] // Example:
	[ ] // STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc = DB_Connect (sCon_string)
	[ ]
	[ ] // DB_Insert (hdbc, "Persons", lsqlInsert )
	[ ] //				where
	[ ] //				'Persons' refers to the table name
	[+] // 				lsqlInsert = {...}
												[ ] // {"P_Id",101,0}
												[ ] // {"FirstName","Amiya",0}
		[ ] //
[+] void DB_Insert (HDATABASE hdb, STRING sTable, LIST OF SQLCOLUMNVALUE lColumnValue)
	[+] do
		[ ]
		[ ] HSQL hsql = NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ]
		[+] do
			[ ] LIST OF STRING lsSQL = SQL_FormatInsert (sTable, lColumnValue)
			[ ] hsql = DB_ExecuteSQL (hdb, SQL_ListToStr (lsSQL))
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ] ListAppend(laLogDetails, "Call to function: DB_Insert in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_Insert in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[ ]
[ ] // Function:	DB_Update function
[ ] // Action:		Updates the specific column values i.e records in a table of a table
[ ] // Syntax:		DB_Update (hdb, sTable, lColumnValue, sWhere)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:	sTable : the name of the database table. STRING.
[ ] // Parameter:	lColumnValue : the list of column's value to be updated. SQLCOLUMNVALUE
[ ] // Parameter:	sWhere : the where condition against which the table will be updated
[ ] // Returns:		void
[ ]
[+] // Example:
	[ ] // STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc = DB_Connect (sCon_string)
	[ ]
	[ ] // DB_Update (hdbc, "Persons", lsqlUpdate, "P_Id = 111")
	[ ] //				where
	[ ] //				'Persons' refers to the table name
	[+] // 				lsqlUpdate = {...}
												[ ] // {"P_Id",101,0}
												[ ] // {"FirstName","Amiya",0}
		[ ] //
	[ ] //				P_Id = 111 refers to the where cluase i.e columnname = columnvalue
[+] void DB_Update (HDATABASE hdb, STRING sTable, LIST OF SQLCOLUMNVALUE lColumnValue, STRING sWhere)
	[+] do
		[ ]
		[ ] HSQL hsql = NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ]
		[+] do
			[ ] LIST OF STRING lsSQL = SQL_FormatUpdate (sTable, lColumnValue) + {"WHERE {sWhere}"}
			[ ] hsql = DB_ExecuteSQL (hdb, SQL_ListToStr (lsSQL))
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ] ListAppend(laLogDetails, "Call to function: DB_Update in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_Update in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
	[ ]
[ ]
[ ]
[ ] // Function:	DB_Execute function
[ ] // Action:		Sends a list of SQL statements to the specified database for execution.
[ ] // Syntax:		DB_Execute (hdb, lsSQL)
[ ] // Parameter:	hdb	: The handle to a database connection as returned by DB_Connect. HDATABASE.
[ ] // Parameter:	lsSQL: list of SQL statement to the specified database for execution. LIST OF STRING.
[ ] // Returns:		void
[+] // Example:
	[ ]
	[ ] // STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] // HDATABASE hdbc = DB_Connect (sCon_string)
	[ ]
	[+] // LIST OF STRING lsQuery = {...}
		[ ] // "select * from Persons where P_Id = 901"
		[ ] // "select * from Persons where P_Id = 101"
		[ ] // "select *from Employee"
	[ ]
	[ ] //DB_Execute(hdbc, lsQuery)
[+] void DB_Execute (HDATABASE hdb, LIST OF STRING lsSQL)
	[+] do
		[ ]
		[ ] HSQL hsql = NULL
		[ ] BOOLEAN bExcept = FALSE
		[ ]
		[+] do
			[ ] hsql = DB_ExecuteSQL (hdb, SQL_ListToStr (lsSQL))
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[+] if (hsql != NULL)
			[ ] DB_FinishSql (hsql)
		[ ]
		[+] if (bExcept)
			[ ] reraise
		[ ] ListAppend(laLogDetails, "Call to function: DB_Execute in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_Execute in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
[ ]
[ ]
[ ] // Function:  	SQ_ExecuteSQLScript function
[ ] // Action:		Excutes a SQL script on the specified database
[ ] // Syntax:		DB_ExecuteSQLScript(sODBC_ConnectString, sFilename)
[ ] // parameter: 	sODBC_ConnectString: The ODBC connection string. STRING.
[ ] // parameter: 	sFilename: The SQL file to execute. STRING.
[ ] // Returns:     viod
[+] // Example:
	[ ]
	[ ] // STRING sCon_string = "DSN=SQLServerPC011663;SRVR=PC011663;UID=sa;PWD=sa"
	[ ] //DB_ExecuteSQLScript(sCon_string, "C:\Test_1.1\SilkTest\Scripts\Test.sql")
	[ ]
[+] VOID DB_ExecuteSQLScript (STRING sODBC_ConnectString, STRING sFilename)
	[+] do
		[ ]
		[ ] HDATABASE 		hdbc 		= NULL
		[ ] HSQL 			hstmnt		= NULL
		[ ] HFILE 			hFile
		[ ] STRING 			sLine		= ""
		[ ] STRING			sCmd		= NULL
		[ ]
		[ ] //Reading the SQL Script file
		[ ] hFile		= FileOpen (sFilename, FM_READ)
		[ ] // connect to database
		[ ] hdbc = DB_Connect (sODBC_ConnectString)
		[ ]
		[ ] // execute the lines
		[+] while (FileReadLine (hFile, sLine))
			[ ] // Remove any leading and trailing whitespace
			[ ] sLine = Ltrim (Rtrim (sLine))
			[+] if (Len(sLine) == 0)
				[ ] continue
			[+] //else
				[ ]
			[ ] sCmd = (IsNull(sCmd) == TRUE) ? sLine : "{sCmd} {sLine}"
			[ ]
			[ ] // A semi-colon terminates the SQL statement
			[+] if (sLine[Len(sLine)] == ';')
				[ ] Print(sCmd)
				[ ] hstmnt = DB_ExecuteSql (hdbc, sCmd)
				[ ] DB_FinishSQL (hstmnt)
				[ ] // Begin of a new command
				[ ] sCmd = NULL
		[ ]
		[ ] // close and disconnect
		[ ] FileClose (hFile)
		[ ] DB_Disconnect (hdbc)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: DB_ExecuteSQLScript in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: DB_ExecuteSQLScript in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] ExceptLog ()
		[ ] return
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ] // Function:
[ ] // Action:
[ ] // Syntax:
[ ] // Parameter:
[ ] // Returns:
[+] INTEGER GetDayCounter (STRING sName, INTEGER nWrap optional)
	[ ] const STRING sFileName  = "{PROJECT_HOME}\SilkTest\Data"+"\DayCounter.txt"
	[ ]
	[ ] HINIFILE hIniFile = IniFileOpen (sFileName)
	[ ]
	[ ] STRING sLast  = IniFileGetValue (hIniFile, sName, "Modified")
	[ ] DATETIME dtLast = (sLast != "") ? ([DATETIME] sLast) : NULL
	[ ] DATETIME dtNow  = GetDateTime ()
	[ ]
	[ ] STRING sValue = IniFileGetValue (hIniFile, sName, "Value")
	[ ] INTEGER nValue = (sValue != "") ? Val (sValue) : NULL
	[ ]
	[+] select
		[+] case (dtLast == NULL) || (nValue == NULL)
			[ ] nValue = 1
		[+] case ([DATE] dtLast != [DATE] dtNow)
			[ ] nValue = 1
		[+] case (nWrap != NULL) && (nValue >= nWrap)
			[ ] nValue = 1
		[+] default
			[ ] nValue += 1
	[ ]
	[ ] IniFileSetValue (hIniFile, sName, "Modified", [STRING] dtNow)
	[ ] IniFileSetValue (hIniFile, sName, "Value", Str (nValue))
	[ ]
	[ ] IniFileClose (hIniFile)
	[ ]
	[ ] return (nValue)
[ ]
[ ] //------------------------------------------------------------------------------------------------------------------------
[ ]
[ ]
[ ] //------------------------------------------------------------------------------------------------------------------------
[ ]
