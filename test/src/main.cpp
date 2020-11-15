#include <fmt/ostream.h>
#include "argparse.hpp"
#include <cstdio>
#include <iostream>

#define PERM_READ (1 << 0)
#define PERM_WRITE (1 << 1)
#define PERM_EXEC (1 << 2)

auto main(int argc, char** argv) -> int {
  veg::ternary tern;
  bool force = true;
  bool test = false;
  long num = 0;
  long double flt = 0;
  char a = 0;
  char const* path = nullptr;

  char const* usage[] = {
      "test_argparse [options] [[--] args]",
      "test_argparse [options]",
  };
  veg::argparse_option options[] = {
      veg::help,
      "Basic options",
      {a, 'c', "char"},
      {tern, 'r', "tern"},
      {force, 'f', "force", "force to do"},
      "More options",
      {path, 'p', "path", "path to read"},
      {flt, "float", "num"},
      {num, "num", "selected num"},
  };

  veg::argparse argparse(
      &argc, argv, options, usage, "description", "more description");

  fmt::print(
      "ternary: {}\n"
      "force: {}\n"
      "test: {}\n"
      "path: {}\n"
      "num: {}\n"
      "flt: {}\n"
      "a: {}\n",
      tern,
      force,
      test,
      path,
      num,
      flt,
      a);

  printf("argc: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, *(argv + i));
  }

  return 0;
}
