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

void grab_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    sync_print(philo, "grabbed a fork", 0);
    if (philo->number_of_philosophers == 1)
    {
        precise_sleep(philo->time_to_die * 2);
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    pthread_mutex_lock(philo->right_fork);
    sync_print(philo, "grabbed a fork", 0);
}

void philo_eat(t_philo *philo)
{
    grab_forks(philo);
    pthread_mutex_lock(philo->lock);
    philo->previous_meal = get_time_in_ms();
    if (*philo->end != 1)
        philo->meals_eaten++;
    pthread_mutex_unlock(philo->lock);
    sync_print(philo, "is eating", 0);
    precise_sleep(philo->time_to_eat);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void philo_sleep(t_philo *philo)
{
    sync_print(philo, "is sleeping", 0);
    precise_sleep(philo->time_to_sleep);
}
 
 void philo_think(t_philo *philo)
 {
    sync_print(philo, "is thinking", 0);
 }
