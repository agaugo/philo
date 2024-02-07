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
        return (-1);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
int  precise_sleep(int duration_in_ms)
{
    int start;

    start = get_time_in_ms();
    while ((get_time_in_ms() - start) < duration_in_ms)
        usleep(1000);
    return(0);
}

// int precise_sleep(int duration_in_ms) {
//     int start = get_time_in_ms();
//     int sleep_time = duration_in_ms - 10; // Sleep for slightly less time using usleep
//     while ((get_time_in_ms() - start) < sleep_time) {
//         usleep(10000); // Sleep in larger chunks to reduce CPU usage
//     }
//     // Busy-wait for the last few milliseconds for accuracy
//     while ((get_time_in_ms() - start) < duration_in_ms) {
//         usleep(100); // Shorter sleeps for accuracy without much CPU usage
//     }
//     return 0;
// }
