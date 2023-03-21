/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:43:01 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 18:16:08 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	mutex_prt_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->anounce) != SUCCESS)
		return ;
	if (*philo->is_die == FALSE)
		printf("%llu %d is eating\n",
			get_elapsed_time(), philo->idx_of_philo + 1);
	pthread_mutex_unlock(philo->anounce);
}

void	mutex_prt_fork(t_philo *philo)
{
	if (pthread_mutex_lock(philo->anounce) != SUCCESS)
		return ;
	if (*philo->is_die == FALSE)
		printf("%llu %d has taken a fork\n",
			get_elapsed_time(), philo->idx_of_philo + 1);
	pthread_mutex_unlock(philo->anounce);
}

void	mutex_prt_sleep(t_philo *philo)
{
	if (pthread_mutex_lock(philo->anounce) != SUCCESS)
		return ;
	if (*philo->is_die == FALSE)
		printf("%llu %d is sleeping\n",
			get_elapsed_time(), philo->idx_of_philo + 1);
	pthread_mutex_unlock(philo->anounce);
}

void	mutex_prt_think(t_philo *philo)
{
	if (pthread_mutex_lock(philo->anounce) != SUCCESS)
		return ;
	if (*philo->is_die == FALSE)
		printf("%llu %d is thinking\n", get_elapsed_time(),
			philo->idx_of_philo + 1);
	pthread_mutex_unlock(philo->anounce);
}

void	mutex_prt_die(t_philo *philo, int is_prt)
{
	*(philo->is_die) = TRUE;
	if (pthread_mutex_lock(philo->anounce) != SUCCESS)
		return ;
	if (is_prt == TRUE)
		printf("%llu %d die\n", get_elapsed_time(),
			philo->idx_of_philo + 1);
	pthread_mutex_unlock(philo->anounce);
}
