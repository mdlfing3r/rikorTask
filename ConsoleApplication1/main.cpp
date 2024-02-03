#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <stdlib.h>

#define ROW_AMOUNT 8192
#define COLUMN_AMOUNT 8192
#define DENOMINATOR 2
#define maxVALUE 8388608
#define VECTOR_CASE

//геом прогрессия: Bi = b1*q^(i-1)

typedef struct Coordinate {
    uint16_t Xpos;
    uint16_t Ypos;
} Coordinate;



uint64_t numResolver(uint64_t FirstNum, uint64_t numPos) {
    uint64_t retval;

    if (!numPos)
        retval = FirstNum;
    else {
        if (FirstNum != 0)
            retval = FirstNum * (std::pow(DENOMINATOR, numPos - 1));
        else 
            retval = 0;
    }
    return retval;
};



void Generator()
{

    std::vector<uint64_t> Arr;


    //for (auto it = 0; it < ROW_AMOUNT; it++) LogicArr.push_back(0);
    //for (auto it = 0; it < COLUMN_AMOUNT-1; it++) arr.push_back(LogicArr);


    uint64_t beginNumber,
             tempval = 0;


    for (auto row = 0; row < COLUMN_AMOUNT; row++) { //строка

        beginNumber = row + 2;
        *&tempval = 0;

        for (auto column = 0; column < ROW_AMOUNT; column++) { //столбец

            if (tempval > maxVALUE) beginNumber = row;

            *&tempval = numResolver(beginNumber, column);

            Arr.push_back(*&tempval);

        }
       
    }
}

bool Finder(uint64_t F1, uint64_t F2, uint64_t F3, Coordinate Position) {
    
}


int main() {
    Generator();
    Finder()

    return 0;
}