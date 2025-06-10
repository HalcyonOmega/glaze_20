// Glaze Library
// For the license information refer to glaze.hpp

#pragma once

#include <concepts>
// #include <expected> // Will be included conditionally
#include <utility>
#include <version> // For feature testing

#if __has_include(<expected>) && defined(__cpp_lib_expected) && __cpp_lib_expected >= 202202L
#include <expected>
#define GLZ_HAS_STD_EXPECTED 1
#else
#include "glaze/ext/tl/expected.hpp" // Assumes tl/expected.hpp is placed here
#define GLZ_HAS_STD_EXPECTED 0
#endif

namespace glz
{
#if GLZ_HAS_STD_EXPECTED
   template <class Expected, class Unexpected>
   using expected = std::expected<Expected, Unexpected>;

   template <class Unexpected>
   using unexpected = std::unexpected<Unexpected>;
#else
   template <class Expected, class Unexpected>
   using expected = tl::expected<Expected, Unexpected>;

   template <class Unexpected>
   using unexpected = tl::unexpected<Unexpected>; // tl::unexpected is the type
                                                  // tl::make_unexpected creates an instance
#endif

   template <class T>
   concept is_expected = requires(T t) {
      typename T::value_type;
      typename T::error_type;
#if GLZ_HAS_STD_EXPECTED
      { t.has_value() } -> std::convertible_to<bool>;
      { t.value() } -> std::convertible_to<typename T::value_type const&>;
      { t.error() } -> std::convertible_to<typename T::error_type const&>;
#else
      // Assuming tl::expected has a similar API
      { t.has_value() } -> std::convertible_to<bool>;
      { t.value() } -> std::convertible_to<typename T::value_type const&>;
      { t.error() } -> std::convertible_to<typename T::error_type const&>;
#endif
   } && std::same_as<std::remove_cvref_t<T>, expected<typename T::value_type, typename T::error_type>>;

// The Clang-specific workaround for std::unexpected might not be needed
// or might need adjustment if using tl::expected. For tl::expected,
// direct use of tl::unexpected or tl::make_unexpected is common.
// This part is removed for now and can be revisited if specific issues arise with tl::expected.
/*
#ifdef __clang__
   template <class Unexpected>
   struct unexpected : public std::unexpected<Unexpected>
   {
      using std::unexpected<Unexpected>::unexpected;
   };
   template <class Unexpected>
   unexpected(Unexpected) -> unexpected<Unexpected>;
#else
   template <class Unexpected>
   using unexpected = std::unexpected<Unexpected>;
#endif
*/
}