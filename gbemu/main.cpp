#include <iostream>

#include "emu.hpp"

int main(int argc, char *argv[]) {
  std::string fileName{"/home/dalton/projects/gbemu/test_roms/01-special.gb"};

  if (argc > 2) {
    std::cerr << "Expected 1 input arument " << argc << " were given"
              << std::endl;
  } else if (argc < 2) {
    // Keep fileName same
  } else {
    fileName = argv[1];
  }

  GbEmu *emu = GbEmu::getInstance(fileName);

  int res = 0;

  try {
    res = emu->emuMain();
  } catch (const std::exception &e) {
    emu->printTicks();
    std::cerr << e.what() << '\n';
    delete emu;
    return 0;
  }

  delete emu;

  return res;
}
