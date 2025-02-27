/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:52:28 by cgoldens          #+#    #+#             */
/*   Updated: 2025/02/27 15:08:38 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_msg_arg(void)
{
	write(2, "USAGE ./philo number_of_philosophers", 37);
	write(2, " time_to_die time_to_eat", 25);
	write(2, " time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 60);
}

int	check_arg(char **ag)
{
	int	i;
	int	j;

	if (ft_atoi(ag[1]) < 1)
		return (1);
	i = 1;
	while (ag[i])
	{
		j = 0;
		while (ag[i][j])
		{
			if (!ft_isdigit(ag[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
