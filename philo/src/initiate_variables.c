/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:21:13 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/29 18:04:30 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	initiate_each_philo(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_num)
	{
		vars->philo[i].eat_time = 0;
		vars->philo[i].id = i + 1;
		vars->philo[i].eat_num = vars->eat_num;
		vars->philo[i].vars = vars;
		vars->philo[i].right_fork = &(vars->fork[i]);
		vars->philo[i].left_fork = &(vars->fork[(i + 1) % vars->philo_num]);
		i++;
	}
}

int	initiate_variables(t_vars *vars)
{
	int	err;
	int	i;

	i = 0;
	vars->philo = NULL;
	vars->fork = NULL;
	vars->philo_thread = NULL;
	err = pthread_mutex_init(&vars->end_check_mutex, NULL);
	err += pthread_mutex_init(&vars->print_mutex, NULL);
	err += pthread_mutex_init(&vars->eat_time_mutex, NULL);
	vars->philo = malloc (sizeof(t_philo) * vars->philo_num);
	vars->fork = malloc (sizeof(pthread_mutex_t) * vars->philo_num);
	vars->philo_thread = malloc (sizeof(t_philo) * vars->philo_num);
	vars->is_end = vars->philo_num;
	if (!vars->philo || !vars->fork || !vars->philo_thread)
		return (1);
	while (i < vars->philo_num)
	{
		err += pthread_mutex_init(&(vars->fork[i]), NULL);
		i++;
	}
	initiate_each_philo(vars);
	return (err);
}
