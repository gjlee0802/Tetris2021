#include "Tetris.h"

void Tetris::init(int * setOfBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES){
    return;
}
    

void Tetris::deleteFullLines()
{
    return;
}

int Tetris::accept(char key)
{
    state = Running;
    
    if ((key >= '0') && (key <='6')){
        if (justStarted == false){
            std::cout << "call deleteFullLines()" << std::endl;
            //deleteFullLines();
        }
        iScreen = new Matrix(oScreen);  //<============
        idxBlockType = (int)key;
        idxBlockDegree = 0;
        
        //currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
        top = 0;
        left = iScreenDw + (int)(iScreenDx/2) - (int)(currBlk->get_dx()/2);
        tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
        tempBlk = tempBlk->add(currBlk);
        justStarted = false;
        std::cout << std::endl;
        if (tempBlk->anyGreaterThan(1)){
            state = Finished;
        }
        oScreen = new Matrix(iScreen);  //<============
        return state;
    }
    else if (key == 'q'){
        // pass
    }
    else if (key == 'a'){
        left--;
    }
    else if (key == 'd'){
        left++;
    }
    else if (key == 's'){
        top++;
    }
    else if (key == 'w'){
        idxBlockDegree = (idxBlockDegree + 1) % nBlockDegrees;
        //currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
    }
    else if (key == ' '){
        while (!tempBlk->anyGreaterThan(1)){
            top++;
            tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left + currBlk->get_dx());
            tempBlk = tempBlk->add(currBlk);
        }
    }
    else{
        std::cout << "Wrong key!" << std::endl;
    }

    tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
    tempBlk = tempBlk->add(currBlk);

    if (tempBlk->anyGreaterThan(1)){
        std::cout << "Wall Collision Detected!" << std::endl;
    }

    return state;
}

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

    for (int y=0; y < iScreenDy; y++){
        for (int x=0; x < iScreenDw; x++){
            arrayScreen[y][x] = 1;
        }
        for (int x=0; x < iScreenDx; x++){
            arrayScreen[y][iScreenDw + x] = 0; 
        }
        for (int x=0; x < iScreenDw; x++){
            arrayScreen[y][iScreenDw + iScreenDx + x] = 1 ;
        }
    }

    for (int y=0; y < iScreenDw; y++){
        for (int x=0; x < arrayScreenDx; x++){
            arrayScreen[iScreenDy + y][x] = 1;
        }
    }

    return arrayScreen;
}

Tetris::Tetris(int _iScreenDy, int _iScreenDx){

    iScreenDy = _iScreenDy;
    iScreenDx = _iScreenDx;
    idxBlockDegree = 0;
    arrayScreen = createArrayScreen();
    iScreen = new Matrix((int*)arrayScreen, iScreenDy, iScreenDx);
    oScreen = new Matrix(iScreen);
    justStarted = true;
}