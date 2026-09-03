#include <Arduboy2.h>
#include "player.h"
#include "bullet.h"
#include "level.h"
#include "fuelGage.h"
#include "enemy.h"
#include "score.h"
#include "fuelPad.h"

Arduboy2 ab;
Player player(&ab);
Enemy enemies[17](&player);
FuelPad fuelPads[5];
FuelGage fuelGage;
Level level(&ab, enemies, fuelPads);
Score score;
int8_t lives = 3;
uint8_t gameState = 0;

void setup() {
  ab.begin();
  ab.setFrameRate(60);
  ab.initRandomSeed();

  lives = 3;
  
  Serial.begin(9600);
}

void loop() {
  if (!ab.nextFrame()) return;

  ab.pollButtons();
  ab.clear();

  switch(gameState) {
    case 0:
      titleScreen();
      break;
    case 1:
      mainGameLoop();
      break;
  }
  
  ab.display();
}

void titleScreen() {
  ab.println("THIS IS A TITLE");
  ab.println("");
  ab.println("");
  ab.println("Press a button");

  if (ab.justPressed(A_BUTTON) || ab.justPressed(B_BUTTON)) {
        ab.initRandomSeed();
        gameState = 1;
  }
}

void mainGameLoop() {
  level.update();
  player.update();
  fuelGage.update();

  

  for (uint8_t enemy = 0; enemy < 17; enemy++) {
    if (enemyHit(player.getBullet(), enemies[enemy])) {
      enemies[enemy].die();
      player.getBullet().respawn();
      score.incScore(25);
    }
    if (playerHit(player, enemies[enemy])) {
      if (!player.isDying()) {
        level.setScrolling(false);
        player.die();
        enemies[enemy].die();
        fuelGage.setActive(false);
        lives--;
      }
    }
  }

  for (uint8_t fuelPad = 0; fuelPad < 5; fuelPad++) {
    if (!playerHit(player, fuelPads[fuelPad]) && !player.isDying()) {
      fuelGage.setActive(true);
    }
  }

  for (uint8_t fuelPad = 0; fuelPad < 5; fuelPad++) {
    if (playerHit(player, fuelPads[fuelPad])) {
      fuelGage.setActive(false);
      if (fuelGage.getCoolDown() <= 0) {
        fuelGage.setFuel(fuelGage.getFuel() + 1);
        fuelGage.setCoolDown(12);
      }
      else {
        fuelGage.setCoolDown(fuelGage.getCoolDown() - 1);
      }
    }
  }

  if (fuelGage.getFuel() <= 0) {
    if (!player.isDying()) {
        level.setScrolling(false);
        player.die();
        fuelGage.setActive(false);
        lives--;
      }
  }

  level.draw();
  player.draw();

  
  // ab.fillRect(106, 0, 24, 64, BLACK);
  // ab.drawBitmap(106, 0, gage, 22, 64, BLACK);
  fuelGage.draw();
  ab.fillRect(121, 0, 7, 64, BLACK);
  ab.drawFastVLine(121, 0, 64, WHITE);

  score.draw(lives);

  // ab.setCursor(10, 0);
  // ab.print(ab.cpuLoad());
  // ab.setCursor(25, 0);
  // ab.print(fuelGage.getFuel());
  // ab.print(fuelGage.getFuel());

}

bool enemyHit(Bullet &blt, Enemy &nme) {
  if (
    blt.getX() + 3 >= nme.getX() &&
    blt.getX() <= nme.getX() + nme.getWidth() &&
    blt.getY() >= nme.getY() &&
    blt.getY() <= nme.getY() + nme.getHeight()
  ) {
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool playerHit (Player &plr, T &nme) {
  if (
    plr.getX() + 8 >= nme.getX() &&
    plr.getX() <= nme.getX() + nme.getWidth() &&
    plr.getY() + 8 >= nme.getY() &&
    plr.getY() <= nme.getY() + nme.getHeight() &&
    !nme.isDying()
  ) {
    return true;
  } else {
    return false;
  }
}
