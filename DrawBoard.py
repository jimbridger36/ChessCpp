import pygame
import numpy as np
from archive import chess

redlst = ["red"] * 1000

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
		drawPieces(screen, board.getSquare())'''


def drawSquares(screen, squares: list = None):  # black                       white
	colours = {
		0       : light,
		1       : dark,
		'red'   : red,
		'green' : green,
		'blue'  : blue,
		'orange': orange,
		'yellow': yellow
	}

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
	lst = list(zip(b.getRedSquares(pos), ["red"]*1000))

	draw(lst)


chess.computeDistanceInfo()
chess.initZVals("hello")


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

b = chess.Board(fenString="empty")
sq = b.getSquare()
print(sq)
board = b

b.setPiece(PieceEnum.queen | PieceEnum.white, 18)
b.setPiece(PieceEnum.bishop | PieceEnum.black)
b.genZVal()
print(b.getZ())

ic = board.INCheck
