okay = 0

def check_valid(int_arr):
    assert len(int_arr) > 2
    valid = True
    
    decreasing = True
    if int_arr[0] < int_arr[1]:
        decreasing = False
    
    l = 0
    r = 1
    while r < len(int_arr):
        diff = (int_arr[l] - int_arr[r])
        if (decreasing and (diff < 1 or diff > 3)) or (not decreasing and (diff > -1 or diff < -3)):
            valid = False
            break
        
        l = r
        r += 1
        
    if valid:
        # if not tolerate:
        # print(int_arr)
        return 1
    return 0        


with open("q1.txt") as f:
    lines = f.readlines()
    
for line in lines:
    int_arr = list(map(int, line.split()))
    right = check_valid(int_arr)
    if not right:
        for i in range(len(int_arr)):
            # print(len(int_arr))
            # print(int_arr)
            # print(i)
            arr = int_arr[:]
            del arr[i]
            print(arr)
            right = check_valid(arr)
            if right:
                break
    okay += right
        


print(okay)