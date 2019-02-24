from __future__ import print_function, absolute_import, division

import sys
import platform
import inspect
from collections import namedtuple
from functools import wraps

try:
    import pynvml
except ImportError:
    raise ImportError('You should install pynvml.\n'
                      'Python 3: pip install nvidia-ml-py3\n'
                      'Python 2: pip install nvidia-ml-py')
from pynvml import NVMLError


_is_osx = platform.system() == "Darwin"
_this_module = sys.modules[__name__]

NVML_ERROR_PYNVX = 1000
GPUMemory = namedtuple('GPUMemory', ['total', 'free', 'used'])


class NVMLError_Pynvx(NVMLError):
    def __new__(typ, msg, value=NVML_ERROR_PYNVX):
        obj = Exception.__new__(typ)
        obj.value = value
        obj.msg = msg
        return obj

    def __str__(self):
        return self.msg


def _cudaDeviceGetHandleByIndex(index):
    return pynvx.cudaDeviceGetHandles()[index]


def _cudaDeviceGetIndex(handle):
    try:
        index = pynvx.cudaDeviceGetHandles().index(handle)
    except ValueError as e:
        raise RuntimeError(str(e))
    return index


def _cudaDeviceGetMemoryInfo(handle):
    info = pynvx.cudaGetMemInfo(handle)
    return GPUMemory(*info)


def _not_implemented_func(*args, **kwargs):
    raise RuntimeError('Not implemented by pynvx, contribution is welcomed: '
                       'https://github.com/1132719438/pynvx/pulls')


def _nothing_to_do_func(*args, **kwargs):
    pass


def wrapper(func):
    @wraps(func)
    def wrapped(*args, **kwargs):
        try:
            ret_val = func(*args, **kwargs)
        except RuntimeError as e:
            raise NVMLError_Pynvx(str(e))
        return ret_val
    return wrapped


if _is_osx:
    try:
        import pynvx
    except ImportError:
        raise ImportError('You should install pynvx on OSX: pip install pynvx')

    _pynvx_func_mapper = {
        'nvmlInit': getattr(pynvx, 'cudaInit'),
        'nvmlShutdown': _nothing_to_do_func,
        'nvmlDeviceGetCount': getattr(pynvx, 'cudaDeviceGetCount'),
        'nvmlDeviceGetHandleByIndex': _cudaDeviceGetHandleByIndex,
        'nvmlDeviceGetIndex': _cudaDeviceGetIndex,
        'nvmlDeviceGetMemoryInfo': _cudaDeviceGetMemoryInfo,
        'nvmlDeviceGetName': getattr(pynvx, 'cudaGetName')
    }

    for func_name, _ in inspect.getmembers(pynvml, inspect.isroutine):
        if func_name.startswith('nvml'):
            if func_name in _pynvx_func_mapper:
                setattr(_this_module, func_name, wrapper(_pynvx_func_mapper[func_name]))
            else:
                setattr(_this_module, func_name, wrapper(_not_implemented_func))

else:
    for func_name, func in inspect.getmembers(pynvml, inspect.isroutine):
        if func_name.startswith('nvml'):
            setattr(_this_module, func_name, func)

setattr(_this_module, 'NVMLError', NVMLError)
