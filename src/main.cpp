#include "Snake/Snake.h"
#include "Adafruit_SSD1306.h"
#include "MPU6050.h"
#include "AT24CX.h"

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
AT24C64 memory;
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

//prints one char at the specified coord
void printXY(int x, int y, char c){
  display.setCursor(x*6,y*8);
  display.print(c);
}
//clears one char at the specified coord
void clearChar(int x, int y, char c){
  display.setTextColor(BLACK);
  display.setCursor(x*6,y*8);
  display.print(c);
  display.setTextColor(WHITE);
}
//Resets the food's position and increases one point
void eat(){
  clearChar(food.posX,food.posY,'X');
  food.randPos();
  printXY(food.posX,food.posY,'X');
  points++;
}
// Where the player plays xD
void game(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  points=0;
  food.randPos();
  snake[0].randPos();
  printXY(food.posX,food.posY,'X');

  while(true){
    snake[0].turn(getDirection());
    for (int i = points + 1; i > 0; i--)
			snake[i] = snake[i - 1];
    snake[0].move();
    for (int i = 0; i <= points; i++)
      printXY(snake[i].posX,snake[i].posY,'0');
    clearChar(snake[points+1].posX,snake[points+1].posY,'0');
    for(int i = 0; i < points; i++)
      if(snake[i+1].crashes(snake[0]))
        return;
    if(food.crashes(snake[0]))
      eat();
    display.display();
  }
}

//Writes with the specified size and coords
void write(int textSize, int coordX, int coordY, String text){
  display.setTextColor(WHITE);
  display.setTextSize(textSize);
  display.setCursor(coordX,coordY);
  display.print(text);
  display.display();
}

void startScreen(){
  display.clearDisplay();
  write(4,4,0,"SNAKE");
  write(1,5,40,"Move 'up' to start");
  while(getDirection()!=UP);
  
}
void showScores(){
  display.clearDisplay();
  write(2,3,0,"HIGHSCORES");
  write(1,48,17,"1: ");display.print(memory.readInt(10)); 
  write(1,48,26,"2: ");display.print(memory.readInt(20));
  write(1,48,35,"3: ");display.print(memory.readInt(30)); 
  write(1,48,44,"4: ");display.print(memory.readInt(40));
  write(1,48,53,"5: ");display.print(memory.readInt(50));
  display.display(); 
  delay(5000);
}
void BubbleSort()
{   
  int temp;
  int num[6];
  for(int i = 0; i < 6; i++)
    num[i]=memory.readInt((i+1)*10);
  
  for(int i = 1; i <= 5; i++)
  {
    for (int j=0; j < 4; j++)
    {
      if (num[j+1] < num[j])     
      { 
          temp = num[j];             
          num[j] = num[j+1];
          num[j+1] = temp;            
      }
    }
  }

  for(int i = 0; i < 6; i++){
    memory.writeInt((i+1)*10,num[i]);
    Serial.println(memory.readInt((i+1)*10));
  }
  
}
void endGame(){
  display.clearDisplay();
  write(2,8,0,"GAME OVER");
  memory.writeInt(60,points);
  int fifth=memory.readInt(50);
  BubbleSort();
  write(1,0,20,(fifth==memory.readInt(50))?"YOUR SCORE ":"NEW HIGHSCORE!!!");display.print(points);display.display();

  delay(5000);
}
void loop() {
  startScreen();
  game();
  endGame();
  showScores();
}
 
void setup()   {                
  Serial.begin(9600);
  Wire.begin();
  sensor.initialize();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  snake[0]=Snake(0,0,20,7,0,0);
  food=snake[0];
}