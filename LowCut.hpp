#ifndef DEF_LOWCUT_HPP
#define DEF_LOWCUT_HPP

///////////////////////////////////////
////////////  LowCut Class ////////////
// process a mono chanel with a low  //
// cut filter of given parameters.   //
// This filter use the Robert Bristow//
// Johnson equation.                 //
///////////////////////////////////////

struct LC_Coefs {
	float _f0;
	float _res;
	float _a0;
	float _a1;
	float _a2;
	float _b1;
	float _b2;
};

class LowCut
{
public:
	LowCut();
	~LowCut();
	void calculateCoefs(float freq, float q);
	float process(float sample);
	LC_Coefs returnCoefs();
	void applyCoefs(LC_Coefs inputCoefs);

private:
	float f0, res, x1, x2, y1, y2, a0, a1, a2, b1, b2;
};

#endif // DEF_LOWCUT_HPP