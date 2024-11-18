def find_target_sum(rolling, target):
    seen = set()
    for n in rolling:
        if n <= target:
            complement = target - n
            if complement in seen:
                print(f"found target {target} from {n} + {complement}")
                return True
            seen.add(n)
    return False


def find_invalid_number(numbers, pre_sz=25):
    rolling = numbers[:pre_sz]

    for i in range(pre_sz, len(numbers) - 1):
        target = numbers[i]
        if not find_target_sum(rolling, target):
            return target, i

        rolling.pop(0)
        rolling.append(numbers[i])
    return None


def find_contiguous_sum(numbers, target):
    start, current_sum = 0, 0

    for end in range(len(numbers)):
        current_sum += numbers[end]
        while current_sum > target:
            current_sum -= numbers[start]
            start += 1
        if current_sum == target:
            contiguous_range = numbers[start : end + 1]
            return min(contiguous_range) + max(contiguous_range)
    return None


if __name__ == "__main__":
    with open("input.txt") as f:
        numbers = [int(s.split("\n")[0]) for s in f.readlines()]
        print(numbers)
        print(f"problem: {find_contiguous_sum(numbers, 50047984)}")
