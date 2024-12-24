# Keypad Layout
keypad = [
    ['X', '^', 'A'],
    ['<', 'v', '>'],
]

# Start position at 'A'

# Movement instructions
instructions = "<v<A>>^AvA^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A"
# instructions = "v<<A>>^AvA^Av<<A>^>AA<vA<A>^>AAvAA^<A>A<vA^>AA<A>Av<A<A>>^AAA<A>vA^A"


# good: <A>Av<<AA>^AA>AvAA^A<vAAA>^A
# bad:  <A>A<AAv<AA>>^AvAA^Av<AAA^>A

# Direction mappings
moves = {
    '^': (-1, 0),  # Up
    'v': (1, 0),   # Down
    '<': (0, -1),  # Left
    '>': (0, 1)    # Right
}

# Helper function to check if a move is valid
def is_valid(pos):
    r, c = pos
    return 0 <= r < len(keypad) and 0 <= c < len(keypad[r])

# Decode the instructions
start_pos = (0, 2)
current_pos = start_pos
pressed_buttons = []

for char in instructions:
    if char in moves:
        # Calculate new position
        new_pos = (current_pos[0] + moves[char][0], current_pos[1] + moves[char][1])
        # print(char, new_pos)
        if not is_valid(new_pos):
            raise Exception("Wrong")
        current_pos = new_pos
    elif char == 'A':
        # Record the button at the current position
        pressed_buttons.append(keypad[current_pos[0]][current_pos[1]])

# Output the result
print("Pressed buttons:", ''.join(pressed_buttons))

instructions = ''.join(pressed_buttons)

start_pos = (0, 2)
current_pos = start_pos
pressed_buttons = []

for char in instructions:
    if char in moves:
        # Calculate new position
        new_pos = (current_pos[0] + moves[char][0], current_pos[1] + moves[char][1])
        if not is_valid(new_pos):
            raise Exception("Wrong2")
        current_pos = new_pos
    elif char == 'A':
        # Record the button at the current position
        pressed_buttons.append(keypad[current_pos[0]][current_pos[1]])

# Output the result
print("Pressed buttons:", ''.join(pressed_buttons))
