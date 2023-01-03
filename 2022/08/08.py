def getScenicScore(forest, size, x, y):
    curTree = int(forest[x][y])
    totalScore = 0

    score = 1
    j = y-1
    while j > 0 and int(forest[x][j]) < curTree:
        j -= 1
        score += 1
    totalScore += score

    score = 1
    j = y+1
    while j < size-1 and int(forest[x][j]) < curTree:
        j += 1
        score += 1
    totalScore *= score

    score = 1
    i = x-1
    while i > 0 and int(forest[i][y]) < curTree:
        i -= 1
        score += 1
    totalScore *= score

    score = 1
    i = x+1
    while i < size-1 and int(forest[i][y]) < curTree:
        i += 1
        score += 1
    totalScore *= score
    return totalScore

def getBestScenic(file):
    forest = [line.strip() for line in open(file).readlines()]
    forestLen = len(forest)
    scenicScores = []
    for i in range(1, forestLen-1):
        for j in range(1, forestLen-1):
            curTreeScore = getScenicScore(forest, forestLen, i, j)
            scenicScores.append(curTreeScore)
    return max(scenicScores)

import sys
if __name__ == '__main__':
    print(f"Maximal scenic score possible: {getBestScenic(sys.argv[1])}")
