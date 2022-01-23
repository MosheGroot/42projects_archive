#include "philo_bonus.h"

/*
    init_philo_processes function

    Inits pocesses for each philosopher.

    Behaviour:
        If all pocesses creations were success setting simulation_status to philo_num
        Then calls init_philo_processes2 function

    Returns:
int     status  -- an error code from init_thread2 function
*/
static int  init_philo_processes2(int *pids, t_setup *setup,
                int created_processes_num);
static void kill_processes(int *pids, int size);

int init_philo_processes(t_setup *setup, t_philosopher *philos_data)
{
    int     *pids;
    int     index;

    pids = malloc(sizeof(int) * setup->num_of_philos);
    if (1 || !pids)
        return (-1);
    index = -1;
    while (++index < setup->num_of_philos)
    {
        philos_data->philo_number = index + 1;
        pids[index] = fork();
        if (pids[index] < 0)
        {
            write(STDERR_FILENO, "Can't fork!\n", 12);
            break ;
        }
        else if (pids[index] == 0)
        {
            process_philosopher_entry(philos_data);
            exit(0);
        }
    }
    return (init_philo_processes2(pids, setup, index));
}

/*
    init_philo_processes2 function

    Behaviour:
        Check for simulation init error (simulation_status)
        If simulation error, kills created processes
        Otherwise, waiting for any child's end (simulation stop).
        After all, free pids array

    Returns:
int     status  -- actual error code (0 or -1)
*/
static int  init_philo_processes2(int *pids, t_setup *setup,
                int created_processes_num)
{
    int tmp;
    int status;

    if (created_processes_num < setup->num_of_philos)
    {
        kill_processes(pids, created_processes_num);
        return (-1);
    }
    tmp = created_processes_num;
    while (tmp--)
        sem_post(setup->simulation_status);
    sem_post(setup->print);
    status = 0;
    while (WEXITSTATUS(status) != EXITSTATUS_DIED)
    {
        if (waitpid(-1, &status, 0) <= 0)
            break ;
    }
    kill_processes(pids, created_processes_num);
    free(pids);
    return (0);
}

static void kill_processes(int *pids, int size)
{
    while (size--)
        kill(pids[size], SIGTERM);
}
