#include "philo_bonus.h"

/*
    thread_daemon_entry function

    Little entry function before general thread function

    Behaviour:
        1) Waits for all prepared philos or simulation error
        2) Waits a little bit more until philosopher set
            his simulation_start_time (required for correct timestamps)
        3) Runs general thread function
*/
void    *thread_daemon_entry(void *data)
{
    t_servicer  *daemon_data;

    daemon_data = (t_servicer *)data;
    while (daemon_data->target->sim_start_time.tv_sec == 0
        && daemon_data->target->sim_start_time.tv_usec == 0)
        usleep(5);
    thread_daemon(daemon_data);
    return (NULL);
}

/*
    thread_daemon function

    Checks death of targeted philosopher.
    Period calulates between last_time_eat and current_time.

    Behaviour:
        1. If is_dead set by philosopher, it means he had enought meals
        2. If period > time_to_die, then daemon "kills" philosopher with mesage
        3. If simulation stoped, there is no death mesages
*/
void    thread_daemon(t_daemon *data)
{
    struct timeval  curr_time;
    long int        period;

    while (data->target->first_print_flag)
        usleep(5);
    while (!data->target->is_dead)
    {
        if (gettimeofday(&curr_time, NULL) != 0)
        {
            write(STDERR_FILENO, "Daemon: can't get current time!\n", 32);
            break ;
        }
        period = get_period(&data->target->last_time_eat, &curr_time);
        if (period > data->global_setup->time_to_die)
        {
            print_event(EV_DIED, EVID_DIED, data->target);
            break ;
        }
        usleep(25);
    }
    data->target->is_dead = 1;
}
