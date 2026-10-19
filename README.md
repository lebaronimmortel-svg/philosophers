*This project has been created as part of the 42 curriculum by alexfuen*

## Description

Philosophers is a core project at 42 focused on learning concurrent programming through the famous Dining Philosophers problem.
The goal is to explore threads, synchronization, and shared resource management while preventing chaos 
such as deadlocks and race conditions. Think of it as teaching a group of hungry thinkers to share 
politely under strict timing constraints.

- prevent data races,
- understand multithreading,
- manage mutex synchronization,
- implement precise time handling,
- build a stable, clean, norm-compliant program.

Each philosopher is a thread,
each fork is protected by a mutex,
actions must be printed with timestamps.

The simulation stops if :
-   a philosopher dies,
-   all philosophers have eaten enough 
    (if the optional argument is provided).

## Instructions

To compile this program, run make at the root of the repository :
```bash
make
```
To launch the simulation, give it 4 or 5 numerical arguments :
```bash
./philo 5 1200 300 200 6
```
To launch the simulation and check threads management :
```bash
valgrind --tool=helgrind ./philo 5 1200 300 200
```

## Resources

 - https://en.wikipedia.org/wiki/Race_condition — Theoretical definition and examples of concurrent data access conflicts.
 - https://www.delftstack.com/fr/howto/c/mutex-in-c/ — Beginner's guide to synchronizing POSIX threads using pthread_mutex_t.
 - https://www.delftstack.com/fr/howto/c/pthread_join-return-value-in-c/ — How to retrieve and handle thread exit values with pthread_join.
 - https://www.geeksforgeeks.org/c/multithreading-in-c/ — Core introduction to C multithreading using standard pthread functions.
 - https://franckh.developpez.com/tutoriels/posix/pthreads/ — Comprehensive tutorial covering thread lifecycle, attributes, and synchronization.
 - https://stackoverflow.com/questions/14320041/pthread-mutex-initializer-vs-pthread-mutex-init-mutex-param — Differences between static (PTHREAD_MUTEX_INITIALIZER) and dynamic mutex initialization.
 - https://stackoverflow.com/questions/37792052/how-does-a-mutex-work-does-a-mutex-protect-variables-globally-does-the-scope-i#37792198 — Clarifies that mutexes guard critical code sections, not memory itself.
 - https://undo.io/resources/gdb-watchpoint/using-helgrind-to-debug-data-races/ — Practical guide to catching synchronization bugs using Valgrind's Helgrind.
 - https://c-for-dummies.com/blog/?p=4236 — Quick example of measuring microsecond-level elapsed time with gettimeofday.
 - https://www.delftstack.com/fr/howto/c/gettimeofday-in-c/ — Practical C examples for computing execution time using gettimeofday.
