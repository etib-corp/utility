/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once

#include <typeinfo>
#include <string>

#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#include <cstdlib>
#elif defined(_MSC_VER)
#include <Windows.h>
#include <dbghelp.h>
#endif

namespace utility {

/**
 * @brief Demangles a C++ type name for better readability.
 *
 * This function takes a mangled type name (as returned by typeid(T).name())
 * and returns a human-readable version of the type name. The implementation
 * is platform-specific and may use compiler-specific APIs to perform the
 * demangling.
 *
 * @tparam Type The type to demangle.
 * @return A human-readable string representing the type name of T.
 */
template <typename Type> std::string demangle(void) {
#if defined(__GNUC__) || defined(__clang__)
  int status = 0;
  char *demangled =
      abi::__cxa_demangle(typeid(Type).name(), nullptr, nullptr, &status);
  std::string result = (status == 0) ? demangled : typeid(Type).name();
  std::free(demangled);
  return result;
#elif defined(_MSC_VER)
  const char *name = typeid(Type).name();
  char buffer[1024] = {0};
  if (UnDecorateSymbolName(name, buffer, static_cast<DWORD>(sizeof(buffer)),
                           UNDNAME_COMPLETE)) {
    return std::string(buffer);
  }
  return std::string(name);
#else
  return std::string(typeid(Type).name());
#endif
}
} // namespace utility