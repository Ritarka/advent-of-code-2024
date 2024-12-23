with open("input.txt") as f:
    lines = f.readlines()
    
sum = 0
for line in lines:
    num = int(line)
    
    secret = num
    for i in range(2000):
        shift = secret << 6
        secret = (shift ^ secret) % 16777216
        
        shift = secret >> 5
        secret = (shift ^ secret) % 16777216

        shift = secret << 11
        secret = (shift ^ secret) % 16777216
        
    print(f"{num}: {secret}")
    sum += secret
    
print(sum)
