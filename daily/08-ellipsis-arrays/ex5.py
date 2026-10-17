def generate_csv():
    yield ('Date', 'Make', 'Model', 'Year', 'Price')
    yield ('2026-01-10', 'Toyota', 'Corolla', 2018, 55000)
    yield ('2026-01-11', 'Ford', 'Focus', 2016, 42000)
    yield ('2026-01-12', 'Tesla', 'Model 3', 2021, 185000)
    yield ('2026-01-13', 'Volkswagen', 'Golf', 2019, 73000)


it = generate_csv()
header, *rows = it
print('CSV Header:', header)
print('Row count: ', len(rows))
for row in rows:
    print(' ', row)