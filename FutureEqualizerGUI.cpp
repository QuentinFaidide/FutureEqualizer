#include "UI.hpp"
#include <lv2gui.hpp>
#include <iostream>


class FutureEqualizerGUI : public LV2::GUI<FutureEqualizerGUI> {
public:
  
  FutureEqualizerGUI(const std::string& URI)
  {
    UI_display = manage(new UI(this));
    set_size_request(560, 370);
    add(*UI_display);
    
  }
  
  void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
  {
    if(port == 0)
    {
      UI_display->refreshLowCutFreq((*static_cast<const float*>(buffer)));
    }
    else if(port == 1)
    {
      UI_display->refreshHighCutFreq((*static_cast<const float*>(buffer)));
    }
  }

  void writeLCFrequency(float value)
  {
    write_control(0, value);
  }

  void writeHCFrequency(float value)
  {
    write_control(1, value);
  }

protected:
  UI* UI_display;  
};


static int _ = FutureEqualizerGUI::register_class("http://future-plugin-suite.org/lv2/future/equalizer/gui");