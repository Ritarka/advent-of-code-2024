with open("input.txt") as f:
    a = int(f.readline().split()[2])
    b = int(f.readline().split()[2])
    c = int(f.readline().split()[2])
    
    print(a, b, c)
    
    f.readline()
    
    program = list(map(int, f.readline().split()[1].split(",")))
    print(program)
    
    def get_combo(num: int):
        if num < 4:
            return num
        elif num == 4:
            return a
        elif num == 5:
            return b
        elif num == 6:
            return c
        
    output = []
    
    # a = 117440
    
    i = 0
    while i < len(program):
        op = program[i]
        operand = program[i+1]
        
        if op == 0:
            a = a // (2 ** get_combo(operand))
        elif op == 1:
            b = b ^ operand
        elif op == 2:
            b = get_combo(operand) % 8
        elif op == 3:
            if a != 0:
                i = operand
                continue
        elif op == 4:
            b = b ^ c
        elif op == 5:
            output.append(get_combo(operand) % 8)
            # print(a, b % 8, c)
        elif op == 6:
            b = a // (2 ** get_combo(operand))
        elif op == 7:
            c = a // (2 ** get_combo(operand))
        
        # print(op, operand)
        
        i += 2
        
    print(','.join(map(str, output)))