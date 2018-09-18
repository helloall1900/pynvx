
```
██████╗ ██╗   ██╗███╗   ██╗██╗   ██╗██╗  ██╗
██╔══██╗╚██╗ ██╔╝████╗  ██║██║   ██║╚██╗██╔╝
██████╔╝ ╚████╔╝ ██╔██╗ ██║██║   ██║ ╚███╔╝
██╔═══╝   ╚██╔╝  ██║╚██╗██║╚██╗ ██╔╝ ██╔██╗
██║        ██║   ██║ ╚████║ ╚████╔╝ ██╔╝ ██╗
╚═╝        ╚═╝   ╚═╝  ╚═══╝  ╚═══╝  ╚═╝  ╚═╝
```


# Pynvx
> Python bindings for NVIDIA CUDA APIs.

[![PyPI](https://img.shields.io/pypi/v/pynvx.svg)](https://pypi.python.org/pypi/pynvx)
[![Build Status](https://travis-ci.org/1132719438/pynvx.svg?branch=master)](https://travis-ci.org/1132719438/pynvx)
[![Build status](https://ci.appveyor.com/api/projects/status/0dv4jdx38uyprt7o/branch/master?svg=true)](https://ci.appveyor.com/project/1132719438/pynvx/branch/master)
[![Release Version](https://img.shields.io/github/release/1132719438/pynvx.svg)](https://github.com/1132719438/pynvx/releases)

A Python interface to get GPU information, built with [pybind11](https://github.com/pybind/pybind11). The main purpose of this project is providing a solution for managing GPU information on OS X, because there is no NVML library on OS X. For Linux and Windows users, [pyNVML](https://pythonhosted.org/nvidia-ml-py/) is recommended.


## Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [APIs](#apis)
- [Special notes for Windows](#special-notes-for-windows)
- [License](#license)
- [Troubleshooting](#troubleshooting)
- [Test & Example](#test--example)

## Prerequisites

### 1. CUDA

You should [set up CUDA](https://docs.nvidia.com/cuda/index.html#installation-guides) before installation.

### 2. Compiler

> Used When installing from source

**On Unix (Linux, OS X)**

* A compiler with C++11 support
* CMake >= 2.8.12

**On Windows**

* Visual Studio 2015 (required for all Python versions, see notes below)
* CMake >= 3.1


## Installation

### 1. Install by `pip` (recommended)

```bash
pip install pynvx
```

### 2. Install from offline wheel file

Download wheel file in [Release page](https://github.com/1132719438/pynvx/releases), then install with `pip`:

```bash
pip install pynvx-*.whl
```

### 3. Install from source

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/1132719438/pynvx.git
pip install ./pynvx
```

With the `setup.py` file included in this project, the `pip install` command will
invoke CMake and build the pybind11 module as specified in `CMakeLists.txt`.


## APIs

See [API](https://github.com/1132719438/pynvx/blob/master/API.md)

## Special notes for Windows

**Compiler requirements**

Pybind11 requires a C++11 compliant compiler, i.e Visual Studio 2015 on Windows.
This applies to all Python versions, including 2.7. Unlike regular C extension
modules, it's perfectly fine to compile a pybind11 module with a VS version newer
than the target Python's VS version. See the [FAQ] for more details.

**Runtime requirements**

The Visual C++ 2015 redistributable packages are a runtime requirement for this
project. It can be found [here][vs2015_runtime]. If you use the Anaconda Python
distribution, you can add `vs2015_runtime` as a platform-dependent runtime
requirement for you package: see the `conda.recipe/meta.yaml` file in this example.


## License

### Pybind11

Pybind11 is provided under a BSD-style license that can be found in the LICENSE file in [pybind11](https://github.com/pybind/pybind11). By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.

### Pynvx
Pynvx is provided under MIT License, see LICENSE file.

## Troubleshooting

If you have problem while installing Pynvx, see [TROUBLESHOOTING](https://github.com/1132719438/pynvx/blob/master/TROUBLESHOOTING.md) before opening an issue.

## Test & Example

See [test.py](https://github.com/1132719438/pynvx/blob/master/tests/test.py) and [info.py](https://github.com/1132719438/pynvx/blob/master/tests/info.py).

[FAQ]: http://pybind11.rtfd.io/en/latest/faq.html#working-with-ancient-visual-studio-2009-builds-on-windows
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145