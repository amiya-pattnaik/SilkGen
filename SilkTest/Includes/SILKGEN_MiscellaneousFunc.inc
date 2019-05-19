[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_MiscellaneousFunc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Miscellaneous Functions are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak 
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		04/06/09	Amiya Pattnayak	Created
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //											Results file wrapper
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type PRINTFLAGS is set
	[ ] PrintFlags_NoNulls
[ ]
[+] window AnyWin RES
	[ ]
	[ ] const STRING CODE_RUNNING         = "[-]"
	[ ] const STRING CODE_PASSED          = "[P]"
	[ ] const STRING CODE_PASSED_WARNINGS = "[Pw]"
	[ ] const STRING CODE_FAILED          = "[F]"
	[ ]
	[+] const LIST OF DATATYPE lSimpleTypes = {...}
		[ ] BOOLEAN
		[ ] NUMBER
		[ ] STRING
		[ ] DATETIME
	[ ]
	[ ] STRING  sDir  = NULL
	[ ] STRING  sName = NULL
	[ ] STRING  sPath = NULL
	[ ]
	[ ] HFILE   hFileRes = NULL
	[ ] HFILE   hFileOut = NULL
	[ ]
	[ ] INTEGER nErrorCount
	[ ] INTEGER nWarningCount
	[ ]
	[+] STRING CreateResultDir ()
		[ ] sDir = "{PROJECT_HOME}\SilkTest\Results"
		[ ]
		[+] if (! hHost->SYS_DirExists (sDir))
			[ ] hHost->SYS_MakeDir (sDir)
		[ ]
		[ ] return (sDir)
	[ ]
	[+] BOOLEAN IsOpen ()
		[ ] return (hFileRes != NULL)
	[ ]
	[+] STRING GenPath (STRING sName, STRING sCode)
		[+] if (sDir == NULL)
			[ ] sDir = CreateResultDir ()
		[ ]
		[ ] STRING sTimeStamp = FormatDateTime (GetDateTime(), "yymmdd-hhmmss")
		[ ] return ("{sDir}\{sName} {sTimeStamp} {sCode}.txt")
	[ ]
	[+] void OpenFile (STRING sOpenName)
		[ ] CloseFile ()
		[ ]
		[ ] sOpenName = StrTran (sOpenName, "/", "-")
		[ ] STRING sOpenPath = GenPath (sOpenName, CODE_RUNNING)
		[ ]
		[+] do
			[ ] hFileRes = FileOpen (sOpenPath, FM_APPEND)
		[+] except
			[ ] ExceptLog()
			[ ] LogWarning ("Unable to open {sPath} - results not being saved")
			[ ] return
		[ ]
		[ ] hFileRes = hFileRes
		[ ] sName = sOpenName
		[ ] sPath = sOpenPath
		[ ]
		[ ] nErrorCount   = GetTestCaseErrorCount()
		[ ] nWarningCount = GetTestCaseWarningCount()
	[ ]
	[+] void CloseFile (BOOLEAN bDelete optional)
		[+] if (hFileRes != NULL)
			[ ] FileClose (hFileRes)
			[ ] hFileRes = NULL
		[ ]
		[+] if (sPath != NULL)
			[+] if ((bDelete != NULL) && bDelete)
				[ ] hHost->SYS_RemoveFile (sPath)
			[+] else
				[ ] STRING sCode
				[ ]
				[+] select
					[+] case (GetTestCaseErrorCount() > nErrorCount)
						[ ] sCode = CODE_FAILED
					[+] case (GetTestCaseWarningCount() > nWarningCount)
						[ ] sCode = CODE_PASSED_WARNINGS
					[+] default
						[ ] sCode = CODE_PASSED
				[ ]
				[ ] STRING sNewPath = StrTran (sPath, CODE_RUNNING, sCode)
				[ ] hHost->SYS_MoveFile (sPath, sNewPath)
		[ ]
		[ ] sName = NULL
		[ ] sPath = NULL
	[ ]
	[+] void DeleteFile ()
		[ ] CloseFile (TRUE)
	[ ]
	[+] void OpenOutputFile (STRING sFullPath)
		[ ] CloseOutputFile ()
		[ ] hFileOut = FileOpen (sFullPath, FM_WRITE)
	[ ]
	[+] void CloseOutputFile ()
		[+] if (hFileOut != NULL)
			[ ] FileClose (hFileOut)
			[ ] hFileOut = NULL
	[ ]
	[+] void Print (varargs va)
		[ ] STRING sText = ""
		[ ]
		[ ] INTEGER i
		[+] for i = 1 to ListCount (va)
			[+] if (i > 1)
				[ ] sText += " "
			[ ] sText += [STRING] va[i]
		[ ]
		[ ] PrintLine (sText)
	[ ]
	[+] void PrintLine (STRING sText)
		[+] if (hFileRes != NULL)
			[ ] FileWriteLine (hFileRes, sText)
		[ ]
		[+] if (hFileOut != NULL)
			[ ] FileWriteLine (hFileOut, sText)
		[+] else
			[ ] ::Print (sText)
	[ ]
	[+] void ListPrint (LIST OF ANYTYPE la)
		[ ] ANYTYPE a
		[+] for each a in la
			[ ] Print (a)
	[ ]
	[+] VOID PrintRecord (ANYTYPE aRecord, STRING sHeader optional, INTEGER nIndent optional, LIST OF STRING lsExclude optional, PRINTFLAGS PrintFlags optional)
		[+] if (nIndent == NULL)
			[ ] nIndent = 0
		[ ]
		[+] if (sHeader != NULL)
			[ ] RES.Print (sHeader)
			[ ] nIndent += 1
		[ ]
		[ ] STRING sIndent = Space (nIndent * 2)
		[ ]
		[ ] STRING sField
		[ ] LIST OF STRING lsFields = FieldsOfRecord (TypeOf (aRecord))
		[ ]
		[ ] INTEGER nMaxNameWidth = 0
		[ ]
		[+] for each sField in lsFields
			[+] if ((lsExclude != NULL) && (ListFind (lsExclude, sField) > 0))
				[ ] continue
			[ ]
			[ ] INTEGER nNameWidth = Len (sField)
			[+] if (nNameWidth > nMaxNameWidth)
				[ ] nMaxNameWidth = nNameWidth
		[ ]
		[ ] BOOLEAN bNoNulls = (PrintFlags != NULL) && (PrintFlags_NoNulls in PrintFlags)
		[ ]
		[+] for each sField in lsFields
			[+] if ((lsExclude != NULL) && (ListFind (lsExclude, sField) > 0))
				[ ] continue
			[ ]
			[ ] ANYTYPE aValue = IsSet (aRecord.@sField) ? aRecord.@sField : "<unset>"
			[ ]
			[+] if ((aValue == NULL) && bNoNulls)
				[ ] continue
			[ ]
			[ ] RES.Print ("{sIndent}{StrPadSpaces(sField,nMaxNameWidth)} = {aValue}")
	[ ]
	[+] void SuperPrint (STRING sDesc, ANYTYPE aValue null, PRINTFLAGS PrintFlags optional, INTEGER nLevel optional)
		[+] if (nLevel == NULL)
			[ ] nLevel = 0
		[ ]
		[ ] BOOLEAN bNoNulls = (PrintFlags != NULL) && (PrintFlags_NoNulls in PrintFlags)
		[ ]
		[ ] STRING sIndent = Replicate (": ", nLevel)
		[ ]
		[+] if (aValue == NULL)
			[ ] RES.Print ("{sIndent}{sDesc} = <NULL>")
			[ ] return
		[ ]
		[ ] /*** CHECK FOR SIMPLE VALUES ***/
		[ ]
		[ ] DATATYPE ValueType = TypeOf (aValue)
		[ ]
		[+] if (ListFind (lSimpleTypes, ValueType) > 0)
			[ ] RES.Print ("{sIndent}{sDesc} = {aValue}")
			[ ] return
		[ ]
		[ ] /*** CHECK FOR LIST OR ARRAY ***/
		[ ]
		[ ] INTEGER nCount
		[ ] INTEGER nIndex
		[ ]
		[+] if (IsList (aValue))
			[+] for nIndex = 1 to ListCount (aValue)
				[ ] SuperPrint ("{sDesc}[{nIndex}]", aValue[nIndex], PrintFlags, nLevel)
			[ ]
			[ ] return
		[ ]
		[+] if (IsArray (aValue))
			[+] for nIndex = 1 to ArraySize (aValue)
				[ ] SuperPrint ("{sDesc}[{nIndex}]", aValue[nIndex], PrintFlags, nLevel)
			[ ]
			[ ] return
		[ ]
		[ ] /*** CHECK FOR RECORD ***/
		[ ]
		[ ] LIST OF STRING lsFields
		[ ]
		[+] do
			[ ] lsFields = FieldsOfRecord (ValueType)
		[+] except
			[ ] lsFields = NULL
		[ ]
		[+] if (lsFields != NULL)
			[ ] BOOLEAN bPrintHeader = TRUE
			[ ]
			[ ] STRING sField
			[+] for each sField in lsFields
				[+] if (! IsSet (aValue.@sField))
					[ ] continue
				[ ]
				[+] if (bNoNulls && (aValue.@sField == NULL))
					[ ] continue
				[ ]
				[+] if (bPrintHeader)
					[ ] RES.Print ("{sIndent}{sDesc}")
					[ ] bPrintHeader = FALSE
				[ ]
				[ ] SuperPrint (sField, aValue.@sField, PrintFlags, nLevel + 1)
			[ ]
			[ ] return
		[ ]
		[ ] /*** JUST PRINT THE VALUE ***/
		[ ]
		[ ] RES.Print ("{sIndent}{sDesc} = {aValue}")
	[ ]
	[+] void SuperPrintToFile (STRING sFileName, STRING sDesc null, ANYTYPE aValue null, PRINTFLAGS PrintFlags optional)
		[ ] BOOLEAN bExcept = FALSE
		[ ] HFILE hSaveFileOut = hFileOut
		[ ]
		[+] do
			[ ] OpenOutputFile (sFileName)
			[ ] SuperPrint (sDesc, aValue, PrintFlags)
			[ ] CloseOutputFile ()
		[+] except
			[ ] bExcept = TRUE
		[ ]
		[ ] hFileOut = hSaveFileOut
		[ ]
		[+] if (bExcept)
			[ ] reraise
	[ ]
	[+] VOID PrintFile (STRING sFileName, STRING sHeader optional, INTEGER nIndent optional)
		[+] if (nIndent == NULL)
			[ ] nIndent = 0
		[ ]
		[+] if (sHeader != NULL)
			[ ] RES.Print (sHeader)
			[ ] nIndent += 1
		[ ]
		[ ] LIST OF STRING lsLines
		[ ] ListRead (lsLines, sFileName)
		[ ]
		[ ] STRING sIndent = Space (nIndent * 2)
		[ ]
		[ ] STRING sLine
		[+] for each sLine in lsLines
			[ ] RES.Print ("{sIndent}{sLine}")
	[ ]
	[+] void LogWarning (STRING sText)
		[+] if (hFileRes != NULL)
			[ ] FileWriteLine (hFileRes, sText)
		[ ]
		[ ] ::LogWarning (sText)
	[ ]
	[+] void LogError (STRING sText)
		[+] if (hFileRes != NULL)
			[ ] FileWriteLine (hFileRes, sText)
		[ ]
		[ ] ::LogError (sText)
	[ ]
	[+] void AppError (STRING sText)
		[+] if (IsSet (hFileRes) && (hFileRes != NULL))
			[ ] FileWriteLine (hFileRes, "*** ABORT: {sText}")
		[ ]
		[ ] ::AppError (sText)
	[ ]
	[+] void ExceptLog ()
		[ ] RES.LogError (ExceptData ())
		[ ]
		[ ] CALL Call
		[ ] INTEGER nIndex = 0
		[+] for each Call in ExceptCalls ()
			[ ] STRING sPrefix =  (nIndex++ == 0) ? "Occurred in" : "Called from"
			[ ] RES.Print ("{sPrefix} {Call.sFunction} at {Call.sModule}({Call.iLine})")
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //											Tag info functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // function:  	GetChildrenTagInfo (LIST OF WINDOW lwChildren, BOOLEAN bHidden optional)
[ ] // Action:     	Returns the tag of all the child objects (i.e. all children) as a LIST OF TAGINFO.
[ ] // Syntax:		lTagInfo = GetChildrenTagInfo (LIST OF WINDOW lwChildren, BOOLEAN bHidden optional)
[ ] // parameter: 	lwChildren: List Of Children for which you wish to get the tag. LIST OF WINDOW
[ ] // parameter: 	bHidden: If set to False, Ignores HtmlHidden Objects. Otherwise not.Default is FALSE (optional). BOOLEAN.
[ ] // returns:   	lTagInfo: Returns the tag information of an objects. such as Objects's Class, Objects's Tag (Including multitag). LIST OF TAGINFO.
[+] LIST OF TAGINFO GetChildrenTagInfo (LIST OF WINDOW lwChildren, BOOLEAN bHidden optional)
	[+] do
		[ ]
		[-] if (bHidden == NULL)
			[ ] bHidden = FALSE
		[ ]
		[ ] LIST OF TAGINFO lTagInfo = {}
		[ ]
		[ ] WINDOW wChild
		[ ] INTEGER nPos
		[ ]
		[+] for each wChild in lwChildren
			[ ] STRING sTag = wChild.WndTag
			[ ]
			[ ] nPos = StrPos ("/", sTag, TRUE)
			[ ] sTag = SubStr (sTag, nPos + 1)
			[ ]
			[ ] STRING sClass = ""
			[ ] STRING sIndex = "1"
			[ ]
			[+] if (sTag[1] == "[")
				[ ] nPos = StrPos ("]", sTag)
				[ ] sClass = SubStr (sTag, 2, nPos - 2)
				[ ] sTag = SubStr (sTag, nPos + 1)
			[ ]
			[+] if (Right (sTag, 1) == "]")
				[ ] nPos = StrPos ("[", sTag, TRUE)
				[+] if (nPos < 1)
					[ ] AppError ("X {nPos} {sTag}")
				[ ] sIndex = SubStr (sTag, nPos + 1, Len (sTag) - nPos - 1)
				[ ] sTag = Left (sTag, nPos - 1)
			[ ]
			[-] if ((! bHidden) && (sClass == "HtmlHidden"))
				[ ] continue
			[ ]
			[ ] ListAppend (lTagInfo, [TAGINFO] {sClass, sTag, sIndex})
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: GetChildrenTagInfo in testcase: {GetTestCaseName()}	success")
		[ ] return (lTagInfo)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetChildrenTagInfo in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ]
