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

void	sync_print(t_body *body, uint64_t id, char *msg)
{
	uint64_t timestamp;

	timestamp = elapsed_time_ms(body);
	
	printf("Timestamp: %llu --- Philosopher %llu: %s\n", timestamp, id, msg);
}

void    *philo_process(void *philosopher)
{
    uint64_t philo_id;
    uint64_t left_chopstick;
    uint64_t right_chopstick;
    t_body   *body;

    body			= (t_body *)philosopher;
    philo_id		= body->id;
    left_chopstick	= philo_id;
	right_chopstick	= (philo_id + 1) % body->init_values.total_philos;
    while (1)
    {
		sync_print(body, philo_id, "is thinking");
		if (philo_id % 2 == 0) 
		{
        	pthread_mutex_lock(&body->chopsticks[left_chopstick]);
        	pthread_mutex_lock(&body->chopsticks[right_chopstick]);
   		} 
		else 
		{
        	pthread_mutex_lock(&body->chopsticks[right_chopstick]);
        	pthread_mutex_lock(&body->chopsticks[left_chopstick]);
    	}

		sync_print(body, philo_id, "has taken a chopstick");
    	sync_print(body, philo_id, "has taken a chopstick");
    	sync_print(body, philo_id, "is eating");
		usleep(body->init_values.time_to_eat * 1000);
		pthread_mutex_unlock(&body->chopsticks[left_chopstick]);
		pthread_mutex_unlock(&body->chopsticks[right_chopstick]);
		sync_print(body, philo_id, "is sleeping");
		usleep(body->init_values.time_to_sleep * 1000);
		body->init_values.times_eat_each--;
    	if (body->init_values.times_eat_each <= 0)
		{
			sync_print(body, philo_id, "has eaten enough");
			break ;
		}
    }
	free(philosopher);
	return NULL;
}

