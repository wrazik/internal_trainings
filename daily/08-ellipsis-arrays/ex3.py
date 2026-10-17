# Flat failed
log = """
2026-01-20 12:03:11  ERROR   user01      Payment failed, change client
2026-01-20 12:05:44  INFO    user02      Login success
2026-01-20 12:07:02  WARNING user03      Disk space low
"""

DATE      = slice(0, 10)
TIME      = slice(11, 19)
LEVEL     = slice(21, 28)
USER      = slice(29, 41)
MESSAGE   = slice(41, None)
lines = log.strip().split('\n')

for line in lines:
    print(
        line[TIME],
        line[DATE],
        line[USER],
        line[LEVEL],
        " ---> ",
        line[MESSAGE]
    )
