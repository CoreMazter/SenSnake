#include <Arduino.h>
#include "Snake.h"

Snake snake[100];
Snake food;
int points;
void setup() {
  // put your setup code here, to run once:
  snake[0]=Snake(0,0,20,20,0,0);
  food=snake[0];
}

void loop() {
  // put your main code here, to run repeatedly:
  game();
  endGame();
  showHighscores();
}

void game(){
  points=0;
  food.randPos();
  snake[0].randPos();
  printXY(food.posX,food.posY,'x');
  while(true){
    snake[0].turn(getDirection());
    for (int i = points + 1; i > 0; i--)
			snake[i] = snake[i - 1];
    snake[0].move();
    for (int i = 0; i <= points; i++)
      printXY(snake[i].posX,snake[i].posY,'0');
    printXY(snake[points+1].posX,snake[points+1].posY,' ');
    for(int i = 0; i < points; i++)
      if(snake[i+1].crashes(snake[0]))
        return;
    if(food.crashes(snake[0]))
      eat();
    delay(getSpeed());
  }
}

void eat(){
  food.randPos();
  printXY(food.posX,food.posY,'x');
  points++;
}
int getDirection();
int getSpeed();
void printXY(int x, int y, char c);
void showHighscores();
void endGame();