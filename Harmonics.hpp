#ifndef DEF_HARMONICS_HPP
#define DEF_HARMONICS_HPP

#include "Peak.hpp"

struct HA_COEFS {
	float _mode;
	float _pfreq;
	float _res;
	float _gain;
	PK_Coefs _p1;
	PK_Coefs _p2;
	PK_Coefs _p3;
};

class Harmonics
{
public:
	Harmonics();
	~Harmonics();
	void calculateCoefs(float freq, float q, float igain, float imode);
	float process(float sample);
	HA_COEFS returnCoefs();
	void applyCoefs(HA_COEFS params);

private:
	float mode, pfreq, res, gain;
	Peak p1, p2, p3;
};

#endif // DEF_HARMONICS_HPP