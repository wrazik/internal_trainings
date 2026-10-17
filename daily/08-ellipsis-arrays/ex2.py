array = [10, 20, 30, 40, 50, 60, 70]

print(array)
print("[index]")
print(f"[-2] = {array[-2]}")

print()
print("[start:stop]")
print(f"[-2:-1] = {array[-2:-1]}")

print()
print("[start:]")
print(f"[-2:] = {array[-2:]}") # last 2 elements

print()
print("[:stop]")
print(f"[:-2] = {array[:-2]}") # all except last 2

print()
print(array)
print("[start:stop:step]")
print(f"[::-1] = {array[::-1]}") # reversed
print(f"[::-2] = {array[::-2]}") # reversed every 2nd
print(f"[1::-1] = {array[1::-1]}") # reversed first two
print(f"[:-3:-1] = {array[:-3:-1]}") # reversed last two
print(f"[-3::-1] = {array[-3::-1]}") # reversed except last two

print()
print(type[::])
print(type[2::-1])

# array[::] calls __get_item__(slice(None, None, None))

print("Good practice: \n"
      "don't use all parameters: either only the last or the range\n"
      "don't use negative steps")

print("This works")
x = '寿司'
y = x[::-1]
print(y)
print("This one not")
w = '寿司'
x = w.encode('utf-8')
y = x[::-1]
z = y.decode('utf-8')
