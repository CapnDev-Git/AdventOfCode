def count_slope_trees(m, h, v):
    t = 0
    j = 0
    for i in range(0, len(m), v):
        if m[i][j] == "#":
            t += 1
        j = (j + h) % len(m[0])
    return t


if __name__ == "__main__":
    m = []
    with open("input.txt") as f:
        for s in f.readlines():
            m.append(list(s[:-1]))
        print(len(m), len(m[0]))
    # max amount of trees is len(m) - 1
    print(count_slope_trees(m, 1, 1))  # positive vertical = down
    print(count_slope_trees(m, 3, 1))  # positive vertical = down
    print(count_slope_trees(m, 5, 1))  # positive vertical = down
    print(count_slope_trees(m, 7, 1))  # positive vertical = down
    print(count_slope_trees(m, 1, 2))  # positive vertical = down
