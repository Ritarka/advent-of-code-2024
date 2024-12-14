# rows = 7
# cols = 11
from PIL import Image
import numpy as np

rows = 103
cols = 101


pos = []
vels = []

with open("input.txt") as f:
    while True:
        line = f.readline()
        if not line:
            break
        p, v = line.split()
        px, py = p.split("=")[1].split(",")
        vx, vy = v.split("=")[1].split(",")
        
        # print(px, py, vx, vy)
        px = int(px)
        py = int(py)
        vx = int(vx)
        vy = int(vy)
        
        # fx = (px + vx * 100) % cols
        # fy = (py + vy * 100) % rows
        
        pos.append([px, py])
        vels.append((vx, vy))
        
min_variance = float('inf')
best_iteration = -1

for i in range(100 * 103):
    image = Image.new('1', (cols, rows))

    # Fill the image with a checkerboard pattern for demonstration
    pixels = image.load()
    locs_x = []
    locs_y = []

    for loc, vel in zip(pos, vels):
        loc[0] = (loc[0] + vel[0]) % cols
        loc[1] = (loc[1] + vel[1]) % rows
        pixels[loc[0], loc[1]] = 1
        locs_x.append(loc[0])
        locs_y.append(loc[1])

    # Calculate variance for loc[0] and loc[1]
    variance_x = np.var(locs_x)
    variance_y = np.var(locs_y)
    total_variance = variance_x + variance_y

    if total_variance < min_variance:
        min_variance = total_variance
        best_iteration = i

    image.save(f"{i}.bmp")

print(f"Iteration with least variance: {best_iteration}, Variance: {min_variance}")

        