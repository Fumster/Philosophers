/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/08 23:12:30 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	*life_watcher(void *v_vars)
{
	t_vars	*vars;

	vars = (t_vars*)v_vars;
//	sleep(1);
	while (1)
	{
		sem_wait(vars->end_check_sem);
//		sem_wait(vars->end_check_sem[vars->id - 1]);
//		printf("use %p id %d sem at check\n", vars->end_check_sem, vars->id);
//		pthread_mutex_lock(&vars->end_check_mutex); //delete this
		if (get_time() - vars->eat_time
			>= (unsigned long)vars->time_to_die)
		{
			sem_wait(vars->print_sem);
			printf("%lu %d died\n",
				get_time() - vars->start_time, vars->id);
			printf("philo %d returning 1\n", vars->id);
//			sem_post(vars->end_check_sem);
//			sem_post(vars->end_check_sem[vars->id - 1]);
//			pthread_mutex_unlock(&vars->end_check_mutex); //delete this
			exit (1);
		}
//		sem_post(vars->end_check_sem[vars->id - 1]);
		sem_post(vars->end_check_sem);
//		pthread_mutex_unlock(&vars->end_check_mutex); //delete this
		usleep(500);
	}
	return (NULL);
}

void	philo_print(t_vars *vars, char *message)
{
	sem_wait(vars->print_sem);
//		printf("use %p id %d sem at print\n", vars->print_sem, vars->id-1);
	printf("%lu %d %s\n",
		get_time() - vars->start_time, vars->id, message);
	sem_post(vars->print_sem);
}

int	check_philo_eat_num(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->eat_num == -1)
		return (0);
	while (i < vars->philo_num)
	{
		sem_wait(vars->eat_num_sem);
		i++;
	}
	return (1);
}

int	start_processes(t_vars *vars)
{
	int	i;
	int	status;

	i = 0;
	vars->start_time = get_time();
	vars->eat_time = vars->start_time;
	while (i < vars->philo_num)
	{
		vars->philo_pid[i] = fork();
		if (vars->philo_pid[i] == -1)
			return (9);
		if (vars->philo_pid[i] == 0)
		{
			vars->id = i + 1;
			return(philo_process(vars));
		}
		i++;
	}
	vars->eat_num_check_pid = fork();
	if (vars->eat_num_check_pid == 0)
		return (check_philo_eat_num(vars));
	while (waitpid(-1, &status, 0) > 0)
	{
		
		if (WEXITSTATUS(status) == 1)
		{
			printf("exitstatus = 1\n");
			killer(vars);
			return (10);
		}
		printf("exitstatus = 0\n");
	}
	return (10);
}
