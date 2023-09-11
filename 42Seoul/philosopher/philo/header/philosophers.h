/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:00:22 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 18:13:09 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
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

# define BUSY			16

typedef struct s_philo
{
	int					idx_of_philo;
	int					*info;
	pthread_mutex_t		*mutex_forks[2];
	int					*forks[2];
	pthread_mutex_t		*anounce;
	pthread_mutex_t		*restriction;
	pthread_mutex_t		*eat;
	pthread_t			thread;
	unsigned long long	start_time;
	unsigned long long	when_die;
	int					*is_die;
	int					cnt_eat;
}	t_philo;

void				action_eat(t_philo *philo);
void				action_sleep(t_philo *philo);
int					hdl_not_legal_num(const char *str);
int					hdl_out_of_int(const char *str);
int					hdl_syscall(const char *msg);
int					hdl_too_few_philo(void);
int					parse_info(int parsed_input[5], char **av);
void				mutex_prt_eat(t_philo *philos);
void				mutex_prt_sleep(t_philo *philos);
void				mutex_prt_think(t_philo *philos);
void				mutex_prt_fork(t_philo *philos);
void				mutex_prt_die(t_philo *philos, int is_prt);
void				destroy_mutexs(t_philo *philos);
int					creat_pthreads(t_philo *philos);
void				join_pthreads(t_philo *philos);
t_philo				*malloc_philos(const int parsed_input[5]);
void				init_philos(t_philo *philos, const int *parsed_input);
int					philo_atoi(const char *str);
size_t				philo_strlen(const char *str);
pthread_mutex_t		*malloc_mutex(size_t size);
void				free_philos(t_philo *philos);
void				philo_msleep(const int msec, t_philo *philo);
unsigned long long	get_time(const int get_start_time);
unsigned long long	get_elapsed_time(void);

#endif