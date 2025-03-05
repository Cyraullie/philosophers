/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:34:27 by cgoldens          #+#    #+#             */
/*   Updated: 2025/03/05 17:30:44 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief print message if base argument aren't respected
 * 
 */
void	print_msg_arg(void)
{
	write(2, "USAGE ./philo number_of_philosophers", 37);
	write(2, " time_to_die time_to_eat", 25);
	write(2, " time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 60);
}

/**
 * @brief print message of philo's activity
 * 
 * @param phi get the philo who do something
 * @param str get string of message for what philo do
 */
void	print(t_philo *phi, char *str)
{
	int			dead;

	pthread_mutex_lock(&(phi->data->print));
	dead = is_dead(phi, 0);
	if (!dead)
	{
		printf("%d %d %s\n", actual_ms(timestamp(), \
		phi->data->t_start), phi->id, str);
	}
	pthread_mutex_unlock(&(phi->data->print));
}
