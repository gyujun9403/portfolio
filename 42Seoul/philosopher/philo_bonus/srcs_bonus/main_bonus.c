/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:51 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/28 00:18:08 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

void	*monitor_full(void *in)
{
	t_philo	*philo;
	int		idx;

	idx = 0;
	philo = (t_philo *)in;
	while (idx++ < philo->info[NUM_OF_PHILO])
		sem_wait(philo->full);
	sem_wait(philo->anounce);
	sem_post(philo->die);
	return (NULL);
}

void	fork_philos(t_philo *philo)
{
	int	idx;
	int	num_of_philo;

	idx = 0;
	num_of_philo = philo->info[NUM_OF_PHILO];
	while (idx < num_of_philo)
	{
		philo->idx_of_philo = idx;
		philo->pids[idx] = fork();
		if (philo->pids[idx] == 0)
			routine(philo);
		++idx;
	}
}

int	main(int ac, char **av)
{
	int		idx;
	int		parsed_input[5];
	t_philo	*philo;

	idx = 0;
	get_time(TRUE);
	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (parse_info(parsed_input, av) == FAILURE)
			return (FAILURE);
	philo = set_philo(parsed_input);
	if (philo == NULL)
		return (FAILURE);
	fork_philos(philo);
	if (parsed_input[NUM_OF_EAT] != INF)
		pthread_create(philo->thread, NULL, monitor_full, philo);
	sem_wait(philo->die);
	while (idx < parsed_input[NUM_OF_PHILO])
		kill(philo->pids[idx++], SIGINT);
	if (parsed_input[NUM_OF_EAT] != INF)
		pthread_detach(*(philo->thread));
	free_philo(philo);
	return (SUCCESS);
}
