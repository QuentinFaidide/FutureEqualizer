#include "FutureEqualizer.hpp"
#include <cmath>

using namespace LV2;

FutureEqualizer::FutureEqualizer(double rate)
  : Plugin<FutureEqualizer>(24) {
    hcToggle = false;
    lcToggle = false;
    p1Toggle = false;
    p2Toggle = false;
    p3Toggle = false;
    harmToggle = false;
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

  PK_Coefs pkvalues = p1L.returnCoefs();
  if( (*p(9) != pkvalues._f0) or (*p(10) != pkvalues._res) or (*p(11) != pkvalues._gain) )
  {
    p1L.calculateCoefs(*p(9), *p(10), *p(11));
    pkvalues = p1L.returnCoefs();
    p1R.applyCoefs(pkvalues);
  }

  pkvalues = p2L.returnCoefs();
  if( (*p(13) != pkvalues._f0) or (*p(14) != pkvalues._res) or (*p(15) != pkvalues._gain) )
  {
    p2L.calculateCoefs(*p(13), *p(14), *p(15));
    pkvalues = p2L.returnCoefs();
    p2R.applyCoefs(pkvalues);
  }

  pkvalues = p3L.returnCoefs();
  if( (*p(17) != pkvalues._f0) or (*p(18) != pkvalues._res) or (*p(19) != pkvalues._gain) )
  {
    p3L.calculateCoefs(*p(17), *p(18), *p(19));
    pkvalues = p3L.returnCoefs();
    p3R.applyCoefs(pkvalues);
  }

  HA_COEFS harmvalues = harmL.returnCoefs();
  if( (*p(20) != harmvalues._mode) or (*p(21) != harmvalues._res) or (*p(22) != harmvalues._gain) or (*p(17) != harmvalues._pfreq) )
  {
    harmL.calculateCoefs(*p(17), *p(21), *p(22), *p(20));
    harmvalues = harmL.returnCoefs();
    harmR.applyCoefs(harmvalues);
  }

  if(*p(6) == 1.0)
  {
    lcToggle = true;
  }

  if(*p(6) == 0.0)
  {
    lcToggle = false;
  }

  if(*p(7) == 1.0)
  {
    hcToggle = true;
  }

  if(*p(7) == 0.0)
  {
    hcToggle = false;
  }

  if(*p(8) == 1.0)
  {
    p1Toggle = true;
  }

  if(*p(8) == 0.0)
  {
    p1Toggle = false;
  }

  if(*p(12) == 1.0)
  {
    p2Toggle = true;
  }

  if(*p(12) == 0.0)
  {
    p2Toggle = false;
  }

  if(*p(16) == 1.0)
  {
    p3Toggle = true;
  }

  if(*p(16) == 0.0)
  {
    p3Toggle = false;
  }

  if(*p(23) == 0.0)
  {
    harmToggle = false;
  }

  if(*p(23) == 1.0)
  {
    harmToggle = true;
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

  if(p1Toggle)
  {
    samplebuffer = p1L.process(samplebuffer);
  }

  if(p2Toggle)
  {
    samplebuffer = p2L.process(samplebuffer);
  }

  if(p3Toggle)
  {
    samplebuffer = p3L.process(samplebuffer);
  }

  if(harmToggle)
  {
    samplebuffer = harmL.process(samplebuffer);
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

  if(p1Toggle)
  {
    samplebuffer = p1R.process(samplebuffer);
  }

  if(p2Toggle)
  {
    samplebuffer = p2R.process(samplebuffer);
  }

  if(p3Toggle)
  {
    samplebuffer = p3R.process(samplebuffer);
  }

  if(harmToggle)
  {
    samplebuffer = harmR.process(samplebuffer);
  }


  return samplebuffer;
}