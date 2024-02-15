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

void	sync_print(t_philo *philo, char *msg, int death)
{
	int	time;

	pthread_mutex_lock(philo->lock);
	time = get_time_in_ms() - philo->start_time;
	if (*philo->end != 1 || death == 1)
		printf("Timestamp: %d --- Philosopher %d: %s\n", time, philo->philo_id,
			msg);
	pthread_mutex_unlock(philo->lock);
}

int	check_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	if ((argc != 5 && argc != 6) || ft_atoi(argv[i]) > PHILO_MAX)
		return (-1);
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	base;
	int	sign;

	base = 0;
	sign = 1;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign *= -1;
			str++;
		}
		while (ft_isdigit(*str))
		{
			base *= 10;
			base += *(str) - '0';
			str++;
		}
		break ;
	}
	return (base * sign);
}
