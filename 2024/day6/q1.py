from rich import print

arr = []
with open("input.txt") as f:
    lines = f.readlines()
    for line in lines:
        arr.append(line.split())
        
print(arr)


for row in arr:
    for pos in row: