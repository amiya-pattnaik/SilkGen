[ ] //	**************************************************************************************************** //
[ ]
[ ] //	File Name			:	SILKGEN_DistributedProcessing.inc
[ ]
[ ] //	**************************************************************************************************** //
[ ] // 	SILKGEN -				:	All SILKGEN_DistributedProcessing functions are incluced here
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
[ ]
[+] VOID ConnectTargetMachine(STRING sMachineName)
	[ ] STRING 		sTargetMachineName 	= sMachineName
	[ ]
	[+] if (Trim(Lower (sTargetMachineName)) == "local")
		[ ] sTargetMachineName = "(local)"
	[ ]
	[+] if !(Lower (sTargetMachineName) == sLocalMachine)
		[ ] bLocalAgent = FALSE
		[+] do
			[ ] hTargetMachine = Connect ("{sTargetMachineName}")
			[ ] SetMachine(hTargetMachine)
		[+] except
			[ ] ExceptLog ()
			[ ] DisconnectAll()
			[ ] sleep(5)
			[ ] hTargetMachine = Connect ("{sTargetMachineName}")
			[ ] SetMachine(hTargetMachine)
			[ ]
	[+] else
		[ ] bLocalAgent = TRUE
		[ ] //hLocalMachine = Connect ("{sLocalMachine}")
		[ ] //SetMachine(hLocalMachine)
		[ ]
	[ ]
[ ]
[+] VOID DisconnectTargetMachine(STRING sMachineName)
	[ ]
	[ ] //if (Lower(sMachineName) != Lower(sLocalMachine))
	[ ] DisConnect("{sMachineName}")
