/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/31 21:53:43 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	check_death(t_vars *vars)
{
	if (get_time() - vars->philo.eat_time >= (unsigned long)vars->time_to_die)
	{
		sem_wait(vars->print_sem);
		printf("%lu %d is died\n",
			get_time() - vars->start_time, vars->philo.id);
		return (1);
	}
	return (0);
}

int	sleep_and_check(t_vars *vars, int delay)
{
	while (delay >= 5)
	{
		mysleep(5);
		if (check_death(vars))
			return (1);
		delay -= 5;
	}
	if (delay > 0)
	{
		mysleep(delay);
		if (check_death(vars))
			return (1);
	}
	return (0);
}

void	philo_print(t_vars *vars, char *message)
{
	sem_wait(vars->print_sem);
	printf("%lu %d %s\n",
		get_time() - vars->start_time, vars->philo.id, message);
	sem_post(vars->print_sem);
}

int	start_processes(t_vars *vars)
{
	int	i;

	i = 0;
	vars->start_time = get_time();
	vars->philo.eat_time = vars->start_time;
	while (i < vars->philo_num)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] == -1)
			return (1);
		if (vars->pid[i] == 0)
		{
			vars->philo.id = i + 1;
			philo_process(vars); 
		}
		i++;
	}
	return (0);
}
