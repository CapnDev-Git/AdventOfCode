def getLengthRange(r):
    return r[1]-r[0]+1

def getOverlaps(file):
    with open(file) as f:
        totalOverlaps = 0
        for line in f:
            l,r = [0]*2,[[0]*2]*2
            line = (line.strip()).split(',')    
            for i in range(2):
                r[i] = [int(e) for e in line[i].split('-')]
                l[i] = getLengthRange(r[i])
            if (r[0][0] == r[1][0]) or \
               (r[0][0]<r[1][0]<=r[0][1]) or \
               (r[1][0]<r[0][0]<=r[1][1]):
                totalOverlaps += 1
    return totalOverlaps

import sys
if __name__ == '__main__':
    print(f"Number of overlapping pairs: {getOverlaps(sys.argv[1])}")
