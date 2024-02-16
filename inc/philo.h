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

#ifndef PHILO_H
# define PHILO_H
# define PHILO_MAX 200

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				eating;
	int				meals_eaten;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times;
	int				start_time;
	int				previous_meal;
	int				*end;
	int				*max;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

typedef struct s_program
{
	int				end;
	int				max;
	t_philo			*philos;
	pthread_mutex_t	lock;
}					t_program;

int					get_time_in_ms(void);
int					check_input(int argc, char *argv[]);
int					ft_atoi(const char *str);

int					initiate_all(t_program *program, t_philo *philos,
						pthread_mutex_t *forks, char *input[]);
int					check_input(int argc, char *argv[]);
void				*routine(void *content);
void				*monitor_routine(void *philos);
void				destroy_mutexes(t_program *program, pthread_mutex_t *forks);
int					launch_threads(t_program *program);
void				sync_print(t_philo *philo, char *msg, int death);
void				philo_actions(t_philo *philo);
int					precise_sleep(int duration_in_ms);
void				monitor_check(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
int					error(char *message);
int					main(int argc, char *argv[]);

#endif