from __future__ import print_function, absolute_import, division

import sys
import pynvx as m

if sys.version_info[0] == 2:
    string_types = basestring
    integer_types = [int, long]
else:
    string_types = str
    integer_types = [int]


# test pynvx api
def test_init():
    v = m.cudaInit(ignore=True)
    assert isinstance(v, int)


def test_driver_version():
    v = m.cudaSystemGetDriverVersion(ignore=True)
    assert isinstance(v, int)


def test_runtime_version():
    v = m.cudaSystemGetRuntimeVersion(ignore=True)
    assert isinstance(v, int)


def test_device_count():
    v = m.cudaDeviceGetCount(ignore=True)
    assert isinstance(v, int)


def test_device_handles():
    v = m.cudaDeviceGetHandles(ignore=True)
    assert isinstance(v, list)


def test_name():
    v = m.cudaGetName(0, ignore=True)
    assert isinstance(v, string_types)


def test_clock_rate():
    v = m.cudaGetClockRate(0, ignore=True)
    assert isinstance(v, int)


def test_compute_capability():
    v = m.cudaGetComputeCapability(0, ignore=True)
    assert isinstance(v, list)


def test_major():
    v = m.cudaGetMajor(0, ignore=True)
    assert isinstance(v, int)


def test_minor():
    v = m.cudaGetMinor(0, ignore=True)
    assert isinstance(v, int)


def test_process_count():
    v = m.cudaGetMultiProcessorCount(0, ignore=True)
    assert isinstance(v, int)


def test_pci_bus_id():
    v = m.cudaGetPciBusID(0, ignore=True)
    assert isinstance(v, int)


def test_pci_device_id():
    v = m.cudaGetPciDeviceID(0, ignore=True)
    assert isinstance(v, int)


def test_pci_domain_id():
    v = m.cudaGetPciDomainID(0, ignore=True)
    assert isinstance(v, int)


def test_memory_info():
    v = m.cudaGetMemInfo(0, ignore=True)
    assert isinstance(v, list)


def test_memory_total():
    v = m.cudaGetMemTotal(0, ignore=True)
    assert type(v) in integer_types


def test_memory_free():
    v = m.cudaGetMemFree(0, ignore=True)
    assert type(v) in integer_types


def test_memory_used():
    v = m.cudaGetMemUsed(0, ignore=True)
    assert type(v) in integer_types


# test pynvml wrapper
def test_pynvml_wrapper():
    from pynvx import pynvml
    from pynvx.pynvml import NVMLError

    try:
        pynvml.nvmlInit()
    except NVMLError:
        pass
