set path="%ProgramFiles%\OriginLab\Origin9\OriginC\OriginLab\CSVOriginImporter"
set user_files="%USERPROFILE%\Documents\OriginLab\90\User Files"
mkdir %path%
copy %~dp0*.h %path%
copy %~dp0*.cpp %path%
copy %~dp0*.ogs %user_files%
echo Instalacion exitosa
pause
