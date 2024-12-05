okay = 0
with open("q1.txt") as f:
    lines = f.readlines()
    
for line in lines:
    int_arr = list(map(int, line.split()))
    decreasing = True
    if int_arr[0] < int_arr[1]:
        decreasing = False
    valid = True
    for i in range(len(int_arr) - 1):
        diff = (int_arr[i] - int_arr[i+1])
        if decreasing and (diff < 1 or diff > 3):
            valid = False
            break
        if not decreasing and (diff > -1 or diff < -3):
            valid = False
            break
    if valid:
        okay += 1
    print(int_arr)
print(okay)