//standard library headers
#include <cmath>
#include <iostream>
#include <stdexcept>
//system headers
//local headers
#include "sound.hpp"

void SoundEngine::append_command(const signed char twelfth_root, const unsigned int duration)
{
  const double exponent = static_cast<double>(twelfth_root) / 12.00;
  const double note_freq = a4_freq * std::pow(2,exponent);
  beep_args.push_back(std::pair<const double, const unsigned int>(note_freq, duration));
}

int SoundEngine::beep()
{
  std::string beep_command = {"beep "};
  for(auto iter = beep_args.begin(); iter != beep_args.end(); ++iter)
  {
    if(beep_command != "beep ")
    { //trailing "-n"s cause extra terminal-frequency beeps at the end of the beep command
      beep_command += std::string("-n ");
    }
    beep_command += std::string("-f ") + std::to_string(std::get<0>(*iter)) + std::string(" -l ") + std::to_string(std::get<1>(*iter)*deci_to_milli) + std::string(" ");
  }
  FILE* fp = popen(beep_command.c_str(), "r");
  if(fp == nullptr)
  {
    throw std::runtime_error("Failed to create file pipe!");
  }
  return pclose(fp);
}
