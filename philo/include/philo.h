/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoldens <cgoldens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:54:30 by cgoldens          #+#    #+#             */
/*   Updated: 2025/01/15 17:44:03 by cgoldens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	unsigned int		last_eat;
	struct s_data		*data;
	int					c_eat;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
}	t_philo;

typedef struct s_data
{
	int				philo_eat;
	int				nb_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int				n_eat;
	unsigned int	t_start;
	int				stop;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat_done;
	pthread_mutex_t	g_stop;
}	t_data;

long long		timestamp(void);
unsigned int	actual_ms(long long ms, long long start);
int				data_init(t_data *data, char **ag);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				philo_init(t_data *data, pthread_mutex_t *f);
void			print(t_philo *phi, char *str);
void			philo_eat(t_philo *philo);
void			ft_usleep(int ms);
void			take_fork(t_philo *philo);
void			*check_death(void *phi);
void			*philo_life(void *phi);
int				is_dead(t_philo *philo, int nb);
void			philo_think(t_philo *philo);
void			check_eat(t_philo *phi);
pthread_mutex_t	*add_fork(int nb);
void			freeall(t_data *data, pthread_mutex_t **f);
void			print_msg_arg(void);
int				check_arg(char **ag);
int				enough_eat(t_philo *philo);

#endif