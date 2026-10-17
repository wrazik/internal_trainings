class OutOfBananas(Exception):
    pass


def out_of_stock():
    print("no bzzzt")


def slice_bananas(count):
    print(f"{'chszt ' * count}")
    return count * 4


def make_smoothies(count):
    if count:
        print(f"{'bzzzt ' * count}")
        return f"{count}-banana-pieces smoothie"
    else:
        raise OutOfBananas


def make_cider(count):
    print(f"apple brrrr {'pskt ' * count}")
    return f"{count}-apple cider"


def make_lemonade(count):
    print(f"lemon brrrr {'pskt ' * count}")
    return f"{count}-lemon lemonade"


def enjoy_classic(fresh_fruit):
    count = fresh_fruit.get("banana", 0)
    if count >= 2:
        pieces = slice_bananas(count)
        to_enjoy = make_smoothies(pieces)
    else:
        count = fresh_fruit.get("apple", 0)
        if count >= 4:
            to_enjoy = make_cider(count)
        else:
            count = fresh_fruit.get("lemon", 0)
            if count:
                to_enjoy = make_lemonade(count)
            else:
                to_enjoy = "Nothing"
    return to_enjoy


def enjoy_classic2(fresh_fruit):
    banana_count = fresh_fruit.get("banana", 0)
    apple_count = fresh_fruit.get("apple", 0)
    lemon_count = fresh_fruit.get("lemon", 0)

    if banana_count >= 2:
        pieces = slice_bananas(banana_count)
        to_enjoy = make_smoothies(pieces)
    elif apple_count >= 4:
        to_enjoy = make_cider(apple_count)
    elif lemon_count:
        to_enjoy = make_lemonade(lemon_count)
    else:
        to_enjoy = "Nothing"
    return to_enjoy


def enjoy_walrus(fresh_fruit):
    if (count := fresh_fruit.get("banana", 0)) >= 2:
        pieces = slice_bananas(count)
        to_enjoy = make_smoothies(pieces)
    elif (count := fresh_fruit.get("apple", 0)) >= 4:
        to_enjoy = make_cider(count)
    elif count := fresh_fruit.get("lemon", 0):
        to_enjoy = make_lemonade(count)
    else:
        to_enjoy = "Nothing"
    return to_enjoy


fresh_fruit = {
    "apple": 3,
    "banana": 2,
    "lemon": 1,
}

print(f"Mmmm, {enjoy_classic(fresh_fruit)}")
print(f"Mmmm, {enjoy_classic2(fresh_fruit)}")
print(f"Mmmm, {enjoy_walrus(fresh_fruit)}")
