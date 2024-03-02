# APIs

## Initialization

**cudaInit**

cudaInit() -> int
> Initialize CUDA Runtime.

## System Queries

**cudaSystemGetDriverVersion**

cudaSystemGetDriverVersion() -> int
> Get CUDA Driver version.

**cudaSystemGetRuntimeVersion**

cudaSystemGetRuntimeVersion() -> int
> Get CUDA Runtime version.

**cudaDeviceGetCount**

cudaDeviceGetCount() -> int
> Get CUDA device count.

**cudaDeviceGetHandles**

cudaDeviceGetHandles() -> List[int]
> Get CUDA device handles in list.

## Device Queries

**cudaGetName**

cudaGetName(handle) -> str
> Get CUDA device name.

**cudaGetClockRate**

cudaGetClockRate(handle) -> int
> Get CUDA device clock rate in kilohertz.

**cudaGetComputeCapability**

cudaGetComputeCapability(handle) -> List[int]
> Get CUDA revision numbers in list [major, minor], defining the device's compute capability.

**cudaGetMajor**

cudaGetMajor(handle) -> int
> Get CUDA major revision numbers defining the device's compute capability.

**cudaGetMinor**

cudaGetMinor(handle) -> int
> Get CUDA minor revision numbers defining the device's compute capability.

**cudaGetMemInfo**

cudaGetMemInfo(handle) -> List[int]
> Get CUDA memory information of the device in list [total, free, used].

**cudaGetMemTotal**

cudaGetMemTotal(handle) -> int
> Get CUDA total memory of the device.

**cudaGetMemFree**

cudaGetMemFree(handle) -> int
> Get CUDA free memory of the device.

**cudaGetMemUsed**

cudaGetMemUsed(handle) -> int
> Get CUDA used memory of the device.

**cudaGetMultiProcessorCount**

cudaGetMultiProcessorCount(handle) -> int
> Get CUDA multiprocessor numbers on the device.

**cudaGetPciBusID**

cudaGetPciBusID(handle) -> int
> Get CUDA PCI bus identifier of the device.

**cudaGetPciDeviceID**

cudaGetPciDeviceID(handle) -> int
> Get CUDA PCI device (sometimes called slot) identifier of the device.

**cudaGetPciDomainID**

cudaGetPciDomainID(handle) -> int
> Get CUDA PCI domain identifier of the device.

