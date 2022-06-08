/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/08 21:19:58 by fchrysta         ###   ########.fr       */
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
//	sem_wait(vars->end_check_sem[vars->id - 1]);
	sem_wait(vars->end_check_sem);
	printf("use %p id %d sem at philo\n", vars->end_check_sem, vars->id);
//	pthread_mutex_lock(&vars->end_check_mutex); //delete this
	vars->eat_time = get_time();
//	pthread_mutex_unlock(&vars->end_check_mutex); // delete this
//	sem_post(vars->end_check_sem[vars->id - 1]);
	sem_post(vars->end_check_sem);
	mysleep (vars->time_to_eat);
	sem_post(vars->forks_sem);
	sem_post(vars->forks_sem);
	vars->eat_num--;
}

int	philo_cycle(t_vars *vars)
{	
	while (1)
	{
		if (!vars->eat_num)
		{
			printf("philo %d returning 0\n", vars->id);
			exit (0);
		}
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
	pthread_create(&(vars->philo_thread),NULL, process_watcher, vars);
	philo_print(vars, "is thinking");
	if (vars->id % 2 == 0 && vars->philo_num != 1)
		mysleep(vars->time_to_eat - 5);
	if (vars->philo_num == 1)
	{
		philo_print(vars, "has taken a fork");
		mysleep(vars->time_to_die + 200);
		ret = -1;
	}
	else
		ret = philo_cycle(vars);
	pthread_join(vars->philo_thread, NULL);
	return (ret);
}
