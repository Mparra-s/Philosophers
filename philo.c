/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:04:27 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/19 11:56:51 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_envph	*monitor;
	t_philo	*philo;
	double	diff;
	int		i;

	monitor = (t_envph *)arg;
	while (1)
	{
		i = -1;
		while (++i < monitor->n_philo)
		{
			philo = &monitor->philo_crew[i];
			diff = time_diff(philo);
			pthread_mutex_lock(&monitor->death_mutex);
			if (check_total_meals(monitor)
				|| monitor_death(monitor, philo, diff))
			{
				pthread_mutex_unlock(&monitor->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&monitor->death_mutex);
		}
		usleep(500);
	}
	return (NULL);
}

void	*schedule(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id_philo % 2 == 0)
		usleep(philo->envp->t_eat);
	if (philo->envp->n_philo == 1)
	{
		philo_one(philo);
		return (NULL);
	}
	while (philo->envp->n_eat == -1 || philo->has_eaten < philo->envp->n_eat)
	{
		if (check_death(philo))
			break ;
		if (philo_eat(philo))
			philo->has_eaten++;
		philo_sleep(philo);
		if (check_death(philo))
			break ;
		print_thinking(philo);
	}
	if (!check_death(philo) && philo->envp->n_eat != -1
		&& philo->has_eaten >= philo->envp->n_eat)
		count_meals(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_envph	*var;

	if (argc != 5 && argc != 6)
		return (1);
	var = get_var(argv, argc);
	if (!var)
		return (1);
	if (var->n_philo < 1 || var->t_die <= 0)
	{
		free(var);
		return (1);
	}
	congregate_council(var);
	free(var);
	return (0);
}
