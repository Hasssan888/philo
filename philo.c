# include "philo.h"

void ft_free(t_data *data)
{
    int i;

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

int check_args(int ac, char **av)
{
    int i;
    int j;

    if (ac < 5 || ac > 6)
    {
        write(2, "error argument\n", 16);
        return (1);
    }
    i = 1;
    while (i < ac)
    {
        j = 0;
        if (av[i][j] == '+' && av[i][j])
            j++;
        while (av[i][j])
        { 
            if (!ft_isdigit(av[i][j]))
            {
                write(2, "invalid input\n", 15);
                return(1);
            }
            j++;
        }
        if(ft_atoi(av[i]) <= 0)
        {
            write(2, "invalid input\n", 15);
            return(1);
        }
        i++;
    }
    return (0);
}


int init_philo(int ac, char **av, t_data *data)
{
    (void) ac;
    data->philo_nb = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        data->meals_nb = ft_atoi(av[5]);
    else 
        data->meals_nb = -1;
    data->philo = (t_philo *) malloc(sizeof(t_philo) * data->philo_nb);
    if (!data->philo)
    {
        write(2, "error: init data\n", 18);
        return (2);
    }
    init_mutex(data);
    init_each_philo(data);
    return 0;
}

int start_simuation(t_data *data)
{
    int i;
    pthread_t monitor_t;

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
    
    return 0;
}

int main(int ac, char **av)
{
    t_data data;
    if (check_args(ac, av))
        return (1);
    if (init_philo(ac, av, &data))
        return (1);
    if (start_simuation(&data))
        return (1);
    ft_free(&data);
    return (0);
}