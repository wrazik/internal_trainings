from typing import NamedTuple
from dataclasses import dataclass

class Coordinate(NamedTuple):
    lat: float
    lon: float
    reference: str = 'WGS84'

# Every instance field must be annotated with a type.

# Types are not checked on runtime
trash = Coordinate('Ni!', None)
print(trash)

print(Coordinate.lat)

@dataclass
class CoordinateDataclass:
    lat: float
    lon: float = 0

print(CoordinateDataclass.lat)
print(CoordinateDataclass.lon)
