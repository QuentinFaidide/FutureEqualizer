#ifndef DEF_HIGHCUT_HPP
#define DEF_HIGHCUT_HPP

///////////////////////////////////////
////////////  HighCut Class ///////////
// process a mono chanel with a high //
// cut filter of given parameters.   //
// This filter use the Robert Bristow//
// Johnson equation.                 //
///////////////////////////////////////

struct HC_Coefs {
	float _f0;
	float _res;
	float _a0;
	float _a1;
	float _a2;
	float _b1;
	float _b2;
};

class HighCut
{
public:
	HighCut();
	~HighCut();
	void calculateCoefs(float freq, float q);
	float process(float sample);
	HC_Coefs returnCoefs();
	void applyCoefs(HC_Coefs inputCoefs);

private:
	float f0, res, x1, x2, y1, y2, a0, a1, a2, b1, b2;
};

#endif // DEF_HIGHCUT_HPP