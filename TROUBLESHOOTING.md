# Troubleshooting

**Python.h: No such file or directory**

You should install python dev library.
> From https://stackoverflow.com/a/21530768.

For apt (`Ubuntu`, `Debian`...):

```
sudo apt-get install python-dev   # for python2.x installs
sudo apt-get install python3-dev  # for python3.x installs
```

For yum (`CentOS`, `RHEL`...):

```
sudo yum install python-devel     # for python2.x installs
sudo yum install python34-devel   # for python3.4 installs
```

For dnf (`Fedora`...):

```
sudo dnf install python2-devel  # for python2.x installs
sudo dnf install python3-devel  # for python3.x installs
```

For zypper (`openSUSE`...):

```
sudo zypper in python-devel   # for python2.x installs
sudo zypper in python3-devel  # for python3.x installs
```

For apk (`Alpine`...):

> This is a departure from the normal Alpine naming
> scheme, which uses py2- and py3- prefixes

```
sudo apk add python2-dev  # for python2.x installs
sudo apk add python3-dev  # for python3.x installs
```

**FindCUDA.cmake:548 (message): Specify CUDA_TOOLKIT_ROOT_DIR**

Make sure you have installed CUDA toolkit, and set environment variables.

For `Linux`:

```
export CUDA_HOME=/usr/local/cuda
export LD_LIBRARY_PATH=${CUDA_HOME}/lib64:${LD_LIBRARY_PATH}
export PATH=${CUDA_HOME}/bin:${PATH}
export CUDA_BIN_PATH=${CUDA_HOME}
```

For `OS X`:

```
export CUDA_HOME=/usr/local/cuda
export DYLD_LIBRARY_PATH=${CUDA_HOME}/lib:${DYLD_LIBRARY_PATH}
export PATH=${CUDA_HOME}/bin:${PATH}
export CUDA_BIN_PATH=${CUDA_HOME}
```

For `Windows`:

Set these paths in system variable `Path`, replace `9.1` to your installed CUDA version.

```
C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.1\bin
C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.1\lib\x64
```
