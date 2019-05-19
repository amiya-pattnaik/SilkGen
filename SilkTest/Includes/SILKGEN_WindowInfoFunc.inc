[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_WindowInfoFunc.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	Window Information related functions are incluced here
[ ] // 	Developer(s)		: 	Amiya Pattnayak
[ ] //	Setup Requirements	: 	NA
[ ]
[+] // 	Revision History
	[ ] //		MM/DD/YY	Creater/Modifier
	[ ] //		04/06/09	Amiya Pattnayak	Created
[ ] //	**************************************************************************************************** //
[ ]
[ ]
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ] //									WINDOW/OBCECT RELATED FUNCTIONS
[ ] //  ---------------------------------------------------------------------------------------------------- //
[ ]
[ ]
[ ] // function:  WaitForWindowGone (wToWaitFor, [iTimeout])
[ ] // parameter: wVerify: The window to wait for. WINDOW.
[ ] // parameter: iTimeout: The amount of time to wait for the window to appear. Defaults to window timeout (optional). INTEGER
[ ] // returns:   void
[ ] // Action:     Waits for a window to disappear, up to the amount of time specified.
[+] VOID WaitForWindowGone (WINDOW wToWaitFor,INTEGER iTimeout optional)
	[+] do
		[ ]
		[ ] INTEGER iWindowTimeout = Agent.GetOption (OPT_WINDOW_TIMEOUT)
		[ ]
		[ ] // if no value supplied use the default window timeout.
		[+] if IsNULL (iTimeout)
			[ ] iTimeout = iWindowTimeout
		[ ]
		[ ] // Raise error if window does not go away in the specified time
		[+] while wToWaitFor.Exists ()
			[+] if iTimeout <= 0
				[ ] AppError ("Window {wToWaitFor} was not closed in the specified timeout")
			[ ] iTimeout = iTimeout - 1
			[ ] sleep (1)
			[ ]
		[ ]
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: WaitForWindowGone in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: WaitForWindowGone in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
[ ]
[ ]
[ ] // function:  ClickCenter (wToClick)
[ ] // parameter: wToClick: The window to click. WINDOW.
[ ] // returns:   void
[ ] // Action:     Clicks in the center of an object, rather than the normal top left corner.
[+] VOID ClickCenter (WINDOW wToClick)
	[+] do
		[ ]
		[ ] POINT pCenter = GetCenter (wToClick)
		[ ] wToClick.Click (1, pCenter.x, pCenter.y)
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ClickCenter in testcase: {GetTestCaseName()}	success")
		[ ] return
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ClickCenter in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] return
[ ]
[ ]
[ ] // function:  pCenter = GetCenter (wCenter)
[ ] // returns:   pCenter: The center point of the window. POINT.
[ ] // parameter: wCenter: The window to locate the center of. WINDOW.
[ ] // returns:   void
[ ] // Action:     Returns the center point of an object.
[+] POINT GetCenter (WINDOW wCenter)
	[+] do
		[ ]
		[ ] RECT rOfWindow = wCenter.GetRect ()		// Get the rect
		[ ]
		[ ] // calculate and return the center point
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: GetCenter in testcase: {GetTestCaseName()}	success")
		[ ] return ({rOfWindow.xPos + (rOfWindow.xSize / 2), rOfWindow.yPos + (rOfWindow.ySize / 2)})
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetCenter in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ]
[ ] // function:  lwWindows = ReturnObjectsOfClassX (wParent, dClass, [iLevels])
[ ] // parameter: wParent: The window to be searched for objects. WINDOW.
[ ] // parameter: dClass: Class to be searched for. DATACLASS.
[ ] // parameter: iLevels: Number of levels to search for children (optional). INTEGER.
[ ] // returns:   lwWindows: The child windows of the specified class. LIST OF WINDOW.
[ ] // Action:     Returns all object children of the specified class, both declared and dynamically instantiated.
[+] LIST OF WINDOW ReturnObjectsOfClassX (WINDOW wParent, DATACLASS dClass, INTEGER iLevels optional)
	[+] do
		[ ]
		[ ] LIST OF WINDOW lwChildren
		[ ] WINDOW wI
		[ ] LIST OF WINDOW lwOfRightClass = {}
		[ ] LIST OF ANYTYPE laMethReturns = {}
		[ ]
		[+] if IsNull (iLevels)
			[ ] lwChildren = wParent.GetChildren (TRUE)
		[+] else
			[ ] lwChildren = GetChildren (wParent, iLevels)
		[ ]
		[ ] // Check all children of the window and build a list if they match the specified class
		[+] for each wI in lwChildren
			[+] if ClassOf (wI) == dClass
				[ ] ListAppend (lwOfRightClass,wI)
				[ ]
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: ReturnObjectsOfClassX in testcase: {GetTestCaseName()}	success")
		[ ] return (lwOfRightClass)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: ReturnObjectsOfClassX in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ] // function:  lwChildren = GetChildren (wParent, iLevels)
