# Assigning to slices

l = list(range(10))
print(l)
l[2:5] = [20, 30]
print(f"[2:5]=[20,30] ->  {l}")
del l[5:7]
l[3::2] = [11, 22]
print(f"l[3::2] = [11, 22] -> {l}")

# l[2:4] = 100  # this will not work, not iterable
l[2:4] = [100]
print(l)

# ========================================================
print()
# multiplying arrays
l = [1, 2, 3]
print(l * 5)

print()
weird_board = [['-'] * 3] * 3
print(weird_board)
weird_board[1][2] = 'x'
print(weird_board)

# This is the same as above
print()
row = ['_'] * 3
board = []
for i in range(3):
    board.append(row)
board[1][2] = "X"
print(board)


# ========================================================
board = [['_'] * 3 for i in range(3)]
print(board)
board[1][2] = 'X'
print(board)

# This is the same as above
board = []
for i in range(3):
    row = ['_'] * 3
    board.append(row)

board[1][2] = 'X'
print(board)