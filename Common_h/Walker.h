#pragma once
#include <functional>

using entid_t = uint64_t;
using walker_t = std::function<entid_t()>();