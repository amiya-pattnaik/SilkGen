@echo off
SET SILKGEN_HOME=C:\SILKGEN
SET PROJECT_HOME=C:\SILKGEN\ProjectWorkingFolders

SET SCRIPT_NAME=C:\SILKGEN\SilkTest\Scripts\Test1.t
SET TCNAME_ARGS=T100 'AMIYA Ranjan pattnayak' 25 /T2 PATT /T3 DASPALLA	
C:
cd %SEGUE_HOME%
start partner.exe -opt %SILKGEN_HOME%\SilkTest\OptionSets\SILKGEN.opt -r %SCRIPT_NAME% %TCNAME_ARGS%


