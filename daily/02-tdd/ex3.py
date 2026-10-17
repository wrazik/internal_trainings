class PasswordValidator:
    def is_strong(self, password: str) -> bool:
        if len(password) < 8:
            return False
        return self._contains_uppercase(password) and self._contains_lowercase(password) and self._contains_number(password)

    def _contains_uppercase(self, password: str) -> bool:
        return any(ch.isupper() for ch in password)

    def _contains_lowercase(self, password: str) -> bool:
        return any(ch.islower() for ch in password)

    def _contains_number(self, passsword: str):
        return any(ch.isdigit() for ch in passsword)


def test_strong_password():
    assert not PasswordValidator().is_strong("dupa")
    assert PasswordValidator().is_strong("!fjaosoi480AASDSADjfbbaslPJSFDPOSJf")

def test_weak_password():
    assert not PasswordValidator().is_strong("12345678")

def test_long_password():
    assert PasswordValidator().is_strong("bardzosilnehaslojestspoko")