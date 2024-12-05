okay = 0

def check_valid(int_arr):
    assert len(int_arr) > 2
    valid = True
    
    decreasing = True
    if int_arr[0] < int_arr[1]:
        decreasing = False
    
    l = 0
    r = 1
    tolerate = True
    while r < len(int_arr):
        diff = (int_arr[l] - int_arr[r])
        if (decreasing and (diff < 1 or diff > 3)) or (not decreasing and (diff > -1 or diff < -3)):
            if tolerate:
                tolerate = False
                r += 1
                continue
            else:
                valid = False
                break
        
        l = r
        r += 1
        
    if valid:
        # if not tolerate:
        print(int_arr)
        return 1
    
    valid = True
    decreasing = True
    if int_arr[0] < int_arr[2]:
        decreasing = False
    
    l = 0
    r = 2
    while r < len(int_arr):
        diff = (int_arr[l] - int_arr[r])
        if (decreasing and (diff < 1 or diff > 3)) or (not decreasing and (diff > -1 or diff < -3)):
            valid = False
            break
        
        l = r
        r += 1
        
    if valid:
        print("Second round")
        # if not tolerate:
        print(int_arr)
        return 1
    
    # print(int_arr)
    valid = True
    decreasing = True
    if int_arr[0] < int_arr[2]:
        decreasing = False
    
    l = 0
    r = 2
    while r < len(int_arr):
        diff = (int_arr[l] - int_arr[r])
        if (decreasing and (diff < 1 or diff > 3)) or (not decreasing and (diff > -1 or diff < -3)):
            valid = False
            break
        
        l = r
        r += 1
        
    if valid:
        # print("Second round")
        # if not tolerate:
        # print(int_arr)
        return 1
    
    valid = True
    decreasing = True
    if int_arr[1] < int_arr[2]:
        decreasing = False
    
    l = 1
    r = 2
    while r < len(int_arr):
        diff = (int_arr[l] - int_arr[r])
        if (decreasing and (diff < 1 or diff > 3)) or (not decreasing and (diff > -1 or diff < -3)):
            valid = False
            break
        
        l = r
        r += 1
        
    if valid:
        print("Third round")
        # if not tolerate:
        print(int_arr)
        return 1
    return 0
        


with open("q1.txt") as f:
    lines = f.readlines()
    
for line in lines:
    int_arr = list(map(int, line.split()))
    okay += check_valid(int_arr)
    
# check_valid([7, 6, 4, 2, 1])
# check_valid([1, 2, 7, 8, 9])
# check_valid([9, 7, 6, 2, 1])
# check_valid([1, 3, 2, 4, 5])
# check_valid([8, 6, 4, 4, 1])
# check_valid([1, 3, 6, 7, 9])


# check_valid([1, 6, 2, 4, 5])
# check_valid([1, 6, 2])
# check_valid([1, 6, 9])



print(okay)