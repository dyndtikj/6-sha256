// Copyright 2021 <geraldy12319@gamil.com>

#include <Hasher.hpp>

std::atomic<bool> Continue = true;
std::atomic<bool> MakeJson = true;
std::string path_to_json;
JsonArray json_file;

void Hasher::stop(int FLAG) {
  if (FLAG == SIGINT) {
    if (MakeJson) {
      std::ofstream out{path_to_json};
      out << json_file;
    }
    Continue = false;
  }
}

void Hasher::hash_analysis(JsonArray& JSON) {
  while (Continue) {
    std::string random_data = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(random_data);
    std::time_t timestamp(std::time(nullptr));
    std::string last_numbers = hash.substr(hash.size() - 4);

    if (last_numbers == "0000") {
      BOOST_LOG_TRIVIAL(info) << "Symbols '0000' in hash <" << hash
                              << "> of data <" << random_data << ">";
      if (MakeJson) {
        JSON.Logging(timestamp, hash, random_data);
      }
    } else {
      BOOST_LOG_TRIVIAL(trace)
          << "Hash <" << hash << "> of data <" << random_data << ">";
    }
  }
}
void Hasher::get_hash(const int& argc, char* argv[]) {
  unsigned int thread_number;
  std::srand(time(nullptr));
  switch (argc) {
    case 1:
      thread_number = std::thread::hardware_concurrency();
      break;
    case 2:
      thread_number = std::atoi(argv[1]);
      if (thread_number == 0 ||
          thread_number > std::thread::hardware_concurrency()) {
        throw std::out_of_range("Wrong number of threads!");
      }
      break;
    case 3:
      thread_number = std::atoi(argv[1]);
      if (thread_number == 0 ||
          thread_number > std::thread::hardware_concurrency()) {
        throw std::out_of_range("Wrong number of threads!");
      }
      path_to_json = argv[2];
      MakeJson = true;
      break;
    default:
      throw std::out_of_range("Wrong number of arguments!");
  }
  Start();
  boost::log::add_common_attributes();
  std::vector<std::thread> vec;
  vec.reserve(thread_number);
  std::signal(SIGINT, Hasher::stop);
  for (size_t i = 0; i < thread_number; i++) {
    vec.emplace_back(Hasher::hash_analysis, std::ref(json_file));
  }
  for (auto& thread : vec) {
    thread.join();
  }
}

