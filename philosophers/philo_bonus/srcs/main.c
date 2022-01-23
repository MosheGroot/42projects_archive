#include "philo_bonus.h"

/*
    init_simuation function

    Init and run simulation with error checks.

    Behaviour:
        1. Creates an array of philosophers data (all_philosophers)
        2. Creates an array of forks (mutexes after mutex_init)
        3. Runs init_philo_processes function to create num_of_philo processes
            with their additional processes
        4. When init_philo_processes returns error code it means that
            simulation has been stoped
        5. => forks and philosophers data don't need anymore, free them

    Returns:
int     status  -- status of simulation run
*/
void    init_philos_data(t_setup *setup, t_philosopher *data);
void    sem_free(t_setup *setup);

static int  init_simulation(t_setup *setup)
{
    t_philosopher   philos_data;

    init_philos_data(setup, &philos_data);
    setup->forks = init_forks_sem(setup);
    if (!setup->forks)
        return (-1);
    setup->print = init_print_sem();
    if (!setup->print)
        return (-1);
    setup->simulation_status = init_simstatus_sem();
    if (!setup->simulation_status)
        return (-1);
    if (init_philo_processes(setup, &philos_data) != 0)
    {
        write(STDERR_FILENO, "Can't init philos!\n", 19);
        return (-1);
    }

    sem_free(setup);
    return (0);
}

void    sem_free(t_setup *setup)
{
    if (sem_close(setup->forks) != 0)
        write(STDERR_FILENO, "Can't close semaphore!\n", 23);
    if (sem_unlink(FORKSEM_NAME) != 0)
        write(STDERR_FILENO, "Can't unlink semaphore!\n", 24);
    if (sem_close(setup->print) != 0)
        write(STDERR_FILENO, "Can't close semaphore!\n", 23);
    if (sem_unlink(PRINTSEM_NAME) != 0)
        write(STDERR_FILENO, "Can't unlink semaphore!\n", 24);
    if (sem_close(setup->simulation_status) != 0)
        write(STDERR_FILENO, "Can't close semaphore!\n", 23);
    if (sem_unlink(SIMSTATUSSEM_NAME) != 0)
        write(STDERR_FILENO, "Can't unlink semaphore!\n", 24);
}

void    init_philos_data(t_setup *setup, t_philosopher *data)
{
    data->global_setup = setup;
    data->is_dead = 0;
    data->meals_number = 0;
    data->ready_to_eat = 0;
    data->sim_start_time.tv_sec = 0;
    data->sim_start_time.tv_usec = 0;
    data->first_print_flag = 1;
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
