#include <iostream>
#include <vector>
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

int main() {
  int N = 100'000;
  int M = 15;

  printMemory();
  initMemory();
  printMemory(); // 0B

  // std::vector<std::vector<int>> vec(N, std::vector<int>(M));
  // for (int i = 0; i < N; ++i) {
  //   if (vec[i].capacity() != M) {
  //     throw std::runtime_error("i: " + std::to_string(i) + " Capacity: " +
  //                              std::to_string(vec[i].capacity()));
  //   }
  // }
  // printMemory(); // Result
  // for (int i = 0; i < N; ++i) {
  //   size_t x = sizeof(vec[i]);
  //   if (x != 24) {
  //     throw std::runtime_error("i: " + std::to_string(i) + " Size: " +
  //                              std::to_string(x));
  //   }
  // }
  
  // Version B
  std::vector<char> vec(N * M);
  printMemory();

  // Version A
  // <char>
  // M:  1 ~  8 ->  3956KB
  // M:  9 ~ 24 ->  5584KB (+1628KB)
  // M: 25 ~ 40 ->  7140KB (+1556KB)
  // M: 41 ~ 56 ->  8748KB (+1608KB)

  // <int>
  // M:  1 ~  2 ->  3956KB
  // M:  3 ~  6 ->  5584KB (+1628KB)
  // M:  7 ~ 10 ->  7140KB (+1556KB)
  // M: 11 ~ 14 ->  8748KB (+1608KB)
  
  // Version B
  // M:  1 -> 108KB
  // M:  2 -> 208KB
  // M:  8 -> 792KB
  // M:  9 -> 892KB
  
  
  return 0;
}