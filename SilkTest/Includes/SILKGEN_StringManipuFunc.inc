[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_StringManipuFunc.inc
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
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] // 										String Functions
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ]
[ ] // function:  	FieldsToList (sString, sDelim, [bLogWarning])
[ ] // Action:     	Returns the fields in a delimited string as a list of strings.
[ ] // Syntax:		lsSegments = FieldsToList ( sString,  sDelim,  bLogWarning [optional])
[ ] // parameter: 	sString: The delimited string to return the segments from. STRING.
[ ] // parameter: 	sDelim: The character(s) to use to separate fields in sString. STRING.
[ ] // parameter: 	bLogWarning: Log a warning if sDelim not found in sString. Default is FALSE (optional). INTEGER.
[ ] // returns:   	lsSegments: The returned segments. LIST OF STRING.
[+] LIST OF STRING FieldsToList (STRING sString, STRING sDelim, BOOLEAN bLogWarning optional)
	[+] do
		[ ]
		[ ] LIST OF STRING lsStrings
		[ ] STRING sOne
		[ ]
		[ ] // set bLogWarning to default value of FALSE if not specified
		[+] if IsNull (bLogWarning)
			[ ] bLogWarning = FALSE
		[ ]
		[ ] // Log a warning if the Delimiter is not found in the target
		[+] if StrPos (sDelim, sString) == 0
			[+] if bLogWarning
				[ ] LogWarning ("***Warning: Delimiter '{sDelim}' was not found in target string '{sString}' [FieldsToList]")
			[ ] return ({sString})
		[ ]
		[ ] // Parse the string as many times as the delimiter is found
		[+] while StrPos (sDelim,sString) != 0
			[ ] sOne = GetField (sString, sDelim, 1)	// Get (next) string
			[ ] ListAppend (lsStrings, sOne)					// append it to list
			[ ]
			[ ] // replace the string, as well as the delimiter (which may be > 1 char)
			[ ] sString = Stuff (sString, 1, StrPos (sDelim,sString) + Len (sDelim) - 1, "")
		[ ]
		[+] // Append the string that is left with no delimiters, unless it's empty
			[ ] // which would mean the delimiter was at the end of the target string
		[+] if sString != ""
			[ ] ListAppend (lsStrings, sString)
		[ ]
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: FieldsToList in testcase: {GetTestCaseName()}	success")
		[ ] return (lsStrings)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: FieldsToList in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ] // function:  	ConvertPathTo8CharFormat (sPath)
[ ] // Action:     	Converts a path to 8 char limit mode.
[ ] // Syntax:		sConvertedPath = ConvertPathTo8CharFormat(sPath)
[ ] // parameter: 	sPath: The original path. STRING.
[ ] // returns:   	sConvertedPath: The path converted to 8 char parts. STRING.
[+] STRING ConvertPathTo8CharFormat(STRING sPath)
	[+] do
		[ ]
		[ ] STRING			sPart, sNewPath
		[ ] LIST OF STRING  lsPathParts
		[ ] INTEGER			iLoop
		[ ]
		[ ] //Convert path to 8 Character directory format
		[ ] lsPathParts = FieldsToList (sPath, "\")
		[ ]
		[ ] iLoop = 1
		[ ] sNewPath = ""
		[+] for each sPart in lsPathParts
			[+] if Len(sPart) > 8
				[ ] sPart = Left (sPart,6)
				[ ] sPart = sPart + "~1"
			[+] if iLoop != 1
				[ ] sNewPath = sNewPath + "\" + sPart
			[+] else
				[ ] sNewPath = sNewPath + sPart
			[ ] iLoop++
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ConvertPathTo8CharFormat in testcase: {GetTestCaseName()}	success")
		[ ] return (sNewPath)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ConvertPathTo8CharFormat in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ] // function:  	GetFieldReverse (sString, sDelim, iField)
