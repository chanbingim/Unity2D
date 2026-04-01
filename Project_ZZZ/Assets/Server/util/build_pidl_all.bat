@echo off
setlocal enabledelayedexpansion

SET TEMP_DIR=C:\pidl_temp
SET SRC_DIR=%~dp0

IF NOT EXIST "%TEMP_DIR%" mkdir "%TEMP_DIR%"

copy /y "%SRC_DIR%PIDL.exe" "%TEMP_DIR%\PIDL.exe" >nul
copy /y "%SRC_DIR%*.pidl" "%TEMP_DIR%\" >nul

cd /d "%TEMP_DIR%"

SET SUCCESS=0
SET FAIL=0

echo.
echo ===== PIDL Build Start =====
echo.

FOR %%F IN (*.pidl) DO (
    echo [Processing] %%~nxF

    REM C++ - common, proxy, stub
    PIDL.exe %%~nxF -outdir "%TEMP_DIR%"
    IF ERRORLEVEL 1 (
        echo   [FAIL] C++ %%~nxF
        SET /A FAIL+=1
    ) ELSE (
        echo   [OK] C++ %%~nF_common.cpp/h / _proxy.cpp/h / _stub.cpp/h
        copy /y "%TEMP_DIR%\%%~nF_common.cpp" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_common.h" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_proxy.cpp" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_proxy.h" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_stub.cpp" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_stub.h" "%SRC_DIR%" >nul
        SET /A SUCCESS+=1
    )

    REM C# - common, proxy, stub
    PIDL.exe -cs %%~nxF -outdir "%TEMP_DIR%"
    IF ERRORLEVEL 1 (
        echo   [FAIL] C# %%~nxF
        SET /A FAIL+=1
    ) ELSE (
        echo   [OK] C# %%~nF_common.cs / _proxy.cs / _stub.cs
        copy /y "%TEMP_DIR%\%%~nF_common.cs" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_proxy.cs" "%SRC_DIR%" >nul
        copy /y "%TEMP_DIR%\%%~nF_stub.cs" "%SRC_DIR%" >nul
        SET /A SUCCESS+=1
    )

    echo.
)

echo ===== Done: OK=%SUCCESS% FAIL=%FAIL% =====
IF %FAIL% GTR 0 (
    pause
    exit /b 1
)
pause
exit /b 0