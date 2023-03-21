/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:06 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 17:27:04 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

pthread_mutex_t	*malloc_mutex(size_t size)
{
	return ((pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size));
}

int	philo_atoi(const char *str)
{
	size_t				idx;
	unsigned long long	result;

	idx = 0;
	result = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			result = result * 10 + str[idx] - '0';
			if (result > INT_MAX)
				return (ERR_OUT_OF_INT);
		}
		else
			return (ERR_NOT_NUM);
		++idx;
	}
	return ((int)result);
}

size_t	philo_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}
