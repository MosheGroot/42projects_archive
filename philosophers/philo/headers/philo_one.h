#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "unistd.h"
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

/* 
    Global setup of general settings

    Contains all what philos, service and daemons (literaly) needs.
        (except for forks, they're need only for service,
            but philo creates servicer)
        (and except of global status code of simulation:
            philos ignore it, they're waiting signal from daemon!)

    Values:
        1) simulation_status:
            * -1    -- error while creating threads
            * 0     -- hasn't begun
            * 1     -- simulation started
            * 2     -- simulation ended
        2) num_of_philos, time_to_die, time_to_eat,
            time_to_sleep, number_of_must_eat       -- any
        3) simulation_start_time, forks -- undefined
*/
typedef struct s_setup
{
    int             simulation_status;
    int             num_of_prepared_philos;
    int             num_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             required_number_of_meals;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
}   t_setup;

/*
    events defines for timestamp prints
*/
# define EV_FORK    "has taken a fork"
# define EV_EAT     "is eating"
# define EV_SLEEP   "is sleeping"
# define EV_THINK   "is thinking"
# define EV_DIED    "died"

# define EVID_FORK  1
# define EVID_EAT   2
# define EVID_SLEEP 3
# define EVID_THINK 4
# define EVID_DIED  5

/*
    Individual philosopher structure.

    Behaviour:
        1) Just lives and waiting death.
        2) Printing only sleep or eating event!
        3) If he has eaten enought times, "kills" himself (is_dead = 1)

    Contains:
int         philo_number    -- indivitual number of philo on the table
int         is_dead         -- death status code. Only daemon changes it!
enum        action_status   -- think, eat or sleep, simple
timeval     last_time_eat   -- updating by philo after eat time
int         meals_number    -- number of how much times philo had
                                meals by this time
*/
typedef struct s_philosopher
{
    int             first_print_flag;
    struct timeval  sim_start_time;
    t_setup         *global_setup;
    int             philo_number;
    int             is_dead;
    struct timeval  last_time_eat;
    int             meals_number;
    int             ready_to_eat;
}   t_philosopher;

/*
    Servicer, which observe individual targeted philosopher
    Creating by philosopher!

    Behaviour:
        1) Taking forks and printing this event each time.
        2) When two forks has been taken
            servicer changing action_status of philo.

    Contains:
pthread_mutex_t     *forks          -- forks.
t_philosopher       *target -- philo., who created this servicer
*/
typedef struct s_servicer
{
    t_setup         *global_setup;
    t_philosopher   *target;
}   t_servicer;

# define FORK_LOCK      1
# define FORK_UNLOCK    2

/*
    Daemon.

    Literaly. It's daemon, who will kill targeted philosopher by time
    (end of simulation or personal death).
    Creating by philosopher too.
    Structure is just like servicer, so there is simple typedef instead
    of whole definition

    Behaviour:
        a) When philosopher dies daemon:
            - printing this event
            - set death status (target->is_dead) to 1
        b) When simulation stops (global_setup->simulation_status == 2),
            kills philosopher without any message.
        c) When philosopher has eaten enought times (is_dead = 1 by himself)
            -- daemon exit whitout message.

    Contains:
t_setup         *global_setup   -- for sim_status and time_to_die
t_philosopher   *target -- philo., who created this servicer
*/
typedef t_servicer  t_daemon;

// parser
int             agruments_parser(int argc, char **argv, t_setup *global_setup);

/* INITS */
// init philosophers' datas
t_philosopher   *init_philos_data(t_setup *setup);
// init forks
pthread_mutex_t *init_forks(t_setup *setup);
void            free_forks(pthread_mutex_t *forks, int num_of_inited_forks);
// init philo threads
int             init_philo_threads(t_setup *setup, t_philosopher *all_philos);

/* THREADS */
// philosopher thread
void            *thread_philosopher_entry(void *philosopher_data);
void            thread_philosopher(t_philosopher *data);
// servicer thread
void            *thread_servicer_entry(void *servicer_data);
void            thread_servicer(t_servicer *data);
// daemon thread
void            *thread_daemon_entry(void *daemon_data);
void            thread_daemon(t_daemon *data);

/* timespamps */
long int        get_period(const struct timeval *b, const struct timeval *e);
void            print_event(const char *event, int ev_id, t_philosopher *trg);
void            my_msleep(int msec);

#endif
