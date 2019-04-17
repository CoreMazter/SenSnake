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
    
    //moves the object one position forwards direction
    void move();
    
    //changes direction if possible (cant go backwards)
    void turn(int direction);
    
    //checks if another object is at the same position
    bool crashes(Snake head);
    
    //changes the position randomly inside the max-min ranges
    void randPos();
};
