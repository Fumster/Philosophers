/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/09 21:56:59 by fchrysta         ###   ########.fr       */
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
	sem_wait(vars->end_check_sem);
	vars->eat_time = get_time();
	sem_post(vars->end_check_sem);
	mysleep (vars->time_to_eat);
	sem_post(vars->forks_sem);
	sem_post(vars->forks_sem);
	vars->eat_num--;
}

void	philo_cycle(t_vars *vars)
{	
	while (1)
	{
		try_eat(vars);
		if (!vars->eat_num)
			sem_post(vars->eat_num_sem);
		philo_print(vars, "is sleeping");
		mysleep (vars->time_to_sleep);
		philo_print(vars, "is thinking");
	}
}

int	philo_process(t_vars *vars)
{
	if (pthread_create(&(vars->life_check_thread), NULL, life_watcher, vars))
	{
		printf("error life_chec_thread_creating\n");
		return (10);
	}
	philo_print(vars, "is thinking");
	if (vars->id % 2 == 0 && vars->philo_num != 1)
		mysleep(vars->time_to_eat - 5);
	if (vars->philo_num == 1)
		philo_print(vars, "has taken a fork");
	else
		philo_cycle(vars);
	pthread_join(vars->life_check_thread, NULL);
	exit(0);
}
