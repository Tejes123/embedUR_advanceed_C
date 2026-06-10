# Assignment 2

## 1. Write a C program to define 3 different threads with the following purposes where N is
the input
. Thread A - To run a loop and return the sum of first N prime numbers
. Thread B & C - should run in parallel. One prints "Thread 1 running" every 2
seconds, and the other prints "Thread 2 running" every 3 seconds for 100
seconds.

## 2. In the above program,

. add signal handling for SIGINT (etc) and prevent termination.
. Convert the above threads to individual functions and note down the time taken
and the flow of execution.

## 3. Know about the following topics and explore them (Write a note on your understandings)

Areas for exploration,

. Child process - fork()
. Handing common signals
. Exploring different Kernel crashes
. Time complexity
. Locking mechanism - mutex/spinlock

## Solution:
## 1. Child Process – `fork()`

1. `fork()` is a system call in Unix/Linux used to create a new process called a **child process**.
2. After `fork()`, both parent and child continue execution from the next instruction.
3. The child process gets a copy of the parent's memory space, file descriptors, and environment.
4. `fork()` returns:

   * `0` in the child process
   * Child PID in the parent process
   * `-1` if creation fails
5. Common uses include process creation, running background tasks, and implementing shells.

Example:

```c
pid_t pid = fork();

if(pid == 0)
    printf("Child Process\n");
else
    printf("Parent Process\n");
```

---

## 2. Handling Common Signals

1. Signals are software interrupts sent to a process to notify it of events.
2. Signal handlers can be registered using `signal()` or `sigaction()`.
3. `SIGINT` is generated when the user presses `Ctrl + C`.
4. `SIGTERM` requests graceful process termination.
5. `SIGSEGV` occurs when a process accesses invalid memory.

Common Signals:

| Signal  | Description         |
| ------- | ------------------- |
| SIGINT  | Interrupt (Ctrl+C)  |
| SIGTERM | Termination request |
| SIGKILL | Force kill process  |
| SIGSEGV | Segmentation fault  |
| SIGALRM | Timer expired       |

Example:

```c
void handler(int sig)
{
    printf("Signal received\n");
}

signal(SIGINT, handler);
```

---

## 3. Exploring Different Kernel Crashes

1. A kernel crash occurs when the operating system kernel encounters an unrecoverable error.
2. Invalid memory access in kernel space can trigger a kernel panic.
3. Null pointer dereferencing inside kernel code is a common cause.
4. Faulty device drivers are one of the most frequent sources of kernel crashes.
5. Race conditions, deadlocks, and stack overflows can also cause system instability.

Common Crash Types:

| Crash Type               | Description                |
| ------------------------ | -------------------------- |
| Kernel Panic             | Fatal kernel error         |
| Oops                     | Non-fatal kernel exception |
| Null Pointer Dereference | Invalid memory access      |
| Stack Overflow           | Kernel stack exhaustion    |
| Driver Crash             | Buggy device driver        |

Linux provides logs using:

```bash
dmesg
```

for crash analysis.

---

## 4. Time Complexity

1. Time complexity measures how the execution time of an algorithm grows with input size.
2. Big-O notation is used to represent the upper bound of growth.
3. Lower time complexity generally indicates better scalability.
4. Complexity analysis helps compare algorithms independently of hardware.
5. Worst-case complexity is most commonly used in algorithm analysis.

Common Complexities:

| Complexity | Example              |
| ---------- | -------------------- |
| O(1)       | Array element access |
| O(log n)   | Binary Search        |
| O(n)       | Linear Search        |
| O(n log n) | Merge Sort           |
| O(n²)      | Bubble Sort          |

Example:

```c
for(int i=0;i<n;i++)
{
    printf("%d", i);
}
```

Time Complexity:

```text
O(n)
```

---

## 5. Locking Mechanism – Mutex and Spinlock

### Mutex

1. A mutex (Mutual Exclusion) protects shared resources from concurrent access.
2. If one thread owns the mutex, other threads are blocked until it is released.
3. Mutexes prevent race conditions in multithreaded programs.
4. They are suitable when lock holding time may be long.
5. Threads waiting on a mutex are put to sleep by the scheduler.

Example:

```c
pthread_mutex_lock(&lock);

/* Critical Section */

pthread_mutex_unlock(&lock);
```

---

### Spinlock

1. A spinlock also provides mutual exclusion for shared resources.
2. Instead of sleeping, waiting threads continuously check (spin) until the lock becomes available.
3. Spinlocks are efficient for very short critical sections.
4. They avoid the overhead of context switching.
5. Excessive spinning wastes CPU time if lock duration is long.

Example:

```c
pthread_spin_lock(&spinlock);

/* Critical Section */

pthread_spin_unlock(&spinlock);
```

### Mutex vs Spinlock

| Feature          | Mutex      | Spinlock    |
| ---------------- | ---------- | ----------- |
| Waiting Method   | Sleep      | Busy Wait   |
| CPU Usage        | Low        | High        |
| Context Switch   | Yes        | No          |
| Best For         | Long waits | Short waits |
| User Space Usage | Common     | Less Common |

