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

// int	death(t_philo *philo)
// {
// 	pthread_mutex_lock(philo->lock_dead);
// 	if (*philo->end == 1)
//     {
//         pthread_mutex_unlock(philo->lock_dead);
// 		return (1);
//     }
// 	pthread_mutex_unlock(philo->lock_dead);
// 	return (0);
// }

// void    *monitor_routine(void *content)
// {
//     t_philo *philo;

//     philo = (t_philo *)content;
//     while (1)
//     {
//         if (monitor_check_eaten(philo) == 1 || monitor_check_death(philo) == 1)
//             break ;
//     }
//     return (content);
// }

void *routine(void *content)
{
    t_philo *philo = (t_philo *)content;

    while (1)
    {
        if (monitor_check_death(philo) == 1 || monitor_check_eaten(philo) == 1)
            break;
        philo_actions(philo);
    }
    return content;
}