[ ] // Action:    	Returns a segment (field) of a string, working backwards from the end of the string.
[ ] // Syntax:		sSegment = GetFieldReverse ( sString,  sDelim,  iField)
[ ] // parameter: 	sString: The string to return a segment from. STRING.
[ ] // parameter: 	sDelim: The character(s) to use to separate fields in sString. STRING.
[ ] // parameter: 	iField: The occurence of the field to return. INTEGER.
[ ] // returns:   	sSegment: The returned segment. STRING.
[+] STRING GetFieldReverse (STRING sString, STRING sDelim, INTEGER iField)
	[+] do
		[ ]
		[ ] // convert the delimited string to a list of strings
		[ ] LIST OF STRING lsStrings = FieldsToList (sString, sDelim)
		[ ]
		[ ] // if the delimiter is at the end of the string, add an empty string to the list
		[+] if Right (sString, Len(sDelim)) == sDelim
			[ ] ListAppend (lsStrings, "")
		[ ]
		[ ] // return the proper string starting from the end of the list
		[+] if (ListCount (lsStrings) + 1 - iField) <= 0
			[ ] return ("")
		[+] else
			[ ] return (lsStrings [ListCount (lsStrings) + 1 - iField])
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: GetFieldReverse in testcase: {GetTestCaseName()}	success")
		[ ]
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetFieldReverse in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ] // function:  	FormatPrecision (sToFormat, iDecimalPlaces)
[ ] // Action:     	Returns a string containing a real number with the specified precision.
[ ] // Syntax:		sFormatted = FormatPrecision ( sToFormat,  iDecimalPlaces)
[ ] // parameter: 	sToFormat: The real number in string form. STRING.
[ ] // parameter: 	iDecimalPlaces: The number of decimal points precision desired. INTEGER.
[ ] // returns:   	sFormatted: The formatted string. STRING.
[+] STRING FormatPrecision (STRING sToFormat, INTEGER iDecimalPlaces)
	[+] do
		[ ] // Get the location of the decimal point
		[ ] INTEGER		iDecimalPointLocation = StrPos (".", sToFormat)
		[ ] INTEGER 	iLength
		[ ] NUMBER		nToRound
		[ ] STRING 		sDecimalPortion = GetField (sToFormat,".",2)
		[ ] STRING 		sIntegerPortion = GetField (sToFormat,".",1)
		[ ] STRING 		sRounded
		[ ]
		[ ] // check if it's already got the correct precision
		[+] if Len (sDecimalPortion) == iDecimalPlaces
			[ ] return (sToFormat)
		[ ]
		[ ] // add 0s if number has less than desired precision
		[+] if Len (sDecimalPortion) < iDecimalPlaces
			[+] while Len (sDecimalPortion) < iDecimalPlaces
				[ ] sDecimalPortion = sDecimalPortion + "0"
			[ ] return (sIntegerPortion + "." + sDecimalPortion)
		[ ]
		[ ] // if 0 precision, return rounded integer portion of number
		[+] if iDecimalPlaces == 0
			[ ] return ([STRING]Round(Val(sToFormat)))
		[ ]
		[ ] // Take the decimal portion of the number and insert a '.' after the number of places desired
		[ ] nToRound = Val (Stuff (sDecimalPortion,iDecimalPlaces+1, 0, "."))
		[ ] iLength = Len (GetField ([STRING]nToRound, ".", 1))
		[ ]
		[ ] // Now round the resulting number so that we know what the effect of the digits after the '.' is
		[ ] sRounded = [STRING](Round (nToRound))
		[ ]
		[+] if Len (sRounded) > iLength
			[ ] sIntegerPortion = [STRING](Val(sIntegerPortion) + 1)
			[ ] sRounded = SubStr (sRounded, 2)
		[ ]
		[ ] // stuff 0s if needed
		[+] while Len (sRounded) < iDecimalPlaces
			[ ] sRounded = "0" + sRounded
		[ ]
		[ ] // otherwise chop off the string (now rounded)
		[+] if Len (sRounded) > iDecimalPlaces
			[ ] sRounded = SubStr (sRounded, 1, iDecimalPlaces)
		[ ]
		[+] // return the resultant string
			[ ] ListAppend(laLogDetails, "Call to function: IE_CloseAllBrowsers in testcase: {GetTestCaseName()}	success")
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: FormatPrecision in testcase: {GetTestCaseName()}	success")
		[ ] return (sIntegerPortion + "." + sRounded)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: FormatPrecision in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ] // function:  	Round (nToRound)
