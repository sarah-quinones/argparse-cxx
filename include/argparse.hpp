/**
 * Copyright (c) 2020 sarah k.
 * Copyright (C) 2012-2015 Yecheng Fu <cofyc.jackson at gmail dot com>
 * All rights reserved.
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 */

#ifndef ARGPARSE_CXX_ARGPARSE_HPP_ZI0LXA5GS
#define ARGPARSE_CXX_ARGPARSE_HPP_ZI0LXA5GS

#include <cstdint>
#include <type_traits>
#include <function_ref.hpp>
#include <iosfwd>

namespace veg {

struct ternary {
  enum ternary_e : unsigned char {
    none,
    yes,
    no,
  };

  constexpr ternary() noexcept = default;
  constexpr ternary /* NOLINT(hicpp-explicit-conversions) */ (
      ternary_e e) noexcept
      : val(e) {}

  constexpr friend auto operator==(ternary a, ternary b) noexcept -> bool {
    return a.val == b.val;
  }

  template <typename CharT, typename Traits>
  friend auto operator<<(std::basic_ostream<CharT, Traits>& out, ternary t)
      -> std::basic_ostream<CharT, Traits>& {
    switch (int(t.val)) {
    case none:
      out.write("none", 4);
      break;
    case yes:
      out.write("yes", 3);
      break;
    case no:
      out.write("no", 2);
      break;
    default:
      out.write("unknown", 7);
    }

    return out;
  }

private:
  ternary_e val = none;
};

struct argparse;
struct argparse_option;
using argparse_callback = function_ref<int(argparse*, argparse_option const*)>;

namespace _argparse {
template <bool Cond>
struct enable_if {
  using type = void;
};
template <>
struct enable_if<false> {};

template <typename T>
using is_supported = typename enable_if<          //
    std::is_same<char const*, T>::value ||        //
    std::is_same<ternary, T>::value ||            //
    std::is_same<bool, T>::value ||               //
                                                  //
    std::is_same<char, T>::value ||               //
                                                  //
    std::is_same<char signed, T>::value ||        //
    std::is_same<short signed, T>::value ||       //
    std::is_same<int signed, T>::value ||         //
    std::is_same<long signed, T>::value ||        //
    std::is_same<long long signed, T>::value ||   //
                                                  //
    std::is_same<char unsigned, T>::value ||      //
    std::is_same<short unsigned, T>::value ||     //
    std::is_same<int unsigned, T>::value ||       //
    std::is_same<long unsigned, T>::value ||      //
    std::is_same<long long unsigned, T>::value || //
                                                  //
    std::is_same<float, T>::value ||              //
    std::is_same<double, T>::value ||             //
    std::is_same<long double, T>::value           //
    >::type;

enum struct argparse_option_type {
  /* special */
  ARGPARSE_OPT_GROUP,
  /* options with no arguments */
  ARGPARSE_OPT_BOOLEAN,
  ARGPARSE_OPT_TERNARY,
  /* options with arguments (optional or required) */
  ARGPARSE_OPT_CHAR,

  ARGPARSE_OPT_UCHAR,
  ARGPARSE_OPT_USHORT,
  ARGPARSE_OPT_UINT,
  ARGPARSE_OPT_ULONG,
  ARGPARSE_OPT_ULONG_LONG,
  ARGPARSE_OPT_SCHAR,
  ARGPARSE_OPT_SSHORT,
  ARGPARSE_OPT_SINT,
  ARGPARSE_OPT_SLONG,
  ARGPARSE_OPT_SLONG_LONG,

  ARGPARSE_OPT_FLOAT,
  ARGPARSE_OPT_DOUBLE,
  ARGPARSE_OPT_LONG_DOUBLE,
  ARGPARSE_OPT_STRING,
};
template <typename T>
struct to_option_type {};

template <>
struct to_option_type<char> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_CHAR;
};

template <>
struct to_option_type<char unsigned> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_UCHAR;
};
template <>
struct to_option_type<short unsigned> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_USHORT;
};
template <>
struct to_option_type<int unsigned> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_UINT;
};
template <>
struct to_option_type<long unsigned> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_ULONG;
};
template <>
struct to_option_type<long long unsigned> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_ULONG_LONG;
};

template <>
struct to_option_type<signed char> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_SCHAR;
};
template <>
struct to_option_type<short> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_SSHORT;
};
template <>
struct to_option_type<int> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_SINT;
};
template <>
struct to_option_type<long> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_SLONG;
};
template <>
struct to_option_type<long long> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_SLONG_LONG;
};

template <>
struct to_option_type<bool> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_BOOLEAN;
};
template <>
struct to_option_type<ternary> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_TERNARY;
};
template <>
struct to_option_type<float> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_FLOAT;
};
template <>
struct to_option_type<double> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_DOUBLE;
};
template <>
struct to_option_type<long double> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_LONG_DOUBLE;
};
template <>
struct to_option_type<char const*> {
  static constexpr _argparse::argparse_option_type value =
      _argparse::argparse_option_type::ARGPARSE_OPT_STRING;
};

