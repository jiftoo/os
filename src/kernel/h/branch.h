#pragma once

#define BRANCH(expr, tru, fls) \
    if (expr)                  \
    {                          \
        tru                    \
    }                          \
    else                       \
    {                          \
        fls                    \
    }                          \
    _Static_assert(true, "semicolon after WAIT_UNTIL") // force a semicolon
    