[ ] // function:  	GetChildTagInfo (WINDOW wChild, BOOLEAN bHidden optional)
[ ] // Action:     	Returns the tag of a child object as a record, TAGINFO.
[ ] // Syntax:		lTagInfo = GetChildTagInfo (WINDOW wChild, BOOLEAN bHidden optional)
[ ] // parameter: 	wChild: The Child object for which you wish to get the tag. WINDOW.
[ ] // parameter: 	bHidden: If set to False, Ignores HtmlHidden Objects. Otherwise not.Default is FALSE (optional). BOOLEAN.
[ ] // returns:   	rTagInfo: Returns the tag information of a child Object, such as Objects's Class, Objects's Tag (Including multitag). TAGINFO.
[+] TAGINFO GetChildTagInfo (WINDOW wChild, BOOLEAN bHidden optional)
	[-] do
		[ ]
		[+] if (bHidden == NULL)
			[ ] bHidden = FALSE
		[ ]
		[ ] TAGINFO rTagInfo = {}
		[ ]
		[ ] INTEGER nPos
		[ ] STRING sTag = wChild.WndTag
		[ ]
		[ ] nPos = StrPos ("/", sTag, TRUE)
		[ ] sTag = SubStr (sTag, nPos + 1)
		[ ]
		[ ] STRING sClass = ""
		[ ] STRING sIndex = "1"
		[ ]
		[+] if (sTag[1] == "[")
			[ ] nPos = StrPos ("]", sTag)
			[ ] sClass = SubStr (sTag, 2, nPos - 2)
			[ ] sTag = SubStr (sTag, nPos + 1)
		[ ]
		[+] if (Right (sTag, 1) == "]")
			[ ] nPos = StrPos ("[", sTag, TRUE)
			[+] if (nPos < 1)
				[ ] AppError ("X {nPos} {sTag}")
			[ ] sIndex = SubStr (sTag, nPos + 1, Len (sTag) - nPos - 1)
			[ ] sTag = Left (sTag, nPos - 1)
		[ ]
		[+] if ((! bHidden) && (sClass == "HtmlHidden"))
			[ ] //Do Nothing
		[ ]
		[ ] rTagInfo.sClass 	= sClass
		[ ] rTagInfo.sTag 		= sTag
		[ ] rTagInfo.sIndex 	= sIndex
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: GetChildTagInfo in testcase: {GetTestCaseName()}	success")
		[ ] return (rTagInfo)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetChildTagInfo in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 						Check Functions - These functions log errors but do not raise exceptions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ] BOOLEAN bCheckPassedLog = TRUE
