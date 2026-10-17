def get_batches(count, size):
    return count // size


def create_packages_classic(fresh_fruit, order):
    package = {}
    for name in order:
        count = fresh_fruit.get(name, 0)
        batches = get_batches(count, 8)
        if batches:
            package[name] = batches
    print(package)


def create_packages_comprehension(fresh_fruit, order):
    package = {
        name: get_batches(fresh_fruit.get(name, 0), 8)
        for name in order
        if get_batches(fresh_fruit.get(name, 0), 8)
    }
    print(package)


def create_packages_walrus(fresh_fruit, order):
    package = {
        name: batches
        for name in order
        if (batches := get_batches(fresh_fruit.get(name, 0), 8))
    }
    print(package)


fresh_fruit = {
    "apple": 1,
    "banana": 34,
    "lemon": 25,
}

order = ["lemon", "banana", "apple"]

create_packages_classic(fresh_fruit, order)
# create_packages_comprehension(fresh_fruit, order)
# create_packages_walrus(fresh_fruit, order)
