/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:33:45 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/09 21:53:49 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	ft_exit(t_vars *vars)
{
	sem_unlink("print_sem");
	sem_unlink("forks_sem");
	sem_unlink("end_check_sem");
	sem_unlink("eat_num_sem");
	sem_close(vars->print_sem);
	sem_close(vars->forks_sem);
	sem_close(vars->end_check_sem);
	sem_close(vars->eat_num_sem);
	if (vars->philo_pid)
		free(vars->philo_pid);
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

int	killer(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_num)
	{
		kill(vars->philo_pid[i], SIGKILL);
		i++;
	}
	kill(vars->eat_num_check_pid, SIGKILL);
	return (0);
}
