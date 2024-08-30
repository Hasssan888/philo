/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:14:48 by hbakrim           #+#    #+#             */
/*   Updated: 2024/08/29 18:14:51 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_is_dead);
	if (philo->data->is_die)
	{
		pthread_mutex_unlock(&philo->data->mutex_is_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_is_dead);
	return (0);
}

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nb)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->last_meal_eat);
	pthread_mutex_destroy(&data->mutex_flag_eat);
	pthread_mutex_destroy(&data->mutex_full);
	pthread_mutex_destroy(&data->mutex_is_dead);
	pthread_mutex_destroy(&data->mutex_write);
	free(data->philo);
	free(data->philosophers);
	free(data->forks);
}
