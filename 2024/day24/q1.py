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

zs = []
while len(ops):
    remove = []
    for line in ops:
        a, op, b, arr, c = line.split()
        
        if not a in values or b not in values: continue
        if op == "AND":
            values[c] = values[a] and values[b]
        elif op == "OR":
            values[c] = values[a] or values[b]        
        elif op == "XOR":
            values[c] = values[a] ^ values[b]
        else:
            raise Exception("Never!!")
        if c[0] == 'z': zs.append(c)
        remove.append(line)
        
    for line in remove:
        ops.remove(line)
        
zs = sorted(zs, reverse=True)
print(zs)
string = ""
for z in zs:
    # print(values[z])
    string += str(values[z])

print(string)
print(int(string, 2))