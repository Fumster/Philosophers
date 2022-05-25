/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:28:58 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/25 19:50:29 by fchrysta         ###   ########.fr       */
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
		exit_now(&vars);
		return (0);
	}
	write(1, "good\n", 6);
	exit_now(&vars);
	return (0);
}
