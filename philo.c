/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbakrim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:46:04 by hbakrim           #+#    #+#             */
/*   Updated: 2024/08/29 18:46:06 by hbakrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][j] == '+' && av[i][j])
			j++;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				write(2, "invalid input\n", 15);
				return (1);
			}
			j++;
		}
		if (ft_atoi(av[i]) < 0)
		{
			write(2, "invalid input\n", 15);
			return (1);
		}
	}
	return (0);
}

int	init_philo(char **av, t_data *data)
{
	data->philo_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_nb = ft_atoi(av[5]);
	else
		data->meals_nb = -1;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philo)
	{
		write(2, "error: init philo\n", 19);
		return (2);
	}
	init_mutex(data);
	init_each_philo(data);
	return (0);
}

int	start_simuation(t_data *data)
{
	int			i;
	pthread_t	monitor_t;

	i = -1;
	data->start = get_time();
	while (++i < data->philo_nb)
		pthread_create(&data->philosophers[i], NULL, routine, &data->philo[i]);
	pthread_create(&monitor_t, NULL, monitor, data);
	i = 0;
	pthread_join(monitor_t, NULL);
	while (i < data->philo_nb)
	{
		pthread_join(data->philosophers[i], NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		write(2, "error argument\n", 16);
		return (1);
	}
	if (check_input(ac, av))
		return (1);
	if (init_philo(av, &data))
		return (1);
	if (data.philo_nb == 0 || data.meals_nb == 0)
		return (0);
	if (start_simuation(&data))
		return (1);
	ft_free(&data);
	return (0);
}
