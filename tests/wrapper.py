from __future__ import print_function, absolute_import, division

from pynvx import pynvml
from pynvx.pynvml import NVMLError


def print_info():
    try:
        pynvml.nvmlInit()
    except NVMLError as e:
        print(e)
        return

    count = pynvml.nvmlDeviceGetCount()
    print('================= GPU INFO =====================')
    print('Device Count    : {}'.format(count))

    for index in range(count):
        handle = pynvml.nvmlDeviceGetHandleByIndex(index)
        print('------------------------------------------------')
        print('Device {}:'.format(handle))
        print('Device Name              : {}'.format(pynvml.nvmlDeviceGetName(handle)))
        mem_info = pynvml.nvmlDeviceGetMemoryInfo(handle)
        print('Device MemTotal          : {} MiB'.format(mem_info.total / (1024 * 1024)))
        print('Device MemFree           : {} MiB'.format(mem_info.free / (1024 * 1024)))
        print('Device MemUsed           : {} MiB'.format(mem_info.used / (1024 * 1024)))

    pynvml.nvmlShutdown()


if __name__ == '__main__':
    print_info()
