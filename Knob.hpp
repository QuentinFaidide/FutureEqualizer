#ifndef DEF_KNOB_HPP
#define DEF_KNOB_HPP

#define KNOB_PATH "/usr/local/share/future-lv2/knob_eq.png"

#include <gtkmm.h>

class Knob
{
public:
	Knob(float kmin, float kmax, float kdef, bool ilog);
	~Knob();
	void drawKnob(Cairo::RefPtr<Cairo::Context> cr, int x, int y);
	void setValue(float port_input);
	float getValue();
	void checkClickZone(int x, int y);
	void onRelease();
	void handleEvent(GdkEventExpose* event);
	void addUp();
	void addDown();

private:
	float min, max, def, current;
	int xpos, ypos;
	bool clicked, isLog;
	Glib::RefPtr<Gdk::Pixbuf> kimage;

};

#endif // DEF_KNOB_HPP