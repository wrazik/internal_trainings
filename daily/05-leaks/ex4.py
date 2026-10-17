from signal import signal, SIGTERM, default_int_handler
signal(SIGTERM, default_int_handler)

import atexit

@atexit.register
def goodbye():
    print("Shutdown")

input("Waiting\n")