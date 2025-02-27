/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:35 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/27 15:08:38 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

	pthread_mutex_lock(&(phi->data->print));
	dead = is_dead(phi, 0);
	if (!dead)
	{
		usleep(5);
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
