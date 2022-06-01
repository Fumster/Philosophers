/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/31 21:53:45 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	try_eat(t_vars *vars)
{
	sem_wait(vars->forks_sem);
	philo_print(vars, "has taken a fork");
	sem_wait(vars->forks_sem);
	philo_print(vars, "has taken a fork");
	philo_print(vars, "is eating");
	vars->philo.eat_time = get_time();
	sleep_and_check (vars, vars->time_to_eat);
	sem_post(vars->forks_sem);
	sem_post(vars->forks_sem);
	philo->eat_num--;
}

int	philo_cycle(t_vars vars)
{	
	while (1)
	{
		try_eat(vars);
		if (!vars->eat_num)
			return (0);
		philo_print(philo, "is sleeping");
		sleep_and_check (vars, vars->time_to_sleep);
		philo_print(philo, "is thinking");
	}
}

void	philo_process(t_vars *vars)
{
	philo_print(philo, "is thinking");
	if (vars->philo.id % 2 == 0 && vars->philo_num != 1)
		mysleep(vars->time_to_eat - 5);
	if (vars->philo_num == 1)
	{
		philo_print(vars, "has taken a fork");
		mysleep(vars->time_to_die + 5);
	}
	else
		philo_cycle(vars);
	return (0);
}
