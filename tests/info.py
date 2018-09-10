from __future__ import print_function

import pynvx


def print_info():
    try:
        pynvx.cudaInit()
    except RuntimeError as e:
        print(e)
        return

    print('================ CUDA INFO =====================')
    print('Driver Version  : {}'.format(pynvx.cudaSystemGetDriverVersion()))
    print('Runtime Version : {}'.format(pynvx.cudaSystemGetRuntimeVersion()))
    print('Device Count    : {}'.format(pynvx.cudaDeviceGetCount()))

    handles = pynvx.cudaDeviceGetHandles()
    for handle in handles:
        print('------------------------------------------------')
        print('Device {}:'.format(handle))
        print('Device Name              : {}'.format(pynvx.cudaGetName(handle)))
        print('Device ClockRate         : {} MHz'.format(pynvx.cudaGetClockRate(handle) / 1024))
        print('Device ComputeCapability : {}'.format(pynvx.cudaGetComputeCapability(handle)))
        print('Device ProcessorCount    : {}'.format(pynvx.cudaGetMultiProcessorCount(handle)))
        print('Device PciBusID          : {}'.format(pynvx.cudaGetPciBusID(handle)))
        print('Device PciDeviceID       : {}'.format(pynvx.cudaGetPciDeviceID(handle)))
        print('Device PciDomainID       : {}'.format(pynvx.cudaGetPciDomainID(handle)))
        print('Device MemTotal          : {} MiB'.format(pynvx.cudaGetMemTotal(handle) / (1024 * 1024)))
        print('Device MemFree           : {} MiB'.format(pynvx.cudaGetMemFree(handle) / (1024 * 1024)))
        print('Device MemUsed           : {} MiB'.format(pynvx.cudaGetMemUsed(handle) / (1024 * 1024)))


if __name__ == '__main__':
    print_info()
