#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
private:
    Matrix *currCBlk;

    Matrix *iCScreen;
public:
    Matrix *oCScreen;
    static Matrix **(*setOfCBlockObjects);

    static void init(int **setOfCBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES);

    void deleteFullLines();
    TetrisState accept(char key);
    CTetris(int cy, int cx);
    ~CTetris();
};

