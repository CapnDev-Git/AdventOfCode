def find_best_seat(seat_map):
    from copy import deepcopy
    current = deepcopy(seat_map)  # Ensure a true deep copy
    i = 0
    stop = 100000
    while i < stop:
        new = process_map(current)
        if new == current:
            break
        current = new  # Update the current map to the new one
        i += 1
    return ("killed" if i == stop else "equilibrium"), new


def count_occupied(m, i, j):
    directions = [
        (-1, -1), (-1, 0), (-1, 1),  # Up-left, Up, Up-right
        (0, -1),         (0, 1),    # Left, Right
        (1, -1), (1, 0), (1, 1)     # Down-left, Down, Down-right
    ]
    occupied = 0
    rows, cols = len(m), len(m[0])

    for di, dj in directions:
        k = 1
        ni, nj = i + di, j + dj
        while 0 <= ni < rows and 0 <= nj < cols and m[ni][nj] == '.':
            k += 1
            ni, nj = i + k*di, j + k*dj
        occupied += 0 if (ni < 0 or ni >= rows or 0 > nj or nj >= cols) else (1 if m[ni][nj] == '#' else 0)
    return occupied


def process_map(m):
    rows, cols = len(m), len(m[0])
    new = [row[:] for row in m]  # Deep copy of the map
    for i in range(rows):
        for j in range(cols):
            occupied = count_occupied(m, i, j)
            # print(occupied)
            if m[i][j] == 'L' and occupied == 0:
                new[i][j] = '#'
            elif m[i][j] == '#' and occupied >= 5:
                new[i][j] = 'L'
            elif m[i][j] == '.':
                continue
    # print_map(new)
    return new


def count_total_occupied(m):
    rows, cols = len(m), len(m[0])
    total = 0
    for i in range(rows):
        for j in range(cols):
            if m[i][j] == '#':
                total += 1
    return total

def print_map(m):
    rows, cols = len(m), len(m[0])
    total = 0
    for i in range(rows):
        for j in range(cols):
            print(m[i][j], end="")
        print()
    return total

if __name__ == "__main__":
    with open("2020/input.txt") as f:
        seat_map = [list(s.strip()) for s in f.readlines()]
        status, new = find_best_seat(seat_map)
        print(status)
        print_map(new)
        print(count_total_occupied(new))