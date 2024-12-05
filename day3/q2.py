import re

with open("input1.txt") as f:
    line = f.readline()
    
# print(line)
line += "do()"

muls = re.finditer("mul\([0-9]+,[0-9]+\)", line)
mult_indices = [m.span() for m in muls]
# print(mult_indices)


muls = re.finditer("do(?:n\'t)?\(\)", line)
control_indices = [m.span() for m in muls]
# print(control_indices)

control_ptr = 0
do = True

sum = 0
for mult in mult_indices:
    mul = line[mult[0]:mult[1]]
    
    while mult[0] > control_indices[control_ptr][0]:
        if line[control_indices[control_ptr][0]:control_indices[control_ptr][1]] == "do()":
            do = True
        else:
            do = False
        # print(control_ptr)
        print(line[control_indices[control_ptr][0]:control_indices[control_ptr][1]])
        control_ptr += 1
            
    if not do:
        continue 
    print(mul)
    
    paran = mul.find("(")
    comma = mul.find(",")
    close = mul.find(")")
    a = int(mul[paran+1:comma])
    b = int(mul[comma+1:close])
    
    sum += a * b
print(sum)