#ifndef SOUND_H
#define SOUND_H
//standard library headers
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
//system headers
//local headers

class SoundEngine
{
  public:
    void append_command(const signed char twelfth_root, const unsigned int duration);
    int beep(); 
  private:
    const unsigned int deci_to_milli = 100u;
    const double a4_freq = 440.00;
    std::vector<std::pair<const double, const unsigned int>> beep_args;
};

#endif // SOUND_H
