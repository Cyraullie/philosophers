/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:45:50 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/13 16:06:31 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **ag)
{
	t_data *data;
	
	if (ac == 5 || ac == 6)
		data = data_init(ac, ag);
	
	printf("time %lld\nnb philo : %d\ntime to die : %d\ntime to eat : %d\ntime to sleep : %d\nnb eat to finish : %d\n", (timestamp() - data->t_start), data->nb_philo, data->t_die, data->t_eat, data->t_sleep, data->n_eat );

	return (0);
}