*This project has been created as part of the 42 curriculum by alexfuen*

# Description

## general :

Philosophers is a core project at 42 focused on learning concurrent programming through the famous Dining Philosophers problem.
The goal is to explore threads, synchronization, and shared resource management while preventing chaos 
such as deadlocks and race conditions. Think of it as teaching a group of hungry thinkers to share 
politely under strict timing constraints.

## objectives :

- prevent data races,
- understand multithreading,
- manage mutex synchronization,
- implement precise time handling,
- build a stable, clean, norm-compliant program.

## rules :

Each philosopher is a thread,
each fork is protected by a mutex,
actions must be printed with timestamps.

The simulation stops if :
-   a philosopher dies,
-   all philosophers have eaten enough 
    (if the optional argument is provided).

# Instructions

To compile this program, type make.
To execute this program, give it 4 or 5 numerical arguments :

```bash
./philo 5 1200 300 200 6
```
To execute this program and check threads management :

```bash
valgrind --tool=helgrind ./philo 5 1200 300 200
```

# Resources

## pthread :

https://en.wikipedia.org/wiki/Race_condition

https://www.delftstack.com/fr/howto/c/mutex-in-c/

https://www.delftstack.com/fr/howto/c/pthread_join-return-value-in-c/

https://www.geeksforgeeks.org/c/multithreading-in-c/

https://franckh.developpez.com/tutoriels/posix/pthreads/

https://stackoverflow.com/questions/14320041/pthread-mutex-initializer-vs-pthread-mutex-init-mutex-param

https://stackoverflow.com/questions/37792052/how-does-a-mutex-work-does-a-mutex-protect-variables-globally-does-the-scope-i#37792198

## helgrind :

https://undo.io/resources/gdb-watchpoint/using-helgrind-to-debug-data-races/

## gettime :

https://c-for-dummies.com/blog/?p=4236

https://www.delftstack.com/fr/howto/c/gettimeofday-in-c/

and the man.

I also used ChatGPT as an improved Internet navigator to learn the following :
- what a thread is,
- what a mutex is,
- what a data race is,
- how does a timeval struct work.