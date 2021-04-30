#pragma once
#include "Matrix.h"

enum TetrisState { Running, NewBlock, Finished };

class Tetris {
    public:
    int state;
    bool justStarted;


    Matrix **setOfBlockObjects = nullptr;

    int nBlockDegrees;
    int nBlockTypes;
    
    
    int iScreenDy;
    int iScreenDx;
    int iScreenDw;
    int idxBlockType;
    int idxBlockDegree;
    int **arrayScreen;

    int arrayScreenDx;
    int arrayScreenDy;

    Matrix *iScreen; 
    Matrix *oScreen;
    
    Matrix *currBlk;
    Matrix *tempBlk;
    
    int top;
    int left;
    
    void init(int * setOfBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES);
    void deleteFullLines();
    int accept(char key);
    int **createArrayScreen();
    Tetris(int _iScreenDy, int _iScreenDx);
};
