import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)

format = "%(asctime)s - %(name)s - %(levelname)s - %(user_id)s - %(message)s"
handler = logging.StreamHandler()
handler.setFormatter(logging.Formatter(format))

logger.addHandler(handler)

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


s1 = User("user1")
s2 = User("user2")
s1.show()
s2.show()
