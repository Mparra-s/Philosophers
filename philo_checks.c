/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:59:34 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/19 11:55:27 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->envp->philo_crew[0].fork);
	print_fork(philo);
	philo_check_solo(philo);
	print_death(philo);
	pthread_mutex_unlock(&philo->envp->philo_crew[0].fork);
	return ;
}

void	check_errors(t_envph *envp, t_philo *council)
{
	envp->philo_crew = NULL;
	free (council);
	return ;
}

void	check_death_monitor(t_envph *monitor, t_philo *philo)
{
	monitor->is_death = 1;
	pthread_mutex_unlock(&monitor->death_mutex);
	if (monitor->n_philo != 1)
		print_death(philo);
	return ;
}

int	check_total_meals(t_envph *monitor)
{
	if (monitor->n_eat != -1 && monitor->total_meal == monitor->n_philo)
		return (1);
	return (0);
}

int	monitor_death(t_envph *monitor, t_philo *philo, double diff)
{
	if (!monitor->is_death && diff * 1000 > monitor->t_die)
	{
		check_death_monitor(monitor, philo);
		return (1);
	}
	return (0);
}
