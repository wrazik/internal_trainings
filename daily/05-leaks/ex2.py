import atexit

@atexit.register
def goodbye():
    print("Shutdown")

input("Waiting\n")