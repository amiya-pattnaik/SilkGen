[ ] //	**************************************************************************************************** //
[ ] 
[ ] //	File Name			:	SILKGEN_DataTypeManipuFunc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Data types manipulation functions are incluced here
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
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										DataType Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type INVALID is enum
	[ ] INVALID_VALUE
[ ]
[ ] // Function:	IsEnumType function
[ ] // Action:		Checks whether the data type is of type Enumerater
[ ] // Syntax:		IsEnumType (DATATYPE Type)
[ ] // Parameter:	Type: the data-type to be checked. DATATYPE.
[ ] // Returns:		Returns TRUE or FALSE. BOOLEAN.
[+] BOOLEAN IsEnumType (DATATYPE Type)
	[+] do
		[ ] ValuesOfEnum (Type)
		[ ] ListAppend(laLogDetails, "Call to function: IsEnumType in testcase: {GetTestCaseName()}	success")
		[ ] return (TRUE)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: IsEnumType in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return FALSE
		[ ]
[ ]
[ ] // Function:	IsSetType function
[ ] // Action:		returns TRUE or FALSE if a set which contains all the members in the set domain.
[ ] // Syntax:		IsSetType (DATATYPE Type)
[ ] // Parameter:	Type: The name of the set data type as defined in a type...is set declaration. DATATYPE.
[ ] // Returns:		Returns TRUE or FALSE. BOOLEAN.
[+] BOOLEAN IsSetType (DATATYPE Type)
	[+] do
		[ ] SetDomain (Type)
		[ ] ListAppend(laLogDetails, "Call to function: IsSetType in testcase: {GetTestCaseName()}	success")
		[ ] return (TRUE)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: IsSetType in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return FALSE
		[ ]
[ ]
[ ] // Function:	ReturnDataType function
[ ] // Action:		Attempt to assign a specified datatype. If successful, return the specified datatype
[ ] // Syntax:		ReturnDataType (inout ANYTYPE aValue null)
[ ] // Parameter:	aValue: [null]. Any value of type anytype. ANYTYPE.
[ ] // Returns:		Returns the specified data-type. DATATYPE.
[+] DATATYPE ReturnDataType (inout ANYTYPE aValue null)
	[ ]
	[ ] DATATYPE Type
	[+] if ((aValue == NULL))
		[ ] return (NULL)
	[ ] Type = typeof (aValue)
	[ ]
	[ ] //ListAppend(laLogDetails, "Call to function: GetTypeOf in testcase: {GetTestCaseName()}	success")
	[ ] return (Type)
	[ ]
[ ]
[ ] // Function:	GetTypeOf function
[ ] // Action:		Attempt to assign a specified datatype. If successful, return the specified datatype
[ ] // Syntax:		GetTypeOf (inout ANYTYPE aValue null)
[ ] // Parameter:	aValue: [null]. Any value of type anytype. ANYTYPE.
[ ] // Returns:		Returns the specified data-type. DATATYPE.
[ ]
[+] DATATYPE GetTypeOf (inout ANYTYPE aValue null)
	[ ] DATATYPE Type
	[ ]
	[ ] // Attempt to assign a STRING value. If successful, return STRING.
	[+] do
		[ ] aValue = ""
		[ ] Type = STRING
	[+] except
		[+] do
			[ ] // Attempt to assign it with 0. If successful, return INTEGER.
			[ ] aValue = 0
			[ ] Type = typeof (aValue)
		[+] except
			[+] do
				[ ] // Attempt to assign it with FALSE. If successful, return BOOLEAN.
				[ ] aValue = false
				[ ] Type = BOOLEAN
			[+] except
				[+] do
					[ ] // Attempt to assign it to a list. If successful, return LIST of <TYPE USED>.
					[ ] aValue = {}
					[ ] Type = typeof (aValue)
				[+] except
					[+] do
						[ ] // Attempt to assign it with INVALID_VALUE. If fails, figure out and return the ENUM type.
						[ ] aValue = INVALID_VALUE
					[+] except
						[ ] STRING sData = ExceptData()
						[ ] LIST OF STRING lsTokens = ParseStringList (sData, " ")
						[ ] STRING sType = lsTokens[ListCount(lsTokens)]
						[ ] Type = @sType
	[ ]
	[ ] return (Type)
