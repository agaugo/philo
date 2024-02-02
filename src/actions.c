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
	
int		philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->lock_eating);
	if (get_time_in_ms() - philo->previous_meal >= philo->time_to_die && philo->eating == 0)
		return (pthread_mutex_unlock(philo->lock_eating), 1);
	pthread_mutex_unlock(philo->lock_eating);
	return (0);

}

int     monitor_check_death(t_philo *philo)
{
    int i;
    int d;
	int	x;

    i = 0;
    d = 0;
	x = philo[0].number_of_philosophers;
    while (i < x)
    {
        pthread_mutex_lock(philo[i].lock_eating);
        if ((get_time_in_ms() - (philo[i].previous_meal)) > philo[0].time_to_die)
        {
			pthread_mutex_lock(philo[0].lock_dead);
			*philo->end = 1;
			pthread_mutex_unlock(philo[0].lock_dead);
			d = 1;
        }
        pthread_mutex_unlock(philo[i].lock_eating);
        i++;
    }
    return (d);
}

int    monitor_check_eaten(t_philo *philos)
{
    int i;
    int have_eaten_enough;

    i = 0;
    have_eaten_enough = 0;
    if (philos[0].number_of_times_each_philosopher_must_eat == -1)
        return (0);
    while (i < philos[0].number_of_philosophers)
    {
        pthread_mutex_lock(philos[i].lock_eating);
        if (philos[i].meals_eaten == philos[i].number_of_times_each_philosopher_must_eat)
            have_eaten_enough++;
        pthread_mutex_unlock(philos[i].lock_eating);
        i++;
    }
    if (have_eaten_enough == philos[0].number_of_philosophers)
    {
        pthread_mutex_lock(philos[0].lock_dead);
        *philos->end = 1;
        pthread_mutex_unlock(philos[0].lock_dead);
        return (1);
    }
    return (0);
}

void	philo_think(t_philo *philo)
{
	sync_print(philo, "is thinking");
}

void    philo_sleep(t_philo *philo)
{
	sync_print(philo, "is sleeping");
    precise_sleep(philo->time_to_sleep);
}

void    philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    sync_print(philo, "grabbed a fork");
	if (philo->number_of_philosophers == 1)
    {
        precise_sleep(philo->time_to_die);
        pthread_mutex_unlock(philo->right_fork);
        return ;
    }
    pthread_mutex_lock(philo->left_fork);
    sync_print(philo, "grabbed a fork");
    pthread_mutex_lock(philo->lock_eating);
    philo->eating = 1;
    philo->previous_meal = get_time_in_ms();
    sync_print(philo, "is eating");
    philo->meals_eaten += 1;
    pthread_mutex_unlock(philo->lock_eating);
    precise_sleep((size_t)philo->time_to_eat);
    philo->eating = 0;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    philo_actions(t_philo *philo)
{
    philo_eat(philo);
    philo_sleep(philo);
    philo_think(philo);
}
