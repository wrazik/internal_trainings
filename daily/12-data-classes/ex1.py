# We want to create simple class - just a collection of fields,
# with little or no extra functionality.

class Coordinate:
    def __init__(self, lat, lon):
        self.lat = lat
        self.lon = lon

szczawin = Coordinate(50.78, 17.06)

print(szczawin)
# __repr__ not very helpful
other_szczawin = Coordinate(50.78, 17.06)
print(szczawin == other_szczawin)
# __eq__ compares object IDs
print((szczawin.lat, szczawin.lon) == (other_szczawin.lat, other_szczawin.lon))