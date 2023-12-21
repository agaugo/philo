/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hflohil- <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by hugo          #+#    #+#                 */
/*   Updated: 2023/12/15 15:39:03 by hugo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*

X amount of philosophers sit at a round table with bowls of food.
Forks are placed in front of each philosopher.
There are as many forks as philosophers.
All day the philosophers take turns eating, sleeping, and thinking.
A philosopher must have two forks in order to eat, and each fork
may only be used by one philosopher at a time. At any time a
philosopher can pick up or set down a fork,
but cannot start eating until picking up both forks.
The philosophers alternatively eat, sleep, or think.
While they are eating, they are not thinking nor sleeping,
while thinking, they are not eating nor sleeping,
and, of course, while sleeping, they are not eating nor thinking.

Allowed functions:
- memset, printf, malloc, free, write,
- usleep,               is used to suspend the execution of the program for a specified number of microseconds.
- gettimeofday,         is used to get the current time and timezone information, including seconds and microseconds since the Epoch.
- pthread_create,       is used to create a new thread. It takes as arguments the thread identifier, attributes, start routine (the function that the new thread will execute), and any arguments to the start routine.
- pthread_detach,       is used to mark a thread as detached. A detached thread will automatically release its resources when it exits, without needing to be joined.
- pthread_join,         is used to wait for a thread to terminate. It suspends the calling thread until the specified thread completes its execution.
- pthread_mutex_init,   is used to initialize a mutex (short for mutual exclusion). Mutexes are used to protect shared resources from simultaneous access by multiple threads.
- pthread_mutex_destroy is used to destroy a previously initialized mutex, freeing any resources associated with it.
- pthread_mutex_lock,   is used to lock a mutex. If the mutex is already locked by another thread, the calling thread will be blocked until the mutex becomes available.
- pthread_mutex_unlock  is used to unlock a previously locked mutex, allowing other threads to acquire the mutex for exclusive access to the shared resource.

*/

//int usleep(useconds_t usec);
//int gettimeofday(struct timeval *tv, struct timezone *tz);
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
//int pthread_detach(pthread_t thread);
//int pthread_join(pthread_t thread, void **retval);
//int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
//int pthread_mutex_destroy(pthread_mutex_t *mutex);
//int pthread_mutex_lock(pthread_mutex_t *mutex);
//int pthread_mutex_unlock(pthread_mutex_t *mutex);

int error(char *msg)
{
    printf("%s\n", msg);
    return (-1);
}

int main(int argc, char *argv[])
{
    t_init      init_values;
    pthread_t   *philosophers;
    uint64_t    *id;
    uint64_t    i;

    if (argc != 6)
        return (0);
    if (initiate_values(argv, &init_values) == -1)
        return (error("ERROR: Value Initialization."));
    philosophers = malloc(init_values.total_philos * sizeof(pthread_t));    //protect
    i = 0;
    while (i < init_values.total_philos)
    {
        id = malloc(sizeof(uint64_t));
        *id = i;
        pthread_create(&philosophers[i], NULL, philo_process, (void *)id);
        i++;
    }
    i = 0;
    while (i < init_values.total_philos)
    {
        pthread_join(philosophers[i], NULL);
        i++;
    }
    return (0);
}