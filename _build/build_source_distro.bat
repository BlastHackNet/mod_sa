@echo off
:: header text
echo -----------------------------------------------------------
echo src_saver.bat for m0d_s0beit_sa                 by nuckfuts
echo -----------------------------------------------------------
echo.

:: set our locations
SET m_Path=%~dp0
SET m_TempRelPath=..\_temp
SET m_TempSubRelPath=%m_TempRelPath%\src_distro_build
SET m_UtilityRelPath=utilities
:: set the sauce locations
SET m_BaseRelPath=..
SET m_SrcRelPath=%m_BaseRelPath%\src
SET m_BinRelPath=%m_BaseRelPath%\bin
SET m_BuildRelPath=%m_BaseRelPath%\_build
SET m_OutputRelPath=%m_BaseRelPath%\_distro_source

:: clean the house first
IF EXIST "%m_TempRelPath%\" rmdir /S /Q "%m_TempRelPath%\"

:: copy ChangeLog.txt
mkdir "%m_TempSubRelPath%\"
copy /Y "%m_BaseRelPath%\ChangeLog.txt" "%m_TempSubRelPath%\" > NUL

:: add required empty support directories
IF NOT EXIST "%m_TempSubRelPath%\_DEV_installers" mkdir "%m_TempSubRelPath%\_DEV_installers"
IF NOT EXIST "%m_TempSubRelPath%\_distro_installers" mkdir "%m_TempSubRelPath%\_distro_installers"
IF NOT EXIST "%m_TempSubRelPath%\_distro_source" mkdir "%m_TempSubRelPath%\_distro_source"

:: copy src
xcopy "%m_SrcRelPath%" "%m_TempSubRelPath%\src\" /E /C /Q /H /R /Y
:: process src
cd "%m_Path%%m_TempSubRelPath%\src\"
IF EXIST "obj\" rmdir /S /Q "obj\"
IF EXIST "ipch\" rmdir /S /Q "ipch\"
IF EXIST "*.user" del /F /S /Q "*.user" > NUL
IF EXIST "*.ncb" del /F /S /Q "*.ncb" > NUL
IF EXIST "*.suo" del /F /S /Q /A:H "*.suo" > NUL
IF EXIST "*.opensdf" del /F /S /Q /A:H "*.opensdf" > NUL
IF EXIST "*.sdf" del /F /S /Q "*.sdf" > NUL
cd "%m_Path%"

:: copy bin
xcopy "%m_BinRelPath%" "%m_TempSubRelPath%\bin\" /E /C /Q /H /R /Y
:: process bin
cd "%m_Path%%m_TempSubRelPath%\bin\"
IF EXIST "d3d9.dll" del /F /S /Q "d3d9.dll" > NUL
cd "%m_Path%"

:: copy _build
xcopy "%m_BuildRelPath%" "%m_TempSubRelPath%\_build\" /E /C /Q /H /R /Y
:: process _build
cd "%m_Path%%m_TempSubRelPath%\_build\"
IF EXIST "temp\" rmdir /S /Q "temp\" > NUL
cd "%m_Path%"

:: remove .svn directories, not needed anymore
::cd "%m_Path%%m_TempSubRelPath%"
::FOR /F "tokens=*" %%G IN ('DIR /B /AD /S *.svn*') DO RMDIR /S /Q "%%G"
::cd "%m_Path%"


echo.
echo -----------------------------------------------------------
:: save the sourcecode
SET /p version_m0d=Please enter version (ie 4.3.2.1):  
SET dir_m0d=mod_sa_v%version_m0d%_source
move /Y "%m_TempSubRelPath%" "%m_TempRelPath%\%dir_m0d%" > NUL
IF EXIST "%m_OutputRelPath%\%dir_m0d%.7z" del /F /Q "%m_OutputRelPath%\%dir_m0d%.7z"
%m_UtilityRelPath%\7z a -t7z -m0=LZMA2 -aoa "%m_OutputRelPath%\%dir_m0d%.7z" "%m_Path%%m_TempRelPath%\%dir_m0d%\"

:: cleanup
IF EXIST "%m_TempRelPath%\" rmdir /S /Q "%m_TempRelPath%\"


echo.
echo -----------------------------------------------------------
echo Complete. %dir_m0d% is ready to distro.
echo -----------------------------------------------------------
echo.
pause
