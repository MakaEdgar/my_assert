// Assert macros for headerless contest systems: just comment one line before sending!
// Makarov Edgar (c), 2024
//
//
// This library contains MYASSERT, MYWARNING and MYDEBUG macroses for additional debug information.
// Benefits over regular assert:
//  - Prints user message and debug information to std::cerr (with coloring).
//  - Active in both Debug and Release builds.
//  - Can be easily switched to regular asserts by commenting one line.
//      Header will not be included, so file can be sent to the contest system as is.
//  - Throwns MyAssertException instead of program termination.
//      Useful to collect fail test cases during (stress) testing.
//
//
// Usage:
// - Copy header to the project folder
// - Use this snippet instead of include
/*
    #define ENABLE_MY_ASSERTS 
    #ifdef ENABLE_MY_ASSERTS
    #    include "my_assert.h"
    #else
    #    ifndef MYASSERTSTUB
    #        define MYASSERTSTUB
    #        include <cassert>
    #        define MYDEBUG(expr) void(0)
    #        define MYWARNING(condition) void(0)
    #        define MYASSERT(condition, ...) assert((condition))
    #        define MYUNREACHABLE(...) exit(42)
    #    endif // MYASSERTSTUB
    #endif // ENABLE_MY_ASSERTS
*/
//
// Documentation:
// - Print expression and its value:
//     `MYDEBUG(expression);`
//
// - Warning if condition is not met:
//     `MYWARNING(condition);`
//
// - Assertions:
//     `MYASSERT(condition);`
//     `MYASSERT(condition, text);`
//
// - Unreachable code:
//     `MYUNREACHABLE();`
//     `MYUNREACHABLE(text);`
//
// - Catch assertion failure inside algorithm (useful for stress testing):
//    `try { output = run_test_case(input) } catch (...) { /* save input */ }`

#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>

// --------------------------------
// === Argument stringification ===
// --------------------------------
#define TOSTR_IMPL(x) #x
#define TOSTR(x) TOSTR_IMPL(x)

// ---------------------
// === Code location ===
// ---------------------
#define LOCATION __FILE__ ":" TOSTR(__LINE__)

// --------------------------------------------
// === Formatted strings for Linux terminal ===
// --------------------------------------------
// foreground colors
#define BLACK_FG_CODE 30   // black
#define RED_FG_CODE 31     // red
#define GREEN_FG_CODE 32   // green
#define YELLOW_FG_CODE 33  // yellow
#define BLUE_FG_CODE 34    // blue
#define MAGENTA_FG_CODE 35 // magenta
#define CYAN_FG_CODE 36    // cyan
#define WHITE_FG_CODE 37   // white

// background colors
#define BLACK_BG_CODE 40   // black
#define RED_BG_CODE 41     // red
#define GREEN_BG_CODE 42   // green
#define YELLOW_BG_CODE 43  // yellow
#define BLUE_BG_CODE 44    // blue
#define MAGENTA_BG_CODE 45 // magenta
#define CYAN_BG_CODE 46    // cyan
#define WHITE_BG_CODE 47   // white

// text styles
#define RESET_CODE 0          // everything back to normal
#define BOLD_CODE 1           // often a brighter shade of the same colour
#define UNDERLINE_CODE 4      // underline
#define INVERSE_CODE 7        // swap foreground and background colours
#define BOLD_OFF_CODE 21      // bold off
#define UNDERLINE_OFF_CODE 24 // underline off
#define INVERSE_OFF_CODE 27   // inverse off

#define FORMATTED_STR_IMPL_(text, code_start, code_end) "\033[1;" #code_start "m" text "\033[" #code_end "m"

#define FORMATTED_STR_IMPL(text, code_start, code_end) FORMATTED_STR_IMPL_(text, code_start, code_end)

