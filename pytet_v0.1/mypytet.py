from matrix import *
import random

def draw_matrix(m):
    array = m.get_array()
    for y in range(m.get_dy()):
        for x in range(m.get_dx()):
            if array[y][x] == 0:
                print("□", end='')
            elif array[y][x] == 1:
                print("■", end='')
            else:
                print("XX", end='')
        print()


###
### initialize variables
###     
arrayBlk_I = [  [[ 0, 0, 1, 0 ], [ 0, 0, 1, 0 ], [ 0, 0, 1, 0 ], [ 0, 0, 1, 0 ]],
                [[ 0 ]*4, [ 0 ]*4, [ 1 ]*4, [ 0 ]*4],
                [[ 0, 1, 0, 0 ], [ 0, 1, 0, 0 ], [ 0, 1, 0, 0 ], [ 0, 1, 0, 0 ]],
                [[ 0 ]*4, [ 1 ]*4, [ 0 ]*4, [ 0 ]*4]
             ]

arrayBlk_J = [  [[ 0, 0, 1, 0 ], [ 0, 0, 1, 0 ], [ 0, 1, 1, 0 ], [ 0 ]*4],
                [[ 0 ]*4, [ 0, 1, 0, 0 ], [ 0, 1, 1, 1 ], [ 0 ]*4],
                [[ 0 ]*4, [ 0, 1, 1, 0 ], [ 0, 1, 0, 0 ], [ 0, 1, 0, 0 ]],
                [[ 0 ]*4, [ 1, 1, 1, 0 ], [ 0, 0, 1, 0 ], [ 0 ]*4]
             ]
arrayBlk_L = [  [[ 0, 1, 0, 0 ], [ 0, 1, 0, 0 ], [ 0, 1, 1, 0 ], [ 0 ]*4],
                [[ 0 ]*4, [ 0, 1, 1, 1 ], [ 0, 1, 0, 0 ], [ 0 ]*4],
                [[ 0 ]*4, [ 0, 1, 1, 0 ], [ 0, 0, 1, 0 ], [ 0, 0, 1, 0 ]],
                [[ 0 ]*4, [ 0, 0, 1, 0 ], [ 1, 1, 1, 0 ], [ 0 ]*4]
             ]
arrayBlk_O = [  [[ 1 ]*2, [ 1 ]*2],
                [[ 1 ]*2, [ 1 ]*2],
                [[ 1 ]*2, [ 1 ]*2],
                [[ 1 ]*2, [ 1 ]*2]
             ]
arrayBlk_S = [  [[ 0, 1, 1 ], [ 1, 1, 0 ], [ 0 ]*3],
                [[ 0, 1, 0 ], [ 0, 1, 1 ], [ 0, 0, 1 ]],
                [[ 0 ]*3, [ 0, 1, 1 ], [ 1, 1, 0 ]],
                [[ 1, 0, 0 ], [ 1, 1, 0 ], [ 0, 1, 0 ]]
             ]
arrayBlk_T = [  [[ 1 ]*3, [ 0, 1, 0 ], [ 0 ]*3],
                [[ 0, 0, 1 ], [ 0, 1, 1 ], [ 0, 0, 1 ]],
                [[ 0 ]*3, [ 0, 1, 0 ], [ 1 ]*3],
                [[ 1, 0, 0 ], [ 1, 1, 0 ], [ 1, 0, 0 ]]
             ]
arrayBlk_Z = [  [[ 1, 1, 0 ], [ 0, 1, 1 ], [ 0 ]*3],
                [[ 0, 0, 1 ], [ 0, 1, 1 ], [ 0, 1, 0 ]],
                [[ 0 ]*3, [ 1, 1, 0 ], [ 0, 1, 1 ]],
                [[ 0 , 1, 0 ], [ 1, 1, 0 ], [ 1, 0, 0 ]]
             ]
Blk_List = [arrayBlk_I, arrayBlk_J, arrayBlk_L, arrayBlk_O, arrayBlk_S, arrayBlk_T, arrayBlk_Z]

### integer variables: must always be integer!
iScreenDy = 15
iScreenDx = 10
iScreenDw = 4
top = 0
left = iScreenDw + iScreenDx//2 - 2
random_Block = random.randrange(0, len(Blk_List))
rotate_index = 0

newBlockNeeded = False

arrayScreen = [
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ],
    [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ] ]

###
### prepare the initial screen output
###  

iScreen = Matrix(arrayScreen)
oScreen = Matrix(iScreen)
currBlk = Matrix(Blk_List[random_Block][rotate_index])
tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx())
tempBlk = tempBlk + currBlk
oScreen.paste(tempBlk, top, left)
draw_matrix(oScreen); print()

###
### execute the loop
###

while True:
    key = input('Enter a key from [ q (quit), a (left), d (right), s (down), w (rotate), \' \' (drop) ] : ')
    if key == 'q':
        print('Game terminated...')
        break
    elif key == 'a': # move left
        left -= 1
    elif key == 'd': # move right
        left += 1
    elif key == 's': # move down
        top += 1
    elif key == 'w': # rotate the block clockwise
        rotate_index = (rotate_index+1)%4
        currBlk = Matrix(Blk_List[random_Block][rotate_index])
    elif key == ' ': # drop the block
        print('Not implemented')
        continue
    else:
        print('Wrong key!!!')
        continue

    tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx())
    tempBlk = tempBlk + currBlk
    if tempBlk.anyGreaterThan(1):
        if key == 'a': # undo: move right
            left += 1
        elif key == 'd': # undo: move left
            left -= 1
        elif key == 's': # undo: move up
            top -= 1
            newBlockNeeded = True
        elif key == 'w': # undo: rotate the block counter-clockwise
            rotate_index = (rotate_index+3)%4
            currBlk = Matrix(Blk_List[random_Block][rotate_index])
        elif key == ' ': # undo: move up
            print('Not implemented')

        tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx())
        tempBlk = tempBlk + currBlk

    oScreen = Matrix(iScreen)
    oScreen.paste(tempBlk, top, left)
    draw_matrix(oScreen); print()

    if newBlockNeeded:
        iScreen = Matrix(oScreen)
        top = 0
        left = iScreenDw + iScreenDx//2 - 2
        random_Block = random.randrange(0, len(Blk_List))
        rotate_index = 0
        newBlockNeeded = False
        currBlk = Matrix(Blk_List[random_Block][rotate_index])
        tempBlk = iScreen.clip(top, left, top+currBlk.get_dy(), left+currBlk.get_dx())
        tempBlk = tempBlk + currBlk
        if tempBlk.anyGreaterThan(1):
            print('Game Over!!!')
            break
        
        oScreen = Matrix(iScreen)
        oScreen.paste(tempBlk, top, left)
        draw_matrix(oScreen); print()
        
###
### end of the loop
###
