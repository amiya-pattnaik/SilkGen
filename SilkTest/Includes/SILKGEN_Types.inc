[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_DataTypes.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Datatype declaration specific to SILKGEN Framework are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak 
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		12/01/08	Amiya Pattnayak	Created
	[ ] //
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ] // type for getting key's value from .properties file //
[+] type PROPERTIES_KEY_VELUES is record
	[ ] STRING		sTargetMachine
	[ ] BROWSERTYPE btDefaultBrowser
	[ ] STRING 		sLocalMachineErrorDir
	[ ] STRING		sRemoteMachineErrorDir
	[ ] STRING 		sReportType
	[ ] STRING		sTestSetName
	[ ] STRING 		sTestDescription
	[ ] INTEGER 	iDebugMode
	[ ] STRING		sTestFileToRun
	[ ]
	[ ]
[ ] PROPERTIES_KEY_VELUES Properties_KeyValues
[ ]
[ ] // type for getting the ScriptName, TestcaseName & its respective TestData from the .txt file
[+] type SCRIPT_TESTCASE_TESTDATA is record
	[ ]
	[ ] LIST OF STRING 	lsScriptName		//Contains only Scripts name
	[ ] LIST OF ANYTYPE laTestCaseTestData	//Variable to hold TestcaseName & its respective TestData
	[ ]
[ ] SCRIPT_TESTCASE_TESTDATA Script_Tc_TData
[ ]
[ ]
[+] type ENV_VARIABLE_TYPE is enum
	[ ] System
	[ ] User
[ ]
[ ] // Define the type for declaring function / argument pairs //
[+] type FUNCTION_DATA is record
	[ ] STRING sFuncName
	[ ] LIST OF ANYTYPE laArgs
[ ]
[ ] // type for capturng web page information //
[+] type WEB_PAGE_SIZE is record
	[ ] INTEGER iPageSize		// size of the web page (in bytes)
	[ ] INTEGER	iNumObjects		// Number of objects on web page
	[ ] NUMBER 	nKB				// size of the web page (in KB)
	[ ]
[ ]
[ ] // type for getting the tag information of an objects. //
[ ] // this records contains the data such as Objects's Class, Objects's Tag (Including multitag) and Index //
[+] type TAGINFO is record
	[ ] STRING sClass
	[ ] STRING sTag
	[ ] STRING sIndex
[ ]
[ ] // type to contain SQL table's Column's name as well as its value
[+] type SQLCOLUMNVALUE is record
	[ ] STRING 	sColumn		// Column name of the table
	[ ] ANYTYPE aValue		// the value against the column name
	[ ] INTEGER nDecimal	// a integer value for decimal representation ( zero to nay number)
[ ]
[ ] // The record used for Mapping the SQL rows with the variables in the record to be stored
[+] // {Ex: lSqlQueryMap = {...}
	[ ] // 	{"Name", 	"sName"}   Here 'Name' is the Column name in the table and 'sName' is the variable in the record
	[ ] // 	{"Value", 	"sValue"}  Here 'Value' is the Column name in the table and 'sValue' is the variable in the record
[+] type SQLQUERYMAP is record
	[ ] STRING sExpr
	[ ] STRING sMember
	[ ] STRING sTrans
	[ ]
	[ ] //Runtime
	[ ] TRANSINFO TransInfo
[ ]
[ ] // The record used for Mapping the Excel rows with the variables in the record to be stored
[+] // {Ex: lExcelMap = {...}
	[ ] // 		{"Name", 	"sName"}   Here 'Name' is the Column name in the table and 'sName' is the variable in the record
	[ ] // 		{"Value", 	"sValue"}  Here 'Value' is the Column name in the table and 'sValue' is the variable in the record
[+] type EXCELMAP is record
	[ ] // The record used for Mapping the Excel rows with the variables in the record to be stored
	[ ]
	[ ] STRING sColumnName
	[ ] STRING sMember
	[ ] STRING sTransform
	[ ]
	[ ] LIST OF EXCELMAP lPropMap
	[ ]
	[ ] //Runtime
	[ ] EXCELRUNFLAGS RunFlags
	[ ] TRANSINFO TransInfo
[ ]
