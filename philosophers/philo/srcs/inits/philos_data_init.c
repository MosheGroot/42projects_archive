#include "philo_one.h"

/*
    init_philos_data function

    Creates and returns array of t_philosopher structures
    for each philosopher (thread).

    Fills known values to each element of array.

    Returns NULL if error.
*/
t_philosopher   *init_philos_data(t_setup *setup)
{
    t_philosopher   *all_philosophers;
    int             index;

    all_philosophers = malloc(sizeof(t_philosopher) * setup->num_of_philos);
    if (!all_philosophers)
    {
        write(STDERR_FILENO, "Can't allocate an array of philos' datas!\n", 42);
        return (NULL);
    }
    index = -1;
    while (++index < setup->num_of_philos)
    {
        all_philosophers[index].global_setup = setup;
        all_philosophers[index].philo_number = index + 1;
        all_philosophers[index].is_dead = 0;
        all_philosophers[index].meals_number = 0;
        all_philosophers[index].ready_to_eat = 0;
        all_philosophers[index].sim_start_time.tv_sec = 0;
        all_philosophers[index].sim_start_time.tv_usec = 0;
        all_philosophers[index].first_print_flag = 1;
    }
    return (all_philosophers);
}
