from rich import print

with open("input.txt") as f:
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
        
# print(ops)

xs = []
ys = []
zs = []

ands = {}
bad = []
for line in ops:
    a, op, b, arr, c = line.split()
    
    if a > b:
        a, b = b, a
    
    if c[0] == 'z':
        if c == 'z45': continue
        if op != "XOR": 
            bad.append(c)
            print(line)
    elif op == "XOR":
        if not (a[0] == 'x' and b[0] == 'y') and not c[0] == 'z':
            print(line)
            bad.append(c)
    if op == "AND":
        ands[c] = 1
        
print(ands)
for line in ops:
    a, op, b, arr, c = line.split()
    if op == 'OR':
        if a not in ands:
            bad.append(a)
        if b not in ands:
            bad.append(b)
        print(line)
            
bad = sorted(set(bad))
print(','.join(bad))
