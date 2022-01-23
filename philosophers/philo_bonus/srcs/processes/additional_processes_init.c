#include "philo_bonus.h"

/*
    generate_additional_threads_and_run function

    Creates additional threads such as personal servicer and personal daemon
    for current philosopher.

    Behaviour:
        1. Prepares gen_data for both threads (structure is the same)
        2. Creates servicer thread
            (throught generate_thread func with error check)
        3. Creates daemon thread:
            a) if there was an error, simulation_status = -1,
                var "created" leaved = 1, so after that we need to
                join only 1 thread
            b) no error, then prepared_philos += 1
        4. Rus 2nd part of function (..._and_run2):
            1) Waits for all prepared philos or simulation error
            2) If no error, sets simulation_start_time and runs philo's thread
            3) Waits for end of additional threads
                (no difference was there error or not)
*/
static int  generate_thread(pthread_t *ptr, void *(*entry_func)(void *),
                void *data);
static void generate_additional_threads_and_run2(t_philosopher *philo_data,
                pthread_t *thrds, int created);

static void generate_additional_threads_and_run(t_philosopher *philo_data)
{
    pthread_t   thrds[2];
    t_servicer  gen_data;
    int         created;

    gen_data.global_setup = philo_data->global_setup;
    gen_data.target = philo_data;
    if (generate_thread(thrds, &thread_servicer_entry, &gen_data) != 0)
        return ;
    created = 1;
    if (generate_thread(thrds + 1, &thread_daemon_entry, &gen_data) == 0)
    {
        created = 2;
        philo_data->global_setup->num_of_prepared_philos++;
    }
    generate_additional_threads_and_run2(philo_data, thrds, created);
}

static void generate_additional_threads_and_run2(t_philosopher *philo_data,
                pthread_t *thrds, int created)
{
    sem_wait(philo_data->global_setup->simulation_status);
    thread_philosopher(philo_data);
    while (--created >= 0)
        if (pthread_join(thrds[created], NULL) != 0)
            write(STDERR_FILENO, "Can't join additional thread!\n", 30);
}

static int  generate_thread(pthread_t *ptr, void *(*entry_func)(void *),
                void *data)
{
    if (pthread_create(ptr, NULL, entry_func, data) != 0)
    {
        write(STDERR_FILENO, "Can't create additional thread!\n", 30);
        return (-1);
    }
    return (0);
}

/*
    process_philosopher_entry function

    Function for each philosopher.
    Works as entry point of simulation.

    Behaviour:
        I) Generaits additional threads
        II) Waits for simulation status sem's value:
            * If simulation init error -- it will be killed by parent
            * Otherwise, simulation begins
        III) When simulation beigns:
            * sets last_time_eat to simulation_start_time
*/
void    process_philosopher_entry(t_philosopher *data)
{
    generate_additional_threads_and_run(data);
}
