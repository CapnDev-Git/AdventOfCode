def sign(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0


def is_safe_report(report):
    prev_diff = report[1] - report[0]
    if abs(prev_diff) < 1 or abs(prev_diff) > 3:
        return False

    prev_sign = sign(prev_diff)
    for i in range(1, len(report) - 1):
        diff = report[i + 1] - report[i]
        if abs(diff) < 1 or abs(diff) > 3 or sign(diff) != prev_sign:
            return False
        prev_sign = sign(diff)
    return True


def find_safe_reports(reports):
    safe_count = 0
    for report in reports:
        if is_safe_report(report):
            safe_count += 1
            continue

        for i in range(len(report)):
            modified_report = report[:i] + report[i + 1 :]
            if is_safe_report(modified_report):
                safe_count += 1
                break
    return safe_count


if __name__ == "__main__":
    with open("2024/input.txt") as f:
        reports = []
        for report in f.readlines():
            reports.append([int(level) for level in report.split(" ")])
        print(find_safe_reports(reports))
