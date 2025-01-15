/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:40:29 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/15 14:35:38 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	death_checker;

	philo = (t_philo *)phi;
	if (philo->id % 2 == 0)
		usleep(philo->data->t_eat / 10);
	pthread_create(&death_checker, NULL, check_death, philo);
	while (!is_dead(philo, 0))
	{
		philo_think(philo);
		take_fork(philo);
		philo_eat(philo);
		check_eat(phi);
	}
	pthread_join(death_checker, NULL);
	return (NULL);
}

void	check_eat(t_philo *phi)
{
	if (phi->c_eat == phi->data->n_eat)
	{
		pthread_mutex_lock(&phi->data->m_stop);
		if (++phi->data->philo_eat == phi->data->nb_philo)
			is_dead(phi, 2);
		pthread_mutex_unlock(&phi->data->m_stop);
		return ;
	}
	return ;
}

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->data->t_die + 1);
	pthread_mutex_lock(&philo->data->m_stop);
	pthread_mutex_lock(&philo->data->m_eat);
	if (!is_dead(philo, 0)
		&& actual_ms(timestamp(), philo->data->t_start) \
		- philo->last_eat >= philo->data->t_die)
	{
		print(philo, " died");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->data->m_eat);
	pthread_mutex_unlock(&philo->data->m_stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->fork_l);
		print(philo, " has taken a fork");
		ft_usleep(philo->data->t_die);
		print(philo, " died");
		pthread_mutex_unlock(philo->fork_l);
		is_dead(philo, 1);
		return ;
	}
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

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating");
	pthread_mutex_lock(&(philo->data->m_eat));
	philo->last_eat = actual_ms(timestamp(), philo->data->t_start);
	philo->c_eat++;
	pthread_mutex_unlock(&(philo->data->m_eat));
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	print(philo, " is sleeping");
	ft_usleep(philo->data->t_sleep);
}
