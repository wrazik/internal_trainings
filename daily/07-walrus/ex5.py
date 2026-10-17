def pick_fruit(fresh_fruit):
    if not fresh_fruit:
        return {}

    fruit, count = fresh_fruit.popitem()
    return {fruit: count}


def make_juice(fruit, count):
    return [f"{fruit}_juice" for _ in range(count)]


def make_bottles_classic(fresh_fruit):
    bottles = []

    picked = pick_fruit(fresh_fruit)
    while picked:
        for fruit, count in picked.items():
            batch = make_juice(fruit, count)
            bottles.extend(batch)
        picked = pick_fruit(fresh_fruit)
    print(bottles)


def make_bottles_classic2(fresh_fruit):
    bottles = []
    while True:
        picked = pick_fruit(fresh_fruit)
        if not picked:
            break
        for fruit, count in picked.items():
            batch = make_juice(fruit, count)
            bottles.extend(batch)
    print(bottles)


def make_bottles_walrus(fresh_fruit):
    bottles = []
    while picked := pick_fruit(fresh_fruit):
        for fruit, count in picked.items():
            batch = make_juice(fruit, count)
            bottles.extend(batch)
    print(bottles)


fresh_fruit = {
    "apple": 3,
    "banana": 1,
    "lemon": 1,
}


make_bottles_classic(fresh_fruit)
# make_bottles_classic2(fresh_fruit)
# make_bottles_walrus(fresh_fruit)
