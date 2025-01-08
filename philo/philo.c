/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:40:29 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/08 16:09:59 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	if (philo->id % 2 == 0)
		usleep(philo->data->t_eat / 10);
	while (!is_dead(philo, 0))
	{
		pthread_create(&t, NULL, check_death, phi);
		philo_think(philo);
		take_fork(philo);
		philo_eat(philo);
		if (philo->c_eat == philo->data->n_eat)
		{
			pthread_mutex_lock(&philo->data->m_stop);
			if (++philo->data->philo_eat == philo->data->nb_philo)
			{
				//printf("tout le monde a fini de manger %d _ %d\n", philo->data->philo_eat, philo->data->nb_philo);
				pthread_mutex_unlock(&philo->data->m_stop);
				is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->data->m_stop);
			return (NULL);
		}

		pthread_detach(t);
	}
	return (NULL);
}

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->data->t_die + 1);
	pthread_mutex_lock(&philo->data->m_eat);
	pthread_mutex_lock(&philo->data->m_stop);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_eat >= (long)(philo->data->t_die))
	{
		pthread_mutex_unlock(&philo->data->m_eat);
		pthread_mutex_unlock(&philo->data->m_stop);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->data->m_eat);
	pthread_mutex_unlock(&philo->data->m_stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	print(philo, " has taken a fork\n");
	if (philo->data->nb_philo == 1)
	{
		ft_usleep(philo->data->t_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	print(philo, " has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->data->m_eat));
	philo->last_eat = timestamp();
	philo->c_eat++;
	pthread_mutex_unlock(&(philo->data->m_eat));
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, " is sleeping\n");
	ft_usleep(philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	print(philo, " is thinking\n");
}