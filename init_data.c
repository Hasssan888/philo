/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:12:08 by hbakrim           #+#    #+#             */
/*   Updated: 2024/08/29 18:12:11 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->last_meal_eat, NULL);
	pthread_mutex_init(&data->mutex_full, NULL);
	pthread_mutex_init(&data->mutex_is_dead, NULL);
	pthread_mutex_init(&data->mutex_flag_eat, NULL);
	pthread_mutex_init(&data->mutex_write, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
	{
		write(2, "error: init forks\n", 19);
		return (2);
	}
		;
	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
}

int	assign_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
	{
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->philo_nb];
		if (data->philo[i].id % 2 == 0)
		{
			data->philo[i].left_fork = &data->forks[(i + 1) % data->philo_nb];
			data->philo[i].right_fork = &data->forks[i];
		}
	}
	return (0);
}

int	init_each_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philosophers = malloc(sizeof(pthread_t) * data->philo_nb);
	while (++i < data->philo_nb)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_meal_time = get_time();
		data->philo[i].data = data;
		data->philo[i].meals_eat = 0;
		data->is_full = 0;
		data->is_die = 0;
		data->flag_eat = 0;
	}
	assign_forks(data);
	return (0);
}
