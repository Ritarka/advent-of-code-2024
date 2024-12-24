with open("input.txt") as f:
    num = f.readline()

disk = ""
for i in range(len(num)):
    if i % 2 == 0:
        disk += (chr(i // 2 + 48) * int(num[i]))
        assert num[i] != 0
    else:
        disk += '.' * int(num[i])
        
print(disk)
# exit()
disk = list(disk)

r = len(disk) - 1
visited = set()
while r > 0:
    while r >= 0 and disk[r] == '.':
        r -= 1
    
    count = 0
    num = disk[r]
    
    if num in visited:
        r -= 1
        continue
    
    visited.add(num)
    while r >= 0 and disk[r] == num:
        count += 1
        r -= 1
        
    # print(disk[r+1:r+count+1])

    l = 0
    while l <= r:
        while l < len(disk) and disk[l] != '.':
            l += 1
        # print(disk[l])
        space = 0
        while l < len(disk) and disk[l] == '.':
            space += 1
            l += 1
        # print(l - space, r + 1, disk[l-space], disk[r+1])
        if l - space > r + 1:
            break

        if space >= count:
            disk[l-space:l-space+count], disk[r+1:r+count+1] = disk[r+1:r+count+1], disk[l-space:l-space+count]
            # print("".join(disk))
            break
       
# print("".join(disk))
            
sum = 0
for i in range(len(disk)):
    if disk[i] == '.':
        continue
    sum += i * (ord(disk[i]) - 48)
print(sum)