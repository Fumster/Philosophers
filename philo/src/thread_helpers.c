/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/28 21:03:11 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	philo_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->vars->end_check_mutex);
	if (philo->vars->is_end <= 0)
	{
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
		return ;
	}
	printf("%lu %d %s\n",
		get_time() - philo->vars->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
}

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_num)
	{
		pthread_join(vars->philo_thread[i], NULL);
		i++;
	}
}

int	start_threads(t_vars *vars)
{
	int	i;

	i = 0;
	vars->start_time = get_time();
	while (i < vars->philo_num)
	{
		vars->philo[i].eat_time = vars->start_time;
		if (pthread_create(&(vars->philo_thread[i]),
				NULL, philo_thread, &(vars->philo[i])))
			return (1);
		i++;
	}
	return (0);
}

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
