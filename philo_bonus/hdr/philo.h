/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:06 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/29 21:53:50 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

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
	sem_t			print_sem;
	sem_t			forks_sem;
}				t_vars;

int				parse_args(int argc, char **argv, t_vars *vars);
unsigned long	get_time(void);
void			mysleep(int slp);
int				initiate_variables(t_vars *vars);
void			ft_exit(t_vars *vars);
void			philo_process(t_vars *vars);
void			philo_print(t_philo *philo, char *message);
int				start_processes(t_vars *vars);
void			process_watcher(t_vars *vars);
#endif
