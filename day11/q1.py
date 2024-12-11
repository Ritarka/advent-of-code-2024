with open("input.txt") as f:
    line = f.readline()
numbers = line.split()
numbers = list(map(int, numbers))


print(numbers)

for i in range(1, 76):
    new_numbers = []
    for number in numbers:
        if number == 0:
            new_numbers.append(1)
        elif len(str(number)) % 2 == 0:
            string = str(number)
            length = len(string)
            new_numbers.append(int(string[:length//2]))
            new_numbers.append(int(string[length//2:]))
        else:
            new_numbers.append(number * 2024)
    numbers = new_numbers
    
    # print(new_numbers)
    # exit()
    
    if i < 7:
        print(numbers)
    print(f"{i}: {len(numbers)}")