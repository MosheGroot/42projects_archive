#include "philo_bonus.h"

/*
    print_event function

    Prints various events with extra possibility

    Behaviour:
        1. If simulation stoped -- no printing events except of death
        2. If simulation runs, prints timestamp and info:
            * except EV_EAT -- then it updates last_time_eat
                (needs for optimization)
*/
long int    get_period(const struct timeval *begin, const struct timeval *end);

void    print_event(const char *event, int event_id, t_philosopher *target)
{
    struct timeval  curr_time;

    sem_wait(target->global_setup->print);
    if (gettimeofday(&curr_time, NULL) != 0)
    {
        write(STDERR_FILENO, "Daemon: can't get current time!\n", 32);
        return ;
    }
    if (event_id == EVID_EAT)
        target->last_time_eat = curr_time;
    printf("%ld\t%d\t%s\n", get_period(&target->sim_start_time, &curr_time),
        target->philo_number, event);
    if (event_id != EVID_DIED)
        sem_post(target->global_setup->print);
}

long int    get_period(const struct timeval *begin, const struct timeval *end)
{
    return ((end->tv_sec - begin->tv_sec) * 1000
        + (end->tv_usec - begin->tv_usec) / 1000);
}

/*
    my_usleep
*/
void    my_msleep(int msec)
{
    struct timeval  begin;
    struct timeval  current;

    if (!msec)
        return ;
    gettimeofday(&begin, NULL);
    while (1)
    {
        gettimeofday(&current, NULL);
        current.tv_sec -= begin.tv_sec;
        current.tv_usec -= begin.tv_usec;
        if (current.tv_sec * 1000000 + current.tv_usec >= msec * 1000)
            return ;
        usleep(25);
    }
}
