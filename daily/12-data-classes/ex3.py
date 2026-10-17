import dataclasses
from collections import namedtuple
from typing import NamedTuple
from dataclasses import dataclass, asdict

Coordinate_namedtuple = namedtuple('Coordinate_namedtuple', 'lat lon', defaults=[1, 2])

class Coordinate_NamedTuple(NamedTuple):
    lat: float = 1
    lon: float = 2

@dataclass
class CoordinateDataclass:
    lat: float = 1
    lon: float = 2

coordinates_namedtuple = Coordinate_namedtuple(50.78, 17.06)
coordinates_NamedTuple = Coordinate_NamedTuple(50.78, 17.06)
coodinates_Dataclass = CoordinateDataclass(50.78, 17.06)

#mutable:
try:
    coordinates_namedtuple.lon = 42
except:
    print("Can't modify namedtuple")
try:
    coordinates_NamedTuple.lon = 42
except:
    print("Can't modify NamedTuple")

coodinates_Dataclass.lon = 42

#construct dict
print("\ndict.....")
print(coordinates_namedtuple._asdict())
print(coordinates_NamedTuple._asdict())
print(asdict(coodinates_Dataclass))

#get field names
print("\nfields.....")
print(coordinates_namedtuple._fields)
print(coordinates_NamedTuple._fields)
print([f.name for f in dataclasses.fields(coodinates_Dataclass)])

print("\ndefualts.....")
#get defaults
print(coordinates_namedtuple._field_defaults)
print(coordinates_NamedTuple._field_defaults)
print([f.default for f in dataclasses.fields(coodinates_Dataclass)])

class Testme(NamedTuple):
    lat: float
    lon: float = 1

#new instance with changes
print(coordinates_namedtuple._replace(lon=42))
print(coordinates_NamedTuple._replace(lon=42))
print(dataclasses.replace(coodinates_Dataclass, lon=42))
