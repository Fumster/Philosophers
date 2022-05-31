/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/31 21:16:58 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	check_philo_eat_num(t_vars *vars, int i)
{
	pthread_mutex_lock(&vars->end_check_mutex);
	while (i < vars->philo_num)
	{		
		if (vars->is_end <= 0)
		{
			pthread_mutex_unlock(&vars->end_check_mutex);
			break ;
		}
		if (!vars->philo[i].eat_over)
		{
			break ;
		}
		i++;
	}
	if (i == vars->philo_num)
	{
		vars->is_end = 0;
	}
	pthread_mutex_unlock(&vars->end_check_mutex);
}

void	check_philo_time(t_vars *vars, int i)
{
	while (i < vars->philo_num)
	{		
		pthread_mutex_lock(&vars->end_check_mutex);
		if (vars->is_end <= 0)
		{
			pthread_mutex_unlock(&vars->end_check_mutex);
			break ;
		}
		pthread_mutex_unlock(&vars->end_check_mutex);
		pthread_mutex_lock(&vars->eat_time_mutex);
		if (get_time() - vars->philo[i].eat_time
			>= (unsigned long)vars->time_to_die)
		{
			pthread_mutex_lock(&vars->end_check_mutex);
			vars->is_end = 0;
			pthread_mutex_unlock(&vars->end_check_mutex);
			printf("%lu %d died\n",
				get_time() - vars->start_time, i + 1);
		}
		i++;
		pthread_mutex_unlock(&vars->eat_time_mutex);
	}
}

void	thread_watcher(t_vars *vars)
{
	while (1)
	{
		pthread_mutex_lock(&vars->end_check_mutex);
		if (vars->is_end <= 0)
		{
			pthread_mutex_unlock(&vars->end_check_mutex);
			break ;
		}
		pthread_mutex_unlock(&vars->end_check_mutex);
		check_philo_time(vars, 0);
		check_philo_eat_num(vars, 0);
		pthread_mutex_unlock(&vars->end_check_mutex);
		usleep(5000);
	}
}

void	philo_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->vars->print_mutex);
	pthread_mutex_lock(&philo->vars->end_check_mutex);
	if (philo->vars->is_end <= 0)
	{
		pthread_mutex_unlock(&philo->vars->print_mutex);
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
		return ;
	}
	printf("%lu %d %s\n",
		get_time() - philo->vars->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->vars->print_mutex);
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
}

int	thread_manager(t_vars *vars, int command)
{
	int	i;

	i = 0;
	if (command == 0)
	{
		while (i < vars->philo_num)
		{
			pthread_join(vars->philo_thread[i], NULL);
			i++;
		}
	}
	if (command == 1)
	{
		vars->start_time = get_time();
		while (i < vars->philo_num)
		{
			vars->philo[i].eat_time = vars->start_time;
			if (pthread_create(&(vars->philo_thread[i]),
					NULL, philo_thread, &(vars->philo[i])))
				return (1);
			i++;
		}
	}
	return (0);
}
