import cppChess as chess


import pygame
import numpy as np
import os


fens = {"bishop bishop rook" : "5k2/8/B7/8/5r2/8/3B4/4K3 w - - 0 1"}


def flipy(arr):
	maxrow = arr.shape[0] - 1
	newArr = np.zeros(arr.shape)

	for row in range(arr.shape[0] // 2):
		newArr[row] = arr[maxrow - row]
		newArr[maxrow - row] = arr[row]

	if arr.shape[0] % 2 == 1:
		newArr[arr.shape[0] // 2] = arr[arr.shape[0] // 2]
	return newArr


width = height = 400

sqrSize = height // 8
maxFPS = 15

images = {}
# declaring colours
if True:
	light = pygame.Color(0xE8, 0xDE, 0xD1);
	dark = pygame.Color(0xA0, 0x81, 0x6C)
	red = pygame.Color(0xFF, 0x00, 0x00);
	orange = pygame.Color(255, 215, 0)
	green = pygame.Color(0, 0xFF, 0);
	blue = pygame.Color(0, 0, 0xFF)
	yellow = pygame.Color(0xFF, 0xFF, 0)


def loadImages():
	pieces = list(range(1, 7)) + list(range(9, 15))

	for piece in pieces: images[piece] = pygame.transform.scale(
		pygame.image.load('Sprites/PieceSprite' + str(piece) + '.png'), (sqrSize, sqrSize))


running = False
screen = None
clock = None


def main():
	pos_x = 1035
	pos_y = 100
	os.environ['SDL_VIDEO_WINDOW_POS'] = '%i,%i' % (pos_x, pos_y)
	pygame.init()
	global screen
	screen = pygame.display.set_mode((width, height))
	global clock
	clock = pygame.time.Clock()
	screen.fill(pygame.Color('white'))
	loadImages()
	running = True
	'''
	while running:
		for error in pygame.event.get():
			if error.type == pygame.QUIT:
				running = False
		clock.tick(maxFPS)
		pygame.display.flip()
		drawSquares(screen)
		drawPieces(screen, board.getSquare())

	'''


def drawSquares(screen, squares: list = None):  # black                       white
	colours = {
		0       : dark,
		1       : light,
		'red'   : red,
		'green' : green,
		'blue'  : blue,
		'orange': orange,
		'yellow': yellow
	}
	if squares != None:
		for index, pair in enumerate(squares):
			squares[index] = (squares[index][0], squares[index][1])

	for rank in range(7,-1,-1):
		for file in range(8):
			# drawing the colour
			if squares != None:
				pos = (7-rank) * 8 + file
				if (pos, 'red') in squares:
					pygame.draw.rect(screen, red, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))
				elif (pos, 'green') in squares:
					pygame.draw.rect(screen, green, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))
				elif (pos, 'blue') in squares:
					pygame.draw.rect(screen, blue, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))
				elif (pos, 'orange') in squares:
					pygame.draw.rect(screen, orange, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))
				elif (pos, 'yellow') in squares:
					pygame.draw.rect(screen, yellow, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))
				else:
					colour = colours[((7 - rank) + file) % 2]
					pygame.draw.rect(screen, colour, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))
			else:
				colour = colours[((7 - rank) + file) % 2]
				pygame.draw.rect(screen, colour, pygame.Rect(file * sqrSize, rank * sqrSize, sqrSize, sqrSize))


def drawPieces(screen, Square):
	for rank in range(8):
		for file in range(8):
			piece = Square[rank][file]
			if piece != 0:
				screen.blit(images[piece], pygame.Rect(file * sqrSize, (7 - rank) * sqrSize, sqrSize, sqrSize))


def draw(squares: list = None):
	running = True
	for error in pygame.event.get():
		if error.type == pygame.QUIT:
			running = False
	print('Got past error detection')
	drawSquares(screen, squares)

	drawPieces(screen, board.getSquare())
	pygame.display.flip()
	clock.tick(maxFPS)
	return running

def attack(rank, file = -1):
	if file == -1:
		pos = rank
	else:
		pos = rank * 8 + file
	lst = list(zip(board.getRedSquares(pos), ["red"]*1000))

	draw(lst)



def B(num):
	initial = format(num, 'b')
	remainder = len(initial) % 4
	if remainder != 0:
		newstr = ('0' * (4-remainder)) + initial
	else:
		newstr = initial
	length = len(newstr)
	for i in range(length - 4, 0, -4):
		newstr = newstr[0:i] + ' ' + newstr[i: len(newstr)]

	return newstr, len(initial), 'bits'



def h(num):
	whole = hex(num)
	return whole[2:], len(whole[2:]) * 4, 'bits'



class PieceEnum:
	empty = 0
	pawn = 1
	knight = 2
	bishop = 3
	rook = 4
	king = 5
	queen = 6

	white = 0
	black = 8
	wpawn = pawn | white

pe = PieceEnum





directionsVec = {PieceEnum.rook  : np.array([[1, 0], [-1, 0], [0, 1], [0, -1]]),
				 PieceEnum.bishop: np.array([[1, 1], [1, -1], [-1, 1], [-1, -1]]),
				 PieceEnum.queen : np.concatenate(
					 ([[1, 0], [-1, 0], [0, 1], [0, -1]], [[1, 1], [1, -1], [-1, 1], [-1, -1]])),
				 PieceEnum.knight: np.array([[2, 1], [2, -1], [-2, 1], [-2, -1], [1, 2], [1, -2], [-1, 2], [-1, -2]])
				 }

z = [None] * 5


board = chess.pyBoard(fens["bishop bishop rook"])
b = board
main()
draw()

'''
z[0] = h(bg.getZ()), 'inital Z'
bg.pyDoCastle(False, True)
z[1] = h(bg.getZ()), 'after castling'
draw()
bg.pyUndoMove()
z[2] = h(bg.getZ()), 'after undoing'
bg.setPiece(pe.pawn, 6, 4)
z[3] = h(bg.getZ()), 'before promotion'
draw()
'''





p = chess.StringToPos
sq = list(np.zeros((8,8)))

chess.pyCheckDist()
print("dist Checked")
v = b.getAllRed(0)


#import cppDebug

b.printZ()
print(p('d2'), p('c3'))
b.doNormalMove(p('d2'), p('c3'))
b.printZ()
b.pyUndoMove()
b.printZ()




