from rich import print

rules_list = []
queries = []

with open("input.txt") as f:
    lines = f.readlines()
    
    passed = False
    for line in lines:
        line = line.strip()
        if line == "":
            passed = True
            continue
        if passed:
            queries.append(line)
        else:
            rules_list.append(line)     
               
    
print(rules_list)
print(queries)


rules = {}
for rule in rules_list:
    a, b = list(map(int, rule.split("|")))

    if a not in rules:
        rules[a] = {}
    if b not in rules:
        rules[b] = {}

    rules[a][b] = 1
    rules[b][a] = -1

print(rules)

new_queries = []
for queury in queries:
    new_queries.append(list(map(int, queury.split(","))))
queries = new_queries
print(queries)

sum = 0
for query in queries:
    okay = True

    for i in range(len(query)):
        a = query[i]
        for j in range(i, len(query)):
            b = query[j]
            if b not in rules[a]: continue
            if rules[a][b] == -1: 
                okay = False
                break
        if not okay:
            while not okay:
                okay = True
                for i in range(len(query)):
                    a = query[i]
                    for j in range(i, len(query)):
                        b = query[j]
                        if b not in rules[a]: continue
                        if rules[a][b] == -1: 
                            okay = False
                            query[i], query[j] = query[j], query[i]
                            break
    
            sum += query[len(query) // 2]
print(sum)