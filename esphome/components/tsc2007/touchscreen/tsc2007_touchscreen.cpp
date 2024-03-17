#include "tsc2007_touchscreen.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace tsc2007 {

static const char *TAG = "tsc2007_touchscreen";

void TSC2007Touchscreen::setup() {
  ESP_LOGCONFIG(TAG, "Setting up TSC2007 Touchscreen...");
  if (!this->tsc_.begin(this->address_, this->wire_)) {
    ESP_LOGE(TAG, "Failed to initialize TSC2007");
    this->mark_failed();
    return;
  }
}

void TSC2007Touchscreen::dump_config() {
  LOG_I2C_DEVICE(this);
  if (this->is_failed()) {
    ESP_LOGE(TAG, "Communication with TSC2007 failed!");
  }
}

void TSC2007Touchscreen::update() {
  uint16_t x, y, z1, z2;
  if (this->tsc_.read_touch(&x, &y, &z1, &z2)) {
    this->publish_state(x, y, z1, z2);
  } else {
    ESP_LOGE(TAG, "Failed to read from TSC2007");
  }
}

}  // namespace tsc2007
}  // namespace esphome