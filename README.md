# My Assertion Lib
C++ assert macros for headerless contest systems: just comment one line before sending! \
Makarov Edgar, 2024 (c)

## Summary
This library contains `MYASSERT`, `MYWARNING`, `MYDEBUG` and `MYUNREACHEABLE` macros for additional debug information.

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
#define ENABLE_MY_ASSERTS  // comment for standart asserts (no header needed)
#ifdef ENABLE_MY_ASSERTS
#    include "my_assert.h"
#else
#    ifndef MYASSERTSTUB
#        define MYASSERTSTUB
#        include <cassert>
#        define MYDEBUG(expr) void(0)
#        define MYWARNING(condition) void(0)
#        define MYASSERT(condition, ...) assert((condition))
#        define MYUNREACHABLE(...) assert(false)
#    endif // MYASSERTSTUB
#endif // ENABLE_MY_ASSERTS
```

## Documentation
- Print expression value:
```cpp
MYDEBUG(expression);
// file_path:line_num: debug: expression = value
```

- Warnings: print message if condition is not met
```cpp
MYWARNING(condition);
// file_path:line_num: warning check failed: condition
```

- Assertions: print message if false and throw MyAssertException
```cpp
// file_path:line_num: assertion check failed: condition
MYASSERT(condition);

// file_path:line_num: assertion check failed: text
MYASSERT(condition, text);
```

- Unreacheable code: print message and throw MyAssertException  
```cpp
// file_path:line_num: unreacheable code.
MYUNREACHEABLE();

// file_path:line_num: unreacheable code. text
MYUNREACHEABLE(text);
```

- Catch assertion failure (e.g., for algorithms stress testing):
```cpp
try {
  output = run_test_case(input)
} catch (/*const my_assert::MyAssertException&*/ ...) {    //
  /* save input */
}
```
