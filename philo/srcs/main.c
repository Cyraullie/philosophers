/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:50 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/03 15:04:47 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief process to free and delete any element at the end of programm
 * 
 * @param data get data struct
 * @param f get fork array
 */
void	freeall(t_data *data, pthread_mutex_t **f)
{
	int	i;

	i = 0;
	while (i < data->nb_philo - 1)
	{
		pthread_mutex_destroy(data->philo[i].fork_l);
		i++;
	}
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->eat_done);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->g_stop);
	free(data->philo);
	free(*f);
}

/**
 * @brief process of creation forks and philos
 * 
 * @param data get data struct
 * @param f get array of fork
 * @return int return success of failed
 */
int	alloc(t_data *data, pthread_mutex_t **f)
{
	*f = add_fork(data->nb_philo);
	if (!*f)
		return (0);
	philo_init(data, *f);
	return (1);
}

/**
 * @brief main function
 * 
 * @param ac get number of arguments
 * @param ag get string of arguments
 * @return int return success or failed
 */
int	main(int ac, char **ag)
{
	t_data			data;
	pthread_mutex_t	*f;

	if ((ac != 5 && ac != 6) || check_arg(ag))
	{
		print_msg_arg();
		return (0);
	}
	if (data_init(&data, ag) == 1)
	{
		free(data.philo);
		return (0);
	}
	alloc(&data, &f);
	freeall(&data, &f);
	return (0);
}
