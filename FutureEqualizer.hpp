#ifndef DEF_FUTURE_EQ_HPP
#define DEF_FUTURE_EQ_HPP

#include <lv2plugin.hpp>
#include "HighCut.hpp"
#include "LowCut.hpp"

using namespace LV2;

class FutureEqualizer : public Plugin<FutureEqualizer> {
public:
  
  FutureEqualizer(double rate);
  
  void run(uint32_t nframes);

private:

  void updateControllers();
  float filterL(float sample);
  float filterR(float sample);
  HighCut hcL, hcR;
  LowCut lcL, lcR;
  bool hcToggle;
  bool lcToggle;
  float samplebuffer;

};

static int _ = FutureEqualizer::register_class("http://future-plugin-suite.org/lv2/future/equalizer");

#endif // DEF_FUTURE_EQ_HPP