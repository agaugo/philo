# philo — Dining Philosophers in C

A solution to the classic [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) using POSIX threads and mutexes. Each philosopher is a thread; each fork is a mutex. The goal is to keep every philosopher alive without deadlock or data races.

Built at [Codam](https://www.codam.nl/) (42 network).

## How it works

- **One thread per philosopher, one mutex per fork.** A philosopher takes the fork on their left, then the one on their right, eats, sleeps, thinks, and repeats.
- **Deadlock avoidance by staggering.** Even-numbered philosophers start with a short delay, so neighbours don't all grab their left fork at the same moment.
- **A monitor watches for starvation.** The main thread loops over all philosophers and checks each one's last meal time against `time_to_die`. The first one to exceed it ends the simulation.
- **Shared state behind a lock.** The "simulation over" flag and meal timestamps are read and written under a mutex, so there are no data races between the philosophers and the monitor.
- **Precise timing.** Sleeps use a custom millisecond loop instead of a single long `usleep`, which drifts under load.

## Build and run

```sh
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_per_philosopher]
```

Times are in milliseconds. Up to 200 philosophers.

```sh
./philo 5 800 200 200      # nobody should die
./philo 5 800 200 200 7    # stops once everyone has eaten 7 times
./philo 4 310 200 100      # a philosopher dies
```

## Structure

| File | Purpose |
|---|---|
| `src/main.c` | Entry point, argument check, cleanup |
| `src/init.c` | Sets up philosophers, forks and shared locks |
| `src/threads.c` | Starts and joins threads, destroys mutexes |
| `src/core.c` | Philosopher routine and the starvation monitor |
| `src/actions.c` | Eat, sleep, think |
| `src/time.c` | Millisecond clock and precise sleep |
