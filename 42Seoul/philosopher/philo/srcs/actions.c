/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:47:47 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 18:13:54 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	action_eat(t_philo *philo)
{
	philo->when_die = get_time(FALSE) + philo->info[TIME_TO_DIE];
	mutex_prt_eat(philo);
	philo_msleep(philo->info[TIME_TO_EAT], philo);
	if (philo->info[NUM_OF_EAT] > 0)
		++(philo->cnt_eat);
}

void	action_sleep(t_philo *philo)
{
	mutex_prt_sleep(philo);
	philo_msleep(philo->info[TIME_TO_SLEEP], philo);
}
