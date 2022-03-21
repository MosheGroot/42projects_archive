# Philosophers project

  Classic dinning philosophers problem.
  
  Language: C

## Goal:
  Solve dinning philosophers problem in two variants:
  * `philo`: with forks between every philosopher (with mutexes usage)
  * `philo_bonus`: with forks at the center of table (with semaphores usage)


## Result:

  Slightly overloaded solutions (quite awfull) with some differences: 
  * `philo`: **threads** for each philosopher, servicers (for forks control) for each philo and daemons (for death control) also for each philo. 
     Forks are controlled by **mutexes**.
  * `philo_bonus`: **processes** for each philosopher, servicers (for forks control) for each philo and daemons (for death control) also for each philo. 
     Forks are controlled by **semaphore**. 

  There are many better solutions, but the project was made that way

## Usage

Each directory has a `Makefile` for `philo` and `philo_bonus`.

Run simulation like this:
```
./philo[_bonus] <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]
```
