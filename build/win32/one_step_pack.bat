::git fetch --all
::git reset --hard origin/release/1.0.0.0
::git reset --hard origin/develop

set ORIGINAL_DATE=%date% 

set YEAR=%date:~0,4%
set MONTH=%date:~5,2%
set DAY=%date:~8,2%
set CURRENT_DATE=%YEAR%-%MONTH%-%DAY%


set HOUR=%time:~0,2%
set MINUTE=%time:~3,2%
set SECOND=%time:~6,2%


set TMP_HOUR=%time:~1,1%
set NINE=9
set ZERO=0

set CURRENT_DATE_TIME_STAMP=%YEAR%_%MONTH%%DAY%_%HOUR%%MINUTE%
echo %CURRENT_DATE_TIME_STAMP%

cd ../../
	

cd build/win32
rd /s /Q ".\pack\"
del output.log

"C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" /Clean "Release|Win32" Rexx.vs12.sln

"C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" Rexx.vs12.sln  /rebuild RELEASE /out output.log

mkdir pack
cd pack
mkdir rexxchain
mkdir rexxchain\bin
mkdir rexxchain\config
mkdir rexxchain\data
mkdir rexxchain\jslib
mkdir rexxchain\log

copy ..\bin\Rexx.exe rexxchain\bin
copy ..\bin\*.bin rexxchain\bin
copy ..\bin\*.dat rexxchain\bin
copy ..\bin\*.dll rexxchain\bin
copy ..\config\rexx-mainnet.json rexxchain\config\
copy ..\config\rexx-testnet.json rexxchain\config\
copy ..\config\rexx-single.json  rexxchain\config\
copy ..\config\ReadMe.txt  rexxchain\config\
copy ..\jslib\jslint.js rexxchain\jslib\

..\zip.exe -r rexxchain-win-%CURRENT_DATE_TIME_STAMP%.zip rexxchain

rd /s /Q ".\rexxchain\"

cd ../
	
