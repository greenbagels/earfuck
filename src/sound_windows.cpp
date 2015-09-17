//standard library headers
#include <cmath>
#include <stdexcept>
//system headers
#include <Windows.h>
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
  for(auto iter = beep_args.begin(); iter != beep_args.end(); iter++)
  {
    if(Beep(static_cast<DWORD>(std::get<0>(*iter)), static_cast<DWORD>(std::get<1>(*iter)*deci_to_milli)) == 0)
    {
      throw std::runtime_error("Beep() failed!");
    }
  }
}
