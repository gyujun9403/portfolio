/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_print_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:24:40 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/03 20:14:45 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

void	sem_prt_eat(const int num, sem_t *sem_prt)
{
	sem_wait(sem_prt);
	printf("%llu %d is eating\n", get_elapsed_time(), num + 1);
	sem_post(sem_prt);
}

void	sem_prt_fork(const int num, sem_t *sem_prt)
{
	sem_wait(sem_prt);
	printf("%llu %d has taken a fork\n", get_elapsed_time(), num + 1);
	sem_post(sem_prt);
}

void	sem_prt_sleep(const int num, sem_t *sem_prt)
{
	sem_wait(sem_prt);
	printf("%llu %d is sleeping\n", get_elapsed_time(), num + 1);
	sem_post(sem_prt);
}

void	sem_prt_think(const int num, sem_t *sem_prt)
{
	sem_wait(sem_prt);
	printf("%llu %d is thinking\n", get_elapsed_time(), num + 1);
	sem_post(sem_prt);
}

void	sem_prt_die(const int num, sem_t *sem_prt)
{
	sem_wait(sem_prt);
	printf("%llu %d die\n", get_elapsed_time(), num + 1);
}
