echo off
del .\bin\prog.exe
echo O | del .\bin\assets\fonts\*.*
echo O | del .\bin\assets\images\*.*
echo O | del .\bin\assets\sons\*.*
copy .\src\assets\images\*.* .\bin\assets\images\
copy .\src\assets\fonts\*.* .\bin\assets\fonts\
copy .\src\assets\sons\*.* .\bin\assets\sons\ 
gcc -Wall -Werror -pedantic src/main.c src/orn/orn_graphics.c -g -o bin/prog -I include -L lib -lmingw32 -lSDL2_image -lSDL2_ttf -lSDL2main -lSDL2 
IF %ERRORLEVEL% EQU 0 (
    echo Compilation OK !
    cd .\bin\
    .\prog.exe
 ) ELSE (
    echo Erreur de compilation !
 )