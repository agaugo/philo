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

void    philo_input(t_philo *philo, char *input[])
{
    philo->number_of_philosophers   = ft_atoi(input[1]);
    philo->time_to_die              = ft_atoi(input[2]);
    philo->time_to_eat              = ft_atoi(input[3]);
    philo->time_to_sleep            = ft_atoi(input[4]);
    if (input[5])
        philo->number_of_times_each_philosopher_must_eat    = ft_atoi(input[5]);
    else
        philo->number_of_times_each_philosopher_must_eat    = -1;
}

void    initiate_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char *input[])
{
    int i;
    int num_of_philos;

    i = 0;
    num_of_philos = ft_atoi(input[1]);
    while (i < num_of_philos)
    {
        philos[i].philo_id      = i + 1;
        philos[i].eating        = 0;
        philos[i].meals_eaten   = 0;
        philo_input(&philos[i], input);
        philos[i].start_time    = get_time_in_ms();
        philos[i].previous_meal = get_time_in_ms();
        philos[i].end           = &program->end;
        philos[i].lock_write    = &program->lock_write;
        philos[i].lock_dead     = &program->lock_dead;
        philos[i].lock_eating   = &program->lock_eating;
        philos[i].left_fork     = &forks[i];
        if (i == 0)
            philos[i].right_fork = &forks[num_of_philos - 1];
        else
            philos[i].right_fork = &forks[i - 1];
        i++;
    }
}

int initiate_forks(pthread_mutex_t *forks, int num_of_forks)
{
    int i;

    i = 0;
    while (i < num_of_forks)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
            return (-1);
        i++;
    }
    return (0);
}

// int initiate_program(t_program *program, t_philo *philos)
// {
//     program->end = 0;
//     program->philos = philos;
//     if (pthread_mutex_init(&program->lock_dead, NULL) != 0)
//         return (error("Mutex Lock Initiation Fail"));
//     if (pthread_mutex_init(&program->lock_eating, NULL) != 0)
//         return (error("Mutex Lock Initiation Fail"));
//     if (pthread_mutex_init(&program->lock_write, NULL) != 0)
//         return (error("Mutex Lock Initiation Fail"));
//     return (0);
// }
int initiate_program(t_program *program, t_philo *philos)
{
    program->end = 0;
    program->philos = philos;

    if (pthread_mutex_init(&program->lock_dead, NULL) != 0 ||
        pthread_mutex_init(&program->lock_eating, NULL) != 0 ||
        pthread_mutex_init(&program->lock_write, NULL) != 0)
    {
        return (error("Mutex Lock Initiation Fail"));
    }

    return (0);
}


int initiate_all(t_program *program, t_philo *philos, pthread_mutex_t *forks, char *input[])
{
    if (initiate_program(program, philos) == -1)
        return (-1);
    if (initiate_forks(forks, ft_atoi(input[1])) == -1)
        return (-1);
    initiate_philos(philos, program, forks, input);
    return (0);
}
