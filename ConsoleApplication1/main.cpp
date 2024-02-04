#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#define ROW_AMOUNT 8192
#define COLUMN_AMOUNT 8192
#define DENOMINATOR 2
#define maxVALUE 8388608
#define VECTOR_CASE

#define F2_MAX (8192 << 13)
#define F3_OFFSET (8192 << 1)

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



std::vector<uint64_t> Generator()
{
    std::vector<uint64_t> Arr;
    std::vector<std::vector<uint64_t>> ArrList;

    uint64_t beginNumber,
             tempval = 0;


    for (auto row = 0; row < COLUMN_AMOUNT; row++) { //строка

        beginNumber = row + 2;
        *&tempval = 0;

        for (auto column = 0; column < ROW_AMOUNT; column++) { //столбец

            if (tempval > maxVALUE) beginNumber = row; //если следовать ТЗ п. 4) то начальное значение вообще не будет меняться   
            *&tempval = numResolver(beginNumber, column);

            Arr.push_back(*&tempval);

        }      
    }
    return Arr;
}


bool Finder(std::vector<uint64_t> array, uint64_t F1, uint64_t F2, uint64_t F3, Coordinate &Position) {

    std::vector<uint64_t>::iterator iter = array.begin();

    while ((iter = std::find(iter, array.end(), F2)) != array.end())
    {
        if (iter >= (array.begin() + F2_MAX)) return 0;

        if (*(iter + 8192) == F1) {
            if (*(iter + F3_OFFSET) == F3) {
                Position.Ypos = ((iter - array.begin()) >> 13);
                Position.Xpos = iter - array.begin();
                while (Position.Xpos > 8192) {
                    *&Position.Xpos = (iter - array.begin()) - 8192;
                }
                return 1;
            }
        }
        

        iter++;
    }

    return 1;//недостижимое условие
}


int main() {
    Coordinate coord;

    if (Finder(Generator(), 128, 64, 256, coord))
        std::cout << "X = " << coord.Xpos << " Y = " << coord.Ypos;
    else
        std::cout << "can`t resolve coordinate";

    
    return 0;
}