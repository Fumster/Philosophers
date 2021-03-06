/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:06 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/09 21:57:55 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_vars
{
	int				id;
	unsigned long	eat_time;
	unsigned long	start_time;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_num;
	pid_t			*philo_pid;
	pid_t			eat_num_check_pid;
	sem_t			*print_sem;
	sem_t			*forks_sem;
	sem_t			*end_check_sem;
	sem_t			*eat_num_sem;
	pthread_t		life_check_thread;
}					t_vars;

int				parse_args(int argc, char **argv, t_vars *vars);
unsigned long	get_time(void);
void			mysleep(int slp);
int				initiate_variables(t_vars *vars);
void			ft_exit(t_vars *vars);
int				philo_process(t_vars *vars);
void			philo_print(t_vars *vars, char *message);
int				start_processes(t_vars *vars);
void			*life_watcher(void *vars);
int				killer(t_vars *vars);
int				ft_strlen(const char *s);
int				ft_atoi(const char *str);
#endif
