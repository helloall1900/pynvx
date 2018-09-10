#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cuda_runtime_api.h>

namespace py = pybind11;

#define CUDA_CHECK(condition) \
    do { \
        cudaError_t status = condition; \
        if (status != cudaSuccess) \
            throw std::runtime_error(cudaGetErrorString(status)); \
    } while (0)

#define CUDA_CHECK_DEFAULT(condition, ignore, dftValue) \
    do { \
        cudaError_t status = condition; \
        if (status != cudaSuccess) { \
            if (ignore) \
                return dftValue; \
            else \
                throw std::runtime_error(cudaGetErrorString(status)); \
        } \
    } while (0)


bool check_bool(std::string key, py::kwargs kwargs) {
    bool value = false;
    for (auto item : kwargs) {
        if (std::string(py::str(item.first)) == key) {
            if (py::isinstance<py::bool_>(item.second)) {
                value = py::reinterpret_borrow<py::bool_>(item.second);
            }
        }
    }
    return value;
}

int cudaInit(py::args args, py::kwargs kwargs) {
    int driverVersion;
    CUDA_CHECK_DEFAULT(cudaRuntimeGetVersion(&driverVersion),
                        check_bool("ignore", kwargs),
                        -1);
    return 0;
}

int cudaSystemGetDriverVersion(py::args args, py::kwargs kwargs) {
    int driverVersion;
    CUDA_CHECK_DEFAULT(cudaDriverGetVersion(&driverVersion),
                        check_bool("ignore", kwargs),
                        0);
    return driverVersion;
}

int cudaSystemGetRuntimeVersion(py::args args, py::kwargs kwargs) {
    int runtimeVersion;
    CUDA_CHECK_DEFAULT(cudaRuntimeGetVersion(&runtimeVersion),
                        check_bool("ignore", kwargs),
                        0);
    return runtimeVersion;
}

int cudaDeviceGetCount(py::args args, py::kwargs kwargs) {
    int deviceCount;
    CUDA_CHECK_DEFAULT(cudaGetDeviceCount(&deviceCount),
                        check_bool("ignore", kwargs),
                        0);
    return deviceCount;
}

std::list<int> cudaDeviceGetHandles(py::args args, py::kwargs kwargs) {
    std::list<int> handles;
    int deviceCount;
    CUDA_CHECK_DEFAULT(cudaGetDeviceCount(&deviceCount),
                        check_bool("ignore", kwargs),
                        handles);
    for (int i=0; i<deviceCount; i++)
        handles.push_back(i);
    return handles;
}

std::string cudaGetName(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        std::string(""));
    return std::string(deviceProp.name);
}

int cudaGetClockRate(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.clockRate;
}

std::list<int> cudaGetComputeCapability(int deviceId, py::args args, py::kwargs kwargs) {
    std::list<int> info;
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        info);
    info.push_back(deviceProp.major);
    info.push_back(deviceProp.minor);
    return info;
}

int cudaGetMajor(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.major;
}

int cudaGetMinor(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.minor;
}

int cudaGetMultiProcessorCount(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.multiProcessorCount;
}

int cudaGetPciBusID(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.pciBusID;
}

int cudaGetPciDeviceID(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.pciDeviceID;
}

int cudaGetPciDomainID(int deviceId, py::args args, py::kwargs kwargs) {
    struct cudaDeviceProp deviceProp;
    CUDA_CHECK_DEFAULT(cudaGetDeviceProperties(&deviceProp, deviceId),
                        check_bool("ignore", kwargs),
                        0);
    return deviceProp.pciDomainID;
}

std::list<size_t> cudaGetMemInfo(int deviceId, py::args args, py::kwargs kwargs) {
    std::list<size_t> info;
    size_t memTotal;
    size_t memFree;
    int curDevice;
    bool ignore = check_bool("ignore", kwargs);
    CUDA_CHECK_DEFAULT(cudaGetDevice(&curDevice),
                        ignore,
                        info);
    CUDA_CHECK_DEFAULT(cudaSetDevice(deviceId),
                        ignore,
                        info);
    CUDA_CHECK_DEFAULT(cudaMemGetInfo(&memFree, &memTotal),
                        ignore,
                        info);
    CUDA_CHECK_DEFAULT(cudaSetDevice(curDevice),
                        ignore,
                        info);
    info.push_back(memTotal);
    info.push_back(memFree);
    info.push_back(memTotal - memFree);
    return info;
}

