#include "Tetris.h"

extern Matrix **(*setOfCBlockObjects);
extern Matrix **(*setOfBlockObjects);

extern int nBlockDegrees;
extern int nBlockTypes;

extern int iScreenDw;

void tetinit(int **setOfBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES){
    int arrayBlk_maxSize = 0;

    nBlockTypes = MAX_BLK_TYPES;
    nBlockDegrees = MAX_BLK_DEGREES;

    setOfBlockObjects = new Matrix**[nBlockTypes];
    for (int y = 0; y < nBlockTypes; y++)
        setOfBlockObjects[y] = new Matrix*[nBlockDegrees];
    for (int y = 0; y < nBlockTypes; y++)
        for (int x = 0; x < nBlockDegrees; x++)
            setOfBlockObjects[y][x] = nullptr;

    // TODO: arrayBlk_maxSize calculation
    for (int i=0; i < nBlockTypes; i++) {
        if (arrayBlk_maxSize <= sizeof(setOfBlockArrays[i][0])){
            arrayBlk_maxSize = sizeof(setOfBlockArrays[i][0]);
        }
    }
    iScreenDw = arrayBlk_maxSize;

    for (int i=0; i < nBlockTypes; i++)
    {
        for (int j=0; j < nBlockDegrees; j++){
            int *arrptr = setOfBlockArrays[i*4 + j];
            Matrix *obj;
            obj = new Matrix(arrptr, sqrt(sizeof(arrptr)/sizeof(int) - 1), sqrt(sizeof(arrptr)/sizeof(int) - 1));
            setOfBlockObjects[i][j] = obj;
        }
    }
    return;
}
    

void Tetris::deleteFullLines()
{
    return;
}

TetrisState Tetris::tetaccept(char key)
{
    TetrisState state = Running;
    
    if ((key >= '0') && (key <='6')){
        if (justStarted == false){
            std::cout << "call deleteFullLines()" << std::endl;
            //deleteFullLines();
        }
        iScreen = new Matrix(oScreen);
        idxBlockType = key-'0';
        idxBlockDegree = 0;

        currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
        top = 0;
        left = iScreenDw + (iScreenDx/2) - (currBlk->get_dx()/2);

        
        tempBlk = iScreen->clip(top, left, top+currBlk->get_dy(), left+currBlk->get_dx());
        tempBlk = tempBlk->add(currBlk);

        justStarted = false;
        std::cout << std::endl;
        if (tempBlk->anyGreaterThan(1)){
            state = Finished;
        }
        oScreen = new Matrix(iScreen);
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
        currBlk = setOfBlockObjects[idxBlockType][idxBlockDegree];
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
    int **arrayScreen2D;
    arrayScreenDx = iScreenDw * 2 + iScreenDx;
    arrayScreenDy = iScreenDy + iScreenDw;

    arrayScreen = new int[arrayScreenDy*arrayScreenDx];

    arrayScreen2D = new int*[arrayScreenDy];
    for (int y = 0; y < arrayScreenDy; y++)
        arrayScreen2D[y] = new int[arrayScreenDx];
    for (int y = 0; y < arrayScreenDy; y++)
        for (int x = 0; x < arrayScreenDx; x++)
            arrayScreen2D[y][x] = 0;


    for (int y=0; y < iScreenDy; y++){
        for (int x=0; x < iScreenDw; x++){
            arrayScreen2D[y][x] = 1;
        }
        for (int x=0; x < iScreenDx; x++){
            arrayScreen2D[y][iScreenDw + x] = 0; 
        }
        for (int x=0; x < iScreenDw; x++){
            arrayScreen2D[y][iScreenDw + iScreenDx + x] = 1 ;
        }
    }

    for (int y=0; y < iScreenDw; y++){
        for (int x=0; x < arrayScreenDx; x++){
            arrayScreen2D[iScreenDy + y][x] = 1;
        }
    }

    return arrayScreen2D;
}


Tetris::Tetris(int _iScreenDy, int _iScreenDx){
    iScreenDy = _iScreenDy;
    iScreenDx = _iScreenDx;
    idxBlockDegree = 0;
    
    int **arrayScreen2D;
    arrayScreen2D = createArrayScreen();
    
    int k = 0;
    for (int y=0; y < arrayScreenDy; y++){   
        for (int x=0; x < arrayScreenDx; x++){
            arrayScreen[k] = arrayScreen2D[y][x];
            k++;
        }
    }
    
    iScreen = new Matrix(arrayScreen, arrayScreenDy, arrayScreenDx);
    //cout << *iScreen << endl;
    oScreen = new Matrix(iScreen);
    //cout << *oScreen << endl;
    justStarted = true;
}

Tetris::~Tetris(){
    delete iScreen;
    delete oScreen;
}