[ ] // Action:     	Rounds a number to the nearest integer.
[ ] // Syntax:		iRound = Round (nToRound)
[ ] // parameter: 	nToRound: The number to round. NUMBER.
[ ] // returns:   	iRound: The nearest integer to the number. INTEGER.
[+] INTEGER Round (NUMBER nToRound)
	[+] do
		[ ]
		[ ] // Get the base integer
		[ ] INTEGER iRounded = [INTEGER]nToRound
		[ ]
		[ ] // Get the fraction
		[ ] REAL rFraction = nToRound % 1.00
		[ ]
		[+] if rFraction >= .50
			[ ] iRounded = iRounded + 1
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: Round in testcase: {GetTestCaseName()}	success")
		[ ] return iRounded
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: Round in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return 0
	[ ]
[ ]
[ ]
[ ] // function:  	RoundDown (nToRound)
[ ] // Action:     	Rounds a number to its integer component.
[ ] // Syntax:		iRound = RoundDown (nToRound)
[ ] // parameter: 	nToRound: The number to round. NUMBER.
[ ] // returns:   	iRound: The integer portion of the real number. INTEGER.
[ ]
[+] INTEGER RoundDown (NUMBER nToRound)
	[+] do
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: RoundDown in testcase: {GetTestCaseName()}	success")
		[ ] return ([INTEGER]nToRound)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: RoundDown in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ] // Function:	StrLen function
[ ] // Action:		StrLen returns the number of characters in sString. If sString is an empty string (""), StrLen returns 0.
[ ] // Syntax:		iLength = StrLen (STRING sStr null)
[ ] // Parameter:	sStr: [null]. The string whose length to return. STRING.
[ ] // Returns:		Returns the length of a string [iLength]. INTEGER.
[+] INTEGER StrLen (STRING sStr null)
	[+] do
		[ ] ListAppend(laLogDetails, "Call to function: StrLen in testcase: {GetTestCaseName()}	success")
		[ ] return ((sStr == NULL) ? NULL : Len (sStr))
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrLen in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return 0
	[ ]
[ ]
[ ]
[ ] // Function:	StrTrim finction
[ ] // Action:		Strips leading and trailing whitespace from a string.
[ ] // Syntax:		sStripped = Trim (sToStrip)
[ ] // Parameter:	sStr: [null] The string to strip. STRING.
[ ] // Returns:		Trim removes leading and trailing whitespace from a string and returns the rest of the string [sStripped]. STRING.
[+] STRING StrTrim (STRING sStr null)
	[+] do
		[ ] ListAppend(laLogDetails, "Call to function: StrTrim in testcase: {GetTestCaseName()}	success")
		[ ] return ((sStr == NULL) ? sStr : Trim (sStr))
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrTrim in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrHasValue function
[ ] // Action:		Checks whether the specified string has any value or not
[ ] // Syntax:		bSttHas = StrHasValue (STRING sStr null)
[ ] // Parameter:	sStr: [null]. The string to be checked. STRING.
[ ] // Returns:		Returns TRUE id the specified string is not equal to NULL or "" else returns FALSE. BOOLEAN.
[+] BOOLEAN StrHasValue (STRING sStr null)
	[+] do
		[ ] ListAppend(laLogDetails, "Call to function: StrHasValue in testcase: {GetTestCaseName()}	success")
		[ ] return ((sStr != NULL) && (sStr != ""))
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrHasValue in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return FALSE
	[ ]