struct layout {
  _argparse::argparse_option_type type{};
  const char short_name{};
  char const* long_name{};
  void* value{};
  char const* help{};
  argparse_callback callback = {};
  int flags{};
};

auto argparse_parse(argparse* self, int argc, char** argv) -> int;
} // namespace _argparse
enum argparse_option_flags {
  OPT_NONEG = 1, /* disable negation */
};

enum argparse_flag {
  ARGPARSE_STOP_AT_NON_OPTION = 1,
};

/**
 *  argparse option
 *
 *  `type`:
 *    holds the type of the option.
 *
 *  `short_name`:
 *    single character to be used as a short option name, '\0' if none.
 *
 *  `long_name`:
 *    the long option name, without the leading dash, nullptr if none.
 *
 *  `value`:
 *    stores pointer to the value to be filled.
 *
 *  `help`:
 *    the short help message associated to what the option does.
 *    Must never be nullptr.
 *
 *  `callback`:
 *    function_ref is called when the corresponding argument is parsed.
 *
 *  `flags`:
 *    option flags.
 */

struct argparse_option : _argparse::layout {

  constexpr argparse_option /* NOLINT(hicpp-explicit-conversions) */ (
      char const* group_name) noexcept
      : argparse_option{
            {_argparse::argparse_option_type::ARGPARSE_OPT_GROUP,
             0,
             nullptr,
             nullptr,
             group_name,
             {},
             0}} {}

  template <typename T, _argparse::is_supported<T>* = nullptr>
  constexpr argparse_option(
      T& value_ref,
      char const* long_name,
      char const* help = "",
      argparse_callback callback = {}) noexcept
      : argparse_option{{
            _argparse::to_option_type<T>::value,
            '\0',
            long_name,
            &value_ref,
            help,
            callback,
            0,
        }} {}

  template <typename T, _argparse::is_supported<T>* = nullptr>
  constexpr argparse_option(
      T& value_ref,
      char short_name,
      char const* long_name = nullptr,
      char const* help = "",
      argparse_callback callback = {}) noexcept
      : argparse_option{{
            _argparse::to_option_type<T>::value,
            short_name,
            long_name,
            &value_ref,
            help,
            callback,
            0,
        }} {}

  explicit constexpr argparse_option(layout l) noexcept : layout{l} {}
};

/**
 * argpparse
 */
struct argparse {
  int argc;
  char** argv;
  argparse_option const* const options;
  std::size_t const argparse_options_len;
  char const* const* const usages;
  std::size_t const usages_len;
  int const flags;
  char const* const description;
  char const* const epilogue;
  char** out;
  int cpidx;
  char const* optvalue; // current option value

  argparse(
      int* argc,
      char** argv,
      argparse_option const* options,
      std::size_t n_options,
      char const* const* usages,
      std::size_t n_usages,
      char const* description = "",
      char const* epilogue = "",
      int flags = 0) noexcept
      : argc(*argc),
        argv(argv),
        options(options),
        argparse_options_len(n_options),
        usages(usages),
        usages_len(n_usages),
        flags(flags),
        description(description),
        epilogue(epilogue),
        out{},
        cpidx{},
        optvalue{} {
    *argc = _argparse::argparse_parse(this, *argc, argv);
  }

  template <std::size_t n_options, std::size_t n_usages>
  argparse(
      int* argc,
      char** argv,
      argparse_option(&&options)[n_options],
      char const*(&&usages)[n_usages],
      char const* description = "",
      char const* epilogue = "",
      int flags = 0) = delete;
  template <std::size_t n_options, std::size_t n_usages>
  argparse(
      int* argc,
      char** argv,
      argparse_option const (&options)[n_options],
      char const*(&&usages)[n_usages],
      char const* description = "",
      char const* epilogue = "",
      int flags = 0) = delete;
  template <std::size_t n_options, std::size_t n_usages>
  argparse(
      int* argc,
      char** argv,
      argparse_option(&&options)[n_options],
      char const* const (&usages)[n_usages],
      char const* description = "",
      char const* epilogue = "",
      int flags = 0) = delete;

  template <std::size_t n_options, std::size_t n_usages>
  argparse(
      int* argc,
      char** argv,
      argparse_option const (&options)[n_options],
      char const* const (&usages)[n_usages],
      char const* description = "",
      char const* epilogue = "",
      int flags = 0) noexcept
      : argparse(
            argc,
            argv,
            options,
            n_options,
            usages,
            n_usages,
            description,
            epilogue,
            flags) {}
};

// built-in callbacks
auto argparse_help_cb(argparse* self, argparse_option const* option) -> int;

static const argparse_option help = argparse_option{
    {_argparse::argparse_option_type::ARGPARSE_OPT_BOOLEAN,
     'h',
     "help",
     nullptr,
     "show this help message and exit",
     argparse_help_cb,
     OPT_NONEG}};

void argparse_usage(argparse const* self);
} // namespace veg

#endif /* end of include guard ARGPARSE_CXX_ARGPARSE_HPP_ZI0LXA5GS */
