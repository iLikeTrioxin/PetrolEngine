#pragma once

using uint = unsigned int;

using  int64 =          long long int;
using uint64 = unsigned long long int;

// std related aliases

using String = std::string;

template<typename T>
using Vector = std::vector<T>;

template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T>
using Optional = std::optional<T>;

template<typename T>
using Set = std::set<T>;