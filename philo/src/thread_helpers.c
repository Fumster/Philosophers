/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/27 18:57:57 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	thread_watcher(t_vars *vars)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < vars->philo_num)
		{
			pthread_mutex_lock(&vars->end_check_mutex);
			if (get_time() - vars->philo[i].eat_time
				>= (unsigned long)vars->time_to_die)
			{
				pthread_mutex_unlock(&vars->end_check_mutex);
				philo_print(&vars->philo[i], "died");
				pthread_mutex_lock(&vars->end_check_mutex);
				vars->is_end = 0;
			}
			i++;
			pthread_mutex_unlock(&vars->end_check_mutex);
		}
		i = 0;
		usleep(100);
	}
}

void	philo_print(t_philo *philo, char *message)
{
	int	end;

	pthread_mutex_lock(&philo->vars->end_check_mutex);
	end = philo->vars->is_end;
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
	if (end != 0)
	{
		pthread_mutex_lock(&philo->vars->print_mutex);
		printf("%lu %d %s\n",
			get_time() - philo->vars->start_time, philo->id, message);
		pthread_mutex_unlock(&philo->vars->print_mutex);
	}

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
	return(0);
}