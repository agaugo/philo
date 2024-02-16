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

#include "../inc/philo.h"

int	error(char *message)
{
	printf("Error: %s\n", message);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (check_input(argc, argv) == -1)
		return (error("Invalid Arguments"));
	if (initiate_all(&program, philos, forks, argv) == -1)
		return (error("Initiation Failure"));
	if (launch_threads(&program) == -1)
	{
		destroy_mutexes(&program, forks);
		return (error("Thread Creation Failure"));
	}
	destroy_mutexes(&program, forks);
	return (0);
}
