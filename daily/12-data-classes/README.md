# Data classes 
Let's consider following class:
```python
class Coordinate:
    def __init__(self, lat, lon):
        self.lat = lat
        self.lon = lon
```
If you try to print it on the screen, you will get:
```bash
<__main__.Coordinate object at 0x7fd3a48886e0>
```
If you try compare two objects, instead of values - python will compare object ids. 

Python offers a few ways to build a simple class that is just a collection of fields, with little or no extra functionality. 
That pattern is known as a “data class” — and dataclasses is one of the packages that supports this pattern.

They are 3 options: collections.namedtuple, typing.NamedTuple and dataclasses.dataclass.

## Overview

You can create namedtuple by providing the name of the class, and list of attributes. List of attributes can be provided as
string separated by space or comma, as well as list of values.
```python
from collections import namedtuple
Coordinate = namedtuple('Coordinate', 'lat lon')
Coordinate = namedtuple('Coordinate', 'lat, lon')
Coordinate = namedtuple('Coordinate', ['lat', 'lon'])

szczawin =  Coordinate(50.78, 17.06)
szczawin2 = Coordinate(50.78, 17.06)
print(szczawin)
# Coordinate(lat=50.78, lon=17.06)
print(szczawin == szczawin2)
# True
```

More convenience is to use NamedTuple, which allows to use class statement. It makes easy to override default methods:
```python
from typing import NamedTuple

class Coordinate_NamedTuple(NamedTuple):
    lat: float
    lon: float

    def __str__(self):
        ns = 'N' if self.lat >= 0 else 'S'
        we = 'E' if self.lon >= 0 else 'W'
        return f'{abs(self.lat):.1f}°{ns}, {abs(self.lon):.1f}°{we}'
```

Last option is to use `@dataclass` decorator:
```python
from dataclasses import dataclass

@dataclass
class Coordinate_NamedTuple(frozen=True):
    lat: float
    lon: float
```

Example that illustrates differences can be found [here](ex2.py)

## namedtuple
You can access underlying elements of the namedtuple both with attribute name & the index:
```python
from collections import namedtuple
City = namedtuple('City', ['name', 'country', 'population', 'coordinates'])
tokyo = City('Tokyo', 'JP', 36.933, (35.689722, 139.691667))
print("1", tokyo)
print("2", tokyo.population)
print("3", tokyo.coordinates)
print("4", tokyo[1])
```

Unlike the tuple, namedtuple generates `__init__` method. If we want to initialize namedtuple the same way as tuple, we cane use `_make`:
```python
City = namedtuple('City', ['name', 'country', 'population', 'coordinates'])
Coordinate = namedtuple('Coordinate', 'lat lon')
delhi_data = ('Delhi NCR', 'IN', 21.935, Coordinate(28.613889, 77.208889))
delhi = City._make(delhi_data)
print(delhi._asdict())
```
We can provide default arguments using `defaults`:
```python
Coordinate = namedtuple('Coordinate', 'lat lon reference', defaults=['WGS84'])
print(Coordinate(0, 0))
print(Coordinate(lat=0, lon=0, reference='WGS84'))
print(Coordinate._field_defaults)
```
defaults takes iterable as parameter, it will provide default value for `n` LAST elements - in example above, the only
field with default value is `reference`.

To override methods, we can use hacky solution with replacing method during runtime:
```python
def _str(self):
    ns = 'N' if self.lat >= 0 else 'S'
    we = 'E' if self.lon >= 0 else 'W'
    return f'{abs(self.lat):.1f}°{ns}, {abs(self.lon):.1f}°{we}'

Coordinate.__str__ = _str
some_coords = Coordinate(28.613889, 77.208889)
print(some_coords)
```
## NamedTuple
In NamedTuple, all types needs to be annotated. Because NamedTuple with generate default parameters to the `__init__` methods,
we can provide only default values for n last arguments. We cannot declare non-default argument after providing the default one.

It's worth noting that provided type is checked only by linters - it is not checked during runtime. Such construction is 100% valid:
```python
class Coordinate(NamedTuple):
    lat: float
    lon: float
    reference: str = 'WGS84'
trash = Coordinate('Ni!', None)
```


## dataclass
Mutable default values are a common source of bugs for beginning Python developers. 
In function definitions, a mutable default value is easily corrupted when one invocation of the function 
mutates the default, changing the behavior of further invocations. Class attributes are often used as default attribute values for instances, 
including in data classes. And @dataclass uses the default values in the type hints to generate parameters with defaults for __init__. 
To prevent bugs, @dataclass rejects the class definition:
```python
@dataclass
class ClubMember:
    name: str
    guests: list = [] # mutable default not allowed
```
The fix is to use `field` with `default_factory`:
```python
from dataclasses import dataclass, field

@dataclass
class ClubMember:
    name: str
    guests: list[str] = field(default_factory=list)  1
```
