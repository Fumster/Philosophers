/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/28 21:01:44 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	try_eat(t_philo *philo, int die_t, int eat_t)
{
	philo_print(philo, "is eating");
	philo->eat_time = get_time();
	sleep_and_check(philo, die_t, eat_t);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_num--;
}

void	philo_cycle(t_philo *philo, int eat_t, int sleep_t, int die_t)
{
	int	end;

	end = 1;
	while (philo->eat_num != 0 && end > 0)
	{
		while (pthread_mutex_lock(philo->left_fork))
			if (sleep_and_check(philo, die_t, 10))
				return ;
		philo_print(philo, "has taken a fork");
		while (pthread_mutex_lock(philo->right_fork))
			if (sleep_and_check(philo, die_t, 10))
				return ;
		philo_print(philo, "has taken a fork");
		try_eat(philo, die_t, eat_t);
		if (!philo->eat_num)
			break ;
		philo_print(philo, "is sleeping");
		sleep_and_check(philo, die_t, sleep_t);
		philo_print(philo, "is thinking");
		pthread_mutex_lock(&philo->vars->end_check_mutex);
		end = philo->vars->is_end;
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
	}
}

void	*philo_thread(void *v_philo)
{
	t_philo	*philo;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_die;

	philo = (t_philo *)v_philo;
	time_to_eat = philo->vars->time_to_eat;
	time_to_sleep = philo->vars->time_to_sleep;
	time_to_die = philo->vars->time_to_die;
	printf("%lu %d is thinking\n",
		get_time() - philo->vars->start_time, philo->id);
	if (philo->id % 2 == 1 && philo->vars->philo_num != 1)
		mysleep(time_to_eat);
	if (philo->vars->philo_num == 1)
	{
		printf("%lu %d has taken a fork\n",
			get_time() - philo->vars->start_time, philo->id);
		sleep_and_check(philo, time_to_die, time_to_die + 5);
	}
	else
		philo_cycle(philo, time_to_eat, time_to_sleep, time_to_die);
	pthread_mutex_lock(&philo->vars->end_check_mutex);
	philo->vars->is_end--;
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
	return (0);
}
