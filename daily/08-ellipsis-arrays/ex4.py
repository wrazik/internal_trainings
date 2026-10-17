# Unpack
car_ages = [0, 9, 4, 8, 7, 20, 19, 1, 6, 15]
car_ages_descending = sorted(car_ages, reverse=True)
# oldest, second_oldest = car_ages_descending # doesn't work

oldest = car_ages_descending[0]
second_oldest = car_ages_descending[1]
others = car_ages_descending[2:]
print(oldest, second_oldest, others)

oldest, second_oldest, *others = car_ages_descending
print(oldest, second_oldest, others)

*others, second_youngest, youngest = car_ages_descending
print(youngest, second_youngest, others)

oldest, *others, youngest = car_ages_descending
print(oldest, others, youngest)
