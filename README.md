# Philosopher Simulation Project

## Overview
This project implements a solution to the "Dining Philosophers Problem" using multithreading (for the mandatory part) and multiprocessing (for the bonus part). Philosophers alternate between thinking, eating, and sleeping while avoiding deadlocks and starvation.
## Features
##### Mandatory Part:
- Each philosopher is represented as a thread.
- A fork is shared between two philosophers (one on the left, one on the right).
- Mutual exclusion is ensured using mutexes to protect the state of the forks.
- Philosophers will eat, think, and sleep until the simulation ends.

#### Bonus Part:
- Forks are placed in the middle of the table and are represented by a semaphore.
- Each philosopher is represented as a separate process.
- The main process controls and monitors the philosophers.

## Project Structure
- philo/: Contains the implementation of the mandatory part.
- philo_bonus/: Contains the implementation of the bonus part.
- Makefile: Compiles the project into the required output files.

- ### Important Files:
- philo.c: Entry point for the simulation.
- philo.h: Header file containing function prototypes and shared structures.
- Makefile: Builds the project.

## Compilation

1. Clone the repository.
```bash
git clone git@github.com:Mouad-kimdil/philosopher.git
```
2. enter the repository.
```bash
cd philosopher && cd philo
```
3. Run <code>make</code> in the root directory to compile the mandatory part.
- use <code>make clean</code> to remove object files.
- use <code>make fclean</code> to remove all compiled files.
- use <code>make re</code> to clean and recompile the project.

to compile the bonus part, navigate for the <code>philo_bonus</code> directory and repeat the steps above.

## Usage
### Mandatory Part:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- <code>number_of_philosophers</code>: Number of philosophers.
- <code>time_to_die</code>: Time (in milliseconds) before a philosopher dies if they don’t start eating.
- <code>time_to_eat</code>: Time (in milliseconds) a philosopher takes to eat.
- <code>time_to_sleep</code>: Time (in milliseconds) a philosopher spends sleeping.
- <code>number_of_times_each_philosopher_must_eat</code>: (optional): Stops the simulation when all philosophers have eaten at least this many times.

### Bonus Part:
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
## Rules
- No global variables are allowed.
- Every philosopher has a state transition log that outputs messages like:
  - [timestamp] philosopher [id] is eating
  - [timestamp] philosopher [id] is thinking
  - [timestamp] philosopher [id] has died
- The program must avoid philosophers dying unnecessarily and handle mutex locks properly.