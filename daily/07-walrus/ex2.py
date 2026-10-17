def make_cider(count):
    print(f"apple rrrr {'pskt ' * count}")


def out_of_stock():
    print("No brrr")


def cider_classic(fresh_fruit):
    count = fresh_fruit.get("apple", 0)
    if count >= 4:
        make_cider(count)
    else:
        out_of_stock()


def cider_walrus(fresh_fruit):
    if count := fresh_fruit.get("apple", 0) >= 4:  # why???
        make_cider(count)
    else:
        out_of_stock()


fresh_fruit = {
    "apple": 4,
    "banana": 8,
    "lemon": 0,
}
cider_classic(fresh_fruit)
# cider_walrus(fresh_fruit)
