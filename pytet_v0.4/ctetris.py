from matrix import *
from tetris import *
from enum import Enum

class TetrisState(Enum):
    Running = 0
    NewBlock = 1
    Finished = 2
### end of class TetrisState():

class CTetris(Tetris):
    nBlockTypes = 0
    nBlockDegrees = 0
    setOfBlockObjects = 0
    iScreenDw = 0   # larget enough to cover the largest block

    def __init__(self, iScreenDy, iScreenDx):
        Tetris.__init__(self, iScreenDy, iScreenDx)
        return

    def accept(self, key):
        self.state = TetrisState.Running

        if key >= '0' and key <= '6':
            if self.justStarted == False:
                self.deleteFullLines()
            self.iScreen = Matrix(self.oScreen)
            self.idxBlockType = int(key)
            self.idxBlockDegree = 0
            self.currBlk = Tetris.setOfBlockObjects[self.idxBlockType][self.idxBlockDegree]
            self.top = 0
            self.left = Tetris.iScreenDw + self.iScreenDx//2 - self.currBlk.get_dx()//2
            self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
            binaryBlk = self.tempBlk.binary() + self.currBlk.binary()
            self.tempBlk = self.tempBlk + self.currBlk
            self.justStarted = False
            print()

            if binaryBlk.anyGreaterThan(1):
            #if self.tempBlk.anyGreaterThan(1):
                self.state = TetrisState.Finished
            self.oScreen = Matrix(self.iScreen)
            self.oScreen.paste(self.tempBlk, self.top, self.left)
            return self.state
        elif key == 'q':
            pass
        elif key == 'a': # move left
            self.left -= 1
        elif key == 'd': # move right
            self.left += 1
        elif key == 's': # move down
            self.top += 1
        elif key == 'w': # rotate the block clockwise
            self.idxBlockDegree = (self.idxBlockDegree + 1) % Tetris.nBlockDegrees
            self.currBlk = Tetris.setOfBlockObjects[self.idxBlockType][self.idxBlockDegree]
        elif key == ' ': # drop the block
            self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
            binaryBlk = self.tempBlk.binary() + self.currBlk.binary()
            while not binaryBlk.anyGreaterThan(1):
                self.top += 1
                self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
                binaryBlk = self.tempBlk.binary() + self.currBlk.binary()
                self.tempBlk = self.tempBlk + self.currBlk
        else:
            print('Wrong key!!!')
            
        self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
        binaryBlk = self.tempBlk.binary() + self.currBlk.binary()
        self.tempBlk = self.tempBlk + self.currBlk

        #if self.tempBlk.anyGreaterThan(1):   ## 벽 충돌시 undo 수행
        if binaryBlk.anyGreaterThan(1): 
            if key == 'a': # undo: move right
                self.left += 1
            elif key == 'd': # undo: move left
                self.left -= 1
            elif key == 's': # undo: move up
                self.top -= 1
                self.state = TetrisState.NewBlock
            elif key == 'w': # undo: rotate the block counter-clockwise
                self.idxBlockDegree = (self.idxBlockDegree - 1) % Tetris.nBlockDegrees
                self.currBlk = Tetris.setOfBlockObjects[self.idxBlockType][self.idxBlockDegree]
            elif key == ' ': # undo: move up
                self.top -= 1
                self.state = TetrisState.NewBlock
            
            self.tempBlk = self.iScreen.clip(self.top, self.left, self.top+self.currBlk.get_dy(), self.left+self.currBlk.get_dx())
            binaryBlk = self.tempBlk.binary() + self.currBlk.binary()
            self.tempBlk = self.tempBlk + self.currBlk

        self.oScreen = Matrix(self.iScreen)
        self.oScreen.paste(self.tempBlk, self.top, self.left)

        return self.state

    def deleteFullLines(self):
        array = self.oScreen.get_array()
        
        for y in range(self.oScreen.get_dy()-Tetris.iScreenDw):
            if 0 not in array[y]:
                # delete line
                del_line = array[y]
                array[y] = [0]*len(array[y])
                del del_line

                # move
                self.top = 1
                self.left = 0

                self.currBlk = self.oScreen.clip(0, 0, y, self.oScreen.get_dx())
                self.tempBlk = self.iScreen.clip(0, 0, y, self.oScreen.get_dx())
                self.tempBlk.paste(self.currBlk, 0, 0)
                self.oScreen = Matrix(self.iScreen)
                self.oScreen.paste(self.tempBlk, self.top, self.left)
                
### end of class Tetris():
