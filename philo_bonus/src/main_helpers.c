/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:33:45 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/02 20:42:06 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	ft_exit(t_vars *vars)
{
	if (sem_post(vars->print_sem) == 0)
		if (sem_unlink("print_sem") == -1)
			printf("unable to unlink print sem\n");
	if (sem_post(vars->forks_sem) == 0)
		if (sem_unlink("forks_sem") == -1)
			printf("unable to unlink forks sem\n");
	if (sem_post(vars->end_check_sem) == 0)
		if (sem_unlink("end_check_sem") == -1)
			printf("unable to unlink end_check sem\n");
	if (sem_close(vars->print_sem))
		printf("unable to close print sem\n");
	if (sem_close(vars->forks_sem))
		printf("unable to close forks sem\n");
	if (sem_close(vars->end_check_sem))
		printf("unable to close end check sem\n");
	if (vars->pid)
		free(vars->pid);
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
		kill(vars->pid[i], SIGKILL);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *s)
{	
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
	while (*str && (*str >= '0' && *str <= '9'))
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > 2147483647 || (*str && (*str < '0' || *str > '9')))
		return (0);
	return (num * sign);
}
