#!usr/bin/python
import random
import itertools 
from sys import argv
import matplotlib.pyplot as plt
from numpy import mean 

bj, deck_amount = argv
allhands = []
countlist = []
avg_left_list = []

def decktime(deck_amount): # define our decks
	global allhands#ondeck
	i = 4*deck_amount
	while i>0:
		allhands.append(range(1,10))
		j = 4
		while j>0: 
			allhands.append([10])
			j -= 1
		i -= 1
	allhands = [a for x in allhands for a in x] # he flattens our guy

def countem(x): 
	if 1 < x < 7:
		point_count = 1
	elif x == 10 or x == 1:
		point_count = -1
	else: 
		point_count = 0
	return point_count

def run_count_list():
	point_count_list = []
	for i in range(len(allhands)):
		point_count_list.append(countem(allhands[i]))
		countlist.append(sum(point_count_list))

def run_true_count_list():
	point_count_list = []
	true_point_count_list = []
	for i in range(len(allhands)):
		point_count_list.append(countem(allhands[i]))
		runnin_count = float(sum(point_count_list))
		decks_left = float(len(allhands[i::])) / 52.0
		true_count = float(runnin_count / decks_left)
		countlist.append(true_count)


def avg_left():
	
	for i in range(len(allhands)):
		avg_left = sum(allhands[i::])/float(len(allhands[i::]))
		avg_left_list.append(avg_left)
	
decktime(int(deck_amount))
random.shuffle(allhands)
#run_count_list()
run_true_count_list()
avg_left()
#print allhands
#print countlist


plt.figure(figsize=(4,3))
plt.plot(countlist, 'r--', avg_left_list, 'b--')
#plt.ylabel('Running Cunt, Average Value Left')
plt.ylabel('True Cunt, Average Value Left')
plt.xlabel('Card #')
plt.show()