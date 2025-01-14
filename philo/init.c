/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:03 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/14 16:08:45 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(char **str)
{
	int	i;
	int	j;

	if (ft_atoi(str[1]) < 1)
		return (1);
	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	data_init(t_data *data, char **ag)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	data->stop = 0;
	data->nb_philo = ft_atoi(ag[1]);
	if (check_num(ag))
	{
		printf("Invalid Arguments\n");
		return (1);
	}
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

int	monitor(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
	 	if (pthread_create(&data->philo[i].thread, NULL, 
	 			&philo_life, &(data->philo[i])) != 0)
	 		return (-1);
	}
	i = -1;
	while (++i < data->nb_philo)
	if (pthread_join(data->philo[i].thread, NULL) != 0)
		return (-1);
	return (0);
}

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
