#include "philo_one.h"

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
    while (!data->is_dead && data->global_setup->simulation_status != 2)
    {
        if (thinking_process(data) != 0)
            break ;
        if (eating_process(data) != 0)
            break ;
        if (sleeping_process(data) != 0)
            break ;
    }
}

static int  thinking_process(t_philosopher *data)
{
    print_event(EV_THINK, EVID_THINK, data);
    data->first_print_flag = 0;
    while (!data->ready_to_eat && !data->is_dead
        && data->global_setup->simulation_status != 2)
        usleep(5);
    if (data->is_dead || data->global_setup->simulation_status == 2)
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
        return (1);
    }
    my_msleep(data->global_setup->time_to_eat);
    data->ready_to_eat = 0;
    if (data->is_dead || data->global_setup->simulation_status == 2)
        return (1);
    return (0);
}

static int  sleeping_process(t_philosopher *data)
{
    print_event(EV_SLEEP, EVID_SLEEP, data);
    my_msleep(data->global_setup->time_to_sleep);
    if (data->is_dead || data->global_setup->simulation_status == 2)
        return (1);
    return (0);
}
