#include "philo_one.h"

/*
    init_forks function

    Creates and returns array of mutexes (forks).

    Each mutex inits in loop.
    If any inition failed all previous mutexes destroys.

    Returns:
        * NULL if error.
        * array with inited forks
*/
pthread_mutex_t *init_forks(t_setup *setup)
{
    pthread_mutex_t     *forks;
    int                 index;

    forks = malloc(sizeof(pthread_mutex_t) * setup->num_of_philos);
    if (!forks)
    {
        write(STDERR_FILENO, "Can't allocate forks array!\n", 28);
        return (NULL);
    }
    index = -1;
    while (++index < setup->num_of_philos)
    {
        if (pthread_mutex_init(forks + index, NULL) != 0)
        {
            write(STDERR_FILENO, "Can't init mutex!\n", 18);
            free_forks(forks, index);
            return (NULL);
        }
    }
    return (forks);
}

/*
    free_forks function

    If initialize of forks failed or all philosophers (threads) are down,
    programm will call this function.

    Function destroys each inited mutex and free an array
*/
void    free_forks(pthread_mutex_t *forks, int num_of_inited_forks)
{
    while (--num_of_inited_forks >= 0)
        if (pthread_mutex_destroy(forks + num_of_inited_forks) != 0)
            write(STDERR_FILENO, "Can't destroy mutex!!!\n", 23);
    free(forks);
}
