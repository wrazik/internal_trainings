class PasswordValidator:
    def is_strong(self, password: str) -> bool:
        if len(password) < 8:
            return False
        return True

def test_strong_password():
    assert not PasswordValidator().is_strong("dupa")
    assert PasswordValidator().is_strong("!fjaosoi480AASDSADjfbbaslPJSFDPOSJf")

def test_weak_password():
    assert not PasswordValidator().is_strong("12345678")