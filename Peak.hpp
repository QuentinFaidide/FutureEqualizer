#ifndef DEF_PEAK_HPP
#define DEF_PEAK_HPP

///////////////////////////////////////
////////////  Peak Class //////////////
// process a mono chanel with a peak //
// filter of given parameters.       //
// This filter use the Robert Bristow//
// Johnson equation.                 //
///////////////////////////////////////

struct PK_Coefs {
	float _f0;
	float _res;
	float _gain;
	float _a0;
	float _a1;
	float _a2;
	float _b1;
	float _b2;
	float _b0;
};

class Peak
{
public:
	Peak();
	~Peak();
	void calculateCoefs(float freq, float q, float igain);
	float process(float sample);
	PK_Coefs returnCoefs();
	void applyCoefs(PK_Coefs inputCoefs);

private:
	float f0, res, gain, x1, x2, y1, y2, a0, a1, a2, b1, b2, b0;
};

#endif // DEF_PEAK_HPP