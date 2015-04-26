#ifndef DEF_FUTURE_EQ_HPP
#define DEF_FUTURE_EQ_HPP

#include <lv2plugin.hpp>
#include "HighCut.hpp"
#include "LowCut.hpp"
#include "Peak.hpp"

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
  Peak p1L, p1R, p2L, p2R, p3L, p3R;

  bool hcToggle, lcToggle, p1Toggle, p2Toggle, p3Toggle;
  float samplebuffer;

};

static int _ = FutureEqualizer::register_class("http://future-plugin-suite.org/lv2/future/equalizer");

#endif // DEF_FUTURE_EQ_HPP