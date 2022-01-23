#include "philo_bonus.h"

/*
    init_forks function

    Creates and returns smaphore for forks.

    Returns:
        * NULL if error.
        * semaphore with num_of_philos value
*/
sem_t   *init_forks_sem(t_setup *setup)
{
    sem_t       *forks;

    sem_unlink(FORKSEM_NAME);
    forks = sem_open(FORKSEM_NAME, O_CREAT, 0777, setup->num_of_philos);
    if (forks == SEM_FAILED)
        write(STDERR_FILENO, "Can't init semaphore!\n", 22);
    return (forks);
}

/*
    init_print_sem function

    Creates and returns smaphore for printing.

    Returns:
        * NULL if error.
        * semaphore with value '0'
*/
sem_t   *init_print_sem(void)
{
    sem_t       *sem;

    sem_unlink(PRINTSEM_NAME);
    sem = sem_open(PRINTSEM_NAME, O_CREAT, 0777, 0);
    if (sem == SEM_FAILED)
        write(STDERR_FILENO, "Can't init semaphore!\n", 22);
    return (sem);
}

/*
    init_print_sem function

    Creates and returns smaphore for printing.

    Returns:
        * NULL if error.
        * semaphore with value '0'
*/
sem_t   *init_simstatus_sem(void)
{
    sem_t       *sem;

    sem_unlink(SIMSTATUSSEM_NAME);
    sem = sem_open(SIMSTATUSSEM_NAME, O_CREAT, 0777, 0);
    if (sem == SEM_FAILED)
        write(STDERR_FILENO, "Can't init semaphore!\n", 22);
    return (sem);
}
