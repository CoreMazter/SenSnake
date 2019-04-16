#include "Snake.h"

Snake::Snake(){
    posX=0; posY=0; maxX=20; maxY=20; minX=0; minY=0;
    direction=RIGHT;
}

Snake::Snake(int posX, int posY, int maxX, int maxY, int minX, int minY) {
    Snake::posX = posX;
    Snake::posY = posY;
    Snake::maxX = maxX;
    Snake::maxY = maxY;
    Snake::minX = minX;
    Snake::minY = minY;
    direction=RIGHT;
}

void Snake::move() {
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

void Snake::turn(int direction){
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
            if(Snake::direction!=UP)
                Snake::direction=direction;
            break;
    
        default:
            break;
    }
}