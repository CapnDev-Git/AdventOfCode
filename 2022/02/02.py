def getRoundScore(L):
    p1, p2 = L[0], L[1]
    score = ord(p2)-87
    if ord(p1) == ord(p2)-23:
        return score + 3
    if p2 == "Y" and p1 == "A" or \
       p2 == "Z" and p1 == "B" or \
       p2 == "X" and p1 == "C":
        return score+6
    return score

def getMove(L):
    p1, p2 = ord(L[0])-65, L[1]
    p2Outcomes = ['X', 'Y', 'Z']
    if p2 == "X":
        L[1] = p2Outcomes[(p1+2)%3]
    elif p2 == "Z":
        L[1] = p2Outcomes[(p1+1)%3]
    else:
        L[1] = p2Outcomes[p1]
    return getRoundScore(L)

def computeStrategyGuide(file):
    totalScore = 0
    with open(file) as f:
        for line in f:
            line = (line.rstrip()).split(" ")
            totalScore += getMove(line)
    return totalScore

import sys
if __name__ == '__main__':
    print(f"Total score: {computeStrategyGuide(sys.argv[1])}")
