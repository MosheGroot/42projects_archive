#include "philo_one.h"

/*
    thread_servicer_entry function

    Behaviours:
        Waits when all philosophers prepared or global error.
        If there is no error then distributes
        privileged and unprivileged philos:
            1) privileged philosophers are:
                a) odd (if num_of_philos % 2 == 0)
                b) even (else)
            2) each unprivileged philosopher waits a bit more
                (half of eat time), than privileged
                (so privileged philo will have time to take both forks)
        And run servicer thread function
*/
static int  check_privilege(const t_philosopher *philo);

void    *thread_servicer_entry(void *data)
{
    t_servicer  *servicer_data;

    servicer_data = (t_servicer *)data;
    while ((servicer_data->global_setup->num_of_prepared_philos
            != servicer_data->global_setup->num_of_philos)
        && servicer_data->global_setup->simulation_status != -1)
        usleep(25);
    if (servicer_data->global_setup->simulation_status != -1)
    {
        while (servicer_data->target->sim_start_time.tv_sec == 0
            && servicer_data->target->sim_start_time.tv_usec == 0)
            usleep(5);
        if (!check_privilege(servicer_data->target))
            my_msleep(servicer_data->global_setup->time_to_eat);
        while (servicer_data->target->first_print_flag)
            usleep(5);
        thread_servicer(servicer_data);
    }
    return (NULL);
}

static int  check_privilege(const t_philosopher *philo)
{
    int out;

    if (philo->global_setup->num_of_philos % 2)
    {
        if (philo->philo_number % 2)
            out = 0;
        else
            out = 1;
    }
    else
    {
        if (philo->philo_number % 2)
            out = 1;
        else
            out = 0;
    }
    return (out);
}

/*
    thread_servicer function

    Servicer trying to take forks. When he taken two, sends signal
    to targeted philosopher.
    If simulation stop then function just ends

    Behaviour:
        1. Remembers two forks needs to take (set_forks_indexes)
        2. Trying to lock left and after that right fork (switch_mutex)
            (with errors check of course)
        3. Sends signal to philosopher (ready_to_eat = 1)
        4. Waiting untill the end of meal (time_to_eat)
        5. Waiting for status change of philosopher a bit more
            (to smooth the time difference between threads)
        6. Unlock mutexes (switch_mutex) and sleep a bit
            (to avoid take this forks again)
*/
static void set_forks_indexes(t_servicer *data, int *fork_l, int *fork_r);
static int  switch_mutex(t_servicer *data, int f_num, int mode);

void    thread_servicer(t_servicer *data)
{
    int     f_l;
    int     f_r;

    if (data->global_setup->num_of_philos <= 1)
        return ;
    set_forks_indexes(data, &f_l, &f_r);
    while (!data->target->is_dead && data->global_setup->simulation_status != 2)
    {
        if (switch_mutex(data, f_l, FORK_LOCK) != 0)
            break ;
        if (switch_mutex(data, f_r, FORK_LOCK) != 0)
            break ;
        data->target->ready_to_eat = 1;
        if (data->global_setup->time_to_eat < data->global_setup->time_to_die)
            my_msleep(data->global_setup->time_to_eat);
        else
            my_msleep(data->global_setup->time_to_die);
        while (data->target->ready_to_eat && !data->target->is_dead)
            ;
        if (switch_mutex(data, f_l, FORK_UNLOCK) != 0)
            break ;
        if (switch_mutex(data, f_r, FORK_UNLOCK) != 0)
            break ;
        my_msleep(data->global_setup->time_to_eat / 2);
    }
}

static void set_forks_indexes(t_servicer *data, int *fork_l, int *fork_r)
{
    if (data->target->philo_number == 1)
        *fork_l = data->global_setup->num_of_philos;
    else
        *fork_l = data->target->philo_number - 1;
    *fork_r = data->target->philo_number;
}

static int  switch_mutex(t_servicer *data, int f_num, int mode)
{
    int     status;

    status = 0;
    if (mode == FORK_LOCK)
    {
        if (pthread_mutex_lock(&data->global_setup->forks[f_num - 1]) != 0)
        {
            write(STDERR_FILENO, "Servicer: can't lock mutex!\n", 28);
            data->global_setup->simulation_status = 2;
            status = -1;
        }
        else
            print_event(EV_FORK, EVID_FORK, data->target);
    }
    else
    {
        if (pthread_mutex_unlock(&data->global_setup->forks[f_num - 1]) != 0)
        {
            write(STDERR_FILENO, "Servicer: can't unlock mutex!\n", 30);
            data->global_setup->simulation_status = 2;
            status = -1;
        }
    }
    return (status);
}
