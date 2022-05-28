/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:33:45 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/28 21:00:45 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	ft_exit(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_num)
	{
		if (pthread_mutex_destroy(&vars->fork[i]))
			printf("unable to destroy fork %d mutex\n", i);
		i++;
	}
	if (pthread_mutex_destroy(&vars->print_mutex))
		printf("unable to destroy print mutex\n");
	if (pthread_mutex_destroy(&vars->end_check_mutex))
		printf("unable to destroy end check mutex\n");
	if (pthread_mutex_destroy(&vars->eat_time_mutex))
		printf("unable to destroy end time mutex\n");
	if (vars->philo)
		free(vars->philo);
	if (vars->philo_thread)
		free(vars->philo_thread);
	if (vars->fork)
		free(vars->fork);
}

int	check_values(t_vars *vars, int argc, char **argv)
{
	if (vars->philo_num < 1 || vars->time_to_die < 1 || vars->time_to_eat < 1
		|| vars->time_to_sleep < 1 || (argc == 6 && vars->eat_num < 1)
		|| ft_strlen(argv[1]) > 10 || ft_strlen(argv[2]) > 10
		|| ft_strlen(argv[3]) > 10 || ft_strlen(argv[4]) > 10
		|| (argc == 6 && ft_strlen(argv[5]) > 10))
	{
		write(1, "incorrect argument type, positive int expected\n", 47);
		return (1);
	}
	if (vars->philo_num > 250)
	{
		write (1, "maximum 250 philosophers\n", 25);
		return (1);
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_vars *vars)
{
	if (argc < 5 || argc > 6)
	{
		write(1, "incorrect arguments number\n", 27);
		return (1);
	}
	vars->philo_num = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->eat_num = -1;
	if (argc == 6)
		vars->eat_num = ft_atoi(argv[5]);
	if (check_values(vars, argc, argv))
		return (1);
	return (0);
}
