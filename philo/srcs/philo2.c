/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:41:04 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/27 15:08:27 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->m_eat));
	pthread_mutex_lock(&philo->data->m_stop);
	if (!philo->data->stop)
		print(philo, " is thinking");
	pthread_mutex_unlock(&(philo->data->m_eat));
	pthread_mutex_unlock(&philo->data->m_stop);
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

int	enough_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_done);
	if (philo->data->philo_eat == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->eat_done);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_done);
	return (0);
}
