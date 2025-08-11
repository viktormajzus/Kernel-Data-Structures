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

  list[5] = 7;
  DbgPrint("BSOD: %d\n", list[5]);

  return STATUS_SUCCESS;
}

extern "C"
void DriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
  UNREFERENCED_PARAMETER(DriverObject);

  DbgPrint("Driver unloaded.\n");
}