[ ]
[+] type CHECKFLAGS is set
	[ ] CheckFlag_Warning
[ ]
[+] VOID CheckValueNull (STRING sDesc, ANYTYPE aActual null)
	[+] if (aActual != NULL)
		[ ] RES.LogError ("Verify {sDesc} failed -- Expected NULL value, Actual={aActual}")
	[+] else if (bCheckPassedLog)
		[ ] RES.Print ("Verify {sDesc} passed -- Expected NULL value, Actual={aActual}")
[ ]
[+] VOID CheckValueNotNull (STRING sDesc, ANYTYPE aActual null)
	[+] if (aActual == NULL)
		[ ] RES.LogError ("Verify {sDesc} failed -- Expected non-NULL value, Actual={aActual}")
	[+] else if (bCheckPassedLog)
		[ ] RES.Print ("Verify {sDesc} passed -- Expected non-NULL value, Actual={aActual}")
[ ]
[+] VOID CheckValueEqual (STRING sDesc, ANYTYPE aExpected, ANYTYPE aActual)
	[+] if (aExpected != aActual)
		[ ] RES.LogError ("Verify {sDesc} failed -- Expected={aExpected}, Actual={aActual}")
	[+] else if (bCheckPassedLog)
		[ ] RES.Print ("Verify {sDesc} passed -- Expected={aExpected}, Actual={aActual}")
[ ]
[+] VOID CheckValueMatch (STRING sDesc, STRING sExpected, STRING sActual)
	[+] if (! MatchStr (sExpected, sActual))
		[ ] RES.LogError ("Verify {sDesc} failed -- Expected={sExpected}, Actual={sActual}")
	[+] else if (bCheckPassedLog)
		[ ] RES.Print ("Verify {sDesc} passed -- Expected={sExpected}, Actual={sActual}")
[ ]
[+] VOID CheckValueListMatch (STRING sDesc, LIST OF STRING lsExpected, STRING sActual)
	[ ] BOOLEAN bMatch = FALSE
	[ ] STRING sExpected
	[ ]
	[+] for each sExpected in lsExpected
		[+] if (MatchStr (sExpected, sActual))
			[ ] bMatch = TRUE
			[ ] break
	[ ]
	[+] if (! bMatch)
		[ ] RES.LogError ("Verify {sDesc} failed -- Expected={lsExpected}, Actual={sActual}")
	[+] else if (bCheckPassedLog)
		[ ] RES.Print ("Verify {sDesc} passed -- Expected={lsExpected}, Actual={sActual}")
[ ]
[+] VOID CheckDateEqual (STRING sDesc, DATE dExpected, ANYTYPE aActual, CHECKFLAGS Flags optional)
	[ ] DATE dActual = NULL
	[ ] DATETIME dtParse
	[ ] STRING sError = ""
	[ ]
	[+] switch (TypeOf (aActual))
		[+] case STRING
			[+] if (MatchStr ("*/*/????", aActual))
				[+] if (ParseDateFormat (aActual, "m/dd/yyyy", dtParse))
					[ ] dActual = [DATE] dtParse
				[+] else
					[ ] sError = " -- Unable to parse actual date (m-dd-yyyy)"
			[+] else if (MatchStr ("????-*-*", aActual))
				[+] if (ParseDateFormat (aActual, "yyyy-mm-dd", dtParse))
					[ ] dActual = [DATE] dtParse
				[+] else
					[ ] sError = " -- Unable to parse actual date (yyyy-mm-dd)"
			[+] else
				[ ] RES.LogError (" -- Actual date format not recognized")
		[ ]
		[+] case DATE
			[ ] dActual = aActual
		[ ]
		[+] case DATETIME
			[ ] dActual = [DATE] aActual
		[ ]
		[+] default
			[ ] RES.LogError (" -- Actual date is of type {TypeOf(aActual)}")
	[ ]
	[+] if (dExpected != dActual)
		[ ] BOOLEAN bWarning = (Flags != NULL) && (CheckFlag_Warning in Flags)
		[ ]
		[+] if (bWarning)
			[ ] RES.LogWarning ("Verify {sDesc} failed -- Expected={dExpected}, Actual={dActual}" + sError)
		[+] else
			[ ] RES.LogError ("Verify {sDesc} failed -- Expected={dExpected}, Actual={dActual}" + sError)
	[+] else if (bCheckPassedLog)
		[ ] RES.Print ("Verify {sDesc} passed -- Expected={dExpected}, Actual={dActual}")
[ ]
[+] BOOLEAN MatchStrAny (LIST OF STRING lsPattern, STRING sString)
	[ ] STRING sPattern
	[+] for each sPattern in lsPattern
		[+] if (MatchStr (sPattern, sString))
			[ ] return (TRUE)
	[ ] return (FALSE)
[ ]
[+] NUMBER ValAllowNull (STRING sValue null)
	[ ] return (sValue != NULL) ? Val (sValue) : NULL
[ ]
[+] STRING ExceptError ()
	[ ] STRING sError = ExceptData()
	[+] if (MatchStr ("*** Error: *", sError))
		[ ] sError = SubStr (sError, 12)
	[ ] return (sError)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										Parse Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[+] BOOLEAN ParseTime (STRING sTime, STRING sFormat, out TIME tmValue)
	[ ] STRING sAMPM = ""
	[ ] STRING sMS = ""
	[ ]
	[+] select
		[+] case (Upper (Right (sFormat, 3)) == "A/P")
			[ ] sFormat = Left (sFormat, Len (sFormat) - 3)
			[ ] sAMPM = Upper (Right (sTime, 1))
			[ ]
			[+] if (ListFind ({"A","P"}, sAMPM) == 0)
				[ ] return (FALSE)
			[ ]
			[ ] sTime = Left (sTime, Len (sTime) - 1)
		[ ]
		[+] case (Upper (Right (sFormat, 5)) == "AM/PM")
			[ ] sFormat = Left (sFormat, Len (sFormat) - 5)
			[ ] sAMPM = Upper (Right (sTime, 2))
			[ ]
			[+] if (ListFind ({"AM","PM"}, sAMPM) == 0)
				[ ] return (FALSE)
			[ ]
			[ ] sTime = Left (sTime, Len (sTime) - 2)
	[ ]
	[+] if (Right (sFormat, 4) == ".fff")
		[ ] sFormat = Left (sFormat, Len (sFormat) - 4)
		[ ]
		[ ] INTEGER nDot = StrPos (".", sTime)
		[+] if (nDot != 0)
			[ ] sMS = SubStr (sTime, nDot)
			[ ] sTime = Left (sTime, nDot - 1)
	[ ]
	[ ] INTEGER nLen = Len (sTime)
	[ ] INTEGER nTime = 0
	[ ]
	[+] switch (sFormat)
		[+] case "hnnss", "hhnnss"
			[ ] nTime = Val (sTime)
		[ ]
		[+] case "h:nn", "hh:nn"
			[+] if ((nLen != 5) && (nLen != 6))
				[ ] return (FALSE)
			[+] if (! MatchStr ("*?:??", sTime))
				[ ] return (FALSE)
			[ ] nTime = Val (StrTran (sTime,":","")) * 100
		[ ]
		[+] case "h:nn:ss", "hh:nn:ss"
			[+] if ((nLen != 7) && (nLen != 8))
				[ ] return (FALSE)
			[+] if (! MatchStr ("*?:??:??", sTime))
				[ ] return (FALSE)
			[ ] nTime = Val (StrTran (sTime,":",""))
		[ ]
		[+] default
			[ ] return (false)
	[ ]
	[ ] INTEGER nHour   = (nTime / 100) / 100
	[ ] INTEGER nMinute = (nTime / 100) % 100
	[ ] INTEGER nSecond = nTime % 100
	[ ]
	[+] if (((sAMPM == "PM") || (sAMPM == "P")) && (nHour < 12))
		[ ] nHour += 12
	[ ]
	[+] if (((sAMPM == "AM") || (sAMPM == "A")) && (nHour == 12))
		[ ] nHour -= 12
	[ ]
	[ ] tmValue = [TIME] ("{nHour}:{nMinute}:{nSecond}{sMS}")
	[ ] return (TRUE)
