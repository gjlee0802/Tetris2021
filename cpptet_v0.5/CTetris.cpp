#include "CTetris.h"

extern Matrix **(*setOfCBlockObjects);
extern Matrix **(*setOfBlockObjects);

extern int nBlockDegrees;
extern int nBlockTypes;
extern int iScreenDw;

void init(int **setOfCBlockArrays, int MAX_BLK_TYPES, int MAX_BLK_DEGREES){
    int i = 0; int j = 0;
    
    tetinit(setOfCBlockArrays, MAX_BLK_TYPES, MAX_BLK_DEGREES);

    setOfCBlockObjects = new Matrix**[nBlockTypes];
    for (int y = 0; y < nBlockTypes; y++)
        setOfCBlockObjects[y] = new Matrix*[nBlockDegrees];
    for (int y = 0; y < nBlockTypes; y++)
        for (int x = 0; x < nBlockDegrees; x++)
            setOfCBlockObjects[y][x] = nullptr;

    for (i=0; i < nBlockTypes; i++)
    {
        for (j=0; j < nBlockDegrees; j++){
            int *arrptr = setOfCBlockArrays[i*4 + j];
            int arrsize = 0;
            while(1){
                if (arrptr[arrsize] == -1){
                    break;
                }
                else{
                    arrsize++;
                }
            }
            Matrix *obj;
            obj = new Matrix(arrptr, sqrt(arrsize), sqrt(arrsize));
            obj->mulc(i+1);
            cout << *obj <<endl;
            setOfCBlockObjects[i][j] = obj;
        }
    }

    return;
}

TetrisState CTetris::accept(char key){
    TetrisState state;

    if ((key >= '0') && (key <= '6')){
        if (justStarted == false){
            this->deleteFullLines();
        }
        iCScreen = new Matrix(oCScreen);
    }
    
    state = tetaccept(key);

    currCBlk = setOfCBlockObjects[this->idxBlockType][this->idxBlockDegree];
    tempBlk = iCScreen->clip(this->top, 
                             this->left, 
                             this->top + currCBlk->get_dy(), 
                             this->left + currCBlk->get_dx());

    tempBlk = tempBlk->add(currCBlk);

    oCScreen = new Matrix(iCScreen);
    oCScreen->paste(tempBlk, this->top, this->left);

    return state;
}

void CTetris::deleteFullLines(){
    system("clear");
    std::cout << "call CTetris::deleteFullLines()" << std::endl;
    bool is_zero = false;
    int ** array = oScreen->get_array();

    int dx = oScreen->get_dx() - iScreenDw*2;

    for (int y=0; y < oScreen->get_dy() - iScreenDw; y++){
        for (int x=0; x < dx; x++){
            if (array[y][x] == 0){
                is_zero = true;
            }
        }

        if (!is_zero){ // if 0 not in array[y]
            for (int x=0; x < dx; x++){
                array[y][x] = 0;
            }
            top = 1;
            left = 0;
            currCBlk = oScreen->clip(0, 0, y, oScreen->get_dx());
            tempBlk = iScreen->clip(0, 0, y, oScreen->get_dx());
            tempBlk->paste(currCBlk, 0, 0);
            oScreen = new Matrix(iScreen);
            oScreen->paste(tempBlk, top, left);
        }
    }
}

CTetris::CTetris(int cy, int cx) : Tetris(cy, cx){
    int **arrayScreen2D;
    arrayScreen2D = createArrayScreen();

    int k = 0;
    for (int y=0; y < arrayScreenDy; y++){   
        for (int x=0; x < arrayScreenDx; x++){
            arrayScreen[k] = arrayScreen2D[y][x];
            k++;
        }
    }

    this->iCScreen = new Matrix(arrayScreen, arrayScreenDy, arrayScreenDx);
    this->oCScreen = new Matrix(iCScreen);
}