#include "Hasher.hpp"

int main(int argc, char* argv[]) {
  Hasher SHA256;
  SHA256.get_hash(argc, argv);
  return 0;
}