[ ]
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										List Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] BOOLEAN ListDeleteValue (inout LIST l, ANYTYPE aValue)
	[ ] INTEGER nIndex = ListFind (l, aValue)
	[+] if (nIndex == 0)
		[ ] return (FALSE)
	[ ]
	[ ] ListDelete (l, nIndex)
	[ ] return (TRUE)
[ ]
[+] void ListPrepend (inout LIST l, ANYTYPE a)
	[+] if (ListCount (l) == 0)
		[ ] ListAppend (l, a)
	[+] else
		[ ] ListInsert (l, 1, a)
[ ]
[+] void ListExtend (inout LIST l null, INTEGER nNewSize)
	[+] if (l == NULL)
		[ ] l = {}
	[ ]
	[ ] INTEGER nCurSize = ListCount (l)
	[ ] INTEGER nExtend = nNewSize - nCurSize
	[+] if (nExtend < 1)
		[ ] return
	[ ]
	[ ] ANYTYPE aEmptyValue = NULL
	[ ] ListAppend (l, aEmptyValue)
	[ ]
	[+] do
		[ ] l[nCurSize + 1] = {}
		[ ] aEmptyValue = {}
	[ ] except
	[ ]
	[+] if (nExtend == 1)
		[ ] return
	[ ]
	[ ] INTEGER i
	[+] for i = 2 to nExtend
		[ ] ListAppend (l, aEmptyValue)
[ ]
[+] void ListTruncate (inout LIST l, INTEGER nNewSize)
	[ ] INTEGER nCount = ListCount (l)
	[ ]
	[ ] INTEGER nIndex
	[+] for nIndex = nCount to nNewSize + 1 step -1
		[ ] ListDelete (l, nIndex)
[ ]
[+] BOOLEAN ListOnlyContains (LIST l, LIST lDomain)
	[ ] ANYTYPE aItem
	[+] for each aItem in l
		[+] if (ListFind (lDomain, aItem) == 0)
			[ ] return (FALSE)
	[ ] return (TRUE)
[ ]
[+] BOOLEAN ListMatch (LIST OF ANYTYPE l1, LIST OF ANYTYPE l2, INTEGER nCount optional)
	[ ] INTEGER nCount1 = ListCount (l1)
	[ ] INTEGER nCount2 = ListCount (l2)
	[ ]
	[+] if (nCount != NULL)
		[+] if ((nCount1 < nCount) || (nCount2 < nCount))
			[ ] return (FALSE)
	[+] else
		[+] if (nCount1 != nCount2)
			[ ] return (FALSE)
		[ ] nCount = nCount1
	[ ]
	[ ] INTEGER nIndex
	[+] for nIndex = 1 to nCount
		[+] if (l1[nIndex] != l2[nIndex])
			[ ] return (FALSE)
	[ ]
	[ ] return (TRUE)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										ValueMap
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type VALUEMAP is record
	[ ] ANYTYPE aValue
	[ ] STRING sMatch
[ ]
[+] BOOLEAN ValueMap_FindValue (LIST OF VALUEMAP lValueMap, ANYTYPE aValue, out STRING sMatch)
	[ ] VALUEMAP ValueMap
	[+] for each ValueMap in lValueMap
		[+] if (ValueMap.aValue == aValue)
			[ ] sMatch = ValueMap.sMatch
			[ ] return (TRUE)
	[ ] return (FALSE)
[ ]
[+] BOOLEAN ValueMap_MatchText (LIST OF VALUEMAP lValueMap, STRING sText, out ANYTYPE aValue)
	[ ] VALUEMAP ValueMap
	[+] for each ValueMap in lValueMap
		[+] if (MatchStr (ValueMap.sMatch, sText))
			[ ] aValue = ValueMap.aValue
			[ ] return (TRUE)
	[ ] return (FALSE)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										WaitFor Window Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] // type WINHANDLER is record
	[ ] // WINDOW wWindow
	[ ] // STRING sMethod
	[ ] // LIST OF ANYTYPE laArgs
[+] // type MSGHANDLER is record
	[ ] // WINDOW wMsg
	[ ] // WINDOW wWindow
	[ ] // STRING sMethod
	[ ] // LIST OF ANYTYPE laArgs
[ ] //
[+] // BOOLEAN WinHandler_Dispatch (LIST OF WINHANDLER lWinHandler null)
	[+] // if (lWinHandler == NULL)
		[ ] // return (FALSE)
	[ ] //
	[ ] // WINHANDLER WinHandler
	[+] // for each WinHandler in lWinHandler
		[+] // if (! WinHandler.wWindow.Exists())
			[ ] // continue
		[ ] //
		[+] // if (WinHandler.laArgs == NULL)
			[ ] // WinHandler.laArgs = {}
		[ ] //
		[ ] // WinHandler.wWindow.ArgListCall (WinHandler.sMethod, WinHandler.laArgs)
		[ ] // return (TRUE)
	[ ] //
	[ ] // return (FALSE)
[+] // BOOLEAN MsgHandler_Dispatch (LIST OF MSGHANDLER lMsgHandler null)
	[+] // if (lMsgHandler == NULL)
		[ ] // return (FALSE)
	[ ] //
	[ ] // MSGHANDLER MsgHandler
	[+] // for each MsgHandler in lMsgHandler
		[+] // if (! MsgHandler.wMsg.Exists())
			[ ] // continue
		[ ] //
		[+] // if (MsgHandler.laArgs == NULL)
			[ ] // MsgHandler.laArgs = {}
		[ ] //
		[ ] // MsgHandler.wWindow.ArgListCall (MsgHandler.sMethod, MsgHandler.laArgs)
		[ ] // return (TRUE)
	[ ] //
	[ ] // return (FALSE)
[ ] //
[+] // void WaitForWindow (WINDOW wWindow, LIST OF WINDOW lwContinue optional, NUMBER nTimeout optional)
	[+] // if (lwContinue == NULL)
		[ ] // lwContinue = {}
	[ ] //
	[+] // if (nTimeout == NULL)
		[ ] // nTimeout = Agent.GetOption (OPT_WINDOW_TIMEOUT)
	[ ] //
	[ ] // INTEGER iNumFound = 0
	[ ] //
	[+] // if (ListCount (lwContinue) == 0)
		[+] // if (wWindow.Exists (nTimeout))
			[ ] // iNumFound += 1
	[+] // else
		[ ] // HTIMER hTimer = TimerCreate ()
		[ ] // TimerStart (hTimer)
		[ ] //
		[+] // while (iNumFound < 2)
			[ ] // WINDOW wContinue
			[ ] //
			[ ] // TimerPause (hTimer)
			[ ] //
			[+] // for each wContinue in lwContinue
				[+] // if (wContinue.Exists())
					[ ] // wContinue.Continue ()
			[ ] //
			[ ] // TimerResume (hTimer)
			[ ] //
			[+] // if (wWindow.Exists (1))
				[ ] // iNumFound += 1
			[ ] //
			[+] // if (TimerValue (hTimer) > nTimeout)
				[ ] // break
		[ ] //
		[ ] // TimerStop (hTimer)
		[ ] // TimerDestroy (hTimer)
	[ ] //
	[+] // if (iNumFound == 0)
		[ ] // RES.AppError ("Window {wWindow} not found")
