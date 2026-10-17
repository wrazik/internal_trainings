f = lambda x: x.upper()

print(f("duze literki"))
print(f("tutaj tez duze literki"))

print()

# Reverse string
print("wojtek"[::-1])

names = ["wojtek", "piotrek", "kajtek"]
print(sorted(names))
print(sorted(names, key = lambda word: word[::-1]))


print()
names = ["kajak", "sedes", "zakaz", "sos", "potop"]
print(sorted(names, key = lambda word: word[::-1]))

print()
numbers = [1, 2, 3, 4, 5]
print(list(map(lambda i: i*2, numbers)))
