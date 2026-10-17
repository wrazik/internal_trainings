from dataclasses import dataclass, field

# @dataclass
# class ClubMember:
#     name: str
#     guests: list = [] # mutable default not allowed

@dataclass
class ClubMember:
    name: str
    guests: list = field(default_factory=list)

@dataclass
class ClubMember:
    name: str
    guests: list[str] = field(default_factory=list)
    athlete: bool = field(default=False, repr=False)

print(ClubMember("Member", ["guest1", "guest2"], False))

from dataclasses import dataclass

@dataclass
class User:
    name: str
    age: int

    def __post_init__(self):
        if self.age < 0:
            raise ValueError("age must be non-negative")
        self.name = self.name.strip().title()

u = User("Alice ", 30)
# u = User("Alice ", -3) ERROR
