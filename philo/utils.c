/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:35 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/19 15:22:22 by cgoldens         ###   ########.fr       */
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
void	print(t_philo *phi, char *str)
{
	printf("%lld %d %s", actual_ms(timestamp(), phi->data->t_start), phi->id, str);
}


void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->dead);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (0);
}