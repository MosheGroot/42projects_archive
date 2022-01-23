#include "philo_bonus.h"

/*
    thread_philosopher function

    Runs until philosopher doesn't dead or simulation stops.

    Behaviour:
        1) thinking:
            * thinking until death, sim stop or ready_to_eat flag
        2) eating:
            * checks "how much times had meals" (if enought -- "dies")
            * eating
            * checks own death while eating (can be)
        3) sleeping:
            * sleeping
            * checks death in bed
*/
static int  thinking_process(t_philosopher *data);
static int  eating_process(t_philosopher *data);
static int  sleeping_process(t_philosopher *data);

void    thread_philosopher(t_philosopher *data)
{
    if (gettimeofday(&data->sim_start_time, NULL) != 0)
    {
        write(STDERR_FILENO, "Can't get time of simulation start!\n", 37);
        return ;
    }
    data->last_time_eat = data->sim_start_time;
    while (!data->is_dead)
    {
        if (thinking_process(data) != 0)
            break ;
        if (eating_process(data) != 0)
            break ;
        if (sleeping_process(data) != 0)
            break ;
    }
    exit(EXITSTATUS_DIED);
}

static int  thinking_process(t_philosopher *data)
{
    print_event(EV_THINK, EVID_THINK, data);
    data->first_print_flag = 0;
    while (!data->ready_to_eat && !data->is_dead)
        usleep(5);
    if (data->is_dead)
        return (1);
    return (0);
}

static int  eating_process(t_philosopher *data)
{
    print_event(EV_EAT, EVID_EAT, data);
    data->meals_number++;
    if (data->meals_number == data->global_setup->required_number_of_meals)
    {
        data->is_dead = 1;
        sem_post(data->global_setup->forks);
        sem_post(data->global_setup->forks);
        exit(EXITSTATUS_DONE);
    }
    my_msleep(data->global_setup->time_to_eat);
    data->ready_to_eat = 0;
    if (data->is_dead)
        return (1);
    return (0);
}

static int  sleeping_process(t_philosopher *data)
{
    print_event(EV_SLEEP, EVID_SLEEP, data);
    my_msleep(data->global_setup->time_to_sleep);
    if (data->is_dead)
        return (1);
    return (0);
}
