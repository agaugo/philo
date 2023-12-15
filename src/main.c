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

#include "../includes/philo.h"

int main(int    argc, char  *argv[])
{
    if (argc != 6)
        return (0);
    printf("num_of_philo:     %s\ntime_to_die:      %s\ntime_to_eat:      %s\ntime_to_sleep:    %s\nnum_times_eat:    %s\n", argv[1], argv[2], argv[3], argv[4], argv[5]);
}