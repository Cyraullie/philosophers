/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:54:30 by cgoldens          #+#    #+#             */
/*   Updated: 2024/12/17 11:31:08 by cgoldens         ###   ########.fr       */
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
	pthread_t		thread;
	long int		last_eat;
	struct s_data	*data;
	int				c_eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}	t_philo;

typedef struct s_data
{
	int				philo_eat;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
}	t_data;

long long	timestamp();
int	data_init(t_data *data, char **ag);
int	ft_atoi(const char *str);
long long	actual_ms(long long ms, long long start);
int	ft_isdigit(int c);
int	philo_init(t_data *data);
void	print(t_philo *phi, char *str);
void	philo_eat(t_philo *philo);
/*void	take_fork(t_philo *philo);
void	*check_death(void *phi);
void	*philo_life(void *phi);*/
#endif