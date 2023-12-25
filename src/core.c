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

void    *philo_process(void *philosopher)
{
    uint64_t philo_id;
    uint64_t left_chopstick;
    uint64_t right_chopstick;
    t_body   *body;

    body = (t_body *)philosopher;
    philo_id = body->id;
    left_chopstick = philo_id;
    right_chopstick = philo_id + 1 % body->init_values.total_philos;
    while (1)
    {
		printf("Timestamp: %llu", elapsed_time_ms(body));
        printf("Philosopher %llu: Is Thinking\n", philo_id);

        pthread_mutex_lock(&body->chopsticks[left_chopstick]);          //pick up left chopsticks
        pthread_mutex_lock(&body->chopsticks[right_chopstick]);         //pick up right chopsticks

		printf("Timestamp: %llu", elapsed_time_ms(body));
        printf("Philosopher %llu: Is Eating\n", philo_id);
        usleep(body->init_values.time_to_eat);                          //taking time to eat

        pthread_mutex_unlock(&body->chopsticks[left_chopstick]);        //putting down left chopsticks
        pthread_mutex_unlock(&body->chopsticks[right_chopstick]);       //putting down right chopsticks
		printf("Timestamp: %llu", elapsed_time_ms(body));
        printf("Philosopher %llu: Is Sleeping\n", philo_id);
        usleep(body->init_values.time_to_sleep);                        //taking time to sleep
        body->init_values.times_eat_each--;
        if (body->init_values.times_eat_each == 0)
            break ;
    }
    return (NULL);
}