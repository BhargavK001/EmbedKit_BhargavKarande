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

## Screenshot

Added a screenshot of the terminal output in the repository.
