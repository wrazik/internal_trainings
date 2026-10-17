import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

format = "%(asctime)s - %(name)s - %(levelname)s - %(user_id)s - %(message)s"
handler = logging.StreamHandler()
handler.setFormatter(logging.Formatter(format))
logger.addHandler(handler)

class User:
    def __init__(self, id):
        self.id = id

    def show(self):
        logger.info("I'm showing the user", extra = {"user_id": self.id})

s1 = User("user1")
s2 = User("user2")
s1.show()
s2.show()
