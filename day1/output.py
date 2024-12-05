a = []
b = []

with open("input.txt") as f:
    lines = f.readlines()

for line in lines:    
    segments = line.split()
    a.append(int(segments[0]))
    b.append(int(segments[1]))
    
sum = 0
a = sorted(a)
b = sorted(b)
for (c, d) in zip(a, b):
    sum += abs(c - d)
    
print(sum)