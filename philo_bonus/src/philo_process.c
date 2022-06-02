/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/02 22:43:09 by fchrysta         ###   ########.fr       */
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
	mysleep (vars->time_to_eat);
	sem_post(vars->forks_sem);
	sem_post(vars->forks_sem);
	vars->eat_num--;
}

int	philo_cycle(t_vars *vars)
{	
	while (1)
	{
		if (vars->is_end <= 0)
		{
			return (1);
		}
		if (!vars->eat_num)
			return (0);
		try_eat(vars);
		philo_print(vars, "is sleeping");
		mysleep (vars->time_to_sleep);
		philo_print(vars, "is thinking");
	}
}

int	philo_process(t_vars *vars)
{
	int	ret;

	ret = 0;
	pthread_create(&(vars->philo_thread),NULL, process_watcher, &vars);
	philo_print(vars, "is thinking");
	if (vars->philo.id % 2 == 0 && vars->philo_num != 1)
		mysleep(vars->time_to_eat - 5);
	if (vars->philo_num == 1)
	{
		philo_print(vars, "has taken a fork");
		mysleep(vars->time_to_die + 200);
		ret = 1;
	}
	else
		ret = philo_cycle(vars);
	pthread_create(&(vars->philo_thread),NULL, process_watcher, &vars);
	return (ret);
}
