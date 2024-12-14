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
    
        cdist = (int(cx) + 10000000000000, int(cy) + 10000000000000)
        # cdist = (int(cx), int(cy))
        
        # print(adist, bdist, cdist)
        denominator = adist[0] * bdist[1] - bdist[0] * adist[1]
        # print(denominator)
        assert denominator != 0
        a = bdist[1] * cdist[0] - bdist[0] * cdist[1]
        b = -adist[1] * cdist[0] + adist[0] * cdist[1]
        
        a /= denominator
        b /= denominator
        
        # print(a, b)
        if a % 1 == 0 and b % 1 == 0:
            total += a * 3 + b
        
print(total)
        # exit()