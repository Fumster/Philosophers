/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:06:36 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/26 21:12:01 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

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
	if (philo->id % 2 == 1)
	{
		philo_print(philo, "is thinking");
		mysleep(10);
	}
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken a fork");
		philo_print(philo, "is eating");
		mysleep (time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->eat_num--;
		if (philo->eat_num == 0)
		{
			philo_print(philo, "is thinking");
			break;
		}
		philo_print(philo, "is sleeping");
		mysleep (time_to_sleep);
		philo_print(philo, "is thinking");
	}
	return (0);
}
