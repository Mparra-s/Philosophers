/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 10:41:55 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/19 11:53:34 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	int	fork_l;
	int	fork_r;
	int	index;

	index = philo->id_philo - 1;
	fork_l = index;
	fork_r = (index + 1) % philo->envp->n_philo;
	if (check_death(philo))
		return (0);
	select_forks(philo, fork_l, fork_r);
	pthread_mutex_lock(&philo->last_meal);
	gettimeofday(&philo->time_eat, NULL);
	pthread_mutex_unlock(&philo->last_meal);
	if (!check_death(philo))
		print_eat(philo);
	if (philo_check_death(philo, philo->envp->t_eat))
	{
		pthread_mutex_unlock(&philo->envp->philo_crew[fork_l].fork);
		pthread_mutex_unlock(&philo->envp->philo_crew[fork_r].fork);
		return (0);
	}
	pthread_mutex_unlock(&philo->envp->philo_crew[fork_l].fork);
	pthread_mutex_unlock(&philo->envp->philo_crew[fork_r].fork);
	return (1);
}

void	select_forks(t_philo *philo, int fork_l, int fork_r)
{
	if (philo->id_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->envp->philo_crew[fork_l].fork);
		print_fork(philo);
		pthread_mutex_lock(&philo->envp->philo_crew[fork_r].fork);
		print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&philo->envp->philo_crew[fork_r].fork);
		print_fork(philo);
		pthread_mutex_lock(&philo->envp->philo_crew[fork_l].fork);
		print_fork(philo);
	}
}

void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->envp->death_mutex);
	philo->envp->total_meal++;
	pthread_mutex_unlock(&philo->envp->death_mutex);
}
