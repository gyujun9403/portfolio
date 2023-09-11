/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:47:26 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 17:04:55 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	destroy_until_unlock(pthread_mutex_t *mutex)
{
	while (1)
	{
		if (pthread_mutex_destroy(mutex) == BUSY)
		{
			pthread_mutex_unlock(mutex);
			usleep(10);
		}
		else
			break ;
	}
}

void	destroy_mutexs(t_philo *philos)
{
	int	idx;

	idx = 0;
	destroy_until_unlock(philos->anounce);
	while (idx < philos->info[NUM_OF_PHILO])
	{
		destroy_until_unlock(philos[idx].restriction);
		destroy_until_unlock(philos[idx].eat);
		destroy_until_unlock(philos[idx].mutex_forks[0]);
		++idx;
	}
}