[ ]
[ ]
[ ] // Function:	StrPadZeroes function
[ ] // Action:		Pads zeroes at beginning of the string
[ ] // Syntax:		sNewString = StrPadZeroes (STRING sStr null, INTEGER nWidth)
[ ] // Parameter:	sStr: [null]. The string to be padded with leading zeroes. STRING.
[ ] // Parameter:	nWidth: The final width of the string including the leading zeroes. INTEGER.
[ ] // Returns:		Returns the string [sNewString] with the leading zeroes. STRING.
[+] STRING StrPadZeroes (STRING sStr null, INTEGER nWidth)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ]
		[ ] INTEGER nLen = Len (sStr)
		[+] if (nLen < nWidth)
			[ ] sStr = Replicate ("0", nWidth - nLen) + sStr
		[ ] ListAppend(laLogDetails, "Call to function: StrPadZeroes in testcase: {GetTestCaseName()}	success")
		[ ] return (sStr)
	[+] except
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrPadZeroes in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
[ ]
[ ]
[ ] // Function:	StrPadSpaces function
[ ] // Action:		Pads trailing whitespace characters at end of the string
[ ] // Syntax:		sNewString = StrPadSpaces (STRING sStr null, INTEGER nWidth)
[ ] // Parameter:	sStr: [null]. The string to be padded with trailing whitespace characters. STRING.
[ ] // Parameter:	nWidth: The final width of the string including the trailing whitespace characters. INTEGER.
[ ] // Returns:		Returns the string [sNewString] with the trailing whitespace characters. STRING.
[+] STRING StrPadSpaces (STRING sStr null, INTEGER nWidth)
	[+] do
			[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ]
		[ ] INTEGER nLen = Len (sStr)
		[+] if (nLen < nWidth)
			[ ] sStr =sStr +  Replicate (" ", nWidth - nLen)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: StrPadSpaces in testcase: {GetTestCaseName()}	success")
		[ ] return (sStr)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrPadSpaces in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrStripDecimalLeft function
[ ] // Action:		Stripts the string before the the decimal character.
[ ] // Syntax:		sNewString = StrStripDecimalLeft (STRING sStr null)
[ ] // Parameter:	sStr: [null]. The string to be striped before the decimal character. STRING.
[ ] // Returns:		Returns the new string [sNewString] before the decimal character if it found, else returns the original string. STRING.
[+] STRING StrStripDecimalLeft (STRING sStr null)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ]
		[ ] INTEGER nDecimal = StrPos (".", sStr)
		[+] if (nDecimal > 0)
			[ ] sStr = Left (sStr, nDecimal - 1)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: StrStripDecimalLeft in testcase: {GetTestCaseName()}	success")
		[ ] return (sStr)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrStripDecimalLeft in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrStripDecimalRight function
[ ] // Action:		Stripts the string after the the decimal character.
[ ] // Syntax:		sNewString = StrStripDecimalRight (STRING sStr null)
[ ] // Parameter:	sStr: [null]. The string to be striped after the decimal character. STRING.
[ ] // Returns:		Returns the new string [sNewString] after the decimal charactor if it found, else returns the original string . STRING.
[+] STRING StrStripDecimalRight (STRING sStr null)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ]
		[ ] INTEGER nDecimal = StrPos (".", sStr)
		[+] if (nDecimal > 0)
			[ ] sStr = SubStr(sStr, nDecimal + 1)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: StrStripDecimalRight in testcase: {GetTestCaseName()}	success")
		[ ] return (sStr)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrStripDecimalRight in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrGetLeftOfSpecialChar function
[ ] // Action:		Returns the string before a particular character(s).
[ ] // Syntax:		sNewString = StrGetLeftOfSpecialChar (STRING sStr null,  STRING sSplChar)
[ ] // Parameter:	sStr: [null]. The string to be striped before a particular character(s). STRING.
[ ] // Parameter:	sSplChar: The special character to be searched in the original string [sStr]. STRING.
[ ] // Returns:		Returns the new string [sNewString] before a particular character(s) if it found, else returns an empty string (""). STRING.
[+] STRING StrGetLeftOfSpecialChar (STRING sStr null,  STRING sSplChar)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ]
		[ ] INTEGER nDecimal = StrPos ("{sSplChar}", sStr)
		[+] if (nDecimal > 0)
			[ ] sStr = Left (sStr, nDecimal - 1)
			[ ]
			[ ] ListAppend(laLogDetails, "Call to function: StrGetLeftOfSpecialChar in testcase: {GetTestCaseName()}	success")
			[ ] return (sStr)
		[+] else
			[ ] ListAppend(laLogDetails, "Call to function: StrGetLeftOfSpecialChar in testcase: {GetTestCaseName()}	success")
			[ ] return ""
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrGetLeftOfSpecialChar in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrGetRightOfSpecialChar function
[ ] // Action:		Returns the string after a particular character(s).
[ ] // Syntax:		sNewString = StrGetRightOfSpecialChar (STRING sStr null,  STRING sSplChar)
[ ] // Parameter:	sStr: [null]. The string to be striped after a particular character(s). STRING.
[ ] // Parameter:	sSplChar: The special character to be searched in the original string [sStr]. STRING.
[ ] // Returns:		Returns the new string [sNewString] after a particular character(s) if it found, else returns an empty string (""). STRING.
[+] STRING StrGetRightOfSpecialChar (STRING sStr null, STRING sSplChar)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ] INTEGER nDecimal = StrPos ("{sSplChar}", sStr)
		[+] if (nDecimal > 0)
			[ ] sStr = Right (sStr, Len(sStr) - nDecimal - Len(sSplChar) + 1 )
			[ ] ListAppend(laLogDetails, "Call to function: StrGetRightOfSpecialChar in testcase: {GetTestCaseName()}	success")
			[ ] return (sStr)
		[+] else
			[ ] ListAppend(laLogDetails, "Call to function: StrGetRightOfSpecialChar in testcase: {GetTestCaseName()}	success")
			[ ] return ""
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrGetRightOfSpecialChar in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrStripOutAnyChar function
[ ] // Action:		Stripts out the specified character from a given string if it has any.
[ ] // Syntax:		sNewString = StrStripOutAnyChar (STRING sStr null, STRING sAnyChar)
[ ] // Parameter:	sStr: [null]. The string to be striped for a given character. STRING.
[ ] // Parameter:	sAnyChar: The special character to be Stripted out in the original string [sStr]. STRING.
[ ] // Returns:		If the said character is found in the original string,
[ ] //				returns the new string [sNewString] after stripping the character from [sStr] else returns the original string. STRING.
[+] STRING StrStripOutAnyChar (STRING sStr null, STRING sAnyChar)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (sStr)
		[ ]
		[ ] STRING 	sNewString 	= "", sTempString = ""
		[ ] INTEGER ilen = Len (sStr), iTemp = 1
		[ ]
		[+] for (iTemp = 1; iTemp <= ilen; iTemp++)
			[ ] sTempString	= GetField(sStr, sAnyChar, 1)
			[ ] sStr		= StrGetRightOfSpecialChar(sStr, sAnyChar)
			[ ] sNewString	= sNewString + sTempString
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: StrStripOutAnyChar in testcase: {GetTestCaseName()}	success")
		[ ] return (sNewString)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrStripOutAnyChar in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:	StrStripLeadingZeros function
[ ] // Action:		Stripts the Leading Zeros before of a string if it has any.
[ ] // Syntax:		sNewString = StrStripLeadingZeros (STRING sStr null)
[ ] // Parameter:	sStr: [null]. The string to be striped for Leading Zeros of a string. STRING.
[ ] // Returns:		Returns the new string [sNewString] after stripping the Leading Zeros. STRING.
[+] STRING StrStripLeadingZeros (STRING sStr null)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return (NULL)
		[ ]
		[ ] INTEGER nPos = 1
		[ ] INTEGER nLen = Len (sStr)
		[ ]
		[+] if ((nLen <= 1) || (sStr[1] != '0'))
			[ ] return (sStr)
		[ ]
		[ ] nPos = 2
		[+] while ((nPos < nLen - 1) && (sStr[nPos] == '0'))
			[ ] nPos += 1
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: StrStripLeadingZeros in testcase: {GetTestCaseName()}	success")
		[ ] return (SubStr (sStr, nPos))
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: StrStripLeadingZeros in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return ""
	[ ]