[+] // void WaitForWindowEx (WINDOW wWindow, LIST OF WINHANDLER lWinHandler optional, LIST OF MSGHANDLER lMsgHandler optional, NUMBER nTimeout optional)
	[+] // if (nTimeout == NULL)
		[ ] // nTimeout = Agent.GetOption (OPT_WINDOW_TIMEOUT)
	[ ] //
	[ ] // INTEGER iNumFound = 0
	[ ] //
	[ ] // HTIMER hTimer = TimerCreate ()
	[ ] // TimerStart (hTimer)
	[ ] //
	[+] // while (iNumFound < 2)
		[ ] // WINDOW wContinue
		[ ] //
		[ ] // TimerPause (hTimer)
		[ ] //
		[+] // if (! WinHandler_Dispatch (lWinHandler))
			[ ] // MsgHandler_Dispatch (lMsgHandler)
		[ ] //
		[ ] // TimerResume (hTimer)
		[ ] //
		[+] // if (wWindow.Exists (1))
			[ ] // iNumFound += 1
		[ ] //
		[+] // if (TimerValue (hTimer) > nTimeout)
			[ ] // break
	[ ] //
	[ ] // TimerStop (hTimer)
	[ ] // TimerDestroy (hTimer)
	[ ] //
	[+] // if (iNumFound == 0)
		[ ] // RES.AppError ("Window {wWindow} not found")
[+] // WINDOW WaitForWindowList (LIST OF WINDOW lwWait, NUMBER nTimeout optional)
	[+] // if (nTimeout == NULL)
		[ ] // nTimeout = Agent.GetOption (OPT_WINDOW_TIMEOUT)
	[ ] //
	[ ] // HTIMER hTimer = TimerCreate ()
	[ ] // TimerStart (hTimer)
	[ ] //
	[ ] // WINDOW wFound = NULL
	[ ] // INTEGER nNumWait = ListCount (lwWait)
	[ ] //
	[+] // while (TRUE)
		[ ] // INTEGER nIndex
		[ ] //
		[+] // for nIndex = 1 to nNumWait
			[ ] // WINDOW wWait = lwWait[nIndex]
			[ ] // REAL rExistTimeout = (nIndex == 1) ? 0.5 : 0
			[ ] //
			[+] // if (wWait.Exists (rExistTimeout))
				[ ] // wFound = wWait
				[ ] // break
		[ ] //
		[+] // if (wFound != NULL)
			[ ] // break
		[ ] //
		[+] // if (TimerValue (hTimer) > nTimeout)
			[ ] // break
	[ ] //
	[ ] // TimerStop (hTimer)
	[ ] // TimerDestroy (hTimer)
	[ ] //
	[+] // if (wFound == NULL)
		[ ] // RES.AppError ("Timeout expired waiting for {lwWait}")
	[ ] //
	[ ] // return (wFound)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //										State Handler Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type STATEHANDLER is record
	[ ] INTEGER nState
	[ ] STRING sFunc
	[ ] LIST OF ANYTYPE laArgs
[ ]
[+] BOOLEAN ExecuteStateHandler (STATEHANDLER StateHandler)
	[+] if (StateHandler.laArgs == NULL)
		[ ] StateHandler.laArgs = {}
	[ ]
	[ ] return (ArgListCall (StateHandler.sFunc, StateHandler.laArgs))
[ ]
[+] BOOLEAN ProcessStateHandlers (LIST OF STATEHANDLER lStateHandler null, integer nState)
	[+] if (lStateHandler == NULL)
		[ ] return (TRUE)
	[ ]
	[ ] INTEGER nIndex
	[+] for nIndex = 1 to ListCount (lStateHandler)
		[+] if (lStateHandler[nIndex].nState != nState)
			[ ] continue
		[ ]
		[+] if (! ExecuteStateHandler (lStateHandler[nIndex]))
			[ ] return (FALSE)
	[ ]
	[ ] return (TRUE)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										NAME-VALUE
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type NAMEVALUE is record
	[ ] STRING sName
	[ ] STRING sValue
[+] type NAMETOFIELD is record
	[ ] STRING sName
	[ ] STRING sField
[ ]
[+] BOOLEAN NameValue_Parse (out NAMEVALUE NameValue, STRING sNameValue)
	[ ] INTEGER nPos = StrPos ("=", sNameValue)
	[+] if (nPos == 0)
		[ ] return (FALSE)
	[ ]
	[ ] STRING sName = Trim (Left (sNameValue, nPos - 1))
	[ ] STRING sValue = Trim (SubStr (sNameValue, nPos + 1))
	[ ]
	[+] if (sName == "")
		[ ] return (FALSE)
	[ ]
	[ ] NameValue.sName  = sName
	[ ] NameValue.sValue = sValue
	[ ]
	[ ] return (TRUE)
[ ]
[+] BOOLEAN NameValueList_Find (LIST OF NAMEVALUE lNameValue, STRING sName, out STRING sValue)
	[ ] NAMEVALUE NameValue
	[+] for each NameValue in lNameValue
		[+] if (NameValue.sName == sName)
			[ ] sValue = NameValue.sValue
			[ ] return (TRUE)
	[ ] return (FALSE)
[ ]
[+] STRING NameValueList_GetValue (LIST OF NAMEVALUE lNameValue, STRING sName, STRING sDefault optional)
	[ ] NAMEVALUE NameValue
	[+] for each NameValue in lNameValue
		[+] if (NameValue.sName == sName)
			[ ] return (NameValue.sValue)
	[ ]
	[ ] return (sDefault)
[ ]
[+] void NameValueList_SetValue (inout LIST OF NAMEVALUE lNameValue, STRING sName, STRING sValue)
	[ ] NAMEVALUE NameValue
	[+] for each NameValue in lNameValue
		[+] if (NameValue.sName == sName)
			[ ] NameValue.sValue = sValue
			[ ] break
	[ ]
	[ ] ListAppend (lNameValue, {sName, sValue})
[ ]
[+] BOOLEAN NameValueList_BinarySearch (LIST OF NAMEVALUE lNameValue, STRING sName, out STRING sValue)
	[ ] INTEGER iLower = 1
	[ ] INTEGER iUpper = ListCount (lNameValue)
	[ ] INTEGER iMid
	[ ]
	[+] while (iLower <= iUpper)
		[ ] iMid = (iLower + iUpper) / 2
		[ ]
		[+] if (sName < lNameValue[iMid].sName)
			[ ] iUpper = iMid - 1
		[+] else if (sName > lNameValue[iMid].sName)
			[ ] iLower = iMid + 1
		[+] else
			[ ] sValue = lNameValue[iMid].sValue
			[ ] return (TRUE)
	[ ]
	[ ] return (FALSE)
[ ]
[+] BOOLEAN NameValueList_Parse (STRING sNameValueList null, STRING sDelim, out LIST OF NAMEVALUE lNameValue)
	[ ] lNameValue = {}
	[ ]
	[+] if ((sNameValueList == NULL) || (sNameValueList == ""))
		[ ] return (TRUE)
	[ ]
	[ ] STRING sNameValue
	[+] for each sNameValue in ParseStringList (sNameValueList, sDelim)
		[ ] NAMEVALUE NameValue
		[+] if (! NameValue_Parse (NameValue, sNameValue))
			[ ] return (FALSE)
		[ ] ListAppend (lNameValue, NameValue)
	[ ]
	[ ] return (TRUE)
[ ]
[+] void NameValueList_SetRecord (LIST OF NAMEVALUE lNameValue, LIST OF NAMETOFIELD lNameToField, inout ANYTYPE aRecord)
	[ ] aRecord = {}
	[ ] ListSort (lNameValue)
	[ ]
	[ ] NAMETOFIELD NameToField
	[+] for each NameToField in lNameToField
		[ ] STRING sValue
		[+] if (NameValueList_Find (lNameValue, NameToField.sName, sValue))
			[ ] aRecord.@(NameToField.sField) = sValue
		[+] else
			[ ] LogWarning ("'{NameToField.sName}' not found")
