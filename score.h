#ifndef SCORE_H;
#define SCORE_H

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM zero[] = {
  4, 8,
  0x3e, 0x41, 0x41, 0x3e,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM one[] = {
  4, 8,
  0x42, 0x7f, 0x40, 0x00,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM two[] = {
  4, 8,
  0x62, 0x51, 0x49, 0x46,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM three[] = {
  4, 8,
  0x22, 0x41, 0x49, 0x36,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM four[] = {
  4, 8,
  0x18, 0x16, 0x7f, 0x10,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM five[] = {
  4, 8,
  0x4f, 0x49, 0x49, 0x31,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM six[] = {
  4, 8,
  0x3e, 0x49, 0x49, 0x30,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM seven[] = {
  4, 8,
  0x01, 0x61, 0x19, 0x07,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM eight[] = {
  4, 8,
  0x36, 0x49, 0x49, 0x36,
};

// 4x8, 1 frame(s), 4 bytes
// Example: Sprites::drawOverwrite(x, y, zero, frame);
const uint8_t PROGMEM nine[] = {
  4, 8,
  0x26, 0x49, 0x49, 0x3e,
};

// 4x8, 1 frame(s), 6 bytes
// Example: Sprites::drawOverwrite(x, y, xSym, frame);
const uint8_t PROGMEM xSym[] = {
  4, 8,
  0x1b, 0x04, 0x04, 0x1b,
};

class Score {
  private:
    uint32_t score = 0;
    uint8_t onesScore = 0;
    uint8_t tensScore = 0;
    uint8_t hundredsScore = 0;
    uint8_t thousandsScore = 0;
    uint8_t tenthousandsScore = 0;
    boolean tensVis = false;
    boolean hundredsVis = false;
    boolean thousandsVis = false;
    boolean tenthousandsVis = false;
  
  public:
    void resetScore() {
      score = 0;
      onesScore = 0;
      tensScore = 0;
      hundredsScore = 0;
      thousandsScore = 0;
      tenthousandsScore = 0;
      tensVis = false;
      hundredsVis = false;
      thousandsVis = false;
      tenthousandsVis = false;
    }

    void incScore(int8_t points) {
      score += points;

      tenthousandsScore = score / 10000;
      thousandsScore = (score / 1000) % 10;
      hundredsScore = (score / 100) % 10;
      tensScore = (score / 10) % 10;
      onesScore = (score / 1) % 10;
    }

    const uint8_t* getSprite(uint8_t number) {
      switch(number) {
        case 0:
          return zero;
          break;
        case 1:
          return one;
          break;
        case 2:
          return two;
          break;
        case 3:
          return three;
          break;
        case 4:
          return four;
          break;
        case 5:
          return five;
          break;
        case 6:
          return six;
          break;
        case 7:
          return seven;
          break;
        case 8:
          return eight;
          break;
        case 9:
          return nine;
          break;
      }
    }

    void draw(uint8_t lives) {
      uint8_t onesY = 56, tensY = 48, hundredsY = 40, thousandsY = 32, tenthousandsY = 24;
      
      // Check what digits to display
      if (score > 9) {
        tensVis = true;
      } 
      if (score > 99) {
        hundredsVis = true;
      }
      if (score > 999) {
        thousandsVis = true;
      }
      if (score > 9999) {
        tenthousandsVis = true;
      }

      Sprites::drawOverwrite(123, onesY, getSprite(onesScore), 0);
      if (tensVis) {Sprites::drawOverwrite(123, tensY, getSprite(tensScore), 0);}
      if (hundredsVis) {Sprites::drawOverwrite(123, hundredsY, getSprite(hundredsScore), 0);}
      if (thousandsVis) {Sprites::drawOverwrite(123, thousandsY, getSprite(thousandsScore), 0);}
      if (tenthousandsVis) {Sprites::drawOverwrite(123, tenthousandsY, getSprite(tenthousandsScore), 0);}

      Sprites::drawOverwrite(123, 1, xSym, 0);
      if (lives > 0 && lives < 9) {
        Sprites::drawOverwrite(123, 7, getSprite(lives), 0);
      } else {
        Sprites::drawOverwrite(123, 7, getSprite(9), 0);
      }
    }

    int32_t getScore() {
      return score;
    }


};

#endif