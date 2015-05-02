#include "Harmonics.hpp"
#include <cmath>

Harmonics::Harmonics()
{
	calculateCoefs(700, 2, 0, 0.1);
}

Harmonics::~Harmonics()
{
	
}

void Harmonics::calculateCoefs(float freq, float q, float igain, float imode)
{
	pfreq = freq;
	res = q;
	gain = igain;
	mode = imode;

	if((mode <= 0.25))
	{
		if(pfreq < 10000)
		{
			p1.calculateCoefs(pfreq*2, res, gain);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);
		}
		else
		{
			p1.calculateCoefs(pfreq, res, 0);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);
		}
	}
	else if((mode > 0.25) and (mode <= 0.5))
	{
		if(pfreq < 10000)
		{
			p1.calculateCoefs(pfreq*pow(2.0, 4/12), res, gain);
			p2.calculateCoefs(pfreq*pow(2.0, 7/12), res, gain);
			p3.calculateCoefs(pfreq*2, res, gain);
		}
		else if( (pfreq*pow(2.0, 7/12))<20000 )
		{
			p1.calculateCoefs(pfreq*pow(2.0, 4/12), res, gain);
			p2.calculateCoefs(pfreq*pow(2.0, 7/12), res, gain);
			p3.calculateCoefs(pfreq, res, 0);
		}
		else if( (pfreq*pow(2.0, 4/12))<20000 )
		{
			p1.calculateCoefs(pfreq*pow(2.0, 4/12), res, gain);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);
		}
		else
		{
			p1.calculateCoefs(pfreq, res, 0);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);
		}
	}
	else if((mode > 0.5) and (mode <= 0.75))
	{
		if(pfreq < 10000)
		{
			p1.calculateCoefs(pfreq*pow(2.0, 3/12), res, gain);
			p2.calculateCoefs(pfreq*pow(2.0, 7/12), res, gain);
			p3.calculateCoefs(pfreq*2, res, gain);
		}
		else if( (pfreq*pow(2.0, 7/12))<20000 )
		{
			p1.calculateCoefs(pfreq*pow(2.0, 3/12), res, gain);
			p2.calculateCoefs(pfreq*pow(2.0, 7/12), res, gain);
			p3.calculateCoefs(pfreq, res, 0);
		}
		else if( (pfreq*pow(2.0, 3/12))<20000 )
		{
			p1.calculateCoefs(pfreq*pow(2.0, 3/12), res, gain);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);
		}
		else
		{
			p1.calculateCoefs(pfreq, res, 0);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);	
		}
	}
	else if((mode > 0.75))
	{
		if(pfreq < 5000)
		{
			p1.calculateCoefs(pfreq*2, res, gain);
			p2.calculateCoefs(pfreq*4, res, gain);
			p3.calculateCoefs(pfreq, res, 0);
		}
		else if(pfreq < 10000)
		{
			p1.calculateCoefs(pfreq*2, res, gain);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);	
		}
		else
		{
			p1.calculateCoefs(pfreq, res, 0);
			p2.calculateCoefs(pfreq, res, 0);
			p3.calculateCoefs(pfreq, res, 0);	
		}
	}
}

float Harmonics::process(float sample)
{
	float result;
	result = p1.process(sample);
	result = p2.process(result);
	result = p3.process(result);
	return result;
}

HA_COEFS Harmonics::returnCoefs()
{
	HA_COEFS haparams;
	haparams._mode = mode;
	haparams._pfreq = pfreq;
	haparams._res = res;
	haparams._gain = gain;
	haparams._p1 = p1.returnCoefs();
	haparams._p2 = p2.returnCoefs();
	haparams._p3 = p3.returnCoefs();

	return haparams;
}

void Harmonics::applyCoefs(HA_COEFS params)
{
	mode = params._mode;
	pfreq = params._pfreq;
	res = params._res;
	gain = params._gain;
	p1.applyCoefs(params._p1);
	p2.applyCoefs(params._p2);
	p3.applyCoefs(params._p3);
}