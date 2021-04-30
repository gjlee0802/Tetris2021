#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
private:
    int **setOfCBlockObjects = 0;

public:
    void init(setOfCBlockArrays, MAX_BLK_TYPES, MAX_BLK_DEGREES);
    
    CTetris();
};
