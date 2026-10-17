class OutOfBananas(Exception):
    pass


def out_of_stock():
    print("no bzzzt")


def slice_bananas(count):
    print(f"banana {'chszt ' * count}")
    return count * 4


def make_smoothies(count):
    if count:
        print(f"{'bzzzt ' * count}")
        return f"{count}-banana-pieces smoothie"
    else:
        raise OutOfBananas


def smoothie_classic1(fresh_fruit):
    pieces = 0
    count = fresh_fruit.get("banana", 0)
    if count >= 2:
        pieces = slice_bananas(count)
    try:
        smoothies = make_smoothies(pieces)
        print(smoothies)
    except OutOfBananas:
        out_of_stock()


def smoothie_classic2(fresh_fruit):
    count = fresh_fruit.get("banana", 0)
    if count >= 2:
        pieces = slice_bananas(count)
    else:
        pieces = 0
    try:
        smoothies = make_smoothies(pieces)
        print(smoothies)
    except OutOfBananas:
        out_of_stock()


def smoothie_walrus(fresh_fruit):
    if (count := fresh_fruit.get("banana", 0)) >= 2:
        pieces = slice_bananas(count)
    else:
        pieces = 0
    try:
        smoothies = make_smoothies(pieces)
        print(smoothies)
    except OutOfBananas:
        out_of_stock()


fresh_fruit = {
    "apple": 10,
    "banana": 2,
    "lemon": 0,
}

smoothie_classic1(fresh_fruit)
smoothie_classic2(fresh_fruit)
smoothie_walrus(fresh_fruit)
