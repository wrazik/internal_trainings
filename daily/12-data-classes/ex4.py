from collections import  namedtuple

City = namedtuple('City', ['name', 'country', 'population', 'coordinates'])
tokyo = City('Tokyo', 'JP', 36.933, (35.689722, 139.691667))
print("1", tokyo)
print("2", tokyo.population)
print("3", tokyo.coordinates)
print("4", tokyo[1])

print("5", City._fields)
Coordinate = namedtuple('Coordinate', 'lat lon')
delhi_data = ('Delhi NCR', 'IN', 21.935, Coordinate(28.613889, 77.208889))
delhi = City._make(delhi_data)
print(delhi._asdict())

import json
print(json.dumps(delhi._asdict()))

Coordinate = namedtuple('Coordinate', 'lat lon reference', defaults=['WGS84'])
print(Coordinate(0, 0))
print(Coordinate(lat=0, lon=0, reference='WGS84'))
print(Coordinate._field_defaults)

# hacking methods
def _str(self):
    ns = 'N' if self.lat >= 0 else 'S'
    we = 'E' if self.lon >= 0 else 'W'
    return f'{abs(self.lat):.1f}°{ns}, {abs(self.lon):.1f}°{we}'

Coordinate.__str__ = _str
some_coords = Coordinate(28.613889, 77.208889)
print(some_coords)