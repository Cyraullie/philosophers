/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:44:55 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/05 17:30:42 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief process to count each philos who has finish to eat
 * 
 * @param philo get one philo
 * @return int return 1 if all philo are enough eat, 0 for not
 */
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

/**
 * @brief process to handle if there is only one philo
 * 
 * @param philo get one philo
 */
void	handle_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print(philo, " has taken a fork");
	ft_usleep(philo->data->t_die);
	print(philo, " died");
	pthread_mutex_unlock(philo->fork_l);
	is_dead(philo, 1);
}

/**
 * @brief process to take a left and right fork
 * 
 * @param philo get one philo
 */
void	take_fork(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
		handle_one(philo);
	if (philo->data->nb_philo > 1)
	{		
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->fork_l);
			print(philo, " has taken a fork");
			pthread_mutex_lock(philo->fork_r);
			print(philo, " has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->fork_r);
			print(philo, " has taken a fork");
			pthread_mutex_lock(philo->fork_l);
			print(philo, " has taken a fork");
		}
	}
}

/**
 * @brief process of eating for a philo
 * 
 * @param philo get one philo
 */
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->m_eat));
	pthread_mutex_lock(&philo->data->m_stop);
	print(philo, " is eating");
	philo->last_eat = actual_ms(timestamp(), philo->data->t_start);
	pthread_mutex_unlock(&philo->data->m_stop);
	pthread_mutex_unlock(&(philo->data->m_eat));
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_lock(&(philo->data->m_eat));
	pthread_mutex_lock(&philo->data->m_stop);
	philo->c_eat++;
	if (philo->c_eat == philo->data->n_eat)
		philo->data->philo_eat++;
	pthread_mutex_unlock(&philo->data->m_stop);
	pthread_mutex_unlock(&(philo->data->m_eat));
	philo_sleep(philo);
}
