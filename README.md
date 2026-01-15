# 🍝 Philosophers

## Description

Philosophers is a project developed as part of the 42 curriculum.  
The objective is to solve the classic Dining Philosophers problem while respecting strict timing and concurrency constraints.

This project introduces multithreading, synchronization mechanisms, and careful resource management to avoid race conditions, deadlocks, and starvation.

<br/>

## Project Objectives

- Understand and manage concurrent execution
- Use threads and mutexes correctly
- Prevent data races and deadlocks
- Respect strict timing constraints
- Simulate philosopher behavior accurately
- Follow the constraints and norms defined by 42

<br/>

## Program Usage

The program is executed as follows:

```bash
./philo  number_of_philosophers  time_to_die  time_to_eat  time_to_sleep  [number_of_times_each_philosopher_must_eat]
```
If the `number_of_times_each_philosopher_must_eat` is not included, the program will run indefinitely until one philosopher dies or the program is stopped.

Example:

```bash
./philo 5 800 200 200
```
<br/>

## Arguments
- `number_of_philosophers` — number of philosophers and forks
- `time_to_die` — time (in milliseconds) a philosopher can survive without eating
- `time_to_eat` — time (in milliseconds) spent eating
- `time_to_sleep` — time (in milliseconds) spent sleeping
- `number_of_times_each_philosopher_must_eat` — optional argument to stop the simulation after all philosophers have eaten a specific number of times

<br/>

## Simulation Rules
- Each philosopher alternates between eating, sleeping, and thinking
- Philosophers need two forks to eat
- Forks are shared resources and must be protected
- A philosopher dies if they do not eat within time_to_die
- The simulation stops when a philosopher dies or when all philosophers have eaten enough times

<br/>

## Implementation Overview
- Each philosopher is represented by a thread
- Mutexes are used to protect forks and shared data
- Time management is handled with millisecond precision
- Output is synchronized to avoid mixed or corrupted logs

<br/>

## Files Structure
The project is composed of the following files:
- philo.c
- philo_checks.c
- philo_eats.c
- philo_management.c
- philo_mutex.c
- philo_sleep.c
- philo_time.c
- print_helpers.c
- utils.c
- philo.h

Each file is designed to keep responsibilities clear and separated.

<br/>

## Compilation
To compile the project, use the provided Makefile:

```bash
make
```
This will generate the philo executable.

Additional rules:

```bash
make clean     # Removes object files
make fclean    # Removes object files and the executable
make re        # Recompiles the project
```
<br/>
