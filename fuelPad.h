#ifndef FUELPAD_H
#define FUELPAD_H

// 17x8, 1 frame(s), 36 bytes
// Example: Sprites::drawPlusMask(x, y, fuelpad, frame);
const uint8_t PROGMEM fuelpad[] = {
  17, 8,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0x81, 0xff, 0x81, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0x81, 0xff, 0x81, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x7e, 0x7e, 0x3c, 0x3c, 0x18, 0x18,
};

class FuelPad {
  private:
    int16_t x = 222;
    uint8_t y = 222;
    uint8_t width = 17;
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

    void setX(int16_t newX) {
      x = newX;
    }

    int16_t getX() {
      return x;
    }

    uint8_t getY() {
      return y;
    }

    uint8_t getWidth() {
      return width;
    }

    uint8_t getHeight() {
      return height;
    }

    bool isDying() {
      return dying;
    }

    void spawn(uint8_t newH, uint8_t newL, int16_t newX) {
      x = newX;
      y = random(newH, newL - height);
      highest = newH;
      lowest = newL;
      active = true;
      moving = false;
    }

    void despawn() {
      x = 222;
      y = 222;
      active = false;
    }

    void update() {
      if (!active) {
        return;
      }

      if (x <= -10) {
        x = 222;
        y = 222;
        active = false;
      }

      
    }

    void draw() {
      if (!active) {
        return;
      }

      Sprites::drawPlusMask(x, y, fuelpad, 0);
    }
};

#endif