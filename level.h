#ifndef LEVEL_H
#define LEVEL_H

#include <Arduboy2.h>
#include "enemy.h"
#include "fuelPad.h"

const uint8_t PROGMEM opening[254][2] = {
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, 
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64},
  {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64}, {0, 64},
  {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, {21, 22}, 
  {21, 22}, {21, 22}, {18, 28}, {15, 34}, {12, 40}, {9, 46}, {6, 52}, {3, 58}, {1, 62}, {1, 62}, {1, 62}, {1, 62}, {2, 59}, {3, 57}, {2, 58}, {2, 59}, {3, 58}, {2, 59}, {3, 59}, {2, 59}, 
  {1, 61}, {1, 60}, {1, 61}, {1, 61}, {2, 59}, {1, 59}, {2, 59}, {1, 59}, {1, 59}, {2, 59}, {3, 59}, {3, 59}, {3, 58}, {3, 59}, {2, 59}, {1, 59}, {2, 58}, {1, 60}, {2, 58}, {1, 60}, 
  {2, 59}, {3, 57}, {3, 58}, {3, 59}, {3, 58}, {3, 57}, {2, 58}, {3, 58}, {2, 60}, {2, 60}, {1, 60}, {2, 58}, {3, 58}, {2, 59}, {3, 57}, {3, 58}, {2, 59}, {1, 60}, {2, 60}, {1, 60}, 
  {2, 60}, {2, 60}, {1, 61}, {1, 61}, {2, 60}, {2, 59}, {2, 59}, {1, 60}, {1, 59}, {1, 60}, {2, 60}, {3, 59}, {3, 58}, {3, 59}, {3, 59}, {3, 58}, {3, 58}, {3, 59}, {2, 60}, {3, 58}, 
  {3, 58}, {3, 59}, {3, 59}, {2, 60}, {1, 60}, {2, 59}, {1, 61}, {2, 59}, {1, 60}, {2, 60}, {1, 60}, {1, 59}, {1, 59}, {2, 58}, {2, 58}, {3, 57}, {3, 57}, {3, 57}, {3, 58}, {3, 57}, 
  {3, 58}, {3, 59}, {3, 59}, {2, 60}, {2, 59}, {3, 59}, {3, 59}, {2, 59}, {1, 61}, {1, 61}, {1, 61}, {1, 60}, {1, 61}, {1, 61}, {1, 60}, {2, 60}, {1, 60}, {1, 61}, {1, 61}, {1, 60}, 
  {1, 61}, {1, 61}, {2, 60}, {1, 60}, {2, 58}, {1, 60}, {2, 59}, {2, 58}, {2, 58}, {1, 59}, {1, 60}, {2, 59}, {2, 60}, {1, 61}, {1, 61}, {2, 60}, {1, 61}, {1, 60}, {2, 59}, {3, 57}, 
  {2, 58}, {2, 59}, {3, 57}, {2, 58}, {1, 59}, {1, 59}, {1, 60}, {1, 60}, {1, 61}, {2, 60}, {3, 58}, {3, 59}, {3, 59}, {3, 58}, {2, 60}, {2, 60}, {1, 61}, {1, 61}, {1, 60}, {1, 61}, 
  {1, 61}, {1, 61}, {2, 60}, {1, 61}, {1, 60}, {2, 58}, {3, 57}, {3, 58}, {3, 58}, {3, 59}, {2, 60}, {3, 58}, {3, 57}, {2, 59}, {1, 61}, {1, 61}
};

struct HighAndLow {
  uint8_t high;
  uint8_t low;
}; 

class Level {
  private:
    Arduboy2 *ab;
    Enemy *enemies;
    FuelPad *fuelPads;
    bool scrolling = true;
    uint8_t lines[254][2];
    uint8_t sectsCompleted = 0;
    uint8_t lineCount = 0;
    uint8_t speed = 2;
    uint8_t speedCount = 4;
    int8_t topHeight = 1;
    int8_t bottomHeight = 1;
    uint8_t mood = 0;
    uint8_t maxEnemies = 17;
    uint8_t maxFuelPads = 4;

  public:
    Level(Arduboy2 *abPtr, Enemy *enem, FuelPad *fp) : ab(abPtr), enemies(enem), fuelPads(fp) {
      memcpy_P(lines, opening, sizeof(lines));
    }

    void setScrolling(bool newScroll) {
      scrolling = newScroll;
    }

