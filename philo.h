/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:21:03 by hbakrim           #+#    #+#             */
/*   Updated: 2024/08/29 18:21:08 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time;
	int				id;
	int				meals_eat;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_nb;
	long			philo_nb;

	int				is_die;
	int				is_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_meal_eat;
	pthread_mutex_t	mutex_full;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	mutex_flag_eat;
	pthread_mutex_t	mutex_write;
	pthread_t		*philosophers;
	t_philo			*philo;
	long			start;
	int				flag_eat;

}					t_data;

// philo_utils
int					ft_isdigit(int d);
long				ft_atoi(const char *str);
long				get_time(void);
int					ft_usleep(t_data *data, long milliseconds);

// monitor
int					finished_meals(t_data *data);
void				*monitor(void *args);

// init_data
int					init_each_philo(t_data *data);
int					assign_forks(t_data *data);
int					init_mutex(t_data *data);

// routine
void				*routine(void *arg);
int					sleeping(t_philo *philo);
void				print_msg(char *msg, t_philo *philo);
void				eating(t_philo *philo);

// utils
int					is_died(t_philo *philo);
void				ft_free(t_data *data);

#endif
