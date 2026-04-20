@echo off
setlocal enabledelayedexpansion

cd /d "%~dp0"

SET SUCCESS=0
SET FAIL=0

echo.
echo ===== PIDL Build Start =====
echo.

FOR %%F IN (*.pidl) DO (
    echo [Processing] %%~nxF

    REM C++ - common, proxy, stub
    PIDL.exe %%~nxF -outdir .
    IF ERRORLEVEL 1 (
        echo   [FAIL] C++ %%~nxF
        SET /A FAIL+=1
    ) ELSE (
        echo   [OK] C++ %%~nF_common.cpp/h / _proxy.cpp/h / _stub.cpp/h
        SET /A SUCCESS+=1
    )

    REM C# - common, proxy, stub
    PIDL.exe -cs %%~nxF -outdir .
    IF ERRORLEVEL 1 (
        echo   [FAIL] C# %%~nxF
        SET /A FAIL+=1
    ) ELSE (
        echo   [OK] C# %%~nF_common.cs / _proxy.cs / _stub.cs
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
