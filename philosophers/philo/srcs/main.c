#include "philo_one.h"

/*
    init_simuation function

    Init and run simulation with error checks.

    Behaviour:
        1. Creates an array of philosophers data (all_philosophers)
        2. Creates an array of forks (mutexes after mutex_init)
        3. Runs init_philo_threads function to create num_of_philo threads
            with their additional threads
        4. When init_philo_threads returns error code it means that
            simulation has been stoped
        5. => forks and philosophers data don't need anymore, free them

    Returns:
int     status  -- status of simulation run
*/
static int  init_simulation(t_setup *setup)
{
    t_philosopher   *all_philosophers;

    all_philosophers = init_philos_data(setup);
    if (!all_philosophers)
        return (-1);
    setup->forks = init_forks(setup);
    if (!setup->forks)
    {
        free(all_philosophers);
        return (-1);
    }
    if (pthread_mutex_init(&setup->print, NULL) != 0
        || init_philo_threads(setup, all_philosophers) != 0)
    {
        write(STDERR_FILENO, "Error\n", 6);
        free_forks(setup->forks, setup->num_of_philos);
        free(all_philosophers);
        return (-1);
    }
    free_forks(setup->forks, setup->num_of_philos);
    free(all_philosophers);
    return (0);
}

int main(int argc, char **argv)
{
    t_setup     global_setup;
    int         status;

    if (agruments_parser(argc, argv, &global_setup) != 0)
    {
        write(STDERR_FILENO, "Invalid agrmunets!\n", 19);
        return (-1);
    }
    status = init_simulation(&global_setup);
    return (status);
}
