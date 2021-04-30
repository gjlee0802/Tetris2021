#pragma once
#include "Tetris.h"

class CTetris : public Tetris {
private:
    Matrix **setOfCBlockObjects = nullptr;

public:
    void init(int * setOfCBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES);
    
    CTetris();
};
