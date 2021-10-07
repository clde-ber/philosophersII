/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:09:39 by clde-ber          #+#    #+#             */
/*   Updated: 2021/10/07 12:52:29 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_error("Error in getting time\n", philo));
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->data->start_time);
}

unsigned long	get_timestamp(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_error("Error in getting time\n", philo));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	get_start_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_error("Error in getting time\n", NULL));
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	wait_action(t_philo *philo, unsigned long time)
{
	unsigned long	time1;
	unsigned long	time2;
	unsigned long	cumul;

	cumul = 0;
	pthread_mutex_lock(&philo->data->time_cmp_mutex);
	time1 = get_timestamp(philo);
	pthread_mutex_unlock(&philo->data->time_cmp_mutex);
	pthread_mutex_lock(&philo->data->time_mutex);
	time2 = get_timestamp(philo);
	pthread_mutex_unlock(&philo->data->time_mutex);
	while (cumul < time)
	{
		pthread_mutex_lock(&philo->data->time_mutex);
		time2 = get_timestamp(philo);
		pthread_mutex_unlock(&philo->data->time_mutex);
		cumul = time2 - time1;
		usleep(1000);
	}
}
