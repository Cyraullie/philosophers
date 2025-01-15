/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:40:29 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/15 17:58:56 by cgoldens         ###   ########.fr       */
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
	}
	pthread_join(death_checker, NULL);
	return (NULL);
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

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (!is_dead(philo, 0))
	{
		pthread_mutex_lock(&philo->data->m_eat);
		if ((!is_dead(philo, 0)
				&& actual_ms(timestamp(), philo->data->t_start) \
				- philo->last_eat >= philo->data->t_die) || enough_eat(philo))
		{
			if (!enough_eat(philo))
				print(philo, " died");
			is_dead(philo, 1);
		}
		pthread_mutex_unlock(&philo->data->m_eat);
	}
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
	if (philo->data->nb_philo > 1)
	{			
		pthread_mutex_lock(philo->fork_l);
		print(philo, " has taken a fork");
		pthread_mutex_lock(philo->fork_r);
		print(philo, " has taken a fork");
	}
}

void	philo_sleep(t_philo *philo)
{
	print(philo, " is sleeping");
	ft_usleep(philo->data->t_sleep);
}
//TODO faire la norminette
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
