
```
██████╗ ██╗   ██╗███╗   ██╗██╗   ██╗██╗  ██╗
██╔══██╗╚██╗ ██╔╝████╗  ██║██║   ██║╚██╗██╔╝
██████╔╝ ╚████╔╝ ██╔██╗ ██║██║   ██║ ╚███╔╝
██╔═══╝   ╚██╔╝  ██║╚██╗██║╚██╗ ██╔╝ ██╔██╗
██║        ██║   ██║ ╚████║ ╚████╔╝ ██╔╝ ██╗
╚═╝        ╚═╝   ╚═╝  ╚═══╝  ╚═══╝  ╚═╝  ╚═╝
```


# pynvx

> Python bindings for NVIDIA CUDA APIs.

[![PyPI](https://img.shields.io/pypi/v/pynvx.svg)](https://pypi.python.org/pypi/pynvx)
[![Release Version](https://img.shields.io/github/release/helloall1900/pynvx.svg)](https://github.com/helloall1900/pynvx/releases)

A Python interface to get GPU information, built with [pybind11](https://github.com/pybind/pybind11). The main purpose of this project is providing a solution for managing GPU information on OS X, because there is no NVML library on OS X.

You can use pynvx as:
- standalone API: `pynvx.cuda*`
- pyNVML wrapper: `pynvml.nvml*`, API call will be invoked to pyNVML on Linux and Windows, or pynvx on OS X.


## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [APIs](#apis)
- [Special notes for Windows](#special-notes-for-windows)
- [License](#license)
- [Troubleshooting](#troubleshooting)
- [Test & Example](#test--example)
- [Special Thanks](#special-thanks)


## Prerequisites

### 1. CUDA

You should [set up CUDA](https://docs.nvidia.com/cuda/index.html#installation-guides) before installation.

### 2. Compiler

> Used When installing from source

**On Unix (Linux, OS X)**

* A compiler with C++11 support
* CMake >= 2.8.12

**On Windows**

* Visual Studio 2015, or Visual Studio 2017 for Python 3.11 and above (see notes below)
* CMake >= 3.1


## Installation

### 1. Install by `pip` (recommended)

```bash
pip install pynvx
```

### 2. Install from offline wheel file

Download wheel file in [Release page](https://github.com/helloall1900/pynvx/releases), then install with `pip`:

```bash
pip install pynvx-*.whl
```

### 3. Install from source

> Please install CUDA and set environment variables first.

> See `FindCUDA.cmake:548 (message): Specify CUDA_TOOLKIT_ROOT_DIR` in [TROUBLESHOOTING](https://github.com/helloall1900/pynvx/blob/master/TROUBLESHOOTING.md).

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/helloall1900/pynvx.git
pip install ./pynvx
```

With the `setup.py` file included in this project, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.


## APIs

- standalone API

  See [API](https://github.com/helloall1900/pynvx/blob/master/API.md)

- pyNVML wrapper

  Please install **pyNVML** when use pynvx as pyNVML wrapper:  
  Python 3: `pip install nvidia-ml-py3`  
  Python 2: `pip install nvidia-ml-py`

  See [WRAPPER](https://github.com/helloall1900/pynvx/blob/master/WRAPPER.md)


## Special notes for Windows

**Compiler requirements**

Pybind11 requires a C++11 compliant compiler, i.e Visual Studio 2015 on Windows (Visual Studio 2017 for Python 3.11 and above).
This applies to all Python versions, including 2.7. Unlike regular C extension
modules, it's perfectly fine to compile a pybind11 module with a VS version newer
than the target Python's VS version. See the [FAQ] for more details.

**Runtime requirements**

The Visual C++ 2015/2017 redistributable packages are a runtime requirement for this
project. It can be found [here][vs2015_runtime]. If you use the Anaconda Python
distribution, you can add `vs2015_runtime`/`vs2017_runtime` as a platform-dependent runtime
requirement for you package: see the `conda.recipe/meta.yaml` file in this example.


## License

`pynvx` is provided under MIT License, see [LICENSE](https://github.com/helloall1900/pynvx/blob/master/LICENSE) file.


## Troubleshooting

If you have problem while installing pynvx, see [TROUBLESHOOTING](https://github.com/helloall1900/pynvx/blob/master/TROUBLESHOOTING.md) before opening an issue.


## Test & Example

- test cases

  [test.py](https://github.com/helloall1900/pynvx/blob/master/tests/test.py)

- standalone API example

  [info.py](https://github.com/helloall1900/pynvx/blob/master/tests/info.py)

- pyNVML wrapper example

  [wrapper.py](https://github.com/helloall1900/pynvx/blob/master/tests/wrapper.py)


## Special Thanks

- Thanks [stas00](https://github.com/stas00) for the idea of pyNVML wrapper and helping to test.


[FAQ]: http://pybind11.rtfd.io/en/latest/faq.html#working-with-ancient-visual-studio-2009-builds-on-windows
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145
