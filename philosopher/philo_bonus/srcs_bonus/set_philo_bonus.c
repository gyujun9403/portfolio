/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:26:27 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 17:20:43 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

int	occupy_sem(sem_t *sem, const int time)
{
	int	idx;

	idx = 0;
	while (idx++ < time)
	{
		if (sem_wait(sem) != 0)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_philo	*set_philo(const int parsed_input[5])
{
	int		num_phlio;
	t_philo	*philo;

	num_phlio = parsed_input[NUM_OF_PHILO];
	philo = (t_philo *)ft_malloc(sizeof(t_philo));
	philo->thread = (pthread_t *)ft_malloc(sizeof(pthread_t));
	philo->pids = (int *)ft_calloc(sizeof(int), num_phlio);
	philo->full = ft_sem_open("full", num_phlio);
	philo->forks = ft_sem_open("forks", num_phlio);
	if (num_phlio == 1)
		philo->restriction = ft_sem_open("restriction", 1);
	else
		philo->restriction = ft_sem_open("restriction", num_phlio - 1);
	philo->die = ft_sem_open("die", num_phlio);
	philo->die_check = ft_sem_open("die_check", 1);
	philo->anounce = ft_sem_open("anounce", 1);
	if (occupy_sem(philo->full, num_phlio) == FAILURE
		|| occupy_sem(philo->die, num_phlio) == FAILURE)
	{
		free_philo(philo);
		return (NULL);
	}
	philo->cnt_eat = 0;
	philo->info = (int *)parsed_input;
	return (philo);
}

void	post_sem(sem_t *sem, const int time)
{
	int	idx;

	idx = 0;
	while (idx++ < time)
		if (sem_post(sem) != 0)
			break ;
}

void	free_philo(t_philo *philo)
{
	post_sem(philo->forks, philo->info[NUM_OF_PHILO]);
	sem_unlink("forks");
	sem_close(philo->forks);
	post_sem(philo->die, 1);
	sem_unlink("die");
	sem_close(philo->die);
	post_sem(philo->die_check, philo->info[NUM_OF_PHILO]);
	sem_unlink("die_check");
	sem_close(philo->die_check);
	post_sem(philo->full, philo->info[NUM_OF_PHILO]);
	sem_unlink("full");
	sem_close(philo->full);
	post_sem(philo->restriction, philo->info[NUM_OF_PHILO] - 1);
	sem_unlink("restriction");
	sem_close(philo->restriction);
	post_sem(philo->anounce, 1);
	sem_unlink("anounce");
	sem_close(philo->anounce);
	free(philo->thread);
	free(philo->pids);
	free(philo);
}
