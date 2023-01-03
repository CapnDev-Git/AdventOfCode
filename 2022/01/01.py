def insertMax(L, n):
    for i in range(3):
        if n > L[i]:
            L[i] = n
            break
    L.sort()
    return L

def topThreeCarriers(file):
    with open(file) as f:
        t3c=[0]*3
        cur = 0
        for line in f:
            line = line.rstrip()
            if line != "":
                cur += int(line)
            else:
                t3c=insertMax(t3c, cur)
                cur = 0
        insertMax(t3c, cur)
    return sum(t3c)

import sys
if __name__ == '__main__':
    print(f"Top 3 carriers total calories: {topThreeCarriers(sys.argv[1])}")
