#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#include "Body.h"
class Snake
{  
public:
    unsigned char posX, posY, maxX, maxY, minX, minY, direction, points;
    struct Body body[167];
    Snake(unsigned char posX,unsigned char posY,unsigned char maxX,unsigned char maxY,unsigned char minX,unsigned char minY, unsigned char points);
    Snake();
    //moves the object one position forwards direction
    void move();
    
    //changes direction if possible (cant go backwards)
    void turn(unsigned char direction);
    
    //checks if another object is at the same position
    bool crashes();
    bool crashes(unsigned char posX, unsigned char posY);
    //changes the position randomly inside the max-min ranges
    void randPos();
};




class Food
{
public:
    unsigned char posX, posY, maxX, maxY, minX, minY;
    Food(unsigned char posX,unsigned char posY,unsigned char maxX,unsigned char maxY,unsigned char minX,unsigned char minY);
    Food();
    void randPos();
};
