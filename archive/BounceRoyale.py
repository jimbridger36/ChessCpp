from playsound import playsound
'''import pydub
import os
from pydub import AudioSegment
from pydub.playback import play'''
from random import random as randfloat
import random
import time
from math import exp



sounds = [1,2,3,4]
def pickSound():


	#pick normal
	return 'BounceSounds/Normal/Hurstpierpoint College ' + str(sounds[random.randint(0,len(sounds)-1)])  + '.m4a'

timePeriod = 10
gracePeriod = 4
graceFrac = gracePeriod / timePeriod

timeSinceLast = 0


def pdf(xScaled):
	if xScaled < gracePeriod:
		return 0.
	else:
		return 1/timePeriod

def randNoise():
	global timeSinceLast
	if randfloat() < pdf(timeSinceLast): # if time to make noise
		print('played')
		timeSinceLast = 0
		playsound(pickSound())

while True:
	randNoise()
	time.sleep(1)
	timeSinceLast += 1
















