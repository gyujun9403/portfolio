/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:23:55 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 18:07:14 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

t_philo	*check_malloc(t_philo *result, const int parsed_input[5])
{
	int	idx;

	if (result != NULL)
	{
		idx = 0;
		while (idx < parsed_input[NUM_OF_PHILO])
		{
			if (result->anounce == NULL || result[idx].eat == NULL
				|| result[idx].mutex_forks[0] == NULL || result->is_die == NULL
				|| result[idx].restriction == NULL)
			{
				hdl_syscall("malloc");
				free_philos(result);
				return (NULL);
			}
			++idx;
		}
		return (result);
	}
	return (NULL);
}

void	malloc_forks(t_philo *philo, t_philo *copy)
{
	if (copy == NULL)
	{
		philo->mutex_forks[0] = malloc_mutex(1);
		philo->forks[0] = (int *)malloc(sizeof(int));
	}
	else
	{
		philo->mutex_forks[1] = copy->mutex_forks[0];
		philo->forks[1] = copy->forks[0];
	}
}

t_philo	*malloc_philos(const int parsed_input[5])
{
	int		idx;
	t_philo	*result;

	result = (t_philo *)malloc(sizeof(t_philo) * parsed_input[NUM_OF_PHILO]);
	if (result == NULL)
		return (NULL);
	result->info = (int *)parsed_input;
	result->anounce = malloc_mutex(1);
	result->is_die = (int *)malloc(sizeof(int));
	result->eat = malloc_mutex(1);
	result->restriction = malloc_mutex(1);
	malloc_forks(result, NULL);
	malloc_forks(result, result);
	idx = 0;
	while (++idx < parsed_input[NUM_OF_PHILO])
	{
		result[idx].eat = malloc_mutex(1);
		result[idx].restriction = malloc_mutex(1);
		malloc_forks(&result[idx], NULL);
		malloc_forks(&result[idx - 1], &result[idx]);
		if (idx + 1 == parsed_input[NUM_OF_PHILO])
			malloc_forks(&result[idx], &result[0]);
	}
	return (check_malloc(result, parsed_input));
}

void	init_philos(t_philo *philos, const int *parsed_input)
{
	int		idx;

	idx = 0;
	pthread_mutex_init(philos->anounce, NULL);
	*(philos->is_die) = FALSE;
	while (idx < parsed_input[NUM_OF_PHILO])
	{
		philos[idx].idx_of_philo = idx;
		pthread_mutex_init(philos[idx].mutex_forks[0], NULL);
		pthread_mutex_init(philos[idx].restriction, NULL);
		pthread_mutex_init(philos[idx].eat, NULL);
		pthread_mutex_lock(philos[idx].restriction);
		pthread_mutex_lock(philos[idx].eat);
		philos[idx].info = (int *)parsed_input;
		philos[idx].start_time = get_time(TRUE);
		philos[idx].when_die = get_time(TRUE) + philos[idx].info[TIME_TO_DIE];
		philos[idx].is_die = philos->is_die;
		philos[idx].anounce = philos->anounce;
		philos[idx].cnt_eat = 0;
		++idx;
	}
}

void	free_philos(t_philo *philos)
{
	int	idx;

	idx = 0;
	if (philos->anounce != NULL)
		free(philos->anounce);
	if (philos->is_die != NULL)
		free(philos->is_die);
	while (idx < philos->info[NUM_OF_PHILO])
	{
		if (philos[idx].mutex_forks[0] != NULL)
			free(philos[idx].mutex_forks[0]);
		if (philos[idx].restriction != NULL)
			free(philos[idx].restriction);
		if (philos[idx].eat != NULL)
			free(philos[idx].eat);
		if (philos[idx].forks[0] != NULL)
			free(philos[idx].forks[0]);
		idx++;
	}
	free(philos);
}
