#ifndef FUELGAGE_H
#define FUELGAGE_H

// 7x64, 1 frame(s), 58 bytes
// Example: Sprites::drawOverwrite(x, y, gage, frame);
const uint8_t PROGMEM gage[] = {
  7, 64,
  0x80, 0xbe, 0x8a, 0x8a, 0x82, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0x01, 0x7d, 0x55, 0x55, 0x45, 0x01, 0xff,
};

// 5x8, 1 frame(s), 12 bytes
// Example: Sprites::drawPlusMask(x, y, needle, frame);
const uint8_t PROGMEM needle[] = {
  5, 8,
  0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x03,
};

class FuelGage {
  private:
    uint8_t x = 222;
    uint8_t y = 222;
    uint32_t lastMillis = 0;
    int8_t fuel = 47; 
    bool active = true;
  public:

    uint8_t getX() {
      return x;
    }

    uint8_t getY() {
      return y;
    }

    int8_t getFuel() {
      return fuel;
    }

    void setFuel(int8_t newFuel) {
      fuel = newFuel;
    }

    void setActive(bool state) {
      active = state;
    }

    void update() {
      const uint32_t currentMillis = millis();

      if (currentMillis - lastMillis >= 740 && active) {
        if (fuel > 0) {
          fuel--;
        }
        lastMillis = currentMillis;
      }
    }

    void draw() {
      Sprites::drawOverwrite(0, 0, gage, 0);
      Sprites::drawPlusMask(0, 46 - fuel + 7, needle, 0);
    }
};

#endif

