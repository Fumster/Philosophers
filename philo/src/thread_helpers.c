/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:47:12 by fchrysta          #+#    #+#             */
/*   Updated: 2022/05/26 19:55:19 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/philo.h"

void	philo_print(t_philo *philo, char *message)
{
//	int		delay;
//	char	*s_id;
//	char	*s_delay;

	pthread_mutex_lock(philo->vars->print_mutex);
/*	delay = get_time() - vars->start_time;
	s_id = ft_itoa(id);
	s_delay = ft_itoa(delay);
	write (1, s_delay, 7);
	write(1, " ", 1);
	write(1, s_id, 4);
	write(1, " ", 1);
	write(1, message, 17);
	write(1, "\n", 1);
*/
	printf("%lu %d %s\n",
		get_time() - philo->vars->start_time, philo->id, message);
	pthread_mutex_unlock(philo->vars->print_mutex);

}

int	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_num)
	{
		if (pthread_join(vars->philo_thread[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	start_threads(t_vars *vars)
{
	int	i;

	i = 0;
	vars->start_time = get_time();
	while (i < vars->philo_num)
	{
		vars->philo[i].eat_time = vars->start_time;
		if (pthread_create(&(vars->philo_thread[i]),
			NULL, philo_thread, &(vars->philo[i])))
			return (1);
		i++;
		//usleep(1);
	}
	join_threads(vars);
	return(0);
}
