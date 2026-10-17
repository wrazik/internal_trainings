class RaiiClass:
    def __enter__(self):
        print("Startup")

    def __exit__(self, *args, **kwargs):
        print("Shutdown")

with RaiiClass() as r:
    input("Waiting . . .")