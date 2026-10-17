print(type(...))
print(... is Ellipsis)

# unfinished
def future_method():
    ...
def future_metho2():
    pass

# ================================================================================
# abstract interfaces
from typing import Protocol
class Schedulable(Protocol):
    uuid: str
    is_active: bool
    def step(self) -> bool: ...
    def save_state(self) -> dict: ...
    def load_state(self, state: dict) -> None: ...

# ================================================================================
# type hints
def log(nums: tuple[int, ...]):
    ...

# ================================================================================
# Callable - annotation
from typing import Callable, Any

def run(func: Callable[..., int], *args: Any, **kwargs: Any) -> int:
    return func(*args, **kwargs)

def no_args() -> int:
    return 1

def one_arg(x: int) -> int:
    return x * 2

def two_args(x: int, y: int) -> int:
    return x + y

print(run(no_args))           # 1
print(run(one_arg, 5))        # 10
print(run(two_args, 3, 4))    # 7

# ================================================================================
# handling ellipsis

class Query:
    def __getitem__(self, key):
        if key is Ellipsis:
            return "SELECT * FROM data"
        return f"SELECT * WHERE id={key}"
q = Query()
print(q[...])
print(q[42])

# ================================================================================
# numpy

import numpy as np
a = np.arange(24).reshape(2, 3, 4)
print(a)
print(a[:, :, -1])
print(a[..., -1])

print(a[0, :, :])
print(a[0, ...])

c = np.zeros((2, 3, 4))
c[..., 0] = 1
print(c)