#include <iostream>
#include <cstdlib>
#include <time.h>
#include "robot.hpp"

using namespace std;

// Default constructor
Character::Character()
{
    this->healthPoint = 100;
    this->attackDamage = 10;
    this->attackRange = 5;
    this->position = {0,0};
}

// Parameterized constructor
Character::Character(int health, int damage, int range, Coordinate pos)
{
    this->healthPoint = health;
    this->attackDamage = damage;
    this->attackRange = range;
    this->position = pos;
}

// Destructor
Character::~Character() {}

// enemyDistance(enemy) is an object function, returns the (x,y) distance (struct) of an object to another object
Coordinate Character::enemyDistance(Coordinate c)
{
    int xCoord, yCoord;

    if ((this->position.x-c.x) >= 0)
        xCoord = this->position.x-c.x;
    else
        xCoord = c.x-this->position.x;

    if ((this->position.y-c.y) >= 0)
        yCoord = this->position.y-c.y;
    else
        yCoord = c.y-this->position.y;

    return {xCoord, yCoord};
}

// attackEnemy(enemy) is a void object function, reduce enemy HP depending on the distance
void Character::attackEnemy(Character* enemy)
{
    if ((enemyDistance(enemy->position).x+enemyDistance(enemy->position).y) <= this->attackRange)
    {
        enemy->healthPoint -= attackDamage;
        cout << "Enemy received " << attackDamage << " damage!" << endl;
    }

    else
    {
        cout << "Attack missed!" << endl;
    }
}

// moveCharacter(direction) is a void object function, change the object position based on the user input
void Character::moveCharacter(Coordinate direction)
{
    this->position.x += direction.x;
    this->position.y += direction.y;
}

// printStatus() is a void object function, print the object status
void Character::printStatus()
{
    cout << "HP\t: " << healthPoint << endl;
    cout << "Damage\t: " << attackDamage << endl;
    cout << "Range\t: " << attackRange << endl;
    cout << "Pos\t: (" << position.x << ',' << position.y << ')' << endl;
}


// Global function
// printDistance is a void function, print the distance between 2 objects
bool isValidMovement(Coordinate c1, Coordinate c2, Coordinate d)
{
    if (c1.x+d.x == c2.x && c1.y+d.y == c2.y)
        return false;
    if (c1.x+d.x >= 0 && c1.y+d.y >= 0)
        return true;
    return false;
}

// print the distance of robot and BMK
void printDistance(Coordinate c1, Coordinate c2)
{
    cout << "Dist\t: (" << abs(c1.x-c2.x) << ',' << abs(c1.y-c2.y) << ')' << endl;
}

// printMap is a void function, print the current map
void printMap(int sizeX, int sizeY, Coordinate c1, Coordinate c2)
{
    for (int i=sizeX-1; i>=0; i--)
    {
        for (int j=0; j<sizeY; j++)
        {
            if (i == c1.y && j == c1.x)
                cout << 'R';
            else if (i == c2.y && j == c2.x)
                cout << 'K';
            else
                cout << '.';
        }
        cout << endl;
    }
}

// generate random number for bot spawn point
Coordinate randomNumber(int sizeX, int sizeY, Coordinate c)
{
    srand((unsigned) time(NULL));

    int x = rand() % sizeX, y = rand() % sizeY;
    if (x == c.x && y == c.y)
        return randomNumber(sizeX, sizeY, c);

    return {x,y};
}

// BunshinMechaKurama AI
void botAction(Character* c1, Character* c2)
{
    if (c1->enemyDistance(c2->position).x + c1->enemyDistance(c2->position).y <= c1->attackRange) // Attack if in range
    {
        c1 -> attackEnemy(c2);
        cout << "BunshinMechaKurama has dealt " << c1->attackDamage << " damage!" << endl;
    }
    else // otherwise move
    {
        if (c1->position.x == c2->position.x) // move vertically if on the same x
        {
            if (c1->position.y > c2->position.y) // go down if higher
                c1->moveCharacter({0,-1});
            else // go up if lower
                c1->moveCharacter({0,1});
        }
        else if (c1->position.y == c2->position.y) // move horizontally if on the same y
        {
            if (c1->position.x > c2->position.x) // go left if right-er
                c1->moveCharacter({-1,0});
            else // go right if left-er
                c1->moveCharacter({1,0});
        }
        else // otherwise
        {
            if (c1->enemyDistance(c2->position).x <= c1->enemyDistance(c2->position).y) // if x distance <= y distance
            {
                if (c1->position.y > c2->position.y) // go left if right-er
                    c1->moveCharacter({0,-1});
                else // go right if lefter
                    c1->moveCharacter({0,1});
            }
            else // if y distance > x distance
            {
                if (c1->position.x > c2->position.x) // go down if higher
                    c1->moveCharacter({-1,0});
                else // go up if lower
                    c1->moveCharacter({1,0});
            }
        }
    }
}
