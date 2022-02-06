// Copyright 2021 <geraldy12319@gamil.com>

#ifndef LAB_06_MULTITHREADS_HASHER_HPP
#define LAB_06_MULTITHREADS_HASHER_HPP

#include <PicoSHA2/picosha2.h>

#include <JsonArray.hpp>
#include <atomic>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

class Hasher{
 public:
  Hasher() = default;
  void get_hash(const int& argc, char* argv[]);
 private:
  static void hash_analysis(JsonArray& JSON);
  static void stop(int FLAG);
};


#endif  // LAB_06_MULTITHREADS_HASHER_HPP