[ ]
[+] void NameValueList_Print (LIST OF NAMEVALUE lNameValue, STRING sHeader optional)
	[ ] INTEGER nIndent = 0
	[ ]
	[+] if (sHeader != NULL)
		[ ] RES.Print (sHeader)
		[ ] nIndent += 2
	[ ]
	[ ] INTEGER nMaxNameWidth = 0
	[ ]
	[ ] NAMEVALUE NameValue
	[+] for each NameValue in lNameValue
		[ ] INTEGER nNameWidth = Len (NameValue.sName)
		[+] if (nNameWidth > nMaxNameWidth)
			[ ] nMaxNameWidth = nNameWidth
	[ ]
	[+] for each NameValue in lNameValue
		[ ] RES.Print (Space (nIndent) + StrPadSpaces (NameValue.sName, nMaxNameWidth) + " = " + NameValue.sValue)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //  									Function Call Parsing
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type FUNCCALL is record
	[ ] STRING sName
	[ ] LIST OF STRING lsArgs
[ ]
[+] BOOLEAN FuncCall_Parse (STRING sCall, out FUNCCALL FuncCall)
	[ ] // Initialize the FUNCCALL record.
	[ ] FuncCall.sName    = ""
	[ ] FuncCall.lsArgs   = {}
	[ ]
	[ ] // Look for the left and right parentheses in the sCall variable.
	[ ] INTEGER iParenL = StrPos ("(", sCall)
	[ ] INTEGER iParenR = StrPos (")", sCall)
	[ ]
	[ ] // If neither exist, just assign the function name with no arguments and return TRUE.
	[+] if ((iParenL == 0) && (iParenR == 0))
		[ ] FuncCall.sName = Upper (Trim (sCall))
		[ ] return (true)
	[ ]
	[ ] // If one parentheses exists, but the other doesn't -- error.
	[+] if (iParenL == 0) || (iParenR == 0) || (iParenL > iParenR)
		[ ] return (FALSE)
	[ ]
	[ ] // Assign the function name.
	[ ] FuncCall.sName = Trim (Left (sCall, iParenL - 1))
	[ ]
	[ ] // If the function name is blank -- error.
	[+] if (FuncCall.sName == "")
		[ ] return (FALSE)
	[ ]
	[ ] // Assign the arguments passed in after the function call.
	[ ] STRING sArgs = Trim (SubStr (sCall, iParenL + 1, iParenR - iParenL - 1))
	[ ]
	[ ] // While there are more parameters, append them to the list of argument variables.
	[+] while (true)
		[ ] INTEGER iPos
		[ ] STRING sArg
		[ ] BOOLEAN bDone
		[ ]
		[ ] bDone = FALSE
		[ ] STRING sChar = Left (sArgs, 1)
		[ ]
		[+] if ((sChar == "'") || (sChar == '"'))
			[ ] sArgs[1] = " "
			[ ] iPos = StrPos (sChar, sArgs)
			[ ]
			[+] if (iPos == 0)
				[ ] return (FALSE)
			[ ]
			[ ] sArg = SubStr (sArgs, 2, iPos - 2)
			[ ] sArgs = LTrim (SubStr (sArgs, iPos + 1))
			[ ]
			[+] if (sArgs == "")
				[ ] bDone = TRUE
			[+] else
				[+] if (sArgs[1] != ",")
					[ ] return (FALSE)
				[ ] sArgs = SubStr (sArgs, 2)
		[+] else
			[ ] iPos = StrPos (",", sArgs)
			[ ]
			[+] if (iPos == 0)
				[ ] sArg = sArgs
				[ ] bDone = TRUE
			[+] else
				[ ] sArg = Left (sArgs, iPos - 1)
				[ ] sArgs = SubStr (sArgs, iPos + 1)
			[ ]
			[ ] sArg = Trim (sArg)
		[ ]
		[+] if ((Len (sArg) >= 2) && (Left (sArg, 1) == "'") && (Right (sArg, 1) == "'"))
			[ ] sArg = SubStr (sArg, 2, Len (sArg) - 2)
		[ ]
		[ ] ListAppend (FuncCall.lsArgs, sArg)
		[ ]
		[+] if (bDone)
			[ ] break
	[ ]
	[ ] return (true)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										Transform Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[+] type TRANSTYPE is enum
	[ ] TransType_Value
	[ ] TransType_Reference
[ ]
[+] type TRANSFUNC is record
	[ ] TRANSTYPE Type
	[ ] WINDOW wWin
	[ ] LIST OF ANYTYPE laArgs
[ ]
[+] type TRANSFLAGS is set
	[ ] TransFlags_Optional
	[ ] TransFlags_Modify
[ ]
[+] type TRANSINFO is record
	[ ] TRANSFLAGS Flags
	[ ]
	[ ] TRANSFUNC Parse
	[ ] TRANSFUNC Format
	[ ] TRANSFUNC Transform
[ ]
[+] void TransFunc_Execute (TRANSFUNC TransFunc null, inout ANYTYPE aVar null, ANYTYPE aValue null)
	[+] if (TransFunc == NULL)
		[ ] return
	[ ]
	[+] switch (TransFunc.Type)
		[+] case TransType_Value
			[ ] aVar = TransFunc.wWin.ArgListCall ("Transform", {aValue} + TransFunc.laArgs)
		[ ]
		[+] case TransType_Reference
			[+] switch (ListCount (TransFunc.laArgs))
				[+] case 0
					[ ] TransFunc.wWin.Transform (aVar, aValue)
				[+] case 1
					[ ] TransFunc.wWin.Transform (aVar, aValue, TransFunc.laArgs[1])
				[+] case 2
					[ ] TransFunc.wWin.Transform (aVar, aValue, TransFunc.laArgs[1], TransFunc.laArgs[2])
				[+] case 3
					[ ] TransFunc.wWin.Transform (aVar, aValue, TransFunc.laArgs[1], TransFunc.laArgs[2], TransFunc.laArgs[3])
				[+] case 4
					[ ] TransFunc.wWin.Transform (aVar, aValue, TransFunc.laArgs[1], TransFunc.laArgs[2], TransFunc.laArgs[3], TransFunc.laArgs[4])
				[+] default
					[ ] RES.AppError ("Transform by reference functions are limited to 4 arguments")
[ ]
[+] void TransFunc_Parse (inout TRANSFUNC TransFunc null, STRING sTrans null, STRING sPrefix optional)
	[ ] TransFunc = NULL
	[ ]
	[ ] TRANSTYPE TransType = TransType_Value
	[ ] WINDOW wWin = NULL
	[ ] LIST OF ANYTYPE laArgs = {}
	[ ]
	[+] if ((sTrans == NULL) || (sTrans == ""))
		[ ] return
	[ ]
	[ ] FUNCCALL FuncCall
	[ ]
	[+] if (! FuncCall_Parse (sTrans, FuncCall))
		[ ] RES.AppError ("Transform '{sTrans}' is not valid")
	[ ]
	[+] if (sPrefix != NULL)
		[ ] FuncCall.sName = sPrefix + FuncCall.sName
	[ ]
	[+] do
		[ ] STRING sWindowName = "Transform_" + Upper (FuncCall.sName)
		[ ] wWin = @sWindowName
	[+] except
		[+] if (sPrefix != NULL)
			[ ] return
		[ ]
		[ ] RES.AppError ("Transform {FuncCall.sName} is not defined")
	[ ]
	[ ] INTEGER nNumArgs
	[ ]
	[+] do
		[ ] nNumArgs = ListCount (wWin.lArgType)
	[+] except
		[ ] nNumArgs = 0
	[ ]
	[ ] INTEGER nCallArgs = ListCount (FuncCall.lsArgs)
	[+] if (nCallArgs > nNumArgs)
		[ ] RES.AppError ("Transform {FuncCall.sName} expects {nNumArgs} argument(s)")
	[ ]
	[ ] INTEGER i
	[+] for i = 1 to nNumArgs
		[+] do
			[+] if (i <= nCallArgs)
				[ ] ListAppend (laArgs, ConvertStrToType (FuncCall.lsArgs[i], wWin.lArgType[i]))
			[+] else
				[ ] ListAppend (laArgs, NULL)
		[+] except
			[ ] RES.AppError ("Argument {i} to transform {FuncCall.sName} is not valid -- {ExceptError()}")
	[ ]
	[+] do
		[+] if (TransFlags_Modify in wWin.Flags)
			[ ] TransType = TransType_Reference
	[ ] except
	[ ]
	[ ] TransFunc = {TransType, wWin, laArgs}
