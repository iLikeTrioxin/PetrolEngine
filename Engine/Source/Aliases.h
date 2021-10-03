#pragma once

// TODO replace std containers with my own (as i want to get the rid of most dependencies)

#if   __cplusplus >= 202002L // Cpp20
    #define CPP 20
#elif __cplusplus >= 201703L // Cpp17
    #define CPP 17
#elif __cplusplus >= 201402L // Cpp14
    #define CPP 14
#elif __cplusplus >= 201103L // Cpp11
    #define CPP 11
#else   // __cplusplus expands to 199711L until Cpp11 but asume not supported, so 00
    #define CPP 00
#endif

#if defined(NDEBUG)
#define PETROL_ENGINE_DEBUG
#endif

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
#define CURRENT_LINE __LINE__
#define CURRENT_FILE __FILE__

#if defined(__GNUC__)
    #define PURE     __attribute  ((         const        ))
    #define FASTCALL __attribute  ((       fastcall       ))
    #define INTERNAL __attribute__((visibility("internal")))
    #define RESTRICT __restrict
    #define VECTORCALL

    #define CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__clang__)
    #define PURE       __attribute  ((         const        ))
    #define FASTCALL   __attribute  ((       fastcall       ))
    #define INTERNAL   __attribute__((visibility("internal")))
    #define RESTRICT   __restrict
    #define VECTORCALL __vectorcall

    #define CURRENT_FUNCTION __PRETTY_FUNCTION__
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

    #define CURRENT_FUNCTION __FUNCTION__
#else
    #define PURE
    #define FASTCALL
    #define INTERNAL
    #define RESTRICT
    #define VECTORCALL

    // if no compiler macro for function is detected use the standard one
    #define CURRENT_FUNCTION __func__
#endif

#include <ostream>
#include "DebugTools.h"

#if defined(PETROL_ENGINE_DEBUG)

#define LOG_SCOPE(name) PetrolEngine::Debugging::ScopeTimer timer##CURRENT_LINE(name)
#define LOG_FUNCTION() LOG_SCOPE(CURRENT_FUNCTION)
#define DEBUG_LOG(msg) std::cout<<msg<<std::endl

#else

// If not debugging then replace those with nothing
#define LOG_SCOPE(name)
#define LOG_FUNCTION()
#define DEBUG_LOG(msg)

#endif

typedef unsigned int uint;

// types with guaranteed length

using  int8 =   signed char;
using uint8 = unsigned char;

using  int16 =   signed short;
using uint16 = unsigned short;

using  int32 =   signed int;
using uint32 = unsigned int;

using  int64 =   signed long long;
using uint64 = unsigned long long;

template<typename from, typename to>
constexpr to CastTo(from& in) { return *reinterpret_cast<to*>(&in); }