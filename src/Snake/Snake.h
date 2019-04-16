#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
class Snake
{
public:
    int posX, posY, maxX, maxY, minX, minY, direction;
    
    Snake();
    Snake(int posX,int posY,int maxX,int maxY,int minX,int minY);

    void move();
    void turn(int direction);
};
