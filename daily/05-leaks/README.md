# Python leaks

In python - we can implement teardown functions in several ways. Using __exit__:
```python
class RaiiClass:
    def __enter__(self):
        print("Startup")

    def __exit__(self, *args, **kwargs):
        print("Shutdown")

with RaiiClass() as r:
    input("Waiting . . .")
```

Or using atexit library:
```python
import atexit

@atexit.register
def goodbye():
    print("Shutdown")

input("Waiting\n")
```

In both cases, Shutdown is called when we type Ctrl+C:
```bash
Waiting . . .^CShutdown
Traceback (most recent call last):
  File "/home/wrazik/src/trainings/daily/15-leaks/ex1.py", line 9, in <module>
    input("Waiting . . .")
    ~~~~~^^^^^^^^^^^^^^^^^
KeyboardInterrupt
```
But not, when we send SIGTERM:
```bash
Waiting . . .[1]    43400 terminated  python ex1.py
```
This may lead to leak of the resources (e.g. socket may remain open...)

This is because python by defaults implements handler for SIGINT, but not for SIGTERM:
```bash
>>> from signal import getsignal, SIGINT, SIGTERM
>>> getsignal(SIGINT)
<built-in function default_int_handler>
>>> getsignal(SIGTERM)
<Handlers.SIG_DFL: 0>
```

We can add handler to SIGTERM using the following:
```python
from signal import signal, SIGTERM, default_int_handler
signal(SIGTERM, default_int_handler)
```
This will use the same handler as for SIGINT (throwing KeyboardInterrupt)

We can also use signal handling in case we want to gracefully implement http-server teardown:
```python
from http.server import HTTPServer, BaseHTTPRequestHandler
from signal import signal, SIGINT, SIGTERM
import sys

class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"Hello, world!")

server = HTTPServer(("0.0.0.0", 8000), Handler)

def graceful_shutdown(signum, frame):
    print("\nShutting down server gracefully...")
    server.shutdown()
    sys.exit(0)

signal(SIGINT, graceful_shutdown)
signal(SIGTERM, graceful_shutdown)

try:
    server.serve_forever()
except KeyboardInterrupt:
    graceful_shutdown(None, None)
```

Or closing the async task, using Event():
```python
import asyncio
from signal import SIGTERM
shutdown_event = asyncio.Event()

async def service():
    try:
        while not shutdown_event.is_set():
            print("Hop hop hop hop")
            await asyncio.sleep(2)
    except asyncio.CancelledError:
        print("Cleanup")
        raise

async def main():
    loop = asyncio.get_running_loop()
    loop.add_signal_handler(SIGTERM, shutdown_event.set)

    tasks = [asyncio.create_task(service())]
    await shutdown_event.wait()
    for task in tasks:
        task.cancel()
        try:
            await task
        except asyncio.CancelledError:
            pass

asyncio.run(main())
```