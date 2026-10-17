# Goal
Our goal is to add contextual information to the logger. 
Example: we have a user class with some `id`, we want to add information about the id to every log:

```python
class User:
    def __init__(self, id):
        self.id = id

    def show(self):
        logger.info(f"I'm showing the user {self.id}")
```

What we want to do is to log the data with some specific format, enforcing to have correct fields. 
## Extra logging arg
First way to do it is to use `extra` argument in logging. Full example:
```python
# ... logger set up
class User:
    def __init__(self, id):
        self.id = id

    def show(self):
        logger.info("I'm showing the user", extra = {"user_id": self.id})
```
## LoggerAdapter:

Another idea is to use the LoggerAdapter:
```python
# ... logger set up
class UserContextualAdapter(logging.LoggerAdapter):
    def __init__(self, logger, user=None):
        super().__init__(logger, {"user_id": getattr(user, "id", "None")})
        self.user = user

    def set_user(self, user):
        self.user = user

    def process(self, msg, kwargs):
        extra = kwargs.pop("extra", {})

        extra.update(
            {"user_id": getattr(self.user, "id", "None")}
        )

        kwargs.update({"extra": extra})
        return msg, kwargs

adapter = UserContextualAdapter(logging.getLogger(__name__))

class User:
    def __init__(self, id):
        self.id = id

    def show(self):
        adapter.set_user(self)
        adapter.info("I'm showing the user")
```
To simplify the code, we can use contextvar:
```python
# ... set up 
from contextvars import ContextVar

userContext = ContextVar("user")

class UserContextualAdapter(logging.LoggerAdapter):
    def process(self, msg, kwargs):
        user = userContext.get()

        extra = kwargs.pop("extra", {})

        extra.update(
            {"user_id": user.id}
        )
        kwargs.update({"extra": extra})
        return msg, kwargs

adapter = UserContextualAdapter(logging.getLogger(__name__))
class User:
    def __init__(self, id):
        self.id = id

    def show(self):
        userContext.set(self)
        adapter.info("I'm showing the user")
```

## LoggingFilter
Alternatively - it is possible to use "logging filters":
```python
#... set up
from contextvars import ContextVar

userContext = ContextVar("user")
class UserContextualFilter(logging.Filter):
    def filter(self, record):
        current_user = userContext.get()
        record.user_id = current_user.id
        return True

logger.addFilter(UserContextualFilter())

class User:
    def __init__(self, id):
        self.id = id

    def show(self):
        userContext.set(self)
        logger.info("I'm showing the user")
```