[ ]
[ ]
[ ] // Function:	GetTypeOfElem function
[ ] // Action:		Returns the datatype of the LIST elements
[ ] // Syntax:		GetTypeOfElem (LIST l)
[ ] // Parameter:	l: Used to declare a list variable. LIST.
[ ] // Returns:		Returns the type of data that is present in the LIST. ANYTYPE.
[+] ANYTYPE GetTypeOfElem (LIST l)
	[+] do
		[ ]
		[ ] ANYTYPE aListType = [STRING] TypeOf (l)
		[ ] ANYTYPE aElemType = GetField (aListType, "LIST OF ", 2)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: GetTypeOfElem in testcase: {GetTestCaseName()}	success")
		[ ] return aElemType
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetTypeOfElem in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return NULL
		[ ]
	[ ]
[ ]
[ ] // Function:	ResolveEnum function
[ ] // Action:		Finds an element in the Enumerater
[ ] // Syntax:		ResolveEnum (DATATYPE EnumType, STRING sValue null)
[ ] // Parameter:	EnumType: The name of the Enumerater in which the element is to be searched. DATATYPE.
[ ] // Parameter:	sValue: [null]. The element to be searched in the Enumerater. STRING.
[ ] // Returns:		Returns the element if exists in the Enumerater else returns NULL. ANYTYPE.
[+] ANYTYPE ResolveEnum (DATATYPE EnumType, STRING sValue null)
	[+] do
		[ ]
		[+] if ((sValue == NULL) || (sValue == ""))
			[ ] return (NULL)
			[ ] ListAppend(laLogDetails, "Call to function: ResolveEnum in testcase: {GetTestCaseName()}	success")
		[ ]
		[ ] STRING sTypeName = [STRING] EnumType
		[ ] INTEGER nTypeNameLen = Len (sTypeName)
		[ ]
		[+] do
			[ ] STRING sVarName = "lValueMap_{sTypeName}"
			[ ] ANYTYPE aValue
			[ ]
			[+] if (ValueMap_MatchText (@sVarName, sValue, aValue))
				[ ] return (aValue)
		[+] except
			[ ]
		[ ]
		[ ] sValue = StrTran (Upper (sValue), " ", "")
		[ ]
		[+] if (StrPos (sTypeName, sValue) == 1)
			[ ] sValue = SubStr (sValue, nTypeNameLen + 1)
		[ ]
		[ ] sValue = StrTran (sValue, "_", "")
		[ ]
		[ ] ANYTYPE aEach
		[+] for each aEach in ValuesOfEnum (EnumType)
			[ ] STRING sEach = StrTran (Upper ([STRING] aEach), " ", "")
			[ ]
			[+] if (StrPos (sTypeName, sEach) == 1)
				[ ] sEach = SubStr (sEach, nTypeNameLen + 1)
			[ ]
			[ ] sEach = StrTran (sEach, "_", "")
			[ ]
			[+] if (sEach == sValue)
				[ ]
				[ ] ListAppend(laLogDetails, "Call to function: ResolveEnum in testcase: {GetTestCaseName()}	success")
				[ ] return (aEach)
		[ ]
	[+] except
		[ ] RES.AppError ("'{sValue}' is not a valid value for enumerated type {EnumType}")
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ResolveEnum in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return NULL
		[ ]
	[ ]
