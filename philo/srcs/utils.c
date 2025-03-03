/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:35 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/03 15:10:35 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief process to get a timestamp
 * 
 * @return long long return actual timestamp
 */
long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 * @brief process to say what time is it compared of start time
 * 
 * @param ms get a timestamp
 * @param start get a start time
 * @return unsigned int return the time compared of actual time and start time
 */
unsigned int	actual_ms(long long ms, long long start)
{
	unsigned int	time;

	time = ms - start;
	return (time);
}

/**
 * @brief process to wait a time
 * 
 * @param ms get a time
 */
void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

/**
 * @brief process to check if the arguments are respected
 * 
 * @param ag string of arguments
 * @return int return success or failed
 */
int	check_arg(char **ag)
{
	int	i;
	int	j;

	if (ft_atoi(ag[1]) < 1)
		return (1);
	i = 1;
	while (ag[i])
	{
		j = 0;
		while (ag[i][j])
		{
			if (!ft_isdigit(ag[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
