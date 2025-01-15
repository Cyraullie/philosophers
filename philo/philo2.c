/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:41:04 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/15 17:59:50 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->m_eat));
	pthread_mutex_lock(&philo->data->m_stop);
	if (!philo->data->stop)
		print(philo, " is thinking");
	pthread_mutex_unlock(&(philo->data->m_eat));
	pthread_mutex_unlock(&philo->data->m_stop);
}
