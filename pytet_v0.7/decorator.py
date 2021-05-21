from game import *
from matrix import *

from tetris import *

##################################################
### ColorDecorator for Tetris Class
##################################################

class ColorDecorator(Game):
	setOfCBlockObjects = 0
	def initCBlocks(self, setOfBlockObjects):
		### initialize self.setOfCBlockObjects
		self.setOfCBlockObjects = [[0] * Tetris.nBlockDegrees for _ in range(Tetris.nBlockTypes)]
		arrayBlk_maxSize = 0
		for i in range(Tetris.nBlockTypes):
		    if arrayBlk_maxSize <= len(setOfBlockObjects[i][0].get_array()):
		        arrayBlk_maxSize = len(setOfBlockObjects[i][0].get_array())
		#Tetris.iScreenDw = arrayBlk_maxSize     # larget enough to cover the largest block

		for i in range(Tetris.nBlockTypes):
		    for j in range(Tetris.nBlockDegrees):
		        self.setOfCBlockObjects[i][j] = Matrix(setOfBlockObjects[i][j].get_array())
		        self.setOfCBlockObjects[i][j].mulc(i+1);
		return
		
	def __init__(self, game):	# do not modify
		self.game = game
		self.initCBlocks(game.setOfBlockObjects)
		arrayScreen = game.createArrayScreen()
		self.iCScreen = Matrix(arrayScreen)
		self.oCScreen = Matrix(self.iCScreen)
		return

	def accept(self, key):
		if key >= '0' and key <= '6':
			if self.game.justStarted ==False:
				self.deleteFullLines()
			self.iCScreen = Matrix(self.oCScreen)
		state = self.game.accept(key)	

		self.currCBlk = self.setOfCBlockObjects[self.game.idxBlockType][self.game.idxBlockDegree]
		tempBlk = self.iCScreen.clip(self.game.top, self.game.left,
					self.game.top + self.currCBlk.get_dy(),
					self.game.left + self.currCBlk.get_dx())
		tempBlk = tempBlk + self.currCBlk
		self.oCScreen = Matrix(self.iCScreen)
		self.oCScreen.paste(tempBlk, self.game.top, self.game.left)
		return state
	
	def getScreen(self):		# do not modify
		return self.oCScreen
	
	def deleteFullLines(self):
                nDeleted = 0
                nScanned = self.game.deleteFullLines()

                zero = Matrix([[ 0 for x in range(0, (self.game.iScreenDx - 2*self.game.iScreenDw))]])
                for y in range(nScanned - 1, -1, -1):
                    cy = self.game.top + y + nDeleted
                    line = self.oCScreen.binary().clip(cy, 0, cy+1, self.oCScreen.get_dx())
                    if line.sum() == self.oCScreen.get_dx():
                        temp = self.oCScreen.clip(0, 0, cy, self.oCScreen.get_dx())
                        self.oCScreen.paste(temp, 1, 0)
                        self.oCScreen.paste(zero, 0, self.game.iScreenDw)
                        nDeleted += 1
                
                return

