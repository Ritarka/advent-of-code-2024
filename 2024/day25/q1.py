# from rich import print

with open("input.txt") as f:
    lines = f.readlines()
    
keys = []
locks = []
object = []
key = True
for line in lines:
    line = line.strip()
    if line == "":
        rows = [0] * 5
        for i in range(5):
            count = -1
            for j in range(7):
                if object[j][i] == '#':
                    count += 1
            rows[i] = count
        # print(rows)
        if key:
            keys.append(rows)
        else:
            locks.append(rows)
            
        object.clear()
        key = True
        continue
            
    if line == "#####" and len(object) == 0:
        key = False
    object.append(line)
    
    
rows = [0] * 5
for i in range(5):
    count = -1
    for j in range(7):
        if object[j][i] == '#':
            count += 1
    rows[i] = count
# print(rows)
if key:
    keys.append(rows)
else:
    locks.append(rows)
    
object.clear()
key = True

    
print(len(keys))
print(len(locks))

print(f"Total: {len(keys) * len(locks)}")

count = 0
for lock in locks:
    for key in keys:
        okay = True
        for i in range(len(key)):
            if lock[i] + key[i] >= 6:
                okay = False
                break
        if not okay:
            continue
        # print(lock, key, sep=" ")
        count += 1
            
print(count)