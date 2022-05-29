/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/29 18:04:05 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	try_eat(t_philo *philo, int eat_t)
{
	pthread_mutex_lock(philo->left_fork);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	pthread_mutex_lock(&philo->vars->eat_time_mutex);
	philo->eat_time = get_time();
	pthread_mutex_unlock(&philo->vars->eat_time_mutex);
	mysleep (eat_t);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_num--;
}

void	philo_cycle(t_philo *philo, int eat_t, int sleep_t)
{	
	while (philo->eat_num != 0)
	{
		pthread_mutex_lock(&philo->vars->end_check_mutex);
		if (philo->vars->is_end <= 0)
		{
			pthread_mutex_unlock(&philo->vars->end_check_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->vars->end_check_mutex);
		try_eat(philo, eat_t);
		if (!philo->eat_num)
		{
			pthread_mutex_lock(&philo->vars->end_check_mutex);
			philo->vars->is_end--;
			pthread_mutex_unlock(&philo->vars->end_check_mutex);
			break ;
		}
		philo_print(philo, "is sleeping");
		mysleep (sleep_t);
		philo_print(philo, "is thinking");
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
	philo_print(philo, "is thinking");
	if (philo->id % 2 == 0 && philo->vars->philo_num != 1)
		mysleep(time_to_eat - 5);
	if (philo->vars->philo_num == 1)
	{
		philo_print(philo, "has taken a fork");
		mysleep(philo->vars->time_to_die + 5);
	}
	else
		philo_cycle(philo, time_to_eat, time_to_sleep);
	return (0);
}
