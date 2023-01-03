def toStack(lines, nbStacks, maxHeight):
    stacks = []
    for i in range(nbStacks):
        stacks.append([])
        for j in range(maxHeight):
            if lines[j][i] != ' ':
                stacks[i].insert(0, lines[j][i])
    return stacks

def parseInput(fileContent):
    lines = []
    for line in fileContent:
        layer = [line[i:i+1] for i in range(1, len(line), 4)]
        if layer[0] == '1':
            return (toStack(lines, len(layer), len(lines)), len(lines)+2)
        lines.append(layer)

def executeInstructions(fileContent, stacks, k):
    for i in range(k, len(fileContent)):
        curInstruc = (fileContent[i].rstrip()).split(" ")
        amount, src, dst = int(curInstruc[1]), int(curInstruc[3])-1, int(curInstruc[5])-1
        s = len(stacks[src])-amount
        sub = stacks[src][s:]
        for _ in range(amount):
            stacks[src].pop()
        stacks[dst].extend(sub)

def getTopCrates(file):
    stacks = []
    res = ""
    with open(file) as f:
        fileContent = f.readlines()
        (stacks, k) = parseInput(fileContent)
        executeInstructions(fileContent, stacks, k)
        for i in range(len(stacks)):
            res += stacks[i][-1]
    return res

import sys
if __name__ == '__main__':
    print(f"Top letters: {getTopCrates(sys.argv[1])}")
