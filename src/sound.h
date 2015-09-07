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
    SoundEngine();
    void append_command(const double frequency, const unsigned int duration);
    int beep(); 
  private:
    const unsigned int deci_to_milli = 100u;
    std::string beep_command;
};

#endif // SOUND_H
