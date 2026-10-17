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
