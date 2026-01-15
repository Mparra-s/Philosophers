/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:46:51 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/15 11:35:44 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	if (check_death(philo))
		return ;
	print_sleep(philo);
	philo_check_death(philo, philo->envp->t_sleep);
}

int	philo_check_solo(t_philo *philo)
{
	long long	start;
	long long	now;

	start = timestamp_ms(philo->envp);
	pthread_mutex_lock(&philo->last_meal);
	gettimeofday(&philo->time_eat, NULL);
	pthread_mutex_unlock(&philo->last_meal);
	while (!check_death(philo))
	{
		now = timestamp_ms(philo->envp);
		if (now - start >= philo->envp->t_die)
			break ;
		usleep(500);
	}
	return (0);
}

int	philo_check_death(t_philo *philo, int ms)
{
	long long	start;
	long long	now;

	start = timestamp_ms(philo->envp);
	while (1)
	{
		if (check_death(philo))
			return (1);
		now = timestamp_ms(philo->envp);
		if (now - start >= ms)
			break ;
		usleep(500);
	}
	return (0);
}
