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
    pthread_mutex_destroy(&program->lock);
    while (i < x)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}

int     launch_threads(t_program *program)
{
    int         i;
    int         x;

    i = 0;
    x = program->philos[0].number_of_philosophers;
    while (i < x)
    {
        if (pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]) != 0)
            return(-1);
        i++;
    }
    monitor_check(program->philos);
    i = 0;
    while (i < x)
    {
        if (pthread_join(program->philos[i].thread, NULL) != 0)
            return(-1);
        i++;
    }
	i = 0;
	while (i < x)
	{
		printf("Philosopher %d has eaten %d meals\n", program->philos[i].philo_id, program->philos[i].meals_eaten);
		i++;
	}
    return (0);
}
/*

	i = 0;
	while (i < x)
	{
		printf("Philosopher %d has eaten %d meals\n", program->philos[i].philo_id, program->philos[i].meals_eaten);
		i++;
	}
    return (0);

*/
