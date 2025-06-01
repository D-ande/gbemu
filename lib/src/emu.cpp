#include "emu.hpp"

GbEmu *GbEmu::instance = nullptr;
std::mutex GbEmu::mutex_;

GbEmu::GbEmu(std::string fileName) {
  m_fileName = fileName;
  m_Cart = new Cart();
  m_Bus = new Bus(m_Cart);
  m_CPU = new CPU(m_Bus);
}

GbEmu::~GbEmu() {
  delete m_Cart;
  delete m_Bus;
  delete m_CPU;
}

int GbEmu::emuMain() {
  // Load cart
  if (!m_Cart->loadCart(m_fileName)) {
    throw std::runtime_error("Cart did not load properly");
  }

  m_running = true;
  m_paused = false;
  m_ticks = 0;

  while (m_running) {
    // if (m_paused) { delay(10); continue; } // I assume delay is in SDL
    if (!m_CPU->cpuStep()) {
      throw std::runtime_error("Error while processing cpu step");
    }

    m_ticks++;
  }

  return 1;
}

void GbEmu::printTicks() {
  mutex_.lock();
  std::cout << "Ticks: " << m_ticks << std::endl;
  mutex_.unlock();
}

void GbEmu::cycle(int cycles) {
  mutex_.lock();
  // Do something about cycling ppu and other things?
  std::cout << "Emu has been locked for cycle" << std::endl;

  mutex_.unlock();
}
