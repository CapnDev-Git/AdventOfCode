def createArchitecture(content):
    archi, curDir = {}, "~"
    for line in content:
        line = line.strip()
        tokens = line.split(" ")
        if tokens[0] == "$":
            if tokens[1] == "cd":
                if tokens[2] == "..":
                    curDir = "/".join(curDir.split("/")[:-1])
                else:
                    if tokens[2] == "/":
                        curDir += "/\\"
                    else:
                        curDir += "/" + tokens[2]
                    if curDir not in archi.keys():
                        archi[curDir] = []
        else:
            archi[curDir].append((tokens[0], curDir + "/" + tokens[1]))
    return archi

def getDirectorySize(archi, folderName):
    size = 0
    for elm in archi[folderName]:
        if elm[0] == "dir":
            size += getDirectorySize(archi, elm[1])
        else:
            size += int(elm[0])
    archi[folderName] = size
    return size

def getTotalSizeMinUnused(file):
    archi = createArchitecture(open(file).readlines())
    print(archi)

    MEM_SIZE = 70_000_000
    UNUSED_REQ = 30_000_000
    CUR_USAGE = getDirectorySize(archi, "~/\\")
    CUR_UNUSED = MEM_SIZE - CUR_USAGE
    TO_FREE = UNUSED_REQ - CUR_UNUSED
    return min([archi[key] for key in archi.keys() if archi[key] >= TO_FREE])

import sys
if __name__ == '__main__':
    print(f"Size of smallest directory to be removed to have enough unused space: {getTotalSizeMinUnused(sys.argv[1])}")
