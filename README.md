# My Assertion Lib
C++ assert macros for headerless contest systems: just comment one line before sending!
Makarov Edgar, 2024 (c)

## Summary
This library contains `MYASSERT`, `MYWARNING` and `MYDEBUG` macros for additional debug information.

**Benefits over regular assert**:
 - Prints user message and debug information to std::cerr (with coloring).
 - Active in both Debug and Release builds.
 - Can be easily switched to regular asserts by commenting one line.
     Header will not be included, so file can be sent to the contest system as is.
 - Throwns MyAssertException instead of program termination.
     Useful to collect fail test cases during (stress) testing.


## Usage
- Copy header to the project folder
- Use this snippet instead of regular include
```cpp
#define ENABLE_MY_ASSERTS  // comment to replace with standart asserts (no header needed)
#ifdef ENABLE_MY_ASSERTS
#include "my_assert.h"
#else
#include <cassert>
#define MYDEBUG(expr) void(0)
#define MYWARNING(condition) void(0)
#define MYASSERT(condition, ...) assert((condition))
#endif
```

## Documentation
- Print expression value:
```cpp
MYDEBUG(expression);
// file_path:line_num: debug: expression = value
```

- Warning if condition is not met:
```cpp
MYWARNING(condition);
// file_path:line_num: warning check failed: condition
```

- Assertions:
```cpp
MYASSERT(condition);
// file_path:line_num: assertion check failed: condition
```
```cpp
MYASSERT(condition, text);
// file_path:line_num: assertion check failed: text
```

- Catch assertion failure inside algorithm (useful for stress testing):
```cpp
try {
  output = run_test_case(input)
} catch (/*const my_assert::MyAssertException&*/ ...) {    //
  /* save input */
}
```
