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
    else if(port == 6)
    {
      UI_display->refreshLCSwitch((*static_cast<const float*>(buffer)));
    }
    else if(port == 7)
    {
      UI_display->refreshHCSwitch((*static_cast<const float*>(buffer)));
    }
    else if(port == 8)
    {
      UI_display->refreshP1Switch((*static_cast<const float*>(buffer)));
    }
    else if(port == 9)
    {
      UI_display->refreshPeak1Freq((*static_cast<const float*>(buffer)));
    }
    else if(port == 10)
    {
      UI_display->refreshPeak1Res((*static_cast<const float*>(buffer)));
    }
    else if(port == 11)
    {
      UI_display->refreshPeak1Gain((*static_cast<const float*>(buffer)));
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

  void writeP1Frequency(float value)
  {
    write_control(9, value);
  }

  void writeP1Resonance(float value)
  {
    write_control(10, value);
  }

  void writeP1Gain(float value)
  {
    write_control(11, value);
  }

  void writeLCSwitch(float value)
  {
    write_control(6, value);
  }

  void writeHCSwitch(float value)
  {
    write_control(7, value);
  }

  void writeP1Switch(float value)
  {
    write_control(8, value);
  }

protected:
  UI* UI_display;  
};


static int _ = FutureEqualizerGUI::register_class("http://future-plugin-suite.org/lv2/future/equalizer/gui");