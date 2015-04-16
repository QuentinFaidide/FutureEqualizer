#ifndef DEF_UI_HPP
#define DEF_UI_HPP

#define BACKGROUND_PATH "/usr/local/share/future-lv2/background_eq.png"

#include <gtkmm.h>
#include "Knob.hpp"

class FutureEqualizerGUI;

class UI : public Gtk::DrawingArea
{
public:
	UI(FutureEqualizerGUI* parent);
	virtual ~UI();
	void refreshLowCutFreq(float value);
	void refreshHighCutFreq(float value);

protected:
	virtual bool on_expose_event(GdkEventExpose* event);
	bool on_button_press_event(GdkEventButton* event);
	bool on_button_release_event(GdkEventButton* event);
	bool on_motion_notify_event (GdkEventMotion* event);
	bool buttonIsPressed;
	int xmouseorigin, ymouseorigin, xmovemem, ymovemem;
	Glib::RefPtr<Gdk::Pixbuf> image;
	FutureEqualizerGUI *parentClass;
	Knob *kn_lc_freq, *kn_hc_freq;
};

#endif // DEF_UI_HPP