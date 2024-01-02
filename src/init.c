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

int initiate_values(char *argv[], t_init *init_values)
{
    init_values->total_philos = (uint64_t)ft_atoi(argv[1]);
    init_values->time_to_die = (uint64_t)ft_atoi(argv[2]);
    init_values->time_to_eat = (uint64_t)ft_atoi(argv[3]);
    init_values->time_to_sleep = (uint64_t)ft_atoi(argv[4]);
    init_values->times_eat_each = (uint64_t)ft_atoi(argv[5]);
    if (init_values->total_philos == 0 ||
        init_values->time_to_die == 0 ||
        init_values->time_to_eat == 0 ||
        init_values->time_to_sleep == 0 ||
        init_values->times_eat_each == 0 ||
        init_values->total_philos > PHILO_MAX)
        return (-1);
    return (1);
}
