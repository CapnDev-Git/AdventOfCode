def execute_bootcode_until_infinite(program):
    acc = 0
    addr = 0
    visited = set()

    while addr < len(program):
        if addr in visited:  # Infinite loop detected
            return acc, False
        visited.add(addr)

        instr, val = program[addr]
        if instr == "jmp":
            addr += val
        else:  # Handles both "nop" and "acc"
            if instr == "acc":
                acc += val
            addr += 1

    # If we exit the loop normally, the program terminated successfully
    return acc, True


def fix_program(program):
    for i in range(len(program)):
        instr, val = program[i]

        # Only try to flip "nop" and "jmp"
        if instr not in ("nop", "jmp"):
            continue

        # Create a modified program with the current instruction flipped
        modified_program = program[:]
        modified_program[i] = ("jmp" if instr == "nop" else "nop", val)

        # Execute the modified program
        acc, terminated = execute_bootcode_until_infinite(modified_program)

        if terminated:  # If the program terminates, we've found the fix
            return acc

    return None  # If no fix is found


if __name__ == "__main__":
    with open("input.txt") as f:
        program = []
        for s in f.readlines():
            instr, val = s.split()
            program.append((instr, int(val)))

        print(f"Accumulator value after fixing the program: {fix_program(program)}")
