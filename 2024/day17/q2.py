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
    
    sa = 0
    sb = b
    sc = c
    while output != program:
        output = []
        # print(program, output)
        sa += 1
        a = sa
        b = sb
        c = sc
        
        if sa % 1_000_000 == 0:
            print(sa)
        # print(f"Testing a: {a} {b} {c}")
        
        i = 0
        pos = 0
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
                val = get_combo(operand) % 8
                if val != program[pos]:
                    break
                pos += 1
                output.append(val)
            elif op == 6:
                b = a // (2 ** get_combo(operand))
            elif op == 7:
                c = a // (2 ** get_combo(operand))
            
            # print(op, operand)
            # print(a, b, c)
            
            i += 2
        
        # print(','.join(map(str, output)))
    print(sa)