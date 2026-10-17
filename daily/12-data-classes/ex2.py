def test(info, val1, val2):
    print(f"issubclass({info}, tuple): ", issubclass(type(val1), tuple))
    print("val1 == val2: ", val1 == val2)
    print(f"__str__(val1): {val1}")
    print(f"__str__(val2): {val2}")


from collections import namedtuple
# >2.6

Coordinate_namedtuple = namedtuple('Coordinate_namedtuple', 'lat lon')
szczawin = Coordinate_namedtuple(50.78, 17.06)
other_szczawin = Coordinate_namedtuple(50.78, 17.06)
test("Coordinate_namedtuple", szczawin, other_szczawin)

print(Coordinate_namedtuple("SomePlace", 33))
print("------")
#############################################################

# >3.6
from typing import NamedTuple

class Coordinate_NamedTuple(NamedTuple):
    lat: float
    lon: float

    def __str__(self):
        ns = 'N' if self.lat >= 0 else 'S'
        we = 'E' if self.lon >= 0 else 'W'
        return f'{abs(self.lat):.1f}°{ns}, {abs(self.lon):.1f}°{we}'

szczawin_Named = Coordinate_NamedTuple(50.78, 17.06)
other_szczawin_Named = Coordinate_NamedTuple(50.78, 17.06)
test("Coordinate_NamedTuple", szczawin_Named, other_szczawin_Named)
print("------")

#############################################################
from dataclasses import dataclass

@dataclass(frozen=True) # read-only
class CoordinateDataclass:
    lat: float
    lon: float

    # def __str__(self):
    #     ns = 'N' if self.lat >= 0 else 'S'
    #     we = 'E' if self.lon >= 0 else 'W'
    #     return f'{abs(self.lat):.1f}°{ns}, {abs(self.lon):.1f}°{we}'

szczawin_Dataclass = CoordinateDataclass(50.78, 17.06)
other_szczawin_Dataclass = CoordinateDataclass(50.78, 17.06)

test("CoordinateDataclass", szczawin_Dataclass, other_szczawin_Dataclass)