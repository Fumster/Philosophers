/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:21:13 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/09 21:55:55 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	initiate_variables(t_vars *vars)
{
	vars->philo_pid = NULL;
	vars->id = 0;
	sem_unlink("print_sem");
	sem_unlink("forks_sem");
	sem_unlink("eat_num_sem");
	sem_unlink("end_check_sem");
	vars->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	vars->forks_sem = sem_open("forks_sem", O_CREAT, 0644, vars->philo_num);
	vars->eat_num_sem = sem_open("eat_num_sem", O_CREAT, 0644, 0);
	vars->end_check_sem = sem_open("end_check_sem", O_CREAT, 0644, 1);
	vars->philo_pid = malloc(sizeof(pid_t *) * vars->philo_num);
	if (vars->print_sem == SEM_FAILED || vars->forks_sem == SEM_FAILED
		|| !vars->philo_pid || vars->eat_num_sem == SEM_FAILED
		|| !vars->end_check_sem)
		return (1);
	return (0);
}
