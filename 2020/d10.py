def find_differences13_count(adapters):
    adapters = [0] + sorted(adapters) + [max(adapters) + 3]
    diff1,diff3 = 0,0

    for i in range(len(adapters)-1):
        ad, nxt = adapters[i], adapters[i+1]
        if nxt - ad == 1:
            diff1 += 1
        elif nxt - ad == 3:
            diff3 += 1
    return diff1, diff3, diff1*diff3

def find_differences123_count(adapters):
    adapters = [0] + sorted(adapters) + [max(adapters) + 3]
    diff1, diff2, diff3 = 0, 0, 0

    for i in range(len(adapters)-1):
        ad, nxt = adapters[i], adapters[i+1]
        if nxt - ad == 1:
            diff1 += 1
        elif nxt - ad == 2:
            diff2 += 1
        elif nxt - ad == 3:
            diff3 += 1
    return diff1, diff2, diff3

def find_arrangements(adapters):
    adapters = [0] + sorted(adapters) + [max(adapters) + 3]
    ways_to_reach = {adapter: 0 for adapter in adapters}
    ways_to_reach[0] = 1  # There's only one way to start at 0
    
    for adapter in adapters:
        for next_adapter in (adapter + 1, adapter + 2, adapter + 3):  # Check up to +3
            if next_adapter in ways_to_reach:
                ways_to_reach[next_adapter] += ways_to_reach[adapter]
    return ways_to_reach[adapters[-1]]


if __name__ == "__main__":
    with open("2020/input.txt") as f:
        adapters = [int(s.split("\n")[0]) for s in f.readlines()]
        print(f"solution: {find_arrangements(adapters)}")
