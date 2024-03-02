#!/bin/bash
#
# Install the core CUDA toolkit for OS X. Requires the
# CUDA_VERSION environment variable to be set to the required version.
#
# Since this script updates environment variables, to execute correctly you must
# 'source' this script, rather than executing it in a sub-process.
#
set -e

# Available CUDA versions
# CUDA8    8.0.61
# CUDA9.0  9.0.176
# CUDA9.1  9.1.128
# CUDA9.2  9.2.64

# CUDA 8 we can use the repo
if [[ ${CUDA_VERSION:0:1} = '8' ]]
then
    travis_retry wget -c --progress=dot:mega https://developer.nvidia.com/compute/cuda/${CUDA_VERSION:0:3}/Prod2/local_installers/cuda_${CUDA_VERSION}_mac-dmg -O cuda_${CUDA_VERSION}.dmg
elif [[ ${CUDA_VERSION:0:3} = '9.0' ]]
then
    # CUDA 9 we use the sh installer
    travis_retry wget -c --progress=dot:mega https://developer.nvidia.com/compute/cuda/${CUDA_VERSION:0:3}/Prod/local_installers/cuda_${CUDA_VERSION}_mac-dmg -O cuda_${CUDA_VERSION}.dmg
elif [[ ${CUDA_VERSION:0:3} = '9.1' ]]
then
    # CUDA 9.1 has a different filename pattern
    travis_retry wget -c --progress=dot:mega https://developer.nvidia.com/compute/cuda/${CUDA_VERSION:0:3}/Prod/local_installers/cuda_${CUDA_VERSION}_mac -O cuda_${CUDA_VERSION}.dmg
elif [[ ${CUDA_VERSION:0:3} = '9.2' ]]
then
    # Cuda 9.2 has a different url pattern
    travis_retry wget -c --progress=dot:mega https://developer.nvidia.com/compute/cuda/${CUDA_VERSION:0:3}/Prod/local_installers/cuda_${CUDA_VERSION}_mac -O cuda_${CUDA_VERSION}.dmg
else
    # Didn't match one of the expected CUDA builds, exit
    echo "CUDA version not specified or invalid version specified!"
    exit 1
fi

brew update
brew install p7zip
brew install gnu-tar

7z x cuda_${CUDA_VERSION}.dmg
sudo gtar -x --skip-old-files -f CUDAMacOSXInstaller/CUDAMacOSXInstaller.app/Contents/Resources/payload/cuda_mac_installer_tk.tar.gz -C /
sudo ln -s /Developer/NVIDIA/CUDA-${CUDA_VERSION:0:3} /usr/local/cuda
rm -rf CUDAMacOSXInstaller

export CUDA_HOME=/usr/local/cuda
export DYLD_LIBRARY_PATH=${CUDA_HOME}/lib:${DYLD_LIBRARY_PATH}
export PATH=${CUDA_HOME}/bin:${PATH}
export CUDA_BIN_PATH=${CUDA_HOME}

set  +e