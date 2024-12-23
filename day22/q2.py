import queue

with open("input.txt") as f:
    lines = f.readlines()
    
global_dict = {}
sum = 0
for line in lines:
    num = int(line)
    # num = 123
    
    prev = None
    price = num % 10
    diff = 0
    secret = num
    
    local_dict = {}
    string = ""
    for i in range(2000):
        shift = secret << 6
        secret = (shift ^ secret) % 16777216
        
        shift = secret >> 5
        secret = (shift ^ secret) % 16777216

        shift = secret << 11
        secret = (shift ^ secret) % 16777216

        prev = price
        price = secret % 10
        if prev is not None:
            diff = price - prev
            string += str(diff) + ","
            if i >= 4:
                string = string[string.find(',')+1:]
                if string in local_dict:
                    continue
                local_dict[string] = 1
                if string not in global_dict:
                    global_dict[string] = 0
                global_dict[string] += price
                
        # print(string, price)
        
    # break
    print(f"{num}: {secret}")
    sum += secret
    
# print(sum)

maxi = 0
sol = None
for key, elem in global_dict.items():
    # print(key, elem)
    if elem > maxi:
        maxi = elem
        sol = key
print("Solution:", sol, maxi)