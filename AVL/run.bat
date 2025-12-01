@echo off
setlocal enabledelayedexpansion

rem Nombre del ejecutable
set EXEC=programa.exe

echo === Compilador C++ con g++ ===
echo.

rem Eliminar ejecutable anterior si existe
if exist %EXEC% del %EXEC%

echo Buscando archivos .cpp...

rem Buscar archivos .cpp recursivamente
set CPP_FILES=
for /r %%f in (*.cpp) do (
    set CPP_FILES=!CPP_FILES! "%%f"
    echo   - %%f
)

rem Verificar si se encontraron archivos
if "!CPP_FILES!"=="" (
    echo ❌ No se encontraron archivos .cpp
    pause
    exit /b 1
)

echo.
echo Compilando con g++...

rem Compilar todos los archivos encontrados
g++ -std=c++17 -Wall -Wextra !CPP_FILES! -o %EXEC%

rem Verificar compilación
if %errorlevel% equ 0 (
    echo ✅ Compilación exitosa. Ejecutando...
    echo ----------------------------------------
    %EXEC%
) else (
    echo ❌ Error en la compilación.
    pause
    exit /b 1
)

pause