[ ]
[ ]
[ ] // Function:
[ ] // Action:
[ ] // Syntax:
[ ] // Parameter:
[ ] // Returns:
[+] // STRING GenerateMaskValues (STRING sMask)
	[ ] // INTEGER iLoop, iCount, iNum
	[ ] // STRING sBuildPONumber = " ", sNum
	[ ] //
	[ ] // // Get the length of the string passed in.
	[ ] // iCount = Len(sMask)
	[ ] //
	[ ] // // Cycle through each letter and build the string.
	[+] // for iLoop = 1 to iCount
		[+] // switch(sMask[iLoop])
			[+] // case '@'
				[ ] // // Set sNum to return a letter.
				[ ] // sNum = "A"
			[+] // case '#'
				[ ] // // Set sNum to return a number.
				[ ] // sNum = "9"
			[+] // case '+'
				[ ] // // Set sNum to return a number or a letter.
				[ ] // sNum = "X"
			[+] // default
				[ ] // // If it gets to this default, you simply add the value to the PO Number.
				[ ] // sNum = sMask[iLoop]
		[ ] //
		[ ] // // Append it to the new PO Number.
		[ ] // sBuildPONumber = Stuff(sBuildPONumber,Len(sBuildPONumber),0,sNum)
	[ ] //
	[ ] // // Use the RandStr() function to generate the PO Number from the mask.
	[ ] // sBuildPONumber = RandStr(sBuildPONumber)
	[ ] //
	[ ] // //Print("PO returned : {sBuildPONumber}")
	[ ] //
	[ ] // return sBuildPONumber
[ ]
[ ]
[ ] // Function:	ParseStringList function
[ ] // Action:		Split the string from a delimiter and store it in a List
[ ] // Syntax:		lsNewList = ParseStringList (sStr [null], sDelim)
[ ] // Parameter:	sStr: [null]. The string to be striped out. STRING.
[ ] // Parameter:	sDelim: The delimiter from which the string will be splited. STRING.
[ ] // Returns:		Returns sub-strings in a LIST OF STRING after parsing is done. LIST OF STRING.
[+] LIST OF STRING ParseStringList (STRING sStr null, STRING sDelim)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return ({})
		[ ]
		[ ] LIST OF STRING lsRet
		[+] while (true)
			[ ] INTEGER iPos = StrPos (sDelim, sStr)
			[+] if (iPos == 0)
				[ ] ListAppend (lsRet, Trim (sStr))
				[ ] break
			[+] else
				[ ] ListAppend (lsRet, Trim (left (sStr, iPos - 1)))
				[ ] sStr = SubStr (sStr, iPos + Len (sDelim))
		[ ]
		[+] if (lsRet == {""})
			[ ] lsRet = {}
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ParseStringList in testcase: {GetTestCaseName()}	success")
		[ ] return (lsRet)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ParseStringList in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return NULL
	[ ]
