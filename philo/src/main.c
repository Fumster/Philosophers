/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:28:58 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/27 17:29:06 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	main(int argc, char **argv)
{
	t_vars			vars;
	if (parse_args(argc, argv, &vars))
		return (0);
	if (initiate_variables(&vars))
	{
		write(1, "error while initiate variables\n", 31);
		ft_exit(&vars);
		return (0);
	}
	if (start_threads(&vars))
	{
		write(1, "error while start threads\n", 26);
		ft_exit(&vars);
		return (0);
	}
	thread_watcher(&vars);
	join_threads(&vars);
	ft_exit(&vars);
	return (0);
}