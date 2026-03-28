
#include "test_demangle.hpp"
#include "utility/demangle.hpp"
#include <string>

namespace tests::utility {

TEST_F(TestDemangle, DemangleInt) {
  std::string demangled = ::utility::demangle<int>();
  // Accept both "int" and platform-specific demangled names
  EXPECT_TRUE(demangled == "int" || demangled.find("int") != std::string::npos);
}

struct CustomType {};

TEST_F(TestDemangle, DemangleCustomType) {
  std::string demangled = ::utility::demangle<CustomType>();
  // Should contain the name "CustomType"
  EXPECT_NE(demangled.find("CustomType"), std::string::npos);
}

} // namespace tests::utility
