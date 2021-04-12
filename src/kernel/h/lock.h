#pragma once
#include "types.h"

#define WAIT_UNTIL(expr) while(!(expr)); _Static_assert(True, "semicolon after WAIT_UNTIL") // force a semicolon