#define BLACK_STR(text) FORMATTED_STR_IMPL(text, BLACK_FG_CODE, RESET_CODE)
#define RED_STR(text) FORMATTED_STR_IMPL(text, RED_FG_CODE, RESET_CODE)
#define GREEN_STR(text) FORMATTED_STR_IMPL(text, GREEN_FG_CODE, RESET_CODE)
#define YELLOW_STR(text) FORMATTED_STR_IMPL(text, YELLOW_FG_CODE, RESET_CODE)
#define BLUE_STR(text) FORMATTED_STR_IMPL(text, BLUE_FG_CODE, RESET_CODE)
#define MAGENTA_STR(text) FORMATTED_STR_IMPL(text, MAGENTA_FG_CODE, RESET_CODE)
#define CYAN_STR(text) FORMATTED_STR_IMPL(text, CYAN_FG_CODE, RESET_CODE)
#define WHITE_STR(text) FORMATTED_STR_IMPL(text, WHITE_FG_CODE, RESET_CODE)

#define BOLD_STR(text) FORMATTED_STR_IMPL(text, BOLD_CODE, RESET_CODE)
#define UNDERLINE_STR(text) FORMATTED_STR_IMPL(text, UNDERLINE_CODE, RESET_CODE)
#define INVERSE_STR(text) FORMATTED_STR_IMPL(text, INVERSE_CODE, RESET_CODE)

// --------------------------
// === Assertion macroses ===
// --------------------------

// Assertions
#define MYASSERT_IMPL(x, text)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(x))                                                                                                      \
        {                                                                                                              \
            std::ostringstream oss;                                                                                    \
            oss << BOLD_STR(LOCATION ": ") << RED_STR("assertion check failed: ") << (text) << std::endl;              \
            std::cerr << oss.str();                                                                                    \
            throw my_assert::MyAssertException{(text), LOCATION};                                                      \
        }                                                                                                              \
    } while (false)
#define MYASSERT(x, ...) MYASSERT_(x, ##__VA_ARGS__, 2, 1)
#define MYASSERT_(x, text, n, ...) MYASSERT##n(x, text)
#define MYASSERT1(x, ...) MYASSERT_IMPL(x, #x)
#define MYASSERT2(x, text) MYASSERT_IMPL(x, text)

// Unreachable code
// Assertions
#define MYUNREACHEABLE_IMPL(text)                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream oss;                                                                                        \
        oss << BOLD_STR(LOCATION ": ") << RED_STR("unreacheable code. ") << (text) << std::endl;                       \
        std::cerr << oss.str();                                                                                        \
        throw my_assert::MyAssertException{(text), LOCATION};                                                          \
    } while (false)
#define MYUNREACHABLE(ZeroOrOneArg...) MYUNREACHEABLE_IMPL("" ZeroOrOneArg)

// Debug printing
// TODO: add support for multiple arguments
#define MYDEBUG(expr)                                                                                                  \
                                                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        std::ostringstream oss;                                                                                        \
        oss << BOLD_STR(LOCATION ": ") << YELLOW_STR("debug: ") << TOSTR(expr) << " = " << (expr) << std::endl;        \
        std::cerr << oss.str();                                                                                        \
    } while (false)

// Warnings
#define MYWARNING(expr)                                                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(expr))                                                                                                   \
        {                                                                                                              \
            std::ostringstream oss;                                                                                    \
            oss << BOLD_STR(LOCATION ": ") << MAGENTA_STR("warning check failed: ") << #expr << std::endl;             \
            std::cerr << oss.str();                                                                                    \
        }                                                                                                              \
    } while (false)

namespace my_assert
{
class MyAssertException : public std::runtime_error
{
public:
    explicit MyAssertException(const std::string& message, const std::string& location = "")
        : std::runtime_error(compose_message(message, location))
    {
    }

private:
    std::string compose_message(const std::string& message, const std::string& location)
    {
        auto location_msg = location.empty() ? "" : location + ": ";
        auto message_msg = message.empty() ? "MyAssertException" : message;
        return std::move(location_msg) + std::move(message_msg);
    }
};
} // namespace my_assert
