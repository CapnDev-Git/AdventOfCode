def mapChar(k):
    if k >= 97:
        return k-97
    else:
        return k-39

def getBadgeType(L):
    for c in L[0]:
        for c2 in L[1]:
            for c3 in L[2]:
                if c == c2 == c3:
                    return mapChar(ord(c))+1

def getPrioritiesSum(file):
    with open(file) as f:
        priority = 0
        group = ""
        k = 0
        for line in f:
            group += line
            k += 1
            if k == 3:
                sacks = group.split('\n')
                sacks.pop()
                priority += getBadgeType(sacks)
                group = ""
                k = 0
    return priority

import sys
if __name__ == '__main__':
    print(f"Sum of priorities of badges: {getPrioritiesSum(sys.argv[1])}")
