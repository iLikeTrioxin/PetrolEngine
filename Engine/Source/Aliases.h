#pragma once

// TODO replace std containers with my own (as i want to get the rid of most dependencies)

#if !defined(__cplusplus)
#    error A C++ compiler is required!
#endif

#if   __cplusplus >= 202002L // Cpp20
#    define CPP 2020
#elif __cplusplus >= 201703L // Cpp17
#    define CPP 2017
#elif __cplusplus >= 201402L // Cpp14
#    define CPP 2014
#elif __cplusplus >= 201103L // Cpp11
#    define CPP 2011
#elif __cplusplus >= 199711L // Cpp98
#    define CPP 1998
#else
#    define CPP 0000
#endif

#if defined(DEBUG)
#    define DEBUG_LEVEL_3
#endif

#if defined(DEBUG_LEVEL_3)
#    define DEBUG_STATEMENT_L3(x) x
#    define DEBUG_STATEMENT_L2(x) x
#    define DEBUG_STATEMENT_L1(x) x
#elif defined(DEBUG_LEVEL_2)
#    define DEBUG_STATEMENT_L3(x)
#    define DEBUG_STATEMENT_L2(x) x
#    define DEBUG_STATEMENT_L1(x) x
#elif defined(DEBUG_LEVEL_1)
#    define DEBUG_STATEMENT_L3(x)
#    define DEBUG_STATEMENT_L2(x)
#    define DEBUG_STATEMENT_L1(x) x
#else
#    define DEBUG_STATEMENT_L3(x)
#    define DEBUG_STATEMENT_L2(x)
#    define DEBUG_STATEMENT_L1(x)
#endif

/*
 *  C++ attributes:
 *  LIKELY
 *  UNLIKELY
 *  NO_DISCARD
 *  NO_DISCARD(reason)
 *  NO_UNIQUE_ADDRESS
 *  MAYBE_UNUSED
 *  FALLTHROUGH
 *  DEPRECATED
 *  DEPRECATED(reason)
 *  DEPENDENT
 *  NO_RETURN
 */

// repair this mess a little

#define   LIKELY  [[likely]] // Cpp 20
#define UNLIKELY [[unlikely]] // Cpp 20
#define NO_UNIQUE_ADDRESS [[no_unique_address]] // Cpp 20

#if CPP >= 20
#    define NO_DISCARD_R(reason) [[nodiscard(reason)]] // Cpp 20
#else
#    define NO_DISCARD_R(reason) [[     nodiscard    ]] // Cpp 17
#endif

#define NO_DISCARD   [[     nodiscard    ]] // Cpp 17
#define MAYBE_UNUSED [[   maybe_unused   ]] // Cpp 17
#define FALLTHROUGH  [[    fallthrough   ]] // Cpp 17

#define DEPRECATED           [[deprecated        ]] // Cpp 14
#define DEPRECATED_R(reason) [[deprecated(reason)]] // Cpp 14
#define DEPENDENT [[carries_dependency]] // Cpp 11
#define NO_RETURN [[     noreturn     ]] // Cpp 11


#if CPP == 0000
#    define   LIKELY [[likely]]
#    define UNLIKELY [[unlikely]]
#    define NO_DISCARD_R(reason) [[nodiscard(reason)]]
#    define NO_UNIQUE_ADDRESS [[no_unique_address]]
#    define MAYBE_UNUSED [[maybe_unused]]
#    define NO_DISCARD [[nodiscard]]
#    define FALLTHROUGH [[fallthrough]]
#    define DEPRECATED [[deprecated]]
#    define DEPRECATED(reason) [[deprecated(reason)]]
#    define DEPENDENT [[carries_dependency]]
#    define NO_RETURN [[noreturn]]
#endif

// Compiler specific attributes
#if defined(__GNUC__)
#    define PURE     __attribute  ((         const        ))
#    define FASTCALL __attribute  ((       fastcall       ))
#    define INTERNAL __attribute__((visibility("internal")))
#    define RESTRICT __restrict
#    define VECTORCALL
#
#    define CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__clang__)
#    define PURE       __attribute  ((         const        ))
#    define FASTCALL   __attribute  ((       fastcall       ))
#    define INTERNAL   __attribute__((visibility("internal")))
#    define RESTRICT   __restrict
#    define VECTORCALL __vectorcall
#
#    define CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__INTEL_COMPILER)
#    if defined(__linux__)
#        define PURE __attribute((const))
#    else
#        define PURE
#    endif
#
#    define FASTCALL   __attribute((fastcall))
#    define INTERNAL   __attribute__((visibility("internal")))
#    define RESTRICT   __restrict
#    define VECTORCALL __vectorcall
#
#    define CURRENT_FUNCTION __FUNCTION__
#else
#    define PURE
#    define FASTCALL
#    define INTERNAL
#    define RESTRICT
#    define VECTORCALL
#    // if no compiler macro for function is detected use the standard one
#    define CURRENT_FUNCTION __func__
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

template<typename T>
inline String toString(T x) { return std::to_string(x); }

#include <vector>
template<typename T>
using Vector = std::vector<T>;

#include <memory>
template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> createRef(Args&& ... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

template<typename T>
constexpr auto move(T t) { return std::move(t); }

template<typename T1, typename T2>
using Pair = std::pair<T1, T2>;

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

using uint = unsigned int;

// types with guaranteed length

using  int8  = std:: int8_t ;
using uint8  = std::uint8_t ;
using  int16 = std:: int16_t;
using uint16 = std::uint16_t;
using  int32 = std:: int32_t;
using uint32 = std::uint32_t;
using  int64 = std:: int64_t;
using uint64 = std::uint64_t;

using sizeType = std::size_t;

#include <cassert>

static_assert(sizeof(int8 ) == 1, "int8  size is not 8  bits.");
static_assert(sizeof(int16) == 2, "int16 size is not 16 bits.");
static_assert(sizeof(int32) == 4, "int32 size is not 32 bits.");
static_assert(sizeof(int64) == 8, "int64 size is not 64 bits.");

#include <cstdio>

// some nice spaghetti here

constexpr bool strSlant(const char *str) { return *str == '/' || *str != 0 && strSlant(str + 1); }

constexpr const char* rSlant           (const char* str) { return *str == '/' ? (str + 1) : rSlant(str - 1); }
constexpr const char* strEnd           (const char *str) { return *str ?  strEnd(str + 1) : str;             }
constexpr const char* constExprFilename(const char* str) { return strSlant(str) ? rSlant(strEnd(str)) : str; }