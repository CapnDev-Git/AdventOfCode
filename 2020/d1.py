def tax_report(num):
    for n in range(len(num)):
        for m in range(n + 1, len(num)):
            for o in range(m + 1, len(num)):
                if num[n] + num[m] + num[o] == 2020:
                    return num[n] * num[m] * num[o]


if __name__ == "__main__":
    with open("input.txt") as f:
        num = [int(i) for i in f.readlines()]
    print(tax_report(num))
