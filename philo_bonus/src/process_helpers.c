/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/09 21:55:38 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	*life_watcher(void *v_vars)
{
	t_vars	*vars;

	vars = (t_vars *)v_vars;
	while (1)
	{
		sem_wait(vars->end_check_sem);
		if (get_time() - vars->eat_time
			>= (unsigned long)vars->time_to_die)
		{
			sem_wait(vars->print_sem);
			printf("%lu %d died\n",
				get_time() - vars->start_time, vars->id);
			exit (0);
		}
		sem_post(vars->end_check_sem);
		usleep(1000);
	}
	return (NULL);
}

void	philo_print(t_vars *vars, char *message)
{
	sem_wait(vars->print_sem);
	printf("%lu %d %s\n",
		get_time() - vars->start_time, vars->id, message);
	sem_post(vars->print_sem);
}

int	check_philo_eat_num(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->eat_num < 1)
		exit(1);
	while (i < vars->philo_num)
	{
		sem_wait(vars->eat_num_sem);
		i++;
	}
	exit (0);
}

int	start_philosophers(t_vars *vars)
{
	int	i;

	i = 0;
	vars->start_time = get_time();
	vars->eat_time = vars->start_time;
	while (i < vars->philo_num)
	{
		vars->philo_pid[i] = fork();
		if (vars->philo_pid[i] == -1)
			return (1);
		vars->id = i + 1;
		if (vars->philo_pid[i] == 0)
			philo_process(vars);
		i++;
	}
	return (0);
}

int	start_processes(t_vars *vars)
{
	int	status;

	vars->eat_num_check_pid = fork();
	if (vars->eat_num_check_pid == -1)
		return (8);
	if (vars->eat_num_check_pid == 0)
		check_philo_eat_num(vars);
	if (start_philosophers(vars))
		return (9);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 0)
		{
			killer(vars);
			return (0);
		}
	}
	return (0);
}
