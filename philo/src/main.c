/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:28:58 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/26 21:12:03 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	main(int argc, char **argv)
{
	t_vars			vars;
	pthread_mutex_t	dead_check_mutex;
	pthread_mutex_t	print_mutex;
	if (parse_args(argc, argv, &vars))
		return (0);
	if (initiate_variables(&vars, &dead_check_mutex, &print_mutex))
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
//	thread_watcher(&vars);
	write(1, "good\n", 6);
	ft_exit(&vars);
	return (0);
}
