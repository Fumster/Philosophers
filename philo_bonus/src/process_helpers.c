/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/29 21:53:52 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	check_death(t_philo *philo, int die_time)
{
	pthread_mutex_lock(&philo->vars->end_check_mutex);
	if (philo->vars->is_end <= 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
		return (1);
	}
	if (get_time() - philo->eat_time >= (unsigned long)die_time)
	{
		philo->vars->is_end = 0;
		printf("%lu %d is died\n",
			get_time() - philo->vars->start_time, philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
	return (0);
}

int	sleep_and_check(t_philo *philo, int die_time, int delay)
{
	while (delay > 10)
	{
		mysleep(10);
		if (check_death(philo, die_time))
			return (1);
		delay -= 10;
	}
	if (delay)
	{
		mysleep(delay);
		if (check_death(philo, die_time))
			return (1);
	}
	return (0);
}

void	philo_print(t_philo *philo, char *message)
{
	sem_wait(vars->print_sem);
	printf("%lu %d %s\n",
		get_time() - philo->vars->start_time, philo->id, message);
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
