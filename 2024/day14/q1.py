# rows = 7
# cols = 11

rows = 103
cols = 101


pos = []

with open("input.txt") as f:
    while True:
        line = f.readline()
        if not line:
            break
        p, v = line.split()
        px, py = p.split("=")[1].split(",")
        vx, vy = v.split("=")[1].split(",")
        
        # print(px, py, vx, vy)
        px = int(px)
        py = int(py)
        vx = int(vx)
        vy = int(vy)
        
        fx = (px + vx * 100) % cols
        fy = (py + vy * 100) % rows
        
        pos.append((fx, fy))
        
# print(pos)
print(len(pos))
arr = [0, 0, 0, 0]
for x, y in pos:
    if x < cols // 2 and y < rows // 2:
        arr[0] += 1
    elif x < cols // 2 and y > rows // 2:
        arr[2] += 1
    elif x > cols // 2 and y > rows // 2:
        arr[3] += 1
    elif x > cols // 2 and y < rows // 2:
        arr[1] += 1
        
print(arr)
prod = 1
for num in arr:
    prod *= num
print(prod)