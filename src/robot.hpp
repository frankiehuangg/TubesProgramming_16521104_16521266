#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__

#include <iostream>

using namespace std;

// STRUCT/CLASS
struct Coordinate
{
    int x,y;
};

class Character
{
public:
    int healthPoint;
    int attackRange;
    int attackDamage;
    Coordinate position;

public:
    Character();
    Character(int health, int damage, int range, Coordinate pos);
    ~Character();

    Coordinate enemyDistance(Coordinate c);
    void attackEnemy(Character *enemy);
    void moveCharacter(Coordinate direction);
    void printStatus();
};


// VARIABLES
extern const int sizeX;
extern const int sizeY;
extern Coordinate U,D,L,R;


// FUNCTION
bool isValidMovement(Coordinate c1, Coordinate c2, Coordinate d);
void printDistance(Coordinate c1, Coordinate c2);
void printMap(int sizeX, int sizeY, Coordinate c1, Coordinate c2);
Coordinate randomNumber(int sizeX, int sizeY, Coordinate c);
void botAction(Character* c1, Character* c2);

#endif  //__ROBOT_HPP__
