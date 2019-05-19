@echo off
SET SILKGEN_HOME=C:\SILKGEN
SET PROJECT_HOME=C:\SILKGEN\ProjectWorkingFolders


SET SCRIPT_NAME=%SILKGEN_HOME%\SilkTest\Scripts\SILKGEN_RunFromFile.t
C:
cd %SEGUE_HOME%
start partner.exe -opt %SILKGEN_HOME%\SilkTest\OptionSets\SILKGEN.opt -r %SCRIPT_NAME%


