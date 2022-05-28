/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:32:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/28 21:00:03 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_atoi(const char *str)
{
	long int	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n' || \
		*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > 2147483647 || (*str && !ft_isdigit(*str)))
		return (0);
	return (num * sign);
}
