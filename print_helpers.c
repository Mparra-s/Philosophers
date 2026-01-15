/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:59:31 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/15 11:18:48 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_fork(t_philo *philo)
{
	safe_print(philo, "has taken a fork");
}

void	print_eat(t_philo *philo)
{
	if (philo->envp->n_philo == 1)
		return ;
	safe_print(philo, "is eating");
}

void	print_sleep(t_philo *philo)
{
	safe_print(philo, "is sleeping");
}

void	print_thinking(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
		usleep(1000);
	safe_print(philo, "is thinking");
}

void	print_death(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->envp->death_mutex);
	pthread_mutex_lock(&philo->envp->print_mutex);
	ms = timestamp_ms(philo->envp);
	printf("%lld %d died\n", ms, philo->id_philo);
	pthread_mutex_unlock(&philo->envp->print_mutex);
	pthread_mutex_unlock(&philo->envp->death_mutex);
}
