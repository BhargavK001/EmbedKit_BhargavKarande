# EmbedKit_BhargavKarande

**Name:** Bhargav Karande

## Module

| File | Description |
|------|-------------|
| `ringbuf.c` | Ring buffer implementation for `uint8_t` data, capacity 8 bytes |

## Environment

I used WSL (Ubuntu 22.04) on Windows for this assignment. After setting up WSL, I ran `sudo apt update && sudo apt upgrade` and then `sudo apt install build-essential` to get gcc on the system. Compiler used is gcc 11.4.0 with C99 standard.

## Build and Run

```bash
gcc -Wall -std=c99 ringbuf.c -o ringbuf
./ringbuf
```

Compiled with zero warnings and zero errors.

## Output

```
[WRITE] 0x41 -> OK (count=1)
[WRITE] 0x42 -> OK (count=2)
[WRITE] 0x43 -> OK (count=3)
[WRITE] 0x44 -> OK (count=4)
[WRITE] 0x45 -> OK (count=5)
[WRITE] 0x46 -> OK (count=6)
[WRITE] 0x47 -> OK (count=7)
[WRITE] 0x48 -> OK (count=8) FULL
[WRITE] 0x99 -> FAIL (buffer full)
[READ] -> 0x41 (count=7)
[READ] -> 0x42 (count=6)
[READ] -> 0x43 (count=5)
[WRITE] 0x49 -> OK (count=6)
[WRITE] 0x4A -> OK (count=7)
[WRITE] 0x4B -> OK (count=8) FULL
[READ] -> 0x44 (count=7)
[READ] -> 0x45 (count=6)
[READ] -> 0x46 (count=5)
[READ] -> 0x47 (count=4)
[READ] -> 0x48 (count=3)
[READ] -> 0x49 (count=2)
[READ] -> 0x4A (count=1)
[READ] -> 0x4B (count=0)
[READ] (empty) -> FAIL (buffer empty)
```

## Screenshot

Added a screenshot of the terminal output in the repository.
