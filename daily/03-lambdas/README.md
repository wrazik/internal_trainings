# Lamba & callable class

## How many different callable types in python?
They are 9!

-------
 1. User defined function
 2. Built-in functions, e.g. len
 3. Built-in methods, e.g. dict.get()
 4. Methods
 5. Classes, when Invoked class run __new__ and then __init__
 6. Class instances (with __call__)
___
 7. Generator functions (use yield in body)
 8. Native coroutines functions (defined with async)
 9. Asynchronous generator functions (async def & yield in their body, when called, returns async generator)
---
 Last 3 callables are `special` - they don't return application data but something that needs some extra work

## Examples
Simplest lambda example:
```python
f = lambda x: x.upper()
print(f("duze literki"))
# Will print "DUZE LITERKI"
```

Another example - using lambdas in High-Order-Functions:
```python
names = ["wojtek", "piotrek", "kajtek"]
print(sorted(names)) # sorted
print(sorted(names, key = lambda word: word[::-1])) # sorted by reversed word

names = ["kajak", "sedes", "zakaz", "sos", "potop"]
print(sorted(names, key = lambda word: word[::-1])) # sorted by reversed word
```

Map below returns generator, so conversion to list is needed
```python
numbers = [1, 2, 3, 4, 5]
print(list(map(lambda i: i*2, numbers))) # function-style, returns modified array
```

Lambdas MUST BE SHORT. If they are not, here is refactoring recipe:
```
FREDRIK LUNDH’S LAMBDA REFACTORING RECIPE
If you find a piece of code hard to understand because of a lambda, Fredrik Lundh suggests this refactoring procedure:
1. Write a comment explaining what the heck that lambda does.
2. Study the comment for a while, and think of a name that captures the essence of the comment.
3. Convert the lambda to a def statement, using that name.
4. Remove the comment.
These steps are quoted from the “Functional Programming HOWTO”, a must read.
```

## Lambda limitation
Biggest lambda limitation is that the body must be _pure expression_. In other words, body cannot contain other Python 
statements like while, try etc. Only allowed expression is walrus operator `:=`.

We can `hack` the limtation, using tuple & walrus operator. Full example:
```python
def as_f(a, b):
    a = a + b
    b = b + a
    return a + b

as_l = lambda a,b: (a:=a+b, b:=b+a, a+b)[-1]

print(as_f(21, 37))
print(as_l(21, 37))
```

## Callable class
To implement `callable` class, user needs to implement `__call__` method:
```python
import random

class BingoCage:
    def __init__(self, items):
        self._items = list(items)
        random.shuffle(self._items)

    def pick(self):
        try:
            return self._items.pop()
        except IndexError:
            raise LookupError('pick from empty BingoCage')

    def __call__(self):
        return self.pick()


words = ["kot", "pies", "ziemniak", "informatyk", "żaba", "student", "AI", "mops", "papiez", "polak", "wielki", "Adam Malysz", "Mariusz pudzianowski", "krowa", "papuga", "pingwin", "minister", "robot", "chomik", "programista", "tańczy", "krzyczy", "śpiewa", "biega", "myśli", "maluje", "pisze", "programuje", "filozofuje", "ucieka", "gotuje", "tańczy", "zjada", "płacze", "śmieje", "tańczy", "kombinuje", "projektuje", "marzy", "rzuca", "kopiuje", "przemawia", "przelicza", "świeci", "lata", "gapi", "leży", "rozmawia", "kradnie", "śpi", "tańczy", "wymyśla", "sra", "na", "pod", "za", "w", "z", "przy", "obok", "między", "sernikiem", "klawiaturą", "drukarką", "bananem", "księżycem", "mikrofalówką", "kanapą", "komputerem", "kawą", "śmietaną", "ziarniem", "spaghetti", "kapeluszem", "lodówką", "biurkiem", "bo", "chociaż", "dlatego", "że", "jak", "gdy", "ponieważ", "niechcący", "znowu", "nagle", "zawsze", "czasem", "wczoraj", "dziś", "jutro", "wiecznie", "bez", "powodu", "dla", "sławy" ]
bingo = BingoCage(words)

print( bingo.pick() )
print( bingo()      )
print( bingo()      )

print(callable(bingo))
```
