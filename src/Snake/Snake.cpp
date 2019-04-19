#include "Snake.h"
#include "stdlib.h"
Snake::Snake(){
    posX=0; posY=0; maxX=20; maxY=20; minX=0; minY=0;
    direction=RIGHT;
    points=0;
}

Snake::Snake(unsigned char posX, unsigned char posY, unsigned char maxX, unsigned char maxY, unsigned char minX, unsigned char minY, unsigned char points) {
    Snake::posX = posX;
    Snake::posY = posY;
    Snake::maxX = maxX;
    Snake::maxY = maxY;
    Snake::minX = minX;
    Snake::minY = minY;
    Snake::points=points;
    direction=RIGHT;
    
}

void Snake::move() {

    for(unsigned char i=points;i>0;i--){
        body[i]=body[i-1];
    }
    body[0].posX=Snake::posX; body[0].posY=Snake::posY;

    switch (direction)
    {
    case UP:
        posY == minY ? posY = maxY : posY--;
        break;
    case DOWN:
        posY == maxY ? posY = minY : posY++;
        break;
    case RIGHT:
        posX == maxX ? posX = minX : posX++;			
        break;
    case LEFT:
        posX == minX ? posX = maxX : posX--;
        break;			
    default:
        break;
    }
}

void Snake::turn(unsigned char direction){
    if(direction==Snake::direction)
        return;
    switch (direction)
    {
        case UP:
            if(Snake::direction!=DOWN)
                Snake::direction=direction;
            break;
        case DOWN:
            if(Snake::direction!=UP)
                Snake::direction=direction;
            break;
        case LEFT:
            if(Snake::direction!=RIGHT)
                Snake::direction=direction;
            break;
        case RIGHT:
            if(Snake::direction!=LEFT)
                Snake::direction=direction;
            break;
    
        default:
            break;
    }
}

bool Snake::crashes() {
    for(unsigned char i = 0; i < points; i++)
    {
        if(body[i].posX==posX&&body[i].posY==posY)
            return true;
    }
    return false;   
}

bool Snake::crashes(unsigned char posX, unsigned char posY){
    if(Snake::posX==posX&&Snake::posY==posY)
        return true;
    return false;
}


void Snake::randPos(){
    posX=(rand() % (maxX - minX + 1)) + minX;
    posY=(rand() % (maxY - minY + 1)) + minY;    
}


Food::Food(unsigned char posX,unsigned char posY,unsigned char maxX,unsigned char maxY,unsigned char minX,unsigned char minY){
    Food::posX = posX;
    Food::posY = posY;
    Food::maxX = maxX;
    Food::maxY = maxY;
    Food::minX = minX;
    Food::minY = minY;
}
Food::Food(){}
void Food::randPos(){
    posX=(rand() % (maxX - minX + 1)) + minX;
    posY=(rand() % (maxY - minY + 1)) + minY;    
}
