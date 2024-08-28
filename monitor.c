#include "philo.h"

// void    *monitor_2(t_data *data, int i, unsigned int tim_last_meal)
// {
//     pthread_mutex_lock(&data->mutex_full);
//     if (data->is_full)
//     {
//         pthread_mutex_unlock(&data->mutex_full);
//         return (NULL);
//     }
//     pthread_mutex_unlock(&data->mutex_full);
//     if (tim_last_meal > data->time_to_die)
//     {
//         pthread_mutex_lock(&data->mutex_is_dead);
//         data->is_die = 1;
//         pthread_mutex_unlock(&data->mutex_is_dead);
//         printf("%ld %d died\n", get_time() - data->start, data->philo[i].id);
//         return (NULL);
//     }
//     return ((void *)1);
// }

// void    *monitor(void *args)
// {
//     t_data *data;
//     int i;
//     unsigned int tim_last_meal;
//     void    *r;

//     data = (t_data *)args;
//     while (1)
//     {
//         i = 0;
//         while (i < data->philo_nb)
//         {
//             pthread_mutex_lock(&data->last_meal_eat);
//             tim_last_meal = get_time() - data->philo[i].last_meal_time;
//             pthread_mutex_unlock(&data->last_meal_eat);
//             r = monitor_2(data, i, tim_last_meal);
//             if (r != (void *)1)
//                 return (r);
//             i++;
//             usleep(1000);
//         }
        

//     }
// }

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
	// unsigned int	time_since_last_meal = 0;

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
// void	*monitor(void *arg)
// {
// 	t_data			*data;
// 	unsigned int	time_since_last_meal = 0;;
// 	int				i;

// 	data = (t_data *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->philo_nb)
// 		{
// 			pthread_mutex_lock(&data->last_meal_eat);
// 			time_since_last_meal = get_time()
// 				- data->philo[i].last_meal_time;
// 			pthread_mutex_unlock(&data->last_meal_eat);
// 			pthread_mutex_lock(&data->mutex_full);
// 			if (data->is_full)
// 			{
// 				pthread_mutex_unlock(&data->mutex_full);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&data->mutex_full);
// 			if (time_since_last_meal > data->time_to_die)
// 			{
// 				pthread_mutex_lock(&data->mutex_is_dead);
//                 data->is_die = 1;
//                 pthread_mutex_unlock(&data->mutex_is_dead);
// 				printf("%ld %d died\n", get_time() - data->start, data->philo[i].id);
// 				return (NULL);
// 			}
// 			i++;
// 			usleep(1000);
// 		}
// 	}
// }