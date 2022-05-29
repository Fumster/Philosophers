/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/29 21:53:48 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	try_eat(t_philo *philo, int eat_t)
{
	sem_wait(vars->forks_sem);
	philo_print(philo, "has taken a fork");
	sem_wait(vars->forks_sem);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	philo->eat_time = get_time();
	pthread_mutex_unlock(&philo->vars->eat_time_mutex);
	mysleep (eat_t);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_num--;
}

int	philo_cycle(t_vars vars)
{	
	while (vars->eat_num != 0)
	{
		try_eat(philo, eat_t);
		if (!vars->eat_num)
			break ;
		philo_print(philo, "is sleeping");
		mysleep (vars->time_to_sleep);
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
