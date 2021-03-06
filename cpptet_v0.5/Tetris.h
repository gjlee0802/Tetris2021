#pragma once
#include "Matrix.h"
#include <cmath> //<=============

enum TetrisState { Running, NewBlock, Finished };

class Tetris {
public:
    bool justStarted;

    int iScreenDy;
    int iScreenDx;
    
    int idxBlockType;
    int idxBlockDegree;

    int *arrayScreen;
    int arrayScreenDx;
    int arrayScreenDy;

    Matrix *iScreen; 
    Matrix *oScreen;
    
    Matrix *currBlk;
    Matrix *tempBlk;
    
    int top;
    int left;

    static Matrix **(*setOfBlockObjects);

    static int nBlockDegrees;
    static int nBlockTypes;

    static int iScreenDw;

    static void init(int **setOfBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES);
    void deleteFullLines();
    TetrisState tetaccept(char key);
    int **createArrayScreen();
    Tetris(int _iScreenDy, int _iScreenDx);
    ~Tetris();
};

