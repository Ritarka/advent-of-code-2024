import re

with open("input1.txt") as f:
    line = f.readline()
    
print(line)

muls = re.findall("mul\([0-9]+,[0-9]+\)", line)
print(muls)


sum = 0
for mul in muls:
    paran = mul.find("(")
    comma = mul.find(",")
    close = mul.find(")")
    a = int(mul[paran+1:comma])
    b = int(mul[comma+1:close])
    
    sum += a * b
print(sum)