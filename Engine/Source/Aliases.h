#pragma once

using uint   = unsigned int;

// types with guaranteed length

using  int8  =          short;
using uint8  = unsigned short;
using  int64 =          long long;
using uint64 = unsigned long long;

// TODO replace std containers with my own (as i want to get the rid of most dependencies)

#ifndef NDEBUG
#define debug_log(x) std::cout<<x<<std::endl
#else
#define debug_log(x)
#endif

#define log_and_return(x, y) { debug_log(x); return y; }

//
// std related aliases
//

#include <string>
using String = std::string;

#include <vector>
template<typename T>
using Vector = std::vector<T>;

#include <memory>
template<typename T>
using Ptr = std::unique_ptr<T>;

#include <optional>
template<typename T>
using Optional = std::optional<T>;

#include <set>
template<typename T>
using Set = std::set<T>;

#include <unordered_map>
template<typename T1, typename T2>
using UnorderedMap = std::unordered_map<T1, T2>;

#include <typeindex>
using TypeIndex = std::type_index;

#include <list>
template<typename T>
using List = std::list<T>;