    void generateLevel() {
      const int8_t values[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
      int8_t offset = 0;
      int8_t length = 0;

      for (uint8_t i = 127; i < 254; i++) {
        topHeight += values[random(8)];
        bottomHeight += values[random(8)];

        if (topHeight <= 0) {
          topHeight = 1;
        }

        if (bottomHeight <= 0) {
          bottomHeight = 1;
        }

        if (topHeight >= 4) {
          topHeight = 3;
        }

        if (bottomHeight >= 4) {
          bottomHeight = 3;
        }

        offset = topHeight;
        length = 63 - (topHeight + bottomHeight);
        
        lines[i][0] = offset;
        lines[i][1] = length;
      }

      spawnEnemies();
    }

    void spawnEnemies() {
      HighAndLow bounds;
      uint8_t *placements;
      uint8_t totalEnemies = 3;
      uint8_t totalFuel = 1;

      for (uint8_t i = maxEnemies; i > 0; i--) {
        
      }

      placements = shuffledNumbers();

      for (uint8_t i = 0; i < totalEnemies; i++) {
        for (uint8_t j = 0; j < maxEnemies; j++) {
          if (!enemies[j].isActive()) {
            bounds = getHighAndLow(128 + (16 * placements[i]), enemies[j].getWidth());
            enemies[j].spawn(bounds.high, bounds.low, 128 + (16 * placements[i]));

            break;
          }
        }
      }

      for (uint8_t i = 0; i < 4; i++) {
        if (!fuelPads[i].isActive()) {
          bounds = getHighAndLow(128 + (16 * placements[i]), fuelPads[i].getWidth());
          fuelPads[i].spawn(bounds.high, bounds.low, 128 + (16 * placements[totalEnemies]));
          break;
        }

      }
    }

    uint8_t* shuffledNumbers() {
      static uint8_t numbers[8] = {0, 1, 2, 3, 4, 7, 6, 5};
      uint8_t firstNum;
      uint8_t secondNum;
      uint8_t newPlace;

      for (uint8_t i = 0; i < 7; ++i) {
        newPlace = random(i, 8);
        firstNum = numbers[i];
        secondNum = numbers[newPlace];

        numbers[i] = secondNum;
        numbers[newPlace] = firstNum;
      }
      
      for (uint8_t i = 0; i < 7; ++i) {
        Serial.print(numbers[i]);
        Serial.print(" ");
      }
      Serial.println("");
      Serial.println("");
      return numbers;
    } 

    void drawBufferLine(uint8_t offset, uint8_t height, uint8_t x) {
      uint8_t *buffer = ab->getBuffer();
      uint8_t line1end = offset;
      uint8_t line2start = offset + height;

      // // Drawing the top lines
      int8_t toDraw1 = offset / 8 - 1;
      uint8_t excess1 = offset % 8;

      if (toDraw1 >= 0) {
        for (uint8_t i = 0; i <= toDraw1; i++) {
          buffer[x + i * 128] = 0b11111111;
        }
      }

      if (excess1 > 0) {
        buffer[x + (toDraw1 + 1) * 128] = determineExcess(excess1, false);
      }

      // // Drawing the bottom lines
      int8_t toDraw2 = line2start / 8;
      uint8_t excess2 = line2start % 8;

      if (toDraw2 >= 0) {
        for (uint8_t i = toDraw2; i < 8; i++) {
          buffer[x + i * 128] = 0b11111111;
        }
      }

      if (excess2 > 0) {
        buffer[x + toDraw2 * 128] = determineExcess(excess2, true);
      }
    }

    uint8_t determineExcess(uint8_t num, bool flipped) {
      uint8_t byte = 0;
      
      if (num == 0) {
        return 0b00000000;  
      }

      byte = 0b11111111 >> (8 - num);

      if (flipped) {
        byte ^= 0b11111111;
      }

      return byte;
    }

    void scrollLevel() {
      for (uint8_t i = 0; i < 253; i++) {
        lines[i][0] = lines[i + 1][0];
        lines[i][1] = lines[i + 1][1];
      }
    }

    void scrollEnemies() {
      for (uint8_t i = 0; i < maxEnemies; i++) {
        if (enemies[i].isActive()) {
          enemies[i].setX(enemies[i].getX() - 1);
        }
      }
    }

    void scrollFuelPads() {
      for (uint8_t i = 0; i < maxFuelPads; i++) {
        if (fuelPads[i].isActive()) {
          fuelPads[i].setX(fuelPads[i].getX() - 1);
        }
      }
    }

    HighAndLow getHighAndLow(uint8_t line, uint8_t width) {
      HighAndLow result;
      uint8_t tempHigh = 0;
      uint8_t tempLow = 64;

      for (uint8_t i = 0; i < width; i++) {
        if (lines[line + i][0] > tempHigh) {
          tempHigh = lines[line + i][0];
        }
        if (lines[line + i][0] + lines[line + i][1] < tempLow) {
          tempLow = lines[line + i][0] + lines[line + i][1];
        }
      }
      
      result.high = tempHigh;
      result.low = tempLow;

      return result;
    }

    void update() {

      if (scrolling){
        if (ab->pressed(LEFT_BUTTON) || ab->pressed(B_BUTTON)) {
          speedCount = 6;
        } else if (ab->pressed(RIGHT_BUTTON)) {
          speedCount = 1;
        } else {
          speedCount = 2;
        }

        speed -= 1;

        if (speed == 0) {
          // if (lineCount % 14 == 0) {
          //   spawnEnemy();
          // }
          scrollLevel();
          scrollEnemies();
          scrollFuelPads();
          lineCount++;
          speed = speedCount;
        }
      }

      if (lineCount >= 128) {
        generateLevel();
        lineCount = 0;
      }

      for (uint8_t i = 0; i < maxEnemies; i++) {
        if (enemies[i].isActive()) {
          enemies[i].update();
        }
      }
    }

    void draw() {
      // ab->drawFastHLine(0, 0, 128, WHITE);
      // ab->drawFastHLine(0, 63, 128, WHITE);

      for (uint8_t i = 0; i < 127; i++) {
        drawBufferLine(lines[i][0], lines[i][1], i);
      }

      for (uint8_t i = 0; i < maxEnemies; i++) {
        if (enemies[i].isActive()) {
          enemies[i].draw();
        }
      }

      for (uint8_t i = 0; i < maxFuelPads; i++) {
        if (fuelPads[i].isActive()) {
          fuelPads[i].draw();
        }
      }

      // ab->setCursor(90, 0);
      // ab->println(lineCount);

      uint8_t activeCount = 0;

      for (uint8_t i = 0; i < maxEnemies; i++) {
        if (enemies[i].isActive()) {
          activeCount++;
        }
      }

      ab->setCursor(70, 0);
      ab->print("E:");
      ab->print(activeCount);
    }
};

#endif