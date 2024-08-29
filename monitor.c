#include "philo.h"

int finished_meals(t_data *data)
{
    int  i = 0;
    while(i < data->philo_nb)
    {
        if(data->meals_nb > 0)
        {
            pthread_mutex_lock(&data->mutex_flag_eat);
            if(data->meals_nb >  data->philo[i].meals_eat)
            {
                pthread_mutex_unlock(&data->mutex_flag_eat);
                return 0;
            }
            pthread_mutex_unlock(&data->mutex_flag_eat);
        }
        i++;
    }
    return 1;
}

void	*monitor(void *arg)
{
	t_data			*data;

	data = (t_data *)arg;
	while (1)
	{
        if (data->meals_nb > 0 && finished_meals(data))
        {
            pthread_mutex_lock(&data->mutex_is_dead);
            data->is_die = 1;
            pthread_mutex_unlock(&data->mutex_is_dead);
            return (NULL);
        }
        pthread_mutex_lock(&data->last_meal_eat);
        if (get_time() - data->philo->last_meal_time > data->time_to_die)
        {
            print_msg("is died\n", data->philo);
            pthread_mutex_lock(&data->mutex_is_dead);
            data->is_die = 1;
            pthread_mutex_unlock(&data->mutex_is_dead);
            pthread_mutex_unlock(&data->last_meal_eat);
            return (NULL);
        }
        pthread_mutex_unlock(&data->last_meal_eat);
	}
    return (NULL);
}