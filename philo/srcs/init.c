/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:03 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/03 14:55:06 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief process to construct data struct
 * 
 * @param data get struct build before
 * @param ag get all arguments
 * @return int return 0 if all is ok 1 if it's not
 */
int	data_init(t_data *data, char **ag)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat_done, NULL);
	pthread_mutex_init(&data->g_stop, NULL);
	data->stop = 0;
	data->nb_philo = ft_atoi(ag[1]);
	data->t_die = ft_atoi(ag[2]);
	data->t_eat = ft_atoi(ag[3]);
	data->t_sleep = ft_atoi(ag[4]);
	data->philo_eat = 0;
	if (ag[5])
		data->n_eat = ft_atoi(ag[5]);
	else
		data->n_eat = -1;
	if (ag[5] && data->n_eat == 0)
		return (1);
	return (0);
}

/**
 * @brief process to create all philo
 * 
 * @param data  get struct build before
 * @param f  get fork build before
 * @return int return state of process
 */
int	philo_init(t_data *data, pthread_mutex_t *f)
{
	int				i;
	t_philo			*philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (2);
	data->t_start = timestamp();
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].data = data;
		philo[i].c_eat = 0;
		philo[i].fork_l = &f[i];
		philo[i].fork_r = &f[(i + 1) % data->nb_philo];
	}
	data->philo = philo;
	return (monitor(data));
}

/**
 * @brief process of creation one fork by philo
 * 
 * @param nb number of philo
 * @return pthread_mutex_t* return array of fork with one thread each
 */
pthread_mutex_t	*add_fork(int nb)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * nb);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i-- > 0)
				pthread_mutex_destroy(&forks[i]);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
