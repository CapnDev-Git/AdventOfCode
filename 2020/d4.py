def check_field_condition(key, val):
    if key == "byr":
        return 1920 <= int(val) <= 2002
    elif key == "iyr":
        return 2010 <= int(val) <= 2020
    elif key == "eyr":
        return 2020 <= int(val) <= 2030
    elif key == "hgt":
        if val[-2:] == "cm":
            return 150 <= int(val[:-2]) <= 193
        elif val[-2:] == "in":
            return 59 <= int(val[:-2]) <= 76
        return False
    elif key == "hcl":
        return (
            val[0] == "#"
            and all([c in "0123456789abcdef" for c in val[1:]])
            and len(val) == 7
        )
    elif key == "ecl":
        return val in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
    elif key == "pid":
        return len(val) == 9 and val.isdigit()
    elif key == "cid":
        return True


def check_passport(passport, optional="cid"):
    field_checker = {
        "byr": 0,
        "iyr": 0,
        "eyr": 0,
        "hgt": 0,
        "hcl": 0,
        "ecl": 0,
        "pid": 0,
        "cid": 1,
    }
    fields = passport.split(" ")

    for f in fields:
        key, val = tuple(f.split(":"))
        if key in field_checker:
            field_checker[key] += 1
            if not check_field_condition(key, val):
                return False
        else:
            return False
    return all([field_checker[k] == 1 for k in field_checker if k != optional])


def count_valid_passports(passports):
    valid = 0
    for p in passports:
        valid += 1 if check_passport(p) else 0
    return valid


if __name__ == "__main__":
    with open("input.txt") as f:
        passports = [p.replace("\n", " ") for p in f.read()[:-1].split("\n\n")]
        print(count_valid_passports(passports))