size_t cudaGetMemTotal(int deviceId, py::args args, py::kwargs kwargs) {
    size_t memTotal;
    size_t memFree;
    int curDevice;
    size_t dftValue = 0L;
    bool ignore = check_bool("ignore", kwargs);
    CUDA_CHECK_DEFAULT(cudaGetDevice(&curDevice),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaSetDevice(deviceId),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaMemGetInfo(&memFree, &memTotal),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaSetDevice(curDevice),
                        ignore,
                        dftValue);
    return memTotal;
}

size_t cudaGetMemFree(int deviceId, py::args args, py::kwargs kwargs) {
    size_t memTotal;
    size_t memFree;
    int curDevice;
    size_t dftValue = 0L;
    bool ignore = check_bool("ignore", kwargs);
    CUDA_CHECK_DEFAULT(cudaGetDevice(&curDevice),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaSetDevice(deviceId),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaMemGetInfo(&memFree, &memTotal),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaSetDevice(curDevice),
                        ignore,
                        dftValue);
    return memFree;
}

size_t cudaGetMemUsed(int deviceId, py::args args, py::kwargs kwargs) {
    size_t memTotal;
    size_t memFree;
    int curDevice;
    size_t dftValue = 0L;
    bool ignore = check_bool("ignore", kwargs);
    CUDA_CHECK_DEFAULT(cudaGetDevice(&curDevice),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaSetDevice(deviceId),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaMemGetInfo(&memFree, &memTotal),
                        ignore,
                        dftValue);
    CUDA_CHECK_DEFAULT(cudaSetDevice(curDevice),
                        ignore,
                        dftValue);
    return memTotal - memFree;
}


PYBIND11_MODULE(pynvx, m) {
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    m.doc() = R"pbdoc(
        Python bindings for NVIDIA CUDA APIs
        -----------------------

        .. APIs::
           :cudaInit
           :cudaSystemGetDriverVersion
           :cudaSystemGetRuntimeVersion
           :cudaDeviceGetCount
           :cudaDeviceGetHandles
           :cudaGetName
           :cudaGetClockRate
           :cudaGetComputeCapability
           :cudaGetMajor
           :cudaGetMinor
           :cudaGetMultiProcessorCount
           :cudaGetPciBusID
           :cudaGetPciDeviceID
           :cudaGetPciDomainID
           :cudaGetMemInfo
           :cudaGetMemTotal
           :cudaGetMemFree
           :cudaGetMemUsed

        .. Notes::
           API will raise RuntimeError if failed, unless called with 'ignore=True'.
    )pbdoc";

    // Initialization
    m.def("cudaInit", &cudaInit,
        "Initialize CUDA Runtime.");

    // System Queries
    m.def("cudaSystemGetDriverVersion", &cudaSystemGetDriverVersion,
        "Get CUDA Driver version.");

    m.def("cudaSystemGetRuntimeVersion", &cudaSystemGetRuntimeVersion,
        "Get CUDA Runtime version.");

    m.def("cudaDeviceGetCount", &cudaDeviceGetCount,
        "Get CUDA device count.");

    m.def("cudaDeviceGetHandles", &cudaDeviceGetHandles,
        "Get CUDA device handles in list.");

    // Device Queries
    m.def("cudaGetName", &cudaGetName,
        "Get CUDA device name.");

    m.def("cudaGetClockRate", &cudaGetClockRate,
        "Get CUDA device clock rate in kilohertz.");

    m.def("cudaGetComputeCapability", &cudaGetComputeCapability,
        "Get CUDA revision numbers in list [major, minor], defining the device's compute capability.");

    m.def("cudaGetMajor", &cudaGetMajor,
        "Get CUDA major revision numbers defining the device's compute capability.");

    m.def("cudaGetMinor", &cudaGetMinor,
        "Get CUDA minor revision numbers defining the device's compute capability.");

    m.def("cudaGetMultiProcessorCount", &cudaGetMultiProcessorCount,
        "Get CUDA multiprocessor numbers on the device.");

    m.def("cudaGetPciBusID", &cudaGetPciBusID,
        "Get CUDA PCI bus identifier of the device.");

    m.def("cudaGetPciDeviceID", &cudaGetPciDeviceID,
        "Get CUDA PCI device (sometimes called slot) identifier of the device.");

    m.def("cudaGetPciDomainID", &cudaGetPciDomainID,
        "Get CUDA PCI domain identifier of the device.");

    m.def("cudaGetMemInfo", &cudaGetMemInfo,
        "Get CUDA memory information of the device in list [total, free, used].");

    m.def("cudaGetMemTotal", &cudaGetMemTotal,
        "Get CUDA total memory of the device.");

    m.def("cudaGetMemFree", &cudaGetMemFree,
        "Get CUDA free memory of the device.");

    m.def("cudaGetMemUsed", &cudaGetMemUsed,
        "Get CUDA used memory of the device.");
}
