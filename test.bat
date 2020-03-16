Debug\Crypt.exe crypt input.txt crypt.txt 101
echo ERROR=%ERRORLEVEL% ? 0

Debug\Crypt.exe decrypt crypt.txt decrypt.txt 101
echo ERROR=%ERRORLEVEL% ? 0


Debug\Crypt.exe crypt input2.txt crypt2.txt 255
echo ERROR=%ERRORLEVEL% ? 0

Debug\Crypt.exe decrypt crypt2.txt decrypt2.txt 255
echo ERROR=%ERRORLEVEL% ? 0


Debug\Crypt.exe crypt input3.txt crypt3.txt 256
echo ERROR=%ERRORLEVEL% ? 3

Debug\Crypt.exe decrypt crypt3.txt decrypt3.txt 259
echo ERROR=%ERRORLEVEL% ? 3


Debug\Crypt.exe crypt input3.txt crypt3.txt
echo ERROR=%ERRORLEVEL% ? 5

Debug\Crypt.exe idontcare input3.txt crypt3.txt 8
echo ERROR=%ERRORLEVEL% ? 2

Debug\Crypt.exe crypt noinput.txt crypt3.txt 8
echo ERROR=%ERRORLEVEL% ? 1

Debug\Crypt.exe crypt input.txt crypt3.txt notnumber
echo ERROR=%ERRORLEVEL% ? 4
pause