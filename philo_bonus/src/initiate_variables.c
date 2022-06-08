/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:21:13 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/08 23:02:46 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

int	initiate_each_philo_sem(t_vars *vars)
{
//	char	*philo_id_sem;
//	int	i;

//	i = 0;
//	while (i < vars->philo_num)
//	{
//		philo_id_sem = ft_itoa(i);
//		printf("create %s sem \n", philo_id_sem);
//		sem_unlink(philo_id_sem);
		printf("create %p sem \n", vars->end_check_sem);
		sem_unlink("end_check_sem");
//		vars->end_check_sem[i] = sem_open(philo_id_sem, O_CREAT, 0644, 1);
		vars->end_check_sem = sem_open("end_check_sem", O_CREAT, 0644, 1);
		printf("create %p sem \n", vars->end_check_sem);
//		if(vars->end_check_sem[i] == SEM_FAILED)
//			return (1);
//		i++;
//	}
	return (0);
}
int	initiate_variables(t_vars *vars)
{
	vars->philo_pid = NULL;
	vars->id = 0;
	sem_unlink("print_sem");
	sem_unlink("forks_sem");
	sem_unlink("eat_num_sem");
	vars->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	vars->forks_sem = sem_open("forks_sem", O_CREAT, 0644, vars->philo_num);
	vars->eat_num_sem = sem_open("eat_num_sem", O_CREAT, 0644, 0);
	vars->philo_pid = malloc(sizeof(pid_t *) * vars->philo_num);
//	vars->end_check_sem = malloc(sizeof(pid_t *) * vars->philo_num);
//	if(vars->print_sem == SEM_FAILED || vars->forks_sem == SEM_FAILED
//			|| !vars->philo_pid
//			|| !vars->end_check_sem || vars->eat_num_sem == SEM_FAILED)
//		return (1);
//	return (initiate_each_philo_sem(vars));
	initiate_each_philo_sem(vars);
	pthread_mutex_init(&vars->end_check_mutex, NULL); // delete this
	return (0);
}
