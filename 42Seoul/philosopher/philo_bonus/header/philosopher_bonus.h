/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:37:50 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/24 17:39:34 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>

# define FALSE			0
# define TRUE			1
# define SUCCESS		0
# define FAILURE		1
# define ERR_NOT_NUM	-1
# define ERR_OUT_OF_INT	-2
# define INF			-10
# define NUM_OF_PHILO	0 
# define TIME_TO_DIE	1
# define TIME_TO_EAT	2
# define TIME_TO_SLEEP	3
# define NUM_OF_EAT		4
# define INT_MAX 2147483647

typedef struct s_philo
{
	pid_t				*pids;
	int					idx_of_philo;
	int					*info;
	sem_t				*forks;
	sem_t				*restriction;
	sem_t				*full;
	sem_t				*die;
	sem_t				*die_check;
	sem_t				*anounce;
	pthread_t			*thread;
	unsigned long long	when_die;
	int					cnt_eat;
}	t_philo;

void				action_eat(t_philo *philo);
void				action_sleep(t_philo *philo);
int					hdl_not_legal_num(const char *str);
int					hdl_out_of_int(const char *str);
int					hdl_syscall(const char *msg);
int					hdl_too_few_philo(void);
int					parse_info(int parsed_input[5], char **av);
void				routine(t_philo *philo);
void				sem_prt_eat(const int num, sem_t *sem_prt);
void				sem_prt_fork(const int num, sem_t *sem_prt);
void				sem_prt_think(const int num, sem_t *sem_prt);
void				sem_prt_sleep(const int num, sem_t *sem_prt);
void				sem_prt_die(const int num, sem_t *sem_prt);
t_philo				*set_philo(const int parsed_input[5]);
void				free_philo(t_philo *philo);
void				*ft_malloc(const size_t size);
sem_t				*ft_sem_open(const char *name, const unsigned int value);
void				*ft_calloc(const size_t count, const size_t size);
int					philo_atoi(char *str);
size_t				philo_strlen(const char *str);
void				philo_msleep(const int msec);
unsigned long long	get_time(const int start_time);
unsigned long long	get_elapsed_time(void);

#endif