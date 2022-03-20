#include <iostream>
#include "robot.hpp"

using namespace std;

int main()
{
    // constant variables
    const int sizeX = 10; // map width
    const int sizeY = 10; // map height

    // coordinates
    Coordinate U = {0,1};
    Coordinate D = {0,-1};
    Coordinate L = {-1,0};
    Coordinate R = {1,0};

    // object
    Character *Robot; Robot = new Character();
    Character *BunshinMechaKurama; BunshinMechaKurama = new Character(10,10,3,randomNumber(sizeX, sizeY,Robot->position));

    // input variables/score counting
    char actionInput, movementInput;
    int score = 0;

    cout << "Defeat as many BunshinMechaKuramas as possible!" << endl;

    while (Robot->healthPoint > 0) // run program while robot health > 0
    {
        // Robot input
        bool validAction = false;
        while (!validAction) // keep asking for input if not A/M
        {
            printMap(sizeX, sizeY, Robot->position, BunshinMechaKurama->position); // print the map

            cout << "\nAction:\na) Attack(A)\nb) Move(M)\nc) Status(S)\nPlayer input\t: "; cin >> actionInput; // ask for user input

            if (actionInput == 'A' || actionInput == 'a') // attack the enemy
            {
                Robot->attackEnemy(BunshinMechaKurama);
                system("cls");
                validAction = true;
            }
            else if (actionInput == 'M' || actionInput == 'm') // move the character
            {
                bool validInput = false;

                while (!validInput) // keep asking for movement input until valid
                {
                    cout << "\nDirection:\na) U\nb) D\nc) L\nd) R\nPlayer input\t: "; cin >> movementInput;

                    // check if X movement is not out of boundry
                    if ((movementInput == 'U' || movementInput == 'u') && isValidMovement(Robot->position, BunshinMechaKurama->position, U))
                    {
                        Robot->moveCharacter(U);
                        validInput = true;
                    }
                    else if ((movementInput == 'R' || movementInput == 'r') && isValidMovement(Robot->position, BunshinMechaKurama->position, R))
                    {
                        Robot->moveCharacter(R);
                        validInput = true;
                    }
                    else if ((movementInput == 'D' || movementInput == 'd') && isValidMovement(Robot->position, BunshinMechaKurama->position, D))
                    {
                        Robot->moveCharacter(D);
                        validInput = true;
                    }
                    else if ((movementInput == 'L' || movementInput == 'l') && isValidMovement(Robot->position, BunshinMechaKurama->position, L))
                    {
                        Robot->moveCharacter(L);
                        validInput = true;
                    }
                    else
                    {
                        cout << "Please input a valid option!" << endl;
                    }
                }
                system("cls");
                validAction = true;
            }
            else if (actionInput == 'S' || actionInput == 's') // check for robot/BMK status
            {
                cout << "Robot:" << endl;
                Robot->printStatus();
                cout << "BunshinMechaKurama:" << endl;
                BunshinMechaKurama->printStatus();
                cout << endl;
                printDistance(Robot->position, BunshinMechaKurama->position);

                cin.get();
                cin.get();
                system("cls");
            }
            else
            {
                system("cls");
                cout << "Please input a valid option!" << endl;
            }
        }

        if (BunshinMechaKurama->healthPoint <= 0) // if BMK died, destroy and make a new one
        {
            cout << "BunshinMechaKurama defeated!" << endl;
            delete BunshinMechaKurama;
            BunshinMechaKurama = new Character(10,10,3,randomNumber(sizeX, sizeY,Robot->position));
            score++;
        }
        else // attack otherwise
        {
            // BunshinMechaKurama action
            botAction(BunshinMechaKurama, Robot);
        }
    }

    cout << "Score\t: " << score << endl;

    return 0;
}
