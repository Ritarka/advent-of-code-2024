with open("input.txt") as f:
    line = f.readline()
numbers = line.split()
numbers_l = list(map(int, numbers))

numbers = {}
for number in numbers_l:
    if number not in numbers:
        numbers[number] = 0
    numbers[number] += 1

print(numbers)

for i in range(1, 76):
    new_numbers = {}
    for number, count in numbers.items():
        if number == 0:
            if 1 not in new_numbers:
                new_numbers[1] = 0
            new_numbers[1] += numbers[0]
        elif len(str(number)) % 2 == 0:
            string = str(number)
            length = len(string)
            
            if int(string[:length//2]) not in new_numbers:
                new_numbers[int(string[:length//2])] = 0
            if int(string[length//2:]) not in new_numbers:
                new_numbers[int(string[length//2:])] = 0
            
            new_numbers[int(string[:length//2])] += count
            new_numbers[int(string[length//2:])] += count
        else:
            if number * 2024 not in new_numbers:
                new_numbers[number * 2024] = 0
            new_numbers[number * 2024] += count
            
    numbers = new_numbers
    
    if i < 7:
        print(numbers)
    sum = 0
    for number, count in numbers.items():
        sum += count
    print(f"{i}: {sum}")