#include "philo_one.h"

/*
    init_threads function

    Inits threads for each philosopher.

    Behaviour:
        If all threads creations were success setting simulation_status to 1
        Then calls init_thread2 function

    Returns:
int     status  -- an error code from init_thread2 function
*/
static int  init_philo_threads2(pthread_t *threads, t_setup *setup,
                int crtd_thrds);

int init_philo_threads(t_setup *setup, t_philosopher *all_philos)
{
    pthread_t   *threads;
    int         index;

    threads = malloc(sizeof(pthread_t) * setup->num_of_philos);
    if (!threads)
        return (-1);
    setup->simulation_status = 0;
    setup->num_of_prepared_philos = 0;
    index = -1;
    while (++index < setup->num_of_philos)
    {
        if (pthread_create(threads + index, NULL,
                &thread_philosopher_entry, all_philos + index) != 0)
        {
            setup->simulation_status = -1;
            write(STDERR_FILENO, "Can't create thread!\n", 21);
            break ;
        }
    }
    return (init_philo_threads2(threads, setup, index));
}

/*
    init_thread2 function

    Behaviour:
        Check for simulation init error (simulation_status)
        If simulation error, waiting for created threads ends
        Otherwise, waiting (join) for each thread until simulation stops.
        After all, free threads array

    Returns:
int     status  -- actual error code (0 or -1)
*/
static int  init_philo_threads2(pthread_t *threads, t_setup *setup,
                int crtd_thrds)
{
    int status;

    if (!setup->simulation_status)
        setup->simulation_status = 1;
    if (setup->simulation_status == -1)
        status = -1;
    else
        status = 0;
    while (--crtd_thrds >= 0)
    {
        if (pthread_join(threads[crtd_thrds], NULL) != 0)
        {
            write(STDERR_FILENO, "Can't join thread!\n", 19);
            status = -1;
        }
    }
    free(threads);
    return (status);
}
