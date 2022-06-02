/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/02 20:16:57 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	check_philo_time(t_vars *vars)
{
	if (vars->is_end <= 0)
		return ;
	if (get_time() - vars->philo.eat_time
		>= (unsigned long)vars->time_to_die)
	{
		vars->is_end = 0;
		printf("%lu %d died\n",
			get_time() - vars->start_time, vars->philo.id + 1);
	}
}

void	*process_watcher(void *v_vars)
{
	t_vars	*vars;

	vars = (t_vars*)v_vars;
	while (1)
	{
		sem_wait(vars->end_check_sem);
		if (vars->is_end <= 0)
		{
			sem_post(vars->end_check_sem);
			break ;
		}
		check_philo_time(vars);
		sem_post(vars->end_check_sem);
		usleep(5000);
	}
	return (NULL);
}

void	philo_print(t_vars *vars, char *message)
{
	sem_wait(vars->print_sem);
	sem_wait(vars->end_check_sem);
	if (vars->is_end <= 0)
	{
		sem_post(vars->end_check_sem);
		sem_post(vars->print_sem);
		return ;
	}
	printf("%lu %d %s\n",
		get_time() - vars->start_time, vars->philo.id, message);
	sem_post(vars->end_check_sem);
	sem_post(vars->print_sem);
}

int	start_processes(t_vars *vars)
{
	int	i;
	int	status;

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
			return(0);
			i++;
		}
		i++;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WEXITSTATUS(status) == 1)
		{
			printf("exitstatus = 1");
			//return (killer(vars));
		}
	}
	return (0);
}
