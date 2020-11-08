import os
import sys

def getSum(word):
	sum = 0
	for char in word:
		sum += ( ord(char) - ord('A') + 1)
	return sum

with open(os.path.join(sys.path[0], "Text - 42.txt"), "r") as f:
    allWords = f.readlines()

words = []

for line in allWords:
	words = line.split(",")

words = [word.replace('"', '') for word in words]

triangleNumbers = [ int((i*(i+1))/2) for i in range(27) ]

ans = 0

for word in words:
	sum = getSum(word)
	if sum in triangleNumbers:
		ans += 1

print(ans)

