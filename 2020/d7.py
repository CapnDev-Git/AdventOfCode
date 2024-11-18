def dfs_search_bag(bags, color, searched, visited):
    if color == searched:
        return True
    visited.add(color)
    for content_color in bags[color].keys():
        if content_color in visited:
            continue
        if dfs_search_bag(bags, content_color, searched, visited):
            return True
    return False

def dfs_count_bag(bags, start):
    total_count = 0
    for sub_bag, capa in bags[start].items():
        total_count += capa + capa * dfs_count_bag(bags, sub_bag)
    return total_count

if __name__ == "__main__":
    with open("input.txt") as f:
        bags = {}
        for line in f:
            line = line.strip().split("contain")
            color = line[0].split("bag")[0].strip()
            bags[color] = {}
            for bag in line[1].split(","):
                bag = bag.strip().split("bag")[0].strip()
                bag_parts = bag.split(" ")
                if bag_parts[0] == "no":
                    break
                bags[color][" ".join(bag_parts[1:])] = int(bag_parts[0])
        print(dfs_count_bag(bags, "shiny gold"))
