//standard library headers
#include <cmath>
#include <stdexcept>
//system headers
//local headers
#include "sound.h"

SoundEngine::SoundEngine()
{
  beep_command = {"beep "};
}

void SoundEngine::append_command(const signed char twelfth_root, const unsigned int duration)
{
  if(beep_command != "beep ")
  { //trailing "-n"s cause extra terminal-frequency beeps at the end of the beep command
    beep_command += std::string("-n ");
  }
  double exponent = static_cast<double>(twelfth_root) / 12.00;
  double note_freq = a4_freq * std::pow(2,exponent);
  beep_command += std::string("-f ") + std::to_string(note_freq) + std::string(" -l ") + std::to_string(duration*deci_to_milli) + std::string(" ");
}

int SoundEngine::beep()
{
  FILE* fp = popen(beep_command.c_str(), "r");
  if(fp == nullptr)
  {
    throw std::runtime_error("Failed to create file pipe!");
  }
  return pclose(fp);
}
