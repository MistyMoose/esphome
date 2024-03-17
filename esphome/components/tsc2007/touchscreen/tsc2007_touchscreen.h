#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/touchscreen/touchscreen.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"

amespace esphome {
namespace tsc2007 {

class TSC2007ButtonListener {
public:
  virtual void update_button(uint8_t index, bool state) = 0;
};

class TSC2007Touchscreen : public touchscreen::Touchscreen, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;

  void set_interrupt_pin(InternalGPIOPin *pin) { this->interrupt_pin_ = pin; }
  void register_button_listener(TSC2007ButtonListener *listener) { this->button_listeners_.push_back(listener); }

 protected:
  void update_touches() override;

  InternalGPIOPin *interrupt_pin_{};
  std::vector<TSC2007ButtonListener *> button_listeners_;
  uint8_t button_state_{0xFF};  // last button state. Initial FF guarantees first update.
};

}  // namespace tsc2007
}  // namespace esphome
```