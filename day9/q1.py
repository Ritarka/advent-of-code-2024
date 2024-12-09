with open("input.txt") as f:
    num = f.readline()
    # print(num)

disk = ""
for i in range(len(num)):
    if i % 2 == 0:
        disk += (chr(i // 2 + 48) * int(num[i]))
        # print(chr(i//2 + 42))
    else:
        disk += '.' * int(num[i])
    # print(disk)
print(disk)
disk = list(disk)
# disk = ['.', '1']
l = 0
r = len(disk) - 1
while l < r:
    while l < len(disk) and disk[l] != '.':
        l += 1
    if l >= len(disk): break
    while r >= 0 and disk[r] == '.':
        r -= 1
    if r < 0: break
    if l >= r: continue
    print(l, r, disk[l], disk[r])
    disk[l], disk[r] = disk[r], disk[l]
    l += 1
    r -= 1
            
# print("".join(disk))
sum = 0
done = False
for i in range(len(disk)):
    if disk[i] == '.':
        done = True
        continue
    if done:
        raise Exception("Not properly shifted!!!")

    sum += i * (ord(disk[i]) - 48)
print(sum)