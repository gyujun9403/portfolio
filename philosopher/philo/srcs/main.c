/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:51 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 18:07:38 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	*scheduler(void *in)
{
	t_philo	*philos;
	int		start;
	int		idx_at_once;
	int		num_at_once;

	start = 0;
	philos = (t_philo *)in;
	if (philos->info[NUM_OF_PHILO] % 2 == 0)
		num_at_once = philos->info[NUM_OF_PHILO] / 2;
	else
		num_at_once = (philos->info[NUM_OF_PHILO] - 1) / 2;
	while (*(philos->is_die) == FALSE)
	{
		idx_at_once = 0;
		while (idx_at_once < num_at_once)
			pthread_mutex_unlock(philos[(start + idx_at_once++ *2)
				% philos->info[NUM_OF_PHILO]].restriction);
		idx_at_once = 0;
		while (idx_at_once < num_at_once)
			pthread_mutex_lock(philos[(start + idx_at_once++ *2)
				% philos->info[NUM_OF_PHILO]].eat);
		start = (start + 1) % philos->info[NUM_OF_PHILO];
		usleep(50);
	}
	return (NULL);
}

void	*scheduler_zero(void *in)
{
	t_philo	*philos;

	philos = (t_philo *)in;
	if (philos->info[NUM_OF_PHILO] == 1)
	{
		pthread_mutex_unlock(philos->restriction);
		return (NULL);
	}
	return (NULL);
}

void	monitor(t_philo *philo)
{
	int	idx;
	int	cnt_full;

	idx = 0;
	cnt_full = 0;
	while (*(philo->is_die) == FALSE)
	{
		if (philo[idx].when_die <= get_time(FALSE))
			mutex_prt_die(&(philo[idx]), TRUE);
		else if (philo->info[NUM_OF_EAT] != INF
			&& philo[idx].cnt_eat >= philo->info[NUM_OF_EAT])
			++cnt_full;
		if (++idx == philo->info[NUM_OF_PHILO])
		{
			if (cnt_full == idx)
				mutex_prt_die(philo, FALSE);
			cnt_full = 0;
			idx = 0;
		}
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	int					parsed_input[5];
	t_philo				*philos;
	pthread_t			p_scheduler;

	get_time(TRUE);
	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (parse_info(parsed_input, av) == FAILURE)
			return (FAILURE);
	philos = malloc_philos(parsed_input);
	if (philos == NULL)
		return (FAILURE);
	init_philos(philos, parsed_input);
	if (parsed_input[NUM_OF_PHILO] == 1)
		pthread_create(&p_scheduler, NULL, scheduler_zero, (void *)philos);
	else
		pthread_create(&p_scheduler, NULL, scheduler, (void *)philos);
	creat_pthreads(philos);
	monitor(philos);
	destroy_mutexs(philos);
	join_pthreads(philos);
	pthread_join(p_scheduler, NULL);
	free_philos(philos);
	return (SUCCESS);
}
