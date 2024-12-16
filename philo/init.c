/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:05:03 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/16 12:04:32 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(char **str)
{
	int	i;
	int	j;

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
	data->nb_philo = ft_atoi(ag[1]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	/*if (data->philo == NULL)
		return (2);*/
	/*if (check_num(av))
	{
		printf("Invalid Arguments\n");
		return (1);
	}*/
	data->t_die = ft_atoi(ag[2]);
	data->t_eat = ft_atoi(ag[3]);
	data->t_sleep = ft_atoi(ag[4]);
	data->t_start = timestamp();
	if (ag[5])
		data->n_eat = ft_atoi(ag[5]);
	else
		data->n_eat = -1;
	/*if (ag[5] && data->n_eat == 0)
		return (1);*/
	return (0);
}