/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hflohil- <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by hugo          #+#    #+#                 */
/*   Updated: 2023/12/15 15:39:03 by hugo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void    destroy_mutexes(t_program *program, pthread_mutex_t *forks)
{
    int i;
    int x;

    i = 0;
    x = program->philos[i].number_of_philosophers;
    pthread_mutex_destroy(&program->lock_write);
    pthread_mutex_destroy(&program->lock_dead);
    pthread_mutex_destroy(&program->lock_eating);
    while (i < x)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}

int     launch_threads(t_program *program)
{
    pthread_t   thread_monitor;
    int         i;
    int         x;

    i = 0;
    x = program->philos[i].number_of_philosophers;
    if (pthread_create(&thread_monitor, NULL, monitor_routine, program->philos) != 0)
        return(-1);
    while (i < x)
    {
        if (pthread_create(&program->philos[i].thread, NULL, routine, &program->philos[i]) != 0)
            return(-1);
        i++;
    }
    if (pthread_join(thread_monitor, NULL) != 0)
        return (-1);
    i = 0;
    while (i < x)
    {
        if (pthread_join(program->philos[i].thread, NULL) != 0)
            return(-1);
        i++;
    }
    return (0);
}
//detach