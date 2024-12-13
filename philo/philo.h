/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:54:30 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/13 16:03:59 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_philo
{
	int				id;
	pthread_t		t_id;
	long int		last_eat;
	struct t_data	*info;
	int				c_eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	long int		t_start;
}	t_data;

#endif