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

// Function to calculate elapsed time in milliseconds
uint64_t elapsed_time_ms(t_body *body)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    uint64_t elapsed_ms = (current_time.tv_sec - body->init_values.start_time.tv_sec) * 1000 + (current_time.tv_usec - body->init_values.start_time.tv_usec) / 1000;

    return elapsed_ms;
}

// Function to get the current time in seconds
uint64_t get_time(void)
{
    // Structure to store current time
    struct timeval time;

    // Get the current time
    gettimeofday(&time, NULL);
    // Return the current time in seconds
    return (time.tv_sec);
}
