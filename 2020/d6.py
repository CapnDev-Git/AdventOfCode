def get_sum_any_yes_answers(groups):
    s = 0
    for g in groups:
        i = 0
        curr = g[0]
        answered = 1
        while i < len(g):
            if g[i] != curr:
                answered += 1
                curr = g[i]
            i += 1
        s += answered
    return s


def get_sum_all_yes_answers(info):
    s = 0
    for ch, sz in info:
        j = 0  # everyone answered yes counter
        occ = 1  # occ of current char
        curr = ch[0]
        for i in range(1, len(ch)):
            char = ch[i]
            if char == curr:
                occ += 1
            else:
                if occ == sz:
                    j += 1
                curr, occ = ch[i], 1  # reset for new character
        if occ == sz:
            j += 1
        s += j
    return s


if __name__ == "__main__":
    with open("input.txt") as f:
        content = f.read()[:-1]
        groups_info = [
            (sorted(g.replace("\n", "")), g.count("\n") + 1)
            for g in content.split("\n\n")
        ]
        print(get_sum_all_yes_answers(groups_info))
