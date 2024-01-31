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

int get_time_in_ms(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) < 0)
        return (error("Time Error"));
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
size_t  precise_sleep(size_t duration_in_ms)
{
    size_t start;

    start = (size_t)get_time_in_ms();
    while ((get_time_in_ms() - start) < duration_in_ms)
        usleep(500);
    return(0);
}