[ ] // parameter: wParent: The parent window to get the children from. WINDOW.
[ ] // parameter: iLevels: The number of levels to return children from.  INTEGER.
[ ] // returns:   lwChildren: The children of the window. LIST OF WINDOW.
[ ] // Action:     Gets the children of the specified parent window to the specified number of levels deep.
[+] LIST OF WINDOW GetChildren (WINDOW wParent, INTEGER iLevels)
	[+] do
		[ ]
		[ ] INTEGER				iLoop, iLevelCount
		[+] LIST OF STRING		lsClasses = {...}
			[ ] "HtmlList"
			[ ] "HtmlTable"
			[ ] "HtmlColumn"
		[ ] LIST OF WINDOW		lw, lwAll, lwThis
		[ ] WINDOW				w
		[ ]
		[ ] // get the first level of window children
		[ ] lwThis = wParent.GetChildren (TRUE)
		[ ]
		[ ] // if levels <= 1, return only the first level children
		[+] if iLevels <= 1
			[ ] return (lwThis)
		[ ]
		[ ] // start the full list with the first level children
		[ ] lwAll = lwThis
		[ ]
		[ ] // get any additional children to the level needed for each first level window
		[+] for each w in lwThis
			[+] if ListFind (lsClasses, [STRING] ClassOf (w))
				[ ] // call this function with level decreased by 1
				[ ] iLevelCount = iLevels - 1
				[ ] lw = GetChildren (w, iLevelCount)
				[ ]
				[ ] // if children were found, merge with the full list and reset the interim list
				[+] if ListCount (lw)
					[ ] ListMerge (lwAll, lw)
					[ ] lw = {}
		[ ]
		[ ] // return the full list of window children
		[ ]
		[ ] ListAppend(laLogDetails, "Call to function: GetChildren in testcase: {GetTestCaseName()}	success")
		[ ] return (lwAll)
	[+] except
		[ ]
		[ ] ListAppend(laLogDetails, "Exception raised in Call to function: GetChildren in testcase: {GetTestCaseName()}")
		[ ] ListAppend(laLogDetails, ExceptData ())
		[ ] //return
	[ ]
[ ]
[ ] // function:  VerifyExists (wToVerify, bExpectExists, [iTimeout])
[ ] // parameter: wToVerify: The window which either will or will not exist. WINDOW.
[ ] // parameter: bExpectExists: If TRUE, verify wToVerify exists. If FALSE, verify wToVerify does not exist. BOOLEAN
[ ] // parameter: iTimeout: The amount of time to wait for the window to appear. Defaults to 1 second (optional). INTEGER
[ ] // notes:     Verifies a specified window either does or does not exist in a given timeout.
[+] VOID VerifyExists (WINDOW wToVerify,BOOLEAN bExpectExists, INTEGER iTimeout optional)
	[ ] INTEGER iWindowTimeout = 1
	[ ]
	[ ] // if no value supplied use 1 second
	[+] if IsNULL (iTimeout)
		[ ] iTimeout = iWindowTimeout
	[ ]
	[ ] // Raise error if window does not exist in the specified time
	[ ] Verify (wToVerify.Exists(iTimeout),bExpectExists,"that the window {wToVerify} exists")
	[ ]
	[ ] return
[ ]
[ ]
[ ] // function:  VerifyWindowsExist (lwVerify, [iTimeout, bVerbose])
[ ] // parameter: lwVerify: The list of windows to verify. LIST OF WINDOW.
[ ] // parameter: iTimeout: The amount of time to wait for the windows to appear. Defaults to window timeout (optional). INTEGER.
[ ] // parameter: bVerbose: If TRUE, positive verifications are logged. Defaults to TRUE (optional). BOOLEAN.
[ ] // notes:     Verifies that the specified list of windows exist.
[+] VOID VerifyWindowsExist (LIST OF WINDOW lwVerify, INTEGER iTimeout optional)
	[ ] INTEGER iWindowTimeout = Agent.GetOption (OPT_WINDOW_TIMEOUT)
	[ ] WINDOW	wToVerify
	[ ]
	[ ]
	[ ] // if no value supplied use the default window timeout.
	[+] if IsNULL (iTimeout)
		[ ] iTimeout = iWindowTimeout
	[ ]
	[ ] // Log error if each window does not exist in the specified time - use the timeout for only the first window
	[+] for each wToVerify in lwVerify
		[+] if !wToVerify.Exists (iTimeout)
			[ ] LogErrorSnapBmp ("***Error: VerifyWindowsExist - Window {wToVerify} did not exist")
		[+] else
			[ ] Print ("VerifyWindowsExist - Verified that window {wToVerify} exists")
		[ ] iTimeout = 0
	[ ]
	[ ] return
[ ]
[ ]
[ ] // function:  VerifyWindowExists (wVerify, [iTimeout])
[ ] // parameter: wVerify: The window to verify. WINDOW.
[ ] // parameter: iTimeout: The amount of time to wait for the window to appear. Defaults to window timeout (optional). INTEGER
[ ] // notes:     Verifies that a specified window exists.
[+] VOID VerifyWindowExists (WINDOW wVerify, INTEGER iTimeout optional)
	[ ] INTEGER iWindowTimeout = Agent.GetOption (OPT_WINDOW_TIMEOUT)
	[ ]
	[ ] // if no value supplied use the default window timeout.
	[+] if IsNULL (iTimeout)
		[ ] iTimeout = iWindowTimeout
	[ ]
	[ ] // Raise error if window does not exist in the specified time
	[+] if !wVerify.Exists (iTimeout)
		[ ] AppError ("Window {wVerify} did not exist")
	[ ]
	[ ] return
[ ]
[ ] // function:  RunMethodInsideWindow (wWindow, sMethod, laArgs)
[ ] // parameter: wParent: The window the method is to be run against. WINDOW.
[ ] // parameter: sMethod: Name of the method to execute. STRING.
[ ] // parameter: laArgs: Arguments to the method (optional). LIST OF ANYTYPE.
[ ] // notes:     Wrapper function which uses ArgListCall to call a method.
[+] VOID RunMethodInsideWindow (WINDOW wWindow, STRING sMethod, LIST OF ANYTYPE laArgs optional)
	[ ] // if no args supplied, use an empty list
	[+] if IsNull (laArgs)
		[ ] laArgs = {}
	[ ]
	[ ] // execute the method
	[ ] wWindow.ArgListCall (sMethod,laArgs)
	[ ] sleep (1)
	[ ] return
[ ]