[ ]
[+] void TransInfo_Init (inout TRANSINFO TransInfo null)
	[ ] TransInfo = {}
	[ ] TransInfo.Flags = {}
[ ]
[+] void TransInfo_ParseFunc (inout TRANSINFO TransInfo null, STRING sTrans null)
	[+] if (TransInfo == NULL)
		[ ] TransInfo_Init (TransInfo)
	[ ]
	[ ] TransFunc_Parse (TransInfo.Transform, sTrans)
[ ]
[+] void TransInfo_ParseType (inout TRANSINFO TransInfo null, STRING sTrans null)
	[+] if (TransInfo == NULL)
		[ ] TransInfo_Init (TransInfo)
	[ ]
	[ ] TransFunc_Parse (TransInfo.Parse,  sTrans, "Parse")
	[ ] TransFunc_Parse (TransInfo.Format, sTrans, "Format")
	[ ]
	[+] if ((TransInfo.Parse == NULL) && (TransInfo.Format == NULL) && (sTrans != NULL))
		[ ] RES.AppError ("Transform type {sTrans} not defined")
[ ]
[+] void SetValueStr (inout ANYTYPE aVar null, STRING sValue null, TRANSINFO TransInfo optional)
	[ ] STRING sCalls = ""
	[ ]
	[+] if (TransInfo != NULL)
		[+] if (TransInfo.Parse != NULL)
			[ ] sCalls += "P"
		[+] if (TransInfo.Transform != NULL)
			[ ] sCalls += "T"
	[ ]
	[+] switch (sCalls)
		[+] case ""
			[ ] aVar = ConvertStrToType (sValue, GetTypeOf (aVar))
		[+] case "P"
			[ ] TransFunc_Execute (TransInfo.Parse, aVar, sValue)
		[+] case "T"
			[ ] TransFunc_Execute (TransInfo.Transform, aVar, sValue)
		[+] case "PT"
			[ ] TransFunc_Execute (TransInfo.Parse, aVar, sValue)
			[ ] TransFunc_Execute (TransInfo.Transform, aVar, aVar)
	[ ]
	[+] if (((! IsSet (aVar)) || (aVar == NULL)) && (TransInfo != NULL) && (TransFlags_Optional in TransInfo.Flags))
		[ ] DATATYPE VarType = GetTypeOf (aVar)
		[+] select
			[+] case (VarType == STRING)
				[ ] aVar = ""
			[+] case IsSetType (VarType)
				[ ] aVar = {}
[ ]
[+] STRING FormatValue (ANYTYPE aValue, TRANSINFO TransInfo optional)
	[ ] STRING sReturn
	[ ]
	[+] if ((TransInfo != NULL) && (TransInfo.Format != NULL))
		[ ] TransFunc_Execute (TransInfo.Format, sReturn, aValue)
	[+] else
		[ ] sReturn = [STRING] aValue
	[ ]
	[ ] return (sReturn)
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										Record Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[+] type MEMBERFLAGS is set
	[ ] Required
[ ]
[+] type MEMBERINFO is record
	[ ] STRING sMember
	[ ] MEMBERFLAGS Flags
[ ]
[+] void Record_Initialize (inout ANYTYPE aRecord null)
	[+] if (aRecord == NULL)
		[ ] aRecord = {}
	[ ]
	[ ] LIST OF STRING lsFields
	[+] do
		[ ] lsFields = FieldsOfRecord (TypeOf (aRecord))
	[+] except
		[ ] lsFields = {}
	[ ]
	[ ] STRING sField
	[+] for each sField in lsFields
		[ ] DATATYPE Type = GetTypeOf (aRecord.@sField)
		[ ] aRecord.@sField = NULL
[ ]
[+] ANYTYPE Record_GetMember (ANYTYPE aRecord, STRING sMember)
	[ ] INTEGER nPos = StrPos (".", sMember)
	[ ]
	[+] if (nPos > 0)
		[ ] STRING sPart1 = Left (sMember, nPos - 1)
		[ ] STRING sPart2 = SubStr (sMember, nPos + 1)
		[ ]
		[ ] return (Record_GetMember (aRecord.@sPart1, sPart2))
	[+] else
		[+] do
			[ ] return (aRecord.@sMember)
		[+] except
			[ ] //RES.ExceptLog()
			[ ] RES.AppError ("Unable to get value of {sMember}")
	[ ]
	[ ] return (NULL)
[ ]
[+] void Record_SetMember (inout ANYTYPE aRecord, STRING sMember, ANYTYPE aValue null)
	[ ] INTEGER nPos = StrPos (".", sMember)
	[ ]
	[+] if (nPos > 0)
		[ ] STRING sPart1 = Left (sMember, nPos - 1)
		[ ] STRING sPart2 = SubStr (sMember, nPos + 1)
		[ ]
		[ ] Record_SetMember (aRecord.@sPart1, sPart2, aValue)
	[+] else
		[+] do
			[ ] aRecord.@sMember = aValue
		[+] except
			[ ] RES.AppError ("Unable to set value of {sMember}")
[ ]
[+] void Record_CopyMember (ANYTYPE aSrcRecord, inout ANYTYPE aDstRecord, STRING sMember, STRING sContext optional, MEMBERFLAGS Flags optional)
	[+] if (sContext == NULL)
		[ ] sContext = ""
	[ ]
	[ ] INTEGER nPos = StrPos (".", sMember)
	[ ]
	[ ] STRING sPart1
	[ ] STRING sPart2
	[ ]
	[+] if (nPos > 0)
		[ ] sPart1 = Left (sMember, nPos - 1)
		[ ] sPart2 = SubStr (sMember, nPos + 1)
	[+] else
		[ ] sPart1 = sMember
		[ ] sPart2 = NULL
	[ ]
	[ ] BOOLEAN bList = (Right (sPart1, 2) == "[]")
	[ ]
	[ ] INTEGER nNumValues
	[ ] INTEGER i
	[ ]
	[+] if (bList)
		[ ] sPart1 = Left (sPart1, Len (sPart1) - 2)
		[ ]
		[+] do
			[ ] nNumValues = ListCount (aSrcRecord.@sPart1)
			[ ] ListExtend (aDstRecord.@sPart1, nNumValues)
		[+] except
			[ ] //ExceptLog()
			[+] if ((Flags != NULL) && (Required in Flags))
				[ ] RES.AppError ("Unable to set {sContext}{sMember} -- {ExceptError()}")
			[ ] return
	[ ]
	[+] if (sPart2 != NULL)
		[+] if (bList)
			[+] for i = 1 to nNumValues
				[ ] Record_CopyMember (aSrcRecord.@sPart1[i], aDstRecord.@sPart1[i], sPart2, "{sPart1}[{i}].", Flags)
		[+] else
			[ ] Record_CopyMember (aSrcRecord.@sPart1, aDstRecord.@sPart1, sPart2, "{sPart1}.", Flags)
	[+] else
		[+] do
			[+] if (bList)
				[+] for i = 1 to nNumValues
					[ ] aDstRecord.@sPart1[i] = aSrcRecord.@sPart1[i]
			[+] else
				[ ] aDstRecord.@sPart1 = aSrcRecord.@sPart1
		[+] except
			[ ] //ExceptLog()
			[+] if ((Flags != NULL) && (Required in Flags))
				[ ] RES.AppError ("Unable to set {sContext}{sMember} -- {ExceptError()}")
