#include "CTetris.h"

void CTetris::init(int * setOfCBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES){
    int i = 0; int j = 0;
    
    Tetris.init(setOfCBlockArrays, MAX_BLK_TYPES, MAX_BLK_DEGREES);
    
    /*
    setOfCBlockObjects = (int **)malloc(sizeof(int*) * Tetris.nBlockTypes); 
    for(i=0; i<Tetris.nBlockTypes; i++)
    {
        setOfCBlockObjects[i] = (int *)malloc(sizeof(int)*Tetris.nBlockDegrees);
    }
    */
    setOfCBlockObjects = new int*[Tetris.nBlockTypes];
    for (int y = 0; y < Tetris.nBlockTypes; y++)
        setOfCBlockObjects[y] = new int[Tetris.nBlockDegrees];
    for (int y = 0; y < Tetris.nBlockTypes; y++)
        for (int x = 0; x < Tetris.nBlockDegrees; x++)
        setOfCBlockObjects[y][x] = 0;

    for (i=0; i < Tetris.nBlockTypes; i++)
    {
        for (j=0; j < Tetris.nBlockDegrees; j++){
            int *arrptr = setOfCBlockArrays[i][j];

            Matrix obj(setOfCBlockArrays[i][j], , );
        }
    }

    return;
}

void CTetris::CTetris(){
    arrayScreen = createArrayScreen();
}