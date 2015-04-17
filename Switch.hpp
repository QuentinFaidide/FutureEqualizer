#ifndef DEF_SWITCH_HPP
#define DEF_SWITCH_HPP

#define SWITCH_PATH "/usr/local/share/future-lv2/toggle_eq.png"

#include <gtkmm.h>

class Switch
{
public:
	Switch();
	~Switch();
	void drawSwitch(Cairo::RefPtr<Cairo::Context> cr, int x, int y);
	void setValue(float port_input);
	float getValue();
	void checkClickZone(int x, int y);
	void onRelease();
	void handleEvent(GdkEventExpose* event);

private:
	float state;
	int xpos, ypos;
	Glib::RefPtr<Gdk::Pixbuf> kimage;

};

#endif // DEF_SWITCH_HPP