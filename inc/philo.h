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

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

# define PHILO_MAX 10000

/* STRUCTS */
typedef struct	s_init
{
    uint64_t    total_philos;
    uint64_t	time_to_die;
    uint64_t	time_to_eat;
    uint64_t	time_to_sleep;
    uint64_t    times_eat_each;
}				t_init;

typedef struct s_body
{
    t_init          init_values;
    uint64_t        id;
    pthread_mutex_t *chopsticks;
}               t_body;

/* CORE */
void        *philo_process(void *id);

/* UTILS */
int          ft_atoi(const char *str);

/* INIT */
int          initiate_values(char *argv[], t_init *init_values);
uint64_t     get_time(void);

/* MAIN */
int          main(int argc, char *argv[]);


#endif