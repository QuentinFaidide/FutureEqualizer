#include "Peak.hpp"
#include <cmath>

Peak::Peak()
{
	f0 = 100;
	res = 1;
	gain = 1;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

Peak::~Peak()
{

}

// RBJ coefs calculation
// Big thanks to the audio filter cookbook
void Peak::calculateCoefs(float freq, float q, float igain)
{
	if((f0 != freq) or (res != q) or (gain != igain))
	{
		f0 = freq;
		res = q;
		gain = igain;

		float A = pow(10, (gain/40));
		float omega = 2*M_PI*(f0/44100);
		float c = cos(omega);
		float s = sin(omega);
		float alpha = s/(2*res);

		b0 = 1 + alpha*A;
		b1 = -2*c;
		b2 = 1 - alpha*A;
		a0 = 1 + alpha/A;
		a1 = -2*c;
		a2 = 1 - alpha/A;

		b0 /= a0;
		b1 /= a0;
		b2 /= a0;
		a1 /= a0;
		a2 /= a0;
	}
}

 
float Peak::process(float sample)
{
    float out = sample*b0 + b1*x1 + b2*x2 - a1*y1 - a2*y2;
    x2 = x1;
    y2 = y1;
    x1 = sample;
    y1 = out;
    return out;
}

PK_Coefs Peak::returnCoefs()
{
	PK_Coefs rbuf;
	rbuf._f0 = f0;
	rbuf._res = res;
	rbuf._gain = gain;
	rbuf._a0 = a0;
	rbuf._a1 = a1;
	rbuf._a2 = a2;
	rbuf._b1 = b1;
	rbuf._b2 = b2;
	rbuf._b0 = b0;

	return rbuf;
}

void Peak::applyCoefs(PK_Coefs toCopy)
{
	f0 = toCopy._f0;
	res = toCopy._res;
	gain = toCopy._gain;
	a0 = toCopy._a0;
	a1 = toCopy._a1;
	a2 = toCopy._a2;
	b1 = toCopy._b1;
	b2 = toCopy._b2;
	b0 = toCopy._b0;
}