from rich import print

with open("test3.txt") as f:
    lines = f.readlines()
    
empty = False
values = {}
ops = set()
for line in lines:
    line = line.strip()
    if line == "":
        empty = True
        continue
        
    if empty:
        ops.add(line)
    else:
        wire, val = line.split(": ")
        print(wire, val)
        values[wire] = int(val)
        
for value in values:
    if value[0] == 'x':
        values[value] = 0
    else:
        values[value] = 1
        
# print(ops)

xs = []
ys = []
zs = []

level = 0
opa = "x00"
opb = "y00"
out = "z00"
carry_out = None
carry_in = None

map = {}

while len(ops):
    remove = []
    for line in ops:
        a, op, b, arr, c = line.split()
                
        if (a[0] == 'x' and b[0] == 'y') or (a[0] == 'y' and b[0] == 'x'):
            if c[0] != 'z':
                if op == "AND":
                    nc = 'a' + a[1:]
                    map[c] = nc
                elif op == "XOR":
                    nc = 'w' + a[1:]
                    if nc == "w00":
                        nc = "c00"
                    map[c] = nc
                else:
                    raise Exception("Should not happen!")  
                c = nc
            # print(a, op, b, arr, c)
        
            remove.append(line)
        else:
            if a not in map or b not in map: continue
            a = map[a]
            b = map[b]
            
            if a > b:
                a, b = b, a
                
            if a[0] == 'a' and b[0] == 'c' and op == "AND":
                nc = 'b' + b[1:]
                map[c] = nc
                c = nc
                remove.append(line)
            elif a[0] == 'a' and b[0] == 'c' and op == "XOR":
                assert int(a[1:]) + 1 == int(b[1:]) and int(b[1:]) == int(c[1:])
                remove.append(line)
            elif a[0] == 'a' and b[0] == 'b' and op == "OR":
                nc = 'c' + b[1:]
                map[c] = nc
                c = nc

                remove.append(line)
            
            print(a, op, b, arr, c)
        
    for line in remove:
        # print(line)
        ops.remove(line)