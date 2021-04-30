#include "Tetris.h"

int **Tetris::createArrayScreen()
{
    arrayScreenDx = iScreenDw * 2 + iScreenDx;
    arrayScreenDy = iScreenDy + iScreenDw;
    arrayScreen = new int*[arrayScreenDy];
    for (int y = 0; y < arrayScreenDy; y++)
        arrayScreen[y] = new int[arrayScreenDx];
    for (int y = 0; y < arrayScreenDy; y++)
        for (int x = 0; x < arrayScreenDx; x++)
        arrayScreen[y][x] = 0;

}

void Tetris::Tetris(int _iScreenDy, int _iScreenDx){

    iScreenDy = _iScreenDy;
    iScreenDx = _iScreenDx;
    idxBlockDegree = 0;
    arrayScreen = createArrayScreen();
    iScreen = new Matrix(arrayScreen, , );
    oScreen = new Matrix(iScreen, , );
    justStarted = True;
}