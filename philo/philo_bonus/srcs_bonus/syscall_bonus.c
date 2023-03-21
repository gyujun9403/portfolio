/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:48:16 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/28 00:18:18 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"
#include <string.h>

void	*ft_malloc(const size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
	{
		hdl_syscall("malloc");
		exit(1);
	}
	return (result);
}

void	*ft_calloc(const size_t count, const size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result == NULL)
	{
		hdl_syscall("malloc");
		exit(1);
	}
	memset(result, 0, count * size);
	return (result);
}

sem_t	*ft_sem_open(const char *name, const unsigned int value)
{
	sem_t	*result;

	result = NULL;
	sem_unlink(name);
	result = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (result == SEM_FAILED)
	{
		hdl_syscall("sem_open");
		exit(1);
	}
	return (result);
}
