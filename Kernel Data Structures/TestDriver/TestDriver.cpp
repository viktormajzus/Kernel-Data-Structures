#include <ntddk.h>

#include "../kds_include/LinkedList.h"

extern "C"
NTSTATUS DriverEntry(
  _In_ PDRIVER_OBJECT  DriverObject,
  _In_ PUNICODE_STRING RegistryPath
)
{
  UNREFERENCED_PARAMETER(DriverObject);
  UNREFERENCED_PARAMETER(RegistryPath);

  kds::LinkedList<int> list{};
  for (auto i = 1; i <= 6; ++i)
    list.push_back(i);

  list.for_each_forward([](const int& value) {
    DbgPrint("List value: %d\n", value);
    });

  return STATUS_SUCCESS;
}