:: Based on https://www.olegtarasov.me/build-cuda-projects-with-appveyor/
:: and https://github.com/willyd/appveyor-cuda-test/blob/master/build.cmd
::
:: Install cuda toolkit for Windows on Appveyor

@echo off

set CUDA_VERSION=%1
echo Try to install CUDA %CUDA_VERSION%
echo ----- System info -----
systeminfo | findstr /C:"OS"

if "%CUDA_VERSION%" == "8.0" (
    set CUDA_LINK="https://developer.nvidia.com/compute/cuda/8.0/prod/local_installers/cuda_8.0.44_windows-exe"
    set CUDA_ART=cudart64_80.dll
) else (
    if "%CUDA_VERSION%" == "9.0" (
        set CUDA_LINK="https://developer.nvidia.com/compute/cuda/9.0/Prod/local_installers/cuda_9.0.176_windows-exe"
        set CUDA_ART=cudart64_90.dll
    ) else (
        echo CUDA version not specified or invalid version specified!
        exit 1
    )
)

if EXIST "%ProgramFiles%\NVIDIA GPU Computing Toolkit\CUDA\v%CUDA_VERSION%\bin\%CUDA_ART%" (
    echo CUDA has already been installed.
    exit 0
)

echo Downloading CUDA toolkit %CUDA_VERSION%
appveyor DownloadFile %CUDA_LINK% -FileName cuda_%CUDA_VERSION%_installer.exe

echo Installing CUDA toolkit %CUDA_VERSION%
7z x cuda_%CUDA_VERSION%_installer.exe -ocuda_%CUDA_VERSION%
cd cuda_%CUDA_VERSION%
setup.exe -s compiler_%CUDA_VERSION% ^
                           cublas_%CUDA_VERSION% ^
                           cublas_dev_%CUDA_VERSION% ^
                           cudart_%CUDA_VERSION% ^
                           curand_%CUDA_VERSION% ^
                           curand_dev_%CUDA_VERSION% ^
                           visual_studio_integration_%CUDA_VERSION%

echo Check CUDA file ("%ProgramFiles%\NVIDIA GPU Computing Toolkit\CUDA\v%CUDA_VERSION%\bin\%CUDA_ART%")
if NOT EXIST "%ProgramFiles%\NVIDIA GPU Computing Toolkit\CUDA\v%CUDA_VERSION%\bin\%CUDA_ART%" (
    echo Failed to install CUDA
    exit 1
)

cd "%APPVEYOR_BUILD_FOLDER%"

exit 0
