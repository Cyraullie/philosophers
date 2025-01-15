/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:35 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/15 17:06:45 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned int	actual_ms(long long ms, long long start)
{
	unsigned int	time;

	time = ms - start;
	return (time);
}

void	print(t_philo *phi, char *str)
{
	int			dead;

	pthread_mutex_lock(&(phi->data->g_stop));
	dead = is_dead(phi, 0);
	pthread_mutex_unlock(&(phi->data->g_stop));
	pthread_mutex_lock(&(phi->data->print));
	if (!dead)
	{
		printf("%d %d %s\n", actual_ms(timestamp(), \
		phi->data->t_start), phi->id, str);
	}
	pthread_mutex_unlock(&(phi->data->print));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}
