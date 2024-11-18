def correct_passwords(policies, passwords):
    correct = 0
    for i in range(len(policies)):
        k = 0
        a, b, char = policies[i]
        if passwords[i][a - 1] == char and passwords[i][b - 1] != char:
            k += 1
        if passwords[i][a - 1] != char and passwords[i][b - 1] == char:
            k += 1
        if k == 1:
            correct += 1
    return correct


if __name__ == "__main__":
    with open("input.txt") as f:
        policies = []
        passwords = []
        for s in f.readlines():
            fields = s.split(" ")
            l, m = (int(i) for i in fields[0].split("-"))
            policies.append((l, m, fields[1][:-1]))
            passwords.append(fields[2][:-1])
    print(policies, passwords)
    print(correct_passwords(policies, passwords))
