
# X starts with value 1
# 2 instructions:
# -> "addx V" = 2 cycles ; after 2c, X incr by V (can be <0)
# -> noop = 1 cycle, no other effect

# signal strength = cycle number * X at 20th cycle & every other 40th cycle


def getSumSignalStrengths(file):
    signalStrengthSum = 0
    cycle = 1
    X = 1
    offset = 0
    queue = []
    content = open(file).readlines()
    sumCycle = "1+"

    for i in range(2*len(content)):
        if (cycle+20) % 40 == 0:
            print(f"sumCycle:{sumCycle}, X:{X}, cycle:{cycle}")
            signalStrengthSum += X * cycle
            sumCycle = f"({X})+"
        
        if (cycle+offset) % 2 == 0 and queue != []:
            op = queue.pop()
            sumCycle += f"({op})+"
            X += op

        if i < len(content):
            line = (content[i].strip()).split(' ')
            if (line[0] == "addx"):
                queue.insert(0, int(line[1]))
            else:
                offset += 1
        
        cycle += 1
        if cycle == 221:
            break
    return X, signalStrengthSum

import sys
if __name__ == '__main__':
    print(f"Signal strength: {getSumSignalStrengths(sys.argv[1])}")
