#pragma once
#include <string>

#define af_bold std::string("\e[1m")
#define af_black af_bold //+"\e[30m"
#define af_gray "\e[30m"
#define af_red af_bold + "\e[31m"
#define af_green af_bold + "\e[32m"
#define af_yellow af_bold + "\e[33m"
#define af_blue af_bold + "\e[34m"
#define af_purple af_bold + "\e[0;35m"
#define af_reset "\e[0m"

#define BOOL(var) af_green + var + af_reset
#define VAR(var) af_black + var + af_reset
#define GLOB(var) af_red + var + af_reset
#define TEMP(var) af_blue + var + af_reset
#define FUN(var) af_purple + var + af_reset
#define TIMPL(var) af_yellow + var + af_reset
#define CONST(var) "\e[32m" + var + af_reset
