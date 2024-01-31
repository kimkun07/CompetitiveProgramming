#include <iostream>
#include <windows.h>

#include <psapi.h> // windows.h should be included first (Watch out for formatting)

SIZE_T toKB(SIZE_T b) { return b / 1024; }

SIZE_T initialMemory = 0;
void initMemory() {
  PROCESS_MEMORY_COUNTERS pmc;
  pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);

  HANDLE hProcess = GetCurrentProcess();
  if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
    initialMemory = pmc.WorkingSetSize;
  }
}
void printMemory() {
  PROCESS_MEMORY_COUNTERS pmc;
  pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS);

  HANDLE hProcess = GetCurrentProcess();
  if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
    std::cout << toKB(pmc.WorkingSetSize - initialMemory) << "KB" << std::endl;
  }

  CloseHandle(hProcess);
}

struct Xn {
  int a; // make sizeof(Xn) == n
};

int main() {
  int N = 100'000;

  printMemory();
  initMemory();
  printMemory(); // 0B

  std::cout << sizeof(Xn) << std::endl;
  std::cout << sizeof(Xn *) << std::endl; // 8B

  // Version A (allocating x bytes N times)
  Xn *(ary[N]);
  for (int i = 0; i < N; ++i) {
    ary[i] = new Xn;
    *(ary[i]) = Xn{};
  }
  printMemory();

  std::cout << (unsigned long long)(ary[3]) - (unsigned long long)(ary[2]) << std::endl;

  // Version B (single x * N bytes allocation)
  // Xn *arr = new Xn[N];
  // for (int i = 0; i < N; ++i) {
  //   arr[i] = Xn{};
  // }
  // printMemory();

  // Version A
  // every pointer is 8B
  // ary[i] = new char; -> 2372KB (N * 8B + N * 16B)
  // ary[i] = new int;  -> 2372KB (N * 8B + N * 16B)
  // ary[i] = new  X8;  -> 2372KB (N * 8B + N * 16B)
  // ary[i] = new X12;  -> 4000KB (N * 8B + N * 32B)
  // ary[i] = new X24;  -> 4000KB (N * 8B + N * 32B)
  // ary[i] = new X28;  -> 5556KB (N * 8B + N * 48B)

  // Version B
  // new char[N] ->  100KB (N *  1B)
  // new int[N]  ->  392KB (N *  4B)
  // new  X8[N]  ->  784KB (N *  8B)
  // new X12[N]  -> 1176KB (N * 12B)
  // new X20[N]  -> 1960KB (N * 20B)
  // new X32[N]  -> 3132KB (N * 32B)

  return 0;
}