[ ]
[ ]
[ ] // Function:	ParseStringToListOfAnytype function
[ ] // Action:		Split the string from a delimiter and store it in a Listof anytype
[ ] // Syntax:		laNewList = ParseStringToListOfAnytype (sStr [null], sDelim)
[ ] // Parameter:	sStr: [null]. The string to be striped out. STRING.
[ ] // Parameter:	sDelim: The delimiter from which the string will be splited. STRING.
[ ] // Returns:		Returns sub-strings in a LIST OF ANYTYPE after parsing is done. LIST OF ANYTYPE.
[+] LIST OF ANYTYPE ParseStringToListOfAnytype (STRING sStr null, STRING sDelim)
	[+] do
		[ ]
		[+] if (sStr == NULL)
			[ ] return ({})
		[ ]
		[ ] LIST OF ANYTYPE laRet
		[+] while (true)
			[ ] INTEGER iPos = StrPos (sDelim, sStr)
			[+] if (iPos == 0)
				[ ] ListAppend (laRet, Trim (sStr))
				[ ] break
			[+] else
				[ ] ListAppend (laRet, Trim (left (sStr, iPos - 1)))
				[ ] sStr = SubStr (sStr, iPos + Len (sDelim))
		[ ]
		[+] if (laRet == {""})
			[ ] laRet = {}
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ParseStringList in testcase: {GetTestCaseName()}	success")
		[ ] return (laRet)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ParseStringList in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return NULL
	[ ]
[ ]
[ ]
[ ] // Function:	ParseNumber function
[ ] // Action:		Parses only number from a String
[ ] // Syntax:		bParse = ParseNumber (sParse, nValue)
[ ] // Parameter:	sParse: [inout]. The original string to be parsed for a number.
[ ] //				Once parsing is done the variable sParse value will be modified and will contain the string part only  STRING.
[ ] // Parameter	nValue: [out]. The variable in which the number will be stored. NUMBER.
[ ] // Returns:		Returns TRUE if parsing is success else FALSE. BOOLEAN.
[+] BOOLEAN ParseNumber (inout STRING sParse, out NUMBER nValue)
	[+] do
		[ ]
		[ ] INTEGER nPos = 1
		[ ] INTEGER nLen = Len (sParse)
		[ ]
		[+] if (nLen == 0)
			[ ] return (FALSE)
		[ ]
		[+] while (IsSpace (sParse[nPos]))
			[ ] nPos += 1
		[ ]
		[+] if ((sParse[nPos] == '-') || (sParse[nPos] == '+') || (sParse[nPos] == '$') || (sParse[nPos] == '.'))
			[ ] nPos += 1
		[ ]
		[+] if (! IsDigit (sParse[nPos]))
			[ ] return (false)
		[ ]
		[+] while (IsDigit (sParse[nPos]))
			[ ] nPos += 1
		[ ]
		[+] if (sParse[nPos] == '.')
			[ ] nPos += 1
			[ ]
			[+] while (IsDigit (sParse[nPos]))
				[ ] nPos += 1
		[ ]
		[+] while (IsSpace (sParse[nPos]))
			[ ] nPos += 1
		[ ]
		[+] if (sParse[1] == '$' || sParse[1] == '.')
			[ ] nValue = Val (SubStr (sParse, 2, nPos - 1))
			[ ] sParse = SubStr (sParse, nPos)
			[ ]
		[+] else
			[ ]
			[ ] nValue = Val (SubStr (sParse, 1, nPos - 1))
			[ ] sParse = SubStr (sParse, nPos)
		[ ] ListAppend(laLogDetails, "Call to function: ParseNumber in testcase: {GetTestCaseName()}	success")
		[ ] return (TRUE)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ParseNumber in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return FALSE
	[ ]
[ ]
[ ] //Newly added Functions
[ ]
[ ]
[ ] // Function:	ListReverse(inout LIST OF ANYTYPE lLIST)
[ ] // Action:		Reverse a given list
[ ] // Syntax:		ListReverse(inout LIST OF ANYTYPE lLIST)
[ ] // Parameter:	lLIST [inout]. The variable in which the LIST will be stored. ANYTYPE
[ ] // Returns:		Returns the reverse list. ANYYTYPE
[+] ListReverse(inout LIST OF ANYTYPE lLIST)
	[ ]
	[ ] INTEGER iTimes 			= 0
	[ ] LIST OF ANYTYPE laTemp 	= {}
	[ ]
	[+] for (iTimes = ListCount(lLIST); iTimes >= 1; iTimes--)
		[ ] ListAppend(laTemp, lLIST[iTimes])
	[ ] lLIST = laTemp
	[ ] //return lLIST
	[ ]
