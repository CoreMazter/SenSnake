#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Snake/Snake.h"
#include "MPU6050.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

MPU6050 sensor;
Snake snake[10];
Snake food;
int points;

//Reads the accelerometer and sets direction
int getDirection(){
  int16_t ax,ay,az;
  sensor.getAcceleration(&ax, &ay, &az);

  if(ay<-5000)
    return LEFT;
  if(ay>5000)
    return RIGHT;
  if(ax<-5000)
    return UP;
  if(ax>5000)
    return DOWN;
  return 0;
}

//prints one char at the specified coord (disabled for the moment)
void printXY(int x, int y, int color){
  display.drawPixel(x,y,color);
  display.display();
}
//Resets the food's position and increases one point
void eat(){
  food.randPos();
  display.drawPixel(food.posX,food.posY,WHITE);
  points++;
}
// Where the player plays xD
void game(){
  display.clearDisplay();
  points=0;
  food.randPos();
  snake[0].randPos();
  display.drawPixel(food.posX,food.posY,WHITE);

  while(true){
    snake[0].turn(getDirection());
    for (int i = points + 1; i > 0; i--)
			snake[i] = snake[i - 1];
    snake[0].move();
    for (int i = 0; i <= points; i++)
      display.drawPixel(snake[i].posX,snake[i].posY,WHITE);
    display.drawPixel(snake[points+1].posX,snake[points+1].posY,BLACK);
    for(int i = 0; i < points; i++)
      if(snake[i+1].crashes(snake[0]))
        return;
    if(food.crashes(snake[0]))
      eat();
    display.display();
  }
}

void loop() {
  game();
}
 
void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();

  Wire.begin();
  sensor.initialize();   
  snake[0]=Snake(0,0,20,20,0,0);
  food=snake[0];
}