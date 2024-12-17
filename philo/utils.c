/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:35 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/16 14:30:47 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	actual_ms(long long ms, long long start)
{
	return (ms - start);
}
void	ft_print(t_data *data, int i, char *str)
{
	printf("%lld %d %s\n", actual_ms(timestamp(), data->t_start), data->philo[i].id, str);
}