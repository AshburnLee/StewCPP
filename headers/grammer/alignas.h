#ifndef GRAMMER_ALIGNSA_HEADER
#define GRAMMER_ALIGNSA_HEADER
#pragma once

#include <iostream>
#include <iomanip>

namespace grammer {
namespace alignda {
void test_alignsa() {
  alignas(16) int x;  // x 的地址将是 16 的倍数  这句话什么意思？
  int y;

  std::cout << "Address of x (alignas(16)): " << std::hex << &x << std::endl;
  std::cout << "Address of y (no alignas): " << std::hex << &y << std::endl;

  // 验证地址是否为 16 的倍数
  std::cout << "x address % 16: " << (reinterpret_cast<uintptr_t>(&x) % 16) << std::endl;
  std::cout << "y address % 16: " << (reinterpret_cast<uintptr_t>(&y) % 16) << std::endl;
}
} // namespace alignda
} // namespace grammer

#endif // GRAMMER_ALIGNSA_HEADER

