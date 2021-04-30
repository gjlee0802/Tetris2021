#pragma once
#include "Matrix.h"

enum TetrisState { Running, NewBlock, Finished };

class Tetris {
    public:
    int nBlockDegrees;
    int nBlockTypes;
    
    int iScreenDy;
    int iScreenDx;
    int iScreenDw;
    int idxBlockDegree;
    int **arrayScreen;

    int arrayScreenDx;
    int arrayScreenDy;

    Matrix *iScreen;
    Matrix *oScreen;
    bool justStarted;

    void Tetris(int _iScreenDy, int _iScreenDx);
    int **createArrayScreen();
};
