#include <iostream>
#include "robot.hpp"

using namespace std;

int main()
{
    // Variable declarations
    const int sizeX = 10;
    const int sizeY = 10;
    Coordinate U = {0,1};
    Coordinate D = {0,-1};
    Coordinate L = {-1,0};
    Coordinate R = {1,0};

    Character *Robot; Robot = new Character();
    Character *BunshinMechaKurama; BunshinMechaKurama = new Character(10,10,5,randomNumber(sizeX, sizeY,Robot->position));

    char actionInput, movementInput;
    int score = 0;

    cout << "Defeat as many BunshinMechaKuramas as possible!" << endl;

    while (Robot->healthPoint > 0)
    {
        printMap(sizeX, sizeY, Robot->position, BunshinMechaKurama->position);

        cout << "\nAction:\na) Attack(A)\nb) Move(M)\nc) Status(S)\nPlayer input\t: "; cin >> actionInput;

        if (BunshinMechaKurama->healthPoint <= 0)
        {
            delete BunshinMechaKurama;
            BunshinMechaKurama = new Character(10,10,5,randomNumber(sizeX, sizeY,Robot->position));
            score++;
        }

        // BunshinMechaKurama action
        botAction(BunshinMechaKurama, Robot);

        // Robot input
        if (actionInput == 'A' || actionInput == 'a')
        {
            Robot->attackEnemy(BunshinMechaKurama);
            system("cls");
        }
        else if (actionInput == 'M' || actionInput == 'm')
        {
            bool validInput = false;

            while (!validInput)
            {
                cout << "\nDirection:\na) U\nb) D\nc) L\nd) R\nPlayer input\t: "; cin >> movementInput;
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
        }
        else if (actionInput == 'S' || actionInput == 's')
        {
            Robot->printStatus();
            BunshinMechaKurama->printStatus();
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

    cout << "Score\t: " << score << endl;

    return 0;
}
