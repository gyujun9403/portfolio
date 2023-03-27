/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:47:47 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/03 20:23:13 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

void	action_eat(t_philo *philo)
{
	philo->when_die = get_time(FALSE) + philo->info[TIME_TO_DIE];
	sem_prt_eat(philo->idx_of_philo, philo->anounce);
	philo_msleep(philo->info[TIME_TO_EAT]);
	if (philo->info[NUM_OF_EAT] != INF
		&& ++(philo->cnt_eat) == philo->info[NUM_OF_EAT])
		sem_post(philo->full);
}

void	action_sleep(t_philo *philo)
{
	sem_prt_sleep(philo->idx_of_philo, philo->anounce);
	philo_msleep(philo->info[TIME_TO_SLEEP]);
}
