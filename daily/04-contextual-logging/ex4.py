import logging
from contextvars import ContextVar

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

format = "%(asctime)s - %(name)s - %(levelname)s - %(user_id)s - %(message)s"
handler = logging.StreamHandler()
handler.setFormatter(logging.Formatter(format))
logger.addHandler(handler)

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


s1 = User("user1")
s2 = User("user2")
s1.show()
s2.show()
