/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:06 by fchrysta          #+#    #+#             */
/*   Updated: 2022/06/02 20:32:55 by fchrysta         ###   ########.fr       */
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

typedef struct s_philo
{
	unsigned long		eat_time;
	int					id;
}				t_philo;

typedef struct s_vars
{
	unsigned long	start_time;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_num;
	int				is_end;
	t_philo			philo;
	pid_t			*pid;
	sem_t			*print_sem;
	sem_t			*forks_sem;
	sem_t			*end_check_sem;
	pthread_t		philo_thread;
}				t_vars;

int				parse_args(int argc, char **argv, t_vars *vars);
unsigned long	get_time(void);
void			mysleep(int slp);
int				initiate_variables(t_vars *vars);
void			ft_exit(t_vars *vars);
int				philo_process(t_vars *vars);
void			philo_print(t_vars *vars, char *message);
int				start_processes(t_vars *vars);
void    		*process_watcher(void *vars);
int    			killer(t_vars *vars);
int				ft_strlen(const char *s);
int				ft_atoi(const char *str);
#endif
