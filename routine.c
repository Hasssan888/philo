/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:14:18 by hbakrim           #+#    #+#             */
/*   Updated: 2024/08/29 18:14:25 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (is_died(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork\n", philo);
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork\n", philo);
	print_msg("is eating\n", philo);
	pthread_mutex_lock(&philo->data->last_meal_eat);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_eat);
	ft_usleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->mutex_flag_eat);
	philo->meals_eat++;
	pthread_mutex_unlock(&philo->data->mutex_flag_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_eat);
	if (philo->meals_eat == philo->data->meals_nb)
	{
		pthread_mutex_unlock(&philo->data->mutex_flag_eat);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_eat);
	if (is_died(philo) == 1)
		return (0);
	print_msg("is sleeping\n", philo);
	ft_usleep(philo->data, philo->data->time_to_sleep);
	if (is_died(philo))
		return (1);
	print_msg("is thinking\n", philo);
	return (1);
}

int	one_philo(t_philo *philo)
{
	if (philo->data->philo_nb == 1)
	{
		print_msg("has taken a fork\n", philo);
		ft_usleep(philo->data, philo->data->time_to_die);
		return (1);
	}
	return (0);
}

int	chab3o(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_eat);
	if (philo->meals_eat == philo->data->meals_nb)
	{
		pthread_mutex_unlock(&philo->data->mutex_flag_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_eat);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		print_msg("is thinking\n", philo);
		usleep(200);
	}
	if (one_philo(philo))
		return (NULL);
	while (1)
	{
		if (chab3o(philo))
			break;
		eating(philo);
		if (!sleeping(philo))
			break ;
		if (philo->data->philo_nb % 2 != 0)
			usleep(500);
	}
	return (NULL);
}
