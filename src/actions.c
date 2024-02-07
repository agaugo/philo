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
	int	x;

    i = 0;
	x = philo[0].number_of_philosophers;
    while (i < x)
    {
        pthread_mutex_lock(philo[i].lock_eating);
        if ((get_time_in_ms() - (philo[i].previous_meal)) > philo[0].time_to_die)
        {
			pthread_mutex_lock(philo[0].lock_dead);
			*philo->end = 1;
			sync_print(&philo[i], "has died");
			pthread_mutex_unlock(philo[0].lock_dead);
			pthread_mutex_unlock(philo[i].lock_eating);
			printf("Philosopher %d, time since last meal: %d\n", philo[i].philo_id, get_time_in_ms() - philo[i].previous_meal);
			return (1);
        }
        pthread_mutex_unlock(philo[i].lock_eating);
        i++;
    }
	

    return (0);
}

int monitor_check_eaten(t_philo *philos) {
    int i;
    int have_eaten_enough = 0;
    int meals[philos[0].number_of_philosophers]; // Store meals eaten count for each philosopher

    if (philos[0].number_of_times_each_philosopher_must_eat == -1)
        return (0);

    for (i = 0; i < philos[0].number_of_philosophers; i++) {
        pthread_mutex_lock(philos[i].lock_eating);
        meals[i] = philos[i].meals_eaten;
        pthread_mutex_unlock(philos[i].lock_eating);
    }

    for (i = 0; i < philos[0].number_of_philosophers; i++) {
        if (meals[i] >= philos[i].number_of_times_each_philosopher_must_eat)
            have_eaten_enough++;
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

void philo_eat(t_philo *philo) {
    pthread_mutex_t *first_fork = (philo->philo_id % 2 == 0) ? philo->left_fork : philo->right_fork;
    pthread_mutex_t *second_fork = (philo->philo_id % 2 == 0) ? philo->right_fork : philo->left_fork;

    pthread_mutex_lock(first_fork);
    sync_print(philo, "grabbed a fork");
    if (philo->number_of_philosophers == 1) {
        precise_sleep(philo->time_to_die);
        pthread_mutex_unlock(first_fork);
        return;
    }
    pthread_mutex_lock(second_fork);
    sync_print(philo, "grabbed a fork");

    pthread_mutex_lock(philo->lock_eating);
    philo->eating = 1; // Set eating flag to true before eating starts
    philo->previous_meal = get_time_in_ms();
    pthread_mutex_unlock(philo->lock_eating);

    sync_print(philo, "is eating");
    precise_sleep(philo->time_to_eat);

    pthread_mutex_lock(philo->lock_eating);
    philo->eating = 0; // Reset eating flag to false after eating
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->lock_eating);

    pthread_mutex_unlock(first_fork);
    pthread_mutex_unlock(second_fork);
}

void philo_sleep(t_philo *philo)
{
    // Sleep
    sync_print(philo, "is sleeping");
    precise_sleep(philo->time_to_sleep);
}
    // Think
 
 void philo_think(t_philo *philo)
 {
    sync_print(philo, "is thinking");
 }
 
void philo_actions(t_philo *philo) 
{
    // if (*philo->end)
	// 	return; // Stop if the simulation is ended.
    philo_eat(philo);
    // if (*philo->end)
	// 	return; // Check again, as the state might have changed.
    philo_sleep(philo);
    // if (*philo->end)
	// 	return;
    philo_think(philo);
}
