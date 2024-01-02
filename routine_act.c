/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_act.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadane <asaadane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:04:03 by asaadane          #+#    #+#             */
/*   Updated: 2024/01/02 23:25:40 by asaadane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// announce actions of philos
void	manage_philos(struct s_info *philo, t_moves action)
{
	if (action == DIE)
		printf(DEATH, ft_time() - philo->start, philo->id);
	else
	{
		pthread_mutex_lock(philo->sync);
		if (action == FORK_TAKEN)
			printf(TAKING_FORKS, ft_time() - philo->start, philo->id);
		else if (action == EAT)
		{
			printf(EATING, ft_time() - philo->start, philo->id);
			philo->last_meal = ft_time();
		}
		else if (action == SLEEP)
			printf(SLEEPING, ft_time() - philo->start, philo->id);
		else if (action == THINK)
			printf(THINKING, ft_time() - philo->start, philo->id);
		pthread_mutex_unlock(philo->sync);
	}
}

// pick up forks for eating
static void	pick_fork(struct s_info *philo)
{
	pthread_mutex_lock(philo->left_fork);
	manage_philos(philo, FORK_TAKEN);
	pthread_mutex_lock(philo->right_fork);
	manage_philos(philo, FORK_TAKEN);
}

// philo eat
void	eat(struct s_info *philo)
{
	pick_fork(philo);
	manage_philos(philo, EAT);
	ft_usleep(philo->t_eat);
	pthread_mutex_lock(philo->sync);
	philo->eating_time++;
	pthread_mutex_unlock(philo->sync);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// philo sleep
void	philo_sleep(struct s_info *philo)
{
	manage_philos(philo, SLEEP);
	ft_usleep(philo->t_sleep);
}

// philo philo_think
void	philo_think(struct s_info *philo)
{
	manage_philos(philo, THINK);
}
