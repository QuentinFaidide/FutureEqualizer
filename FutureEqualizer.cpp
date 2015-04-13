#include "FutureEqualizer.hpp"
#include <cmath>

using namespace LV2;

FutureEqualizer::FutureEqualizer(double rate)
  : Plugin<FutureEqualizer>(6) {
    hcToggle = true;
    lcToggle = true;
}
  
void FutureEqualizer::FutureEqualizer::run(uint32_t nframes) {
  updateControllers();

  for (int i = 0; i < nframes; i++) {
    p(4)[i] = filterL(p(2)[i]);
    p(5)[i] = filterR(p(3)[i]);
  }
}

void FutureEqualizer::updateControllers()
{
  HC_Coefs hcvalues = hcL.returnCoefs();
  if(*p(1) != hcvalues._f0)
  {
    hcL.calculateCoefs(*p(1), 1);
    hcvalues = hcL.returnCoefs();
    hcR.applyCoefs(hcvalues);
  }

  LC_Coefs lcvalues = lcL.returnCoefs();
  if(*p(0) != lcvalues._f0)
  {
    lcL.calculateCoefs(*p(0), 1);
    lcvalues = lcL.returnCoefs();
    lcR.applyCoefs(lcvalues);
  }
}

float FutureEqualizer::filterL(float sample)
{
  samplebuffer = sample;
  if(hcToggle)
  {
    samplebuffer = hcL.process(samplebuffer);
  }

  if(lcToggle)
  {
    samplebuffer = lcL.process(samplebuffer);
  }

  return samplebuffer;
}

float FutureEqualizer::filterR(float sample)
{
  samplebuffer = sample;
  if(hcToggle)
  {
    samplebuffer = hcR.process(samplebuffer);
  }

  if(lcToggle)
  {
    samplebuffer = lcR.process(samplebuffer);
  }

  return samplebuffer;
}