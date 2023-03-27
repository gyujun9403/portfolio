/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errhandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:47:59 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/04 12:58:09 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	hdl_syscall(const char *msg)
{
	write(2, msg, philo_strlen(msg));
	write(2, " system call false!\n", 20);
	return (FAILURE);
}

int	hdl_too_few_philo(void)
{
	write(2,
		  "Too few philosophers had been set\nSet philosophers more than 1.\n",
		  64);
	return (FAILURE);
}

int	hdl_not_legal_num(const char *str)
{
	write(2, str, philo_strlen(str));
	write(2,
		  " is illegal input\nUse positive integer numbers.\n",
		  48);
	return (FAILURE);
}

int	hdl_out_of_int(const char *str)
{
	write(2, str, philo_strlen(str));
	write(2,
		  " is out of INT area\nUse positive integer numbers.\n",
		  50);
	return (FAILURE);
}
