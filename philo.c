/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadane <asaadane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:03:57 by asaadane          #+#    #+#             */
/*   Updated: 2024/01/02 23:23:48 by asaadane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if all philos have finished eating
static int	is_finished(t_philo *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		if (info->philo[i].eating_time < info->nbr_meals)
			break ;
		i++;
		if (i > info->n_philo - 1)
			return (1);
	}
	return (0);
}

// monitoring philos and handle their actions
int	check_philos(t_philo *info)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->sync);
		if (ft_time() - info->philo[i].last_meal > info->t_die)
			break ;
		if (info->philo_eaft_time && is_finished(info))
			return (0);
		pthread_mutex_unlock(&info->sync);
		i++;
		if (i > info->n_philo - 1)
		{
			if (info->t_die > 200)
				usleep(20);
			i = 0;
		}
	}
	manage_philos(&info->philo[i], DIE);
	return (0);
}
