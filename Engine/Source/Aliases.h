#pragma once

using uint   = unsigned int;

// types with guaranteed length

using  int8  =          short;
using uint8  = unsigned short;
using  int64 =          long long;
using uint64 = unsigned long long;

// TODO replace std containers with my own (as i want to get the rid of most dependencies)

#if defined(NDEBUG)
#define debug_log(x) std::cout<<x<<std::endl
#else
#define debug_log(x)
#endif

#define log_and_return(x, y) { debug_log(x); return y; }

/* TODO: figure out if should those be implemented

#if defined(SSEs)
#define writeWOC8B(x) _mm_stream_si64(x)
#endif

#if defined(SSE)
#define prefetch(x) _mm_prefetch(x)
#define writeWOC16B(x, y) _mm_stream_ps(x, y)
#endif

#if defined(SSE2)
#define writeWOC4B (x, y) _mm_stream_si32(x, y)
#define writeWOC16B(x, y) _mm_stream_pd  (x, y)
/// I can't find out what this differ from '_mm_stream_pd', so :/
//#define writeWOC16B(x, y) _mm_stream_si128(x, y)
#endif

 */

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

// c++ macros
#define LINE __LINE__
//#define FILE __FILE__

#if defined(__GNUC__)

#define PURE       __attribute  ((         const        ))
#define FASTCALL   __attribute  ((       fastcall       ))
#define INTERNAL   __attribute__((visibility("internal")))
#define RESTRICT   __restrict
#define VECTORCALL

#elif defined(__clang__)

#define PURE       __attribute((  const ))
#define FASTCALL   __attribute((fastcall))
#define INTERNAL  __attribute__((visibility("internal")))
#define RESTRICT   __restrict
#define VECTORCALL __vectorcall

#elif defined(__INTEL_COMPILER)

#if defined(__linux__)
#define PURE __attribute((const))
#else
#define PURE
#endif

#define FASTCALL   __attribute((fastcall))
#define INTERNAL   __attribute__((visibility("internal")))
#define RESTRICT   __restrict
#define VECTORCALL __vectorcall

#else

#define PURE
#define FASTCALL
#define INTERNAL
#define RESTRICT
#define VECTORCALL

#endif