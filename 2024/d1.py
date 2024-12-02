def find_total_distance(l1, l2):
    return sum([abs(l1[i] - l2[i]) for i in range(len(l1))])


def compute_similarity_score(l1, l2):
    return sum([n * l2.count(n) for n in l1])


if __name__ == "__main__":
    with open("2024/input.txt") as f:
        l1, l2 = [], []
        for line in f.readlines():
            l, r = (e.strip() for e in line.split(" ") if e != "")
            l1.append(int(l))
            l2.append(int(r))
        # print(find_total_distance(sorted(l1),sorted(l2)))
        print(compute_similarity_score(l1, l2))
