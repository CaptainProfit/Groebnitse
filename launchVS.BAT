::%comspec% /k 

chcp 1251 > nul
:: оно нужно?
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"
code .