#include "LowCut.hpp"
#include <cmath>

LowCut::LowCut()
{
	f0 = 100;
	res = 1;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

LowCut::~LowCut()
{

}

// RBJ coefs calculation
void LowCut::calculateCoefs(float freq, float q)
{
	if((f0 != freq) or (res != q))
	{
		f0 = freq;
		res = q;

	    float omega = 2.f * M_PI * (f0 / 44100.f);
	    float sn = sin(omega);
	    float cs = cos(omega);
	    float alpha = sn / (2.f * res);
	    float inva = 1 / (1+alpha);

	    a0 = inva*(1.0 + cs)*0.5;
	    a1 = -2*a0;
	    a2 = a0;

	    b1 = -2*cs*inva;
	    b2 = inva*(1 - alpha);
	}
}


// simplified lp processing func by calf devs 
float LowCut::process(float sample)
{
    double out = a0*(sample - x1 - x1 + x2) - y1 * b1 - y2 * b2;
    x2 = x1;
    y2 = y1;
    x1 = sample;
    y1 = out;
    return out;
}

LC_Coefs LowCut::returnCoefs()
{
	LC_Coefs rbuf;
	rbuf._f0 = f0;
	rbuf._res = res;
	rbuf._a0 = a0;
	rbuf._a1 = a1;
	rbuf._a2 = a2;
	rbuf._b1 = b1;
	rbuf._b2 = b2;

	return rbuf;
}

void LowCut::applyCoefs(LC_Coefs toCopy)
{
	f0 = toCopy._f0;
	res = toCopy._res;
	a0 = toCopy._a0;
	a1 = toCopy._a1;
	a2 = toCopy._a2;
	b1 = toCopy._b1;
	b2 = toCopy._b2;
}