/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:28:58 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/02 22:43:11 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (parse_args(argc, argv, &vars))
		return (0);
	if (initiate_variables(&vars))
	{
		write(1, "error while initiate variables\n", 31);
		ft_exit(&vars);
		return (0);
	}
	start_processes(&vars);
//	{
	//	write(1, "error while start processes\n", 28);
//		ft_exit(&vars);
//		return (0);
//	}
	ft_exit(&vars);
	return (0);
}
