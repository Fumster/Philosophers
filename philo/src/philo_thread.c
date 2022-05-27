/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/27 22:03:32 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	philo_cycle(t_philo *philo, int eat_t, int sleep_t)
{
	while (philo->eat_num != 0)
	{
		pthread_mutex_lock(&philo->vars->end_check_mutex);
		if (philo->vars->is_end <= 0)
			break ;
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken a fork", get_time());
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken a fork", get_time());
		philo_print(philo, "is eating", get_time());
		pthread_mutex_lock(&philo->vars->eat_time_mutex);
		philo->eat_time = get_time();
		pthread_mutex_unlock(&philo->vars->eat_time_mutex);
		mysleep (eat_t);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->eat_num--;
		if (!philo->eat_num)
			break ;
		philo_print(philo, "is sleeping", get_time());
		mysleep (sleep_t);
		philo_print(philo, "is thinking", get_time());
	}
}

void	*philo_thread(void *v_philo)
{
	t_philo	*philo;
	int		time_to_eat;
	int		time_to_sleep;

	philo = (t_philo *)v_philo;
	time_to_eat = philo->vars->time_to_eat;
	time_to_sleep = philo->vars->time_to_sleep;
	philo_print(philo, "is thinking", get_time());
	if (philo->id % 2 == 1)
		usleep(20000);
	philo_cycle(philo, time_to_eat, time_to_sleep);
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
	pthread_mutex_lock(&philo->vars->end_check_mutex);
	philo->vars->is_end--;
	pthread_mutex_unlock(&philo->vars->end_check_mutex);
	return (0);
}
