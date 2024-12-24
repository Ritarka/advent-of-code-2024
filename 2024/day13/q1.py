total = 0

with open("input.txt") as f:
    while True:
        a = f.readline()
        b = f.readline()
        c = f.readline()

        buffer = f.readline()
        
        if a == "": break
        
        ax, ay = a.split()[2:]
        ax = ax[ax.find("+")+1:ax.find(",")]
        ay = ay[ay.find("+")+1:]
    
        adist = (int(ax), int(ay))
        
        bx, by = b.split()[2:]
        bx = bx[bx.find("+")+1:bx.find(",")]
        by = by[by.find("+")+1:]
    
        bdist = (int(bx), int(by))
        
        cx, cy = c.split()[1:]
        cx = cx[cx.find("=")+1:cx.find(",")]
        cy = cy[cy.find("=")+1:]
    
        cdist = (int(cx), int(cy))
        
        # print(adist, bdist, cdist)
        
        minimum = 1000000000000
        visited = set()
        stack = [(0, 0)]
        while len(stack):
            # print(stack)
            num = stack.pop()
            if num in visited:
                continue
            visited.add(num)
            pos = (num[0] * adist[0] + num[1] * bdist[0], num[0] * adist[1] + num[1] * bdist[1])
            if pos[0] == cdist[0] and pos[1] == cdist[1]:
                minimum = min(minimum, 3 * num[0] + num[1])
                continue
            elif pos[0] > cdist[0] or pos[1] > cdist[1]:
                continue
            # print("Testing: ", num, pos)
            stack.append((num[0] + 1, num[1]))
            stack.append((num[0], num[1] + 1))
            
        # print(minimum)
        if minimum < 1000000000000:
            total += minimum
print(total)
        # exit()