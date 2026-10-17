'''                     CZERWONY
                      .===========-.
                     /              \
                    |   TEST FAILS   |                     
                     \              /                      
                      '===========-'                       
                   -\                 \                    
                  /                    \    taptaptaptaptap
                 /                      -                  
                /                        \
  NIEBIESKI    /                          _|  ZIELONY
    .-==========-.                        .-===========-.  
   /              \                      /               \
  |    REFACTOR    |   < ------------   |   TEST PASSES   |
   \              /                      \               / 
    '-==========-'                        '-===========-'
'''

class PasswordValidator:
    def is_strong(self, password: str) -> bool:
        return False

def test_strong_password():
    assert not PasswordValidator().is_strong("dupa")
    assert PasswordValidator().is_strong("!fjaosoi480AASDSADjfbbaslPJSFDPOSJf")