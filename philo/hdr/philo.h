/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:17:06 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/25 19:50:26 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	unsigned long		eat_time;
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_num;
	struct s_vars		*vars;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*print_mutex;
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
	t_philo			*philo;
	pthread_t		*philo_thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_check_mutex;
}				t_vars;

int				parse_args(int argc, char **argv, t_vars *vars);
unsigned long	get_time(void);
void			mysleep(int slp);
int				initiate_variables(t_vars *vars,
	pthread_mutex_t *dead_check_mutex, pthread_mutex_t *print_mutex);
void			exit_now(t_vars *vars);

#endif
