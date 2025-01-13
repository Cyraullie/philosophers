/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:03 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/13 14:52:02 by cgoldens         ###   ########.fr       */
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
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (data->philo == NULL)
		return (2);
	if (check_num(ag))
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	data->t_die = ft_atoi(ag[2]);
	data->t_eat = ft_atoi(ag[3]);
	data->t_sleep = ft_atoi(ag[4]);
	if (ag[5])
		data->n_eat = ft_atoi(ag[5]);
	else
		data->n_eat = -1;
	if (ag[5] && data->n_eat == 0)
		return (1);
	return (0);
}

int	philo_init(t_data *data)
{
	int	i;

	data->t_start = timestamp();
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].data = data;
		data->philo[i].c_eat = 0;
		add_fork(data, i);
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}
void	add_fork(t_data *data, int i)
{
	data->philo[i].fork_r = malloc(sizeof(pthread_mutex_t *));
	pthread_mutex_init(&(data->philo[i].fork_l), NULL);
	if (i == data->nb_philo - 1)
		data->philo[i].fork_r = &data->philo[0].fork_l;
	else
		data->philo[i].fork_r = &data->philo[i + 1].fork_l;
}