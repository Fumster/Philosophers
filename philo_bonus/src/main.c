/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:28:58 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/07 22:57:33 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		ret;

	if (parse_args(argc, argv, &vars))
		return (0);
	if (initiate_variables(&vars))
	{
		write(1, "error while initiate variables\n", 31);
		ft_exit(&vars);
		return (9);
	}
	ret = start_processes(&vars);
	if (ret == 10) 
	{
		sleep(3);
		ft_exit(&vars);
		return (0);
	}
	else if (ret == 9)
	{
		printf("Error while starting processes");
		ft_exit(&vars);
	}
	return (ret);
}
