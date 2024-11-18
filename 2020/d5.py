def letters_to_binary(s):
    new = ""
    for i in range(len(s)):
        curr = s[i]
        if curr == "F" or curr == "L":
            new += "0"
        else:
            new += "1"
    return new


def find_missing_seat_id(ids, min_seat, nb_seats):
    checks = [False] * (nb_seats + 1)

    for id_ in ids:
        row = int(letters_to_binary(id_[:7]), 2)
        col = int(letters_to_binary(id_[-3:]), 2)
        seat = row * 8 + col
        checks[seat - min_seat] = True
    return checks.index(False) + min_seat


if __name__ == "__main__":
    with open("input.txt") as f:
        ids = [s[:-1] for s in f.readlines()]
        max_seat = 838
        min_seat = 95
        print(find_missing_seat_id(ids, min_seat, max_seat - min_seat))
