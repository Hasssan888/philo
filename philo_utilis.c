#include "philo.h"

int ft_strlen(char *str)
{
	int i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(int d)
{
	return (d >= '0' && d <= '9');
}

// long	ft_atoi(char *str)
// {
// 	long (i), (sig), (res);
// 	res = 0;
// 	i = 0;
// 	sig = 1;
// 	while (str[i] == 32 && str[i])
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i++] == '-')
// 			sig = -1;
// 		if (str[i] == '-' || str[i] == '+')
// 			return (0);
// 	}
// 	while (str[i] == '0')
// 		i++;
// 	if ((ft_strlen(&str[i]) > 11))
// 		return (0);
// 	while (str[i] >= '0' && str[i] <= '9' && str[i])
// 		res = res * 10 + str[i++] - '0';
// 	if (res * sig < 0)
// 		return (0);
// 	if (str[i] || str[i - 1] == '-' || str[i - 1] == '+')
// 		return (0);
// 	return (sig * res);
// }

long	ft_atoi(const char *str)
{
	long	r;
	int					i;
	int					s;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r * s);
}

long get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int	ft_usleep(t_data *data, long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
    {
        pthread_mutex_lock(&data->mutex_is_dead);
        if (data->is_die)
        {
            pthread_mutex_unlock(&data->mutex_is_dead);
            break;
        }
        pthread_mutex_unlock(&data->mutex_is_dead);
		usleep(500);
    }
	return (0);
}