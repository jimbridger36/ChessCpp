// InPycharmProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Universal.h"
#include "ZStuff.h"
#include <iostream>
#include "Board.h"
#include "Debug.h"
#include "StartUpFunctions.h"

bool f(int x) {
    return x + 1;
}


int main()
{   
    /*
    int a = 0;
    TEST::tClass tobj = TEST::tClass();

    std::cout << tobj.funcT(a) << std::endl;
    */

    StartUpFunctions::InitAll(1);

    //Debug::saveDistanceInfoFlatToFile();



    Board::BOARD b = Board::BOARD();

    //a = Coord((char)1, (char)2);
    //Coord b = Coord(3, 4);
    //Coord c = a + b;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
