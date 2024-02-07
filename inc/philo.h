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

#ifndef PHILO_H
# define PHILO_H
# define PHILO_MAX 200

//LIBRARIES
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

//STRUCTS
typedef struct   s_philo
{
    pthread_t       thread;
    int     philo_id;
    int     eating;
    int     meals_eaten;
    int     number_of_philosophers;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     number_of_times_each_philosopher_must_eat;
    int     start_time;
    int     previous_meal;
    int     *end;
    pthread_mutex_t *lock_write;
    pthread_mutex_t *lock_dead;
    pthread_mutex_t *lock_eating;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
}               t_philo;

typedef struct s_program
{
    int             end;
    t_philo         *philos;
    pthread_mutex_t lock_write;
    pthread_mutex_t lock_dead;
    pthread_mutex_t lock_eating;
}               t_program;

//UTILITIES
int get_time_in_ms(void);
int check_input(int argc, char *argv[]);
int	ft_atoi(const char *str);

//INITIATE FUNCTIONS
int initiate_all(t_program *program, t_philo *philos, pthread_mutex_t *forks, char *input[]);
int check_input(int argc, char *argv[]);

//CORE ROUTINE
void    *routine(void *content);
void    *monitor_routine(void *philos);

void    destroy_mutexes(t_program *program, pthread_mutex_t *forks);
int     launch_threads(t_program *program);
void	sync_print(t_philo *philo, char *msg);
void    philo_actions(t_philo *philo);
int  	precise_sleep(int duration_in_ms);
int    	monitor_check_death(t_philo *philo);
int    	monitor_check_eaten(t_philo *philo);


//MAIN
int error(char *message);
int main(int argc, char *argv[]);


#endif