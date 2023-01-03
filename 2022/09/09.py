def getRopePositions(file):
    head = (0, 0)  # Initialize head position at (0, 0)
    tail = (0, 0)  # Initialize tail position at (0, 0)
    visited = set()  # Initialize set to store visited positions
    visited.add(tail)  # Add starting position to visited set
    instructions = open(file).readlines()

    # Loop through each instruction
    for instruction in instructions:
        direction, distance = instruction[0], int(instruction[1:])

        # Update head position based on direction
        if direction == 'R':
            head = (head[0] + distance, head[1])
        elif direction == 'L':
            head = (head[0] - distance, head[1])
        elif direction == 'U':
            head = (head[0], head[1] + distance)
        elif direction == 'D':
            head = (head[0], head[1] - distance)

        # Update tail position based on head position
        if abs(head[0] - tail[0]) > 1 or abs(head[1] - tail[1]) > 1:
            if head[0] > tail[0]:
                tail = (tail[0] + 1, tail[1])
            elif head[0] < tail[0]:
                tail = (tail[0] - 1, tail[1])
            elif head[1] > tail[1]:
                tail = (tail[0], tail[1] + 1)
            elif head[1] < tail[1]:
                tail = (tail[0], tail[1] - 1)
        elif abs(head[0] - tail[0]) == 1 and abs(head[1] - tail[1]) == 1:
            tail = head
        else:
            if head[0] == tail[0]:
                if head[1] > tail[1]:
                    tail = (tail[0], tail[1] + 1)
                else:
                    tail = (tail[0], tail[1] - 1)
            elif head[1] == tail[1]:
                if head[0] > tail[0]:
                    tail = (tail[0] + 1, tail[1])
                else:
                    tail = (tail[0] - 1, tail[1])
            else:
                if head[0] > tail[0]:
                    if head[1] > tail[1]:
                        tail = (tail[0] + 1, tail[1] + 1)
                    else:
                        tail = (tail[0] + 1, tail[1] - 1)
                else:
                    if head[1] > tail[1]:
                        tail = (tail[0] - 1, tail[1] + 1)
                    else:
                        tail = (tail[0] - 1, tail[1] - 1)
        visited.add(tail)  # Add current tail position to visited set

    return len(visited)  # Return number of unique positions visited

import sys
if __name__ == '__main__':
    print(f"Number of positions the tail visited at least once: {getRopePositions(sys.argv[1])}")
