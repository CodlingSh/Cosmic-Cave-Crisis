#ifndef FUELPAD_H
#define FUELPAD_H

// 14x8, 1 frame(s), 16 bytes
// Example: Sprites::drawOverwrite(x, y, pad, frame);
const uint8_t PROGMEM pad[] = {
  14, 8,
  0xff, 0x81, 0x81, 0x81, 0xff, 0xff, 0xff, 0x81, 0x81, 0x81, 0xff, 0x7e,
  0x3c, 0x18,
};

class FuelPad {
  private:
    int16_t x = 222;
    uint8_t y = 222;
    uint8_t width = 14;
    uint8_t height = 8;
    //const uint8_t *spr = nullox;
    uint8_t highest = 0;
    uint8_t lowest = 0;
    bool active = false;
    bool moving = false;
    bool dying = false;
    int8_t deathTimer = 0;

  public:

    bool isActive() {
      return active;
    }

    void setX(uint8_t newX) {
      x = newX;
    }

    uint8_t getX() {
      return x;
    }

    void spawn(uint8_t newH, uint8_t newL, uint8_t newX) {
      x = newX;
      y = random(newH, newL - height);
      highest = newH;
      lowest = newL;
      active = true;
      moving = false;
    }

    void update() {
      if (!active) {
        return;
      }

      if (x >= -10) {
        x = 222;
        y = 222;
        active = false;
      }

      
    }

    void draw() {
      if (!active) {
        return;
      }

      Sprites::drawOverwrite(x, y, pad, 0);
    }
};

#endif