#include "philo_one.h"

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
                void *data, int *simulation_status);
static void generate_additional_threads_and_run2(t_philosopher *philo_data,
                pthread_t *thrds, int created);

static void generate_additional_threads_and_run(t_philosopher *philo_data)
{
    pthread_t   thrds[2];
    t_servicer  gen_data;
    int         *stat;
    int         created;

    gen_data.global_setup = philo_data->global_setup;
    gen_data.target = philo_data;
    stat = &philo_data->global_setup->simulation_status;
    if (generate_thread(thrds, &thread_servicer_entry, &gen_data, stat) != 0)
        return ;
    created = 1;
    if (generate_thread(thrds + 1, &thread_daemon_entry, &gen_data, stat) == 0)
    {
        created = 2;
        philo_data->global_setup->num_of_prepared_philos++;
    }
    generate_additional_threads_and_run2(philo_data, thrds, created);
}

static void generate_additional_threads_and_run2(t_philosopher *philo_data,
                pthread_t *thrds, int created)
{
    while ((philo_data->global_setup->num_of_prepared_philos
            != philo_data->global_setup->num_of_philos)
        && philo_data->global_setup->simulation_status != -1)
        usleep(5);
    if (philo_data->global_setup->simulation_status != -1)
    {
        if (gettimeofday(&philo_data->sim_start_time, NULL) != 0)
        {
            write(STDERR_FILENO, "Can't get time of simulation start!\n", 37);
            philo_data->global_setup->simulation_status = -1;
        }
        philo_data->last_time_eat = philo_data->sim_start_time;
        thread_philosopher(philo_data);
    }
    while (--created >= 0)
        if (pthread_join(thrds[created], NULL) != 0)
            write(STDERR_FILENO, "Can't join additional thread!\n", 30);
}

static int  generate_thread(pthread_t *ptr, void *(*entry_func)(void *),
                void *data, int *simulation_status)
{
    if (pthread_create(ptr, NULL, entry_func, data) != 0)
    {
        *simulation_status = -1;
        write(STDERR_FILENO, "Can't create additional thread!\n", 30);
        return (-1);
    }
    return (0);
}

/*
    thread_philo_entry function

    Thread function for each philosopher.
    Works as entry point of simulation.

    Behaviour:
        I) If simulation_status:
            * -1    -- error occured, exit
            * 0     -- waiting for beginning of simulation
            * 1     -- simulation has begun
                        (and simulation_start_time has been set)
        II) When simulation beigns:
            * sets last_time_eat to simulation_start_time
*/
void    *thread_philosopher_entry(void *philosopher_data)
{
    t_philosopher   *data;

    data = (t_philosopher *)philosopher_data;
    while (data->global_setup->simulation_status == 0)
        ;
    if (data->global_setup->simulation_status == 1)
        generate_additional_threads_and_run(data);
    return (NULL);
}
