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
