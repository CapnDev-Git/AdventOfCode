def areDifferent(s, size):
    for i in range(size):
        for j in range(i+1, size):
            if s[j] == s[i]:
                return False
    return True

def getMessageMarker(file):
    res = []
    k = 0
    curMarker = ""
    with open(file) as f:
        for line in f:
            line = line.strip()
            for i in range(13):
                curMarker += line[i]
                k += 1

            for i in range(13, len(line)):
                k += 1
                curMarker += line[i]
                if areDifferent(curMarker, 14):
                    res.append(k)
                    k = 0
                    curMarker = ""
                    break
                curMarker = curMarker[1:]
    return res

import sys
if __name__ == '__main__':
    print(f"First start-of-message marker: {getMessageMarker(sys.argv[1])}")