[ ]
[+] void Record_CopyMembers (ANYTYPE aSrcRecord, inout ANYTYPE aDstRecord, LIST OF MEMBERINFO lMemberInfo)
	[ ] MEMBERINFO MemberInfo
	[+] for each MemberInfo in lMemberInfo
		[ ] Record_CopyMember (aSrcRecord, aDstRecord, MemberInfo.sMember, NULL, MemberInfo.Flags)
[ ]
[+] void Record_AppendToList (ANYTYPE aSrcRecord, inout LIST OF ANYTYPE laDstList, LIST OF MEMBERINFO lMemberInfo)
	[ ] ListAppend (laDstList, {})
	[ ] INTEGER nCount = ListCount (laDstList)
	[ ] Record_CopyMembers (aSrcRecord, laDstList[nCount], lMemberInfo)
[ ]
[+] void Record_CopyList (LIST OF ANYTYPE laSrcList null, inout LIST OF ANYTYPE laDstList null, LIST OF MEMBERINFO lMemberInfo)
	[+] if (laSrcList == NULL)
		[ ] laDstList = NULL
		[ ] return
	[ ]
	[ ] INTEGER nCount = ListCount (laSrcList)
	[ ] INTEGER nIndex
	[ ]
	[ ] laDstList = {}
	[ ]
	[+] for nIndex = 1 to nCount
		[ ] ListAppend (laDstList, {})
		[ ] Record_CopyMembers (laSrcList[nIndex], laDstList[nIndex], lMemberInfo)
[ ]
[+] void Record_SetValueStr (inout ANYTYPE aRecord null, STRING sMember, STRING sValue null, TRANSINFO TransInfo optional, STRING sContext optional)
	[+] if (aRecord == NULL)
		[ ] Record_Initialize (aRecord)
	[ ]
	[+] if (sContext == NULL)
		[ ] sContext = ""
	[ ]
	[ ] /*** PARSE THE MEMBER ***/
	[ ]
	[ ] INTEGER nPos = StrPos (".", sMember)
	[ ]
	[ ] STRING sPart1
	[ ] STRING sPart2
	[ ]
	[+] if (nPos > 0)
		[ ] sPart1 = Left (sMember, nPos - 1)
		[ ] sPart2 = SubStr (sMember, nPos + 1)
	[+] else
		[ ] sPart1 = sMember
		[ ] sPart2 = NULL
	[ ]
	[ ] /*** PROCESS MEMBER LISTS (OLD STYLE) ***/
	[ ]
	[+] if (Right (sPart1, 2) == "[]")
		[ ] LIST OF STRING lsValues
		[ ] INTEGER nNumValues
		[ ] INTEGER i
		[ ]
		[ ] sPart1 = Left (sPart1, Len (sPart1) - 2)
		[ ]
		[ ] lsValues = ParseStringList (sValue, EXCEL_LIST_DELIM)
		[ ] nNumValues = ListCount (lsValues)
		[ ]
		[ ] ListExtend (aRecord.@sPart1, nNumValues)
		[ ]
		[+] if (sPart2 != NULL)
			[+] for i = 1 to nNumValues
				[ ] Record_SetValueStr (aRecord.@sPart1[i], sPart2, lsValues[i], TransInfo, "{sPart1}[{i}].")
		[+] else
			[+] do
				[+] for i = 1 to nNumValues
					[ ] SetValueStr (aRecord.@sPart1[i], lsValues[i], TransInfo)
			[+] except
				[ ] RES.AppError ("Unable to set {sContext}{sPart1}[{i}] -- {ExceptError()}")
		[ ]
		[ ] return
	[ ]
	[ ] /*** PROCESS MEMBER LISTS (NEW STYLE) ***/
	[ ]
	[ ] INTEGER nFind = ListFind ({"[*]","[-]"}, Right (sPart1, 3))
	[ ]
	[+] if (nFind > 0)
		[ ] BOOLEAN bGroup = (nFind == 1)
		[ ] sPart1 = Left (sPart1, Len (sPart1) - 3)
		[ ]
		[+] if (aRecord.@sPart1 == NULL)
			[ ] aRecord.@sPart1 = {}
		[ ]
		[ ] INTEGER nIndex = ListCount (aRecord.@sPart1)
		[ ] BOOLEAN bHasValue = (sValue != NULL) && (sValue != "")
		[ ]
		[+] if (bGroup)
			[+] if (bHasValue)
				[ ] ListAppend (aRecord.@sPart1, {})
				[ ] nIndex += 1
			[+] else
				[ ] return
		[+] else
			[+] if ((nIndex == 0) || (! bHasValue))
				[ ] return
		[ ]
		[+] if (sPart1 != NULL)
			[ ] Record_SetValueStr (aRecord.@(sPart1)[nIndex], sPart2, sValue, TransInfo, "{sPart1}[{nIndex}].")
		[+] else
			[+] do
				[ ] SetValueStr (aRecord.@sPart1[nIndex], sValue, TransInfo)
			[+] except
				[ ] RES.AppError ("Unable to set {sContext}{sPart1}[{nIndex}] -- {ExceptError()}")
		[ ]
		[ ] return
	[ ]
	[ ] /*** PROCESS MEMBER (NOT A LIST) ***/
	[ ]
	[+] if (sPart2 != NULL)
		[ ] Record_SetValueStr (aRecord.@sPart1, sPart2, sValue, TransInfo, "{sPart1}.")
	[+] else
		[+] do
			[ ] SetValueStr (aRecord.@sPart1, sValue, TransInfo)
		[+] except
			[ ] //RES.ExceptLog ()
			[ ] RES.AppError ("Unable to set {sContext}{sMember} -- {ExceptError()}")
[ ]
[+] void Record_SetProperties (inout ANYTYPE aRecord null, EXCELMAP ExcelMap, STRING sProperties null)
	[ ] LIST OF STRING lsPropLines = ParseStringList (sProperties, EXCEL_LIST_DELIM)
	[ ]
	[ ] INTEGER nNumProps = ListCount (ExcelMap.lPropMap)
	[ ] INTEGER nNumLines = ListCount (lsPropLines)
	[ ]
	[+] if (nNumLines == 0)
		[ ] nNumLines = 1
		[ ] lsPropLines = {""}
	[ ]
	[ ] STRING aasPropValues[nNumProps][nNumLines]
	[ ]
	[ ] INTEGER nProp
	[ ] INTEGER nLine
	[+] for nProp = 1 to nNumProps
		[+] for nLine = 1 to nNumLines
			[ ] aasPropValues[nProp][nLine] = NULL
	[ ]
	[+] for nLine = 1 to nNumLines
		[ ] STRING sLine = lsPropLines[nLine]
		[ ]
		[ ] LIST OF NAMEVALUE lNameValue
		[+] if (! NameValueList_Parse (sLine, EXCEL_PROP_DELIM, lNameValue))
			[ ] RES.AppError ("Unable to process column [{ExcelMap.sColumnName}] -- Property list not valid")
		[ ]
		[ ] NAMEVALUE NameValue
		[+] for each NameValue in lNameValue
			[ ] nProp = ExcelMap_FindByName (ExcelMap.lPropMap, NameValue.sName)
			[+] if (nProp == 0)
				[ ] RES.AppError ("Unable to process column [{ExcelMap.sColumnName}] -- '{NameValue.sName}' is not a known property")
			[ ]
			[ ] aasPropValues[nProp][nLine] = NameValue.sValue
	[ ]
	[+] for nProp = 1 to nNumProps
		[ ] EXCELMAP PropMap = ExcelMap.lPropMap[nProp]
		[ ]
		[ ] STRING sValue = NULL
		[ ] INTEGER nNonNull = 0
		[ ]
		[+] for nLine = 1 to nNumLines
			[+] if (sValue == NULL)
				[ ] sValue = ""
			[+] else
				[ ] sValue += EXCEL_LIST_DELIM
			[ ]
			[+] if (aasPropValues[nProp][nLine] != NULL)
				[ ] sValue += aasPropValues[nProp][nLine]
				[ ] nNonNull += 1
		[ ]
		[+] if (nNonNull > 0)
			[ ] Record_SetValueStr (aRecord, PropMap.sMember, sValue, PropMap.TransInfo)
	[ ]
[ ]
