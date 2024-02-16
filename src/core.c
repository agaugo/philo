/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hflohil- <hflohil-@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:16:15 by hugo          #+#    #+#                 */
/*   Updated: 2023/12/15 15:39:03 by hugo          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	monitor_check(t_philo *philo)
{
	int	i;
	int	d;

	i = 0;
	d = 1;
	while (1)
	{
		while (i < philo->number_of_philosophers)
		{
			pthread_mutex_lock(philo->lock);
			if (*philo->max == 1)
				d = 0;
			if (get_time_in_ms() - philo[i].previous_meal > philo->time_to_die)
			{
				*philo->end = 1;
				pthread_mutex_unlock(philo->lock);
				sync_print(&philo[i], "has died", d);
				return ;
			}
			pthread_mutex_unlock(philo->lock);
			i++;
			usleep(25);
		}
		i = 0;
	}
}

void	max_reached(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	*philo->max = 1;
	pthread_mutex_unlock(philo->lock);
}

void	*routine(void *content)
{
	t_philo	*philo;

	philo = (t_philo *)content;
	if (philo->philo_id % 2 == 0)
		precise_sleep(philo->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(philo->lock);
		if (*philo->end == 1)
		{
			pthread_mutex_unlock(philo->lock);
			break ;
		}
		pthread_mutex_unlock(philo->lock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philo->number_of_times != -1
			&& philo->meals_eaten >= philo->number_of_times)
		{
			max_reached(philo);
			break ;
		}
	}
	return (content);
}
