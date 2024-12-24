a = []
b = {}

similarity = 0

with open("input.txt") as f:
    lines = f.readlines()

for line in lines:    
    segments = line.split()
    x = int(segments[0])
    y = int(segments[1])
    
    a.append(x)
    
    if y not in b:
        b[y] = 0
    b[y] += 1

for num in a:
    if num not in b: continue
    similarity += num * b[num]
print(similarity)