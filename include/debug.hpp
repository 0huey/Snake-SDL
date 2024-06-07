#pragma once

#include <iostream>

#ifdef DEBUG_ENABLE
#define DEBUG_PRINT(args) std::cerr << args << std::endl;
#else
#define DEBUG_PRINT(args)
#endif
