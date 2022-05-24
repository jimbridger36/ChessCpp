import chess
import matplotlib.pyplot as plt
import random
import numpy as np

initialWins = 0
if True:
    def valDoesntWork(val):
        indexes = []
        for i in range(0, 4):
            index = ((1 >> val) << 1) % val
            if index in indexes:
                return True
            else:
                indexes.append(index)


    def tryRange(start, end):
        gen = range(start, end // 2, 2)
        for val in gen:
            if not valDoesntWork(val):
                print(val, "works")
                return

    wp = .535
    def getInit():
        return initialWins
    def p(iter, title = '', GRID = True):
        plt.plot(iter)
        if GRID:
            plt.grid(axis = "x")
        plt.title(title)
        plt.show()

    def numTimes(p=0.5, repeats=2):
        num = 1
        wins = getInit()

        while wins < repeats:
            # play a game
            if random.random() < p:
                wins += 1
            else:
                wins = 0

            num += 1
        return num


    def showDist(prob, repeats, upTo = 50, average = 10_0000):
        dist = np.zeros((upTo))
        for i in range(average):
            times = numTimes(prob, repeats)
            if times < upTo:
                dist[times] += 1
        dist /= average
        p(dist, str(prob))
        cumul = np.zeros((upTo))
        cumul[0] = dist[0]
        for i in range(1,upTo):
            cumul[i] = cumul[i-1] + dist[i]

        return dist, cumul


    def mean(arr):
        Sum = 0
        for i in range(arr.shape[0]):
            Sum += arr[i] * i
        return Sum

    def t(winsRequired):
        return meanTimes(.535, winsRequired)

    def meanTimes(prob, winsRequired, upTo = 50,oneMinus = True, displayUpTo = 50):
        d, a = showDist(prob, winsRequired, upTo)
        if not oneMinus:
            p(a[:displayUpTo],title ='p = ' + str(prob) + ', required = ' + str(winsRequired))
        else:
            p(1-a[:displayUpTo],title ='p = ' + str(prob) + ', required = ' + str(winsRequired))
        return mean(d)
    mt = meanTimes

b = chess.Board()

pc = chess.pcpy




