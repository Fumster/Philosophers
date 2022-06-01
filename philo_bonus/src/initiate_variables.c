/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:21:13 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/02 01:10:20 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	initiate_variables(t_vars *vars)
{
	int	err;

	err = 0;
	vars->pid = NULL;
	vars->philo.id = 0;
//	err = sem_unlink("print_sem");
//	err +=sem_unlink("forks_sem");
	err +=sem_unlink("end_check_sem");
	vars->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	vars->forks_sem = sem_open("forks_sem", O_CREAT, 0644, vars->philo_num);
	vars->print_sem = sem_open("end_check_sem", O_CREAT, 0644, 1);
	vars->is_end = 1;
	vars->pid = malloc(sizeof(pid_t) * vars->philo_num);
	if(vars->print_sem == SEM_FAILED || vars->forks_sem == SEM_FAILED
			|| !vars->pid)
		return (1);
	return (err);
}
