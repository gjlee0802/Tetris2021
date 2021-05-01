#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
private:
    Matrix *currCBlk;
public:
    Matrix *iCScreen;
    Matrix *oCScreen;

    void deleteFullLines();
    
    TetrisState accept(char key);
    CTetris(int cy, int cx);
};

void init(int **setOfCBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES);