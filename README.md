*This project has been created as part of the 42 curriculum by epetrill.*

**Description**
- **Goal:** Implement the `get_next_line` function that reads and returns the next line from a file descriptor (including the terminating newline when present) on each call.
- **Overview:** The program reads from a file descriptor in fixed-size chunks (`BUFFER_SIZE`), accumulates data until a newline is found (or EOF), and returns a freshly allocated string containing the next line. The implementation must correctly handle multiple file descriptors (bonus), manage dynamic memory without leaks, and handle edge cases like empty files, files that don't end with a newline, and read errors.

**Instructions**
- **Files:** `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` are the core files in this repository.
- **Compile:** Use `gcc` to compile. Example command:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c -o gnl_test
```

- **Run (example):**

```bash
./gnl_test input.txt
```

- **Notes:**
  - You can change `BUFFER_SIZE` by passing `-D BUFFER_SIZE=<N>` to `gcc`.
  - Ensure your `main` test program opens the file and repeatedly calls `get_next_line(fd)` until it returns `NULL`.

**Resources**
- **Documentation:**
  - POSIX `read(2)` manual: https://man7.org/linux/man-pages/man2/read.2.html
  - C standard library memory management: `malloc(3)`, `free(3)`
- **Articles & Tutorials:**
  - Explanations of line-based input buffering and static storage in C (various online tutorials and 42 resources).
- **AI Usage:**
  - An AI assistant (GPT-5 mini) was used to draft this README, structure the instructions, and write the algorithm explanation and pseudocode. AI was NOT used to write or modify the project source files in this repository; it only helped produce documentation and explanatory material.

**Algorithm (detailed explanation & justification)**
- **High-level idea:**
  - Maintain a per-file-descriptor remainder (a static buffer or a structure indexed by `fd`) that stores bytes read but not yet returned as part of a line.
  - Repeatedly call `read(fd, buf, BUFFER_SIZE)` to fill a temporary buffer. Append the new bytes to the remainder.
  - If the combined data contains a newline (`'\n'`), extract everything up to and including the first newline as the line to return; keep leftovers in the remainder for the next call.
  - If `read` returns 0 (EOF) and the remainder is non-empty, return the remainder as the last line (without appending a newline). If the remainder is empty, return `NULL`.
  - On read error or malloc failure, free any allocated resources and return `NULL`.

- **Data structures:**
  - A small temporary buffer `buf` of size `BUFFER_SIZE + 1` for each `read` call.
  - A dynamically allocated string for the remainder per `fd` (commonly implemented as a static array indexed by `fd`, or a linked list/array of structures to support many FDs).
  - Returned strings are freshly `malloc`-ed; the caller is responsible for `free`.

- **Why this algorithm:**
  - **Correctness:** It ensures that each returned string corresponds exactly to a single line from the input (including newline when present) and preserves leftover data for subsequent calls.
  - **Efficiency:** Reading in chunks reduces the number of system calls; appending to a remainder only reallocates when necessary. Overall time is linear in the number of bytes processed.
  - **Memory management:** Using a persistent remainder avoids re-reading bytes multiple times and minimizes temporary allocations. Carefully freeing memory on EOF or error avoids leaks.
  - **Multiple file descriptors:** Storing one remainder per `fd` lets the function be safely interleaved across multiple descriptors (the bonus objective in the original 42 project).

- **Edge cases and handling:**
  - **Empty file:** First `read` returns 0; remainder is empty → return `NULL`.
  - **File without newline at end:** Last line is returned when `read` returns 0 and remainder contains data.
  - **Very long lines (> BUFFER_SIZE):** The loop continues reading and appending until a newline or EOF is found; the algorithm handles arbitrarily long lines (subject to available memory).
  - **Read errors:** Any `read` error should cause cleanup and return `NULL`.
  - **Memory allocation failures:** Detect `malloc`/`realloc` failures, free allocated data, and return `NULL`.

- **Complexity:**
  - Time complexity: O(n) where n is the number of bytes read overall; each byte is processed a constant number of times.
  - Space complexity: O(k) where k is the size of the largest pending remainder plus `BUFFER_SIZE`.

**Usage example (simple `main`)**
- Typical `main` loop to test `get_next_line`:

```c
int fd = open("input.txt", O_RDONLY);
char *line;
while ((line = get_next_line(fd)) != NULL) {
    printf("%s", line);
    free(line);
}
close(fd);
```

**Files**
- **Source:** `get_next_line.c`, `get_next_line_utils.c`
- **Header:** `get_next_line.h`

**Next steps / Suggestions**
- Add a small `main.c` test harness to the repo for quick manual testing.
- Run `valgrind` to ensure there are no memory leaks:

```bash
valgrind --leak-check=full ./gnl_test input.txt
```

---
If you'd like, I can also add a minimal `main.c` test file and update the `gcc` command in this README; tell me which behaviors you want to verify (multiple fds, very large lines, etc.).