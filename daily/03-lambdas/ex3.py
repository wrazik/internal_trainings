def as_f(a, b):
    a = a + b
    b = b + a
    return a + b

as_l = lambda a,b: (a:=a+b, b:=b+a, a+b)[-1]

print(as_f(21, 37))
print(as_l(21, 37))
