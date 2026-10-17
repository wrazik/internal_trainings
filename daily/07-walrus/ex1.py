def make_lemonade(count):
    print(f"lemon brrrr {'pskt ' * count}")


def out_of_stock():
    print("No brrr")


def lemonade_classic(fresh_fruit):
    count = fresh_fruit.get("lemon", 0)
    if count:
        make_lemonade(count)
    else:
        out_of_stock()


def lemonade_walrus(fresh_fruit):
    if count := fresh_fruit.get("lemon", 0):
        make_lemonade(count)
    else:
        out_of_stock()


fresh_fruit = {
    "apple": 10,
    "banana": 8,
    "lemon": 3,
}
lemonade_classic(fresh_fruit)
lemonade_walrus(fresh_fruit)
