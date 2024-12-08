# from tqdm import tqdm

def base3(num):
    acc = ""
    while num:
        remainder = num % 3
        num = num // 3
        acc += str(remainder)
    acc = acc[::-1]
    if acc == "": acc = "0"
    return acc

with open("input.txt") as f:
    lines = f.readlines()

valid = 0
for line in lines:
    target, elements = line.split(":")
    target = int(target)
    nums = list(map(int, elements.split()))
    # print(target)
    # print(nums)
    
    size = len(nums) - 1
    max_size = 3 ** size - 1
    
    i = 0
    while i <= max_size:
        # str_rep = format(i, f"0{size}b")
        str_rep = base3(i)
        str_rep = ("0" * (size - len(str_rep))) + str_rep
        assert len(str_rep) == size, f"{str_rep}...{size}, {i}"
        sum = nums[0]
        # print(str_rep)
        for j in range(size):
            # print(str_rep[j], nums[j+1], sum)
            if str_rep[j] == '0':
                sum += nums[j+1]
            elif str_rep[j] == '1':
                sum *= nums[j+1]
            elif str_rep[j] == '2':
                sum = int(str(sum) + str(nums[j+1]))
            else:
                raise Exception(f"Got something weird of type {type(str_rep[j])} and value {str_rep[j]}")

            if sum > target:
                break
        
        if sum == target:
            # print(f"{target} = {nums[0]}", end=" ")
            # for j in range(size-1):
            #     if str_rep[j] == '0':
            #         print(f"+ {nums[j+1]}", end=" ")
            #     elif str_rep[j] == '1':
            #         print(f"* {nums[j+1]}", end=" ")
            #     elif str_rep[j] == '2':
            #         print(f"|| {nums[j+1]}", end=" ")
            # print()
            valid += target
            break
            
        i += 1
print(valid)

    

# base3(0)
# base3(1)
# base3(2)
# base3(3)
# base3(4)
# base3(5)
# base3(6)
# base3(7)
# base3(8)
# base3(9)



