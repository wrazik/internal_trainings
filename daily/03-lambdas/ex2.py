some_value = (print("x"), print("y"))

some_value = (print("x"), print("y"), 42)[-1]
print(some_value)

l = lambda x: (
    print(f"Before: {x}"),
    x.upper()
)[-1]

print(l("twoja"))
print(l("stara"))

print()
l = lambda x, y: (
    z:=x+y
)

print(l(1, 2))
print(l(1, 2))