[ ]
[ ] // Function:	ResolveSet function
[ ] // Action:		Finds an element in the SET.
[ ] // Syntax:		ResolveSet (DATATYPE SetType, STRING sValue null)
[ ] // Parameter:	SetType: The name of the SET datatype in which the element is to be searched. DATATYPE.
[ ] // Parameter:	sValue: [null]. The element to be searched in the SET dtatype. STRING.
[ ] // Returns:		Returns the element if exists in the SET else returns NULL. ANYTYPE.
[+] ANYTYPE ResolveSet (DATATYPE SetType, STRING sValue null)
	[+] do
		[ ]
		[+] if ((sValue == NULL) || (sValue == ""))
			[ ] return NULL
		[ ]
		[+] if (StrPos (EXCEL_SET_DELIM, sValue) > 0)
			[ ] ANYTYPE aReturn = NULL
			[+] for each sValue in ParseStringList (sValue, EXCEL_SET_DELIM)
				[+] if (aReturn == NULL)
					[ ] aReturn = ResolveSet (SetType, sValue)
				[+] else
					[ ] aReturn += ResolveSet (SetType, sValue)
			[ ]
			[ ] ListAppend(laLogDetails, "Call to function: ResolveSet in testcase: {GetTestCaseName()}	success")
			[ ] return (aReturn)
		[ ]
		[ ] STRING sTypeName = [STRING] SetType
		[ ] INTEGER nTypeNameLen = Len (sTypeName)
		[ ]
		[+] do
			[ ] STRING sVarName = "lValueMap_{sTypeName}"
			[ ] ANYTYPE aValue
			[ ]
			[+] if (ValueMap_MatchText (@sVarName, sValue, aValue))
				[ ] return (aValue)
		[ ] except
		[ ]
		[ ] sValue = StrTran (Upper (sValue), " ", "")
		[ ]
		[+] if (StrPos (sTypeName, sValue) == 1)
			[ ] sValue = SubStr (sValue, nTypeNameLen + 1)
		[ ]
		[ ] sValue = StrTran (sValue, "_", "")
		[ ]
		[ ] ANYTYPE aEach
		[+] for each aEach in SetDomain (SetType)
			[ ] STRING sEach = StrTran (Upper ([STRING] aEach), " ", "")
			[ ]
			[+] if (StrPos (sTypeName, sEach) == 1)
				[ ] sEach = SubStr (sEach, nTypeNameLen + 1)
			[ ]
			[ ] sEach = StrTran (sEach, "_", "")
			[ ]
			[+] if (sEach == sValue)
				[ ] ListAppend(laLogDetails, "Call to function: ResolveSet in testcase: {GetTestCaseName()}	success")
				[ ] return (aEach)
	[+] except
		[ ] RES.AppError ("'{sValue}' is not a valid value for SET type {SetType}")
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ResolveSet in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return NULL
		[ ]
	[ ]
[ ]
[ ] // Function:	ConvertStrToType function
[ ] // Action:		Convert a string to a specified datatype (can be STRING, NUMBER, BOOLEAN, ENUM, SET)
[ ] // Syntax:		ConvertStrToType (STRING sValue null, DATATYPE VarType)
[ ] // Parameter:	sValue : [null]. The string to convert. STRING.
[ ] // Parameter:	VarType : Explicit type conversions require (Ex. STRING, NUMBER, BOOLEAN, ENUM, SET). DATATYPE
[ ] // Returns:		Returns the sValue in the specified type. ANYTYPE.
[+] ANYTYPE ConvertStrToType (STRING sValue null, DATATYPE VarType)
	[+] do
		[ ]
		[+] if (sValue == NULL)
			[ ] return (NULL)
		[ ]
		[+] select
			[+] case (VarType == STRING)
				[ ] return (sValue)
			[+] case (VarType == NUMBER)
				[ ] return (Val (sValue))
			[+] case (VarType == BOOLEAN)
				[+] switch Trim (Upper (sValue))
					[+] case "T","TRUE","YES", "Y", "1"
						[ ] return (TRUE)
					[+] case "F","FALSE","NO", "N", "0"
						[ ] return (FALSE)
					[+] default
						[ ] RES.AppError ("'{sValue}' is not a valid boolean value")
			[+] case (IsEnumType (VarType))
				[ ] return (ResolveEnum (VarType, sValue))
			[+] case (IsSetType (VarType))
				[ ] return (ResolveSet (VarType, sValue))
			[+] default
				[ ] RES.AppError ("Unable to convert {sValue} to {VarType}")
			[ ]
			[ ] ListAppend(laLogDetails, "Call to function: ConvertStrToType in testcase: {GetTestCaseName()}	success")
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ConvertStrToType in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return NULL
		[ ]
	[ ]
