/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:51:07 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/15 13:37:03 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	time_diff(t_philo *philo)
{
	struct timeval	now;
	struct timeval	meal;
	double			diff;

	pthread_mutex_lock(&philo->last_meal);
	meal = philo->time_eat;
	pthread_mutex_unlock(&philo->last_meal);
	gettimeofday(&now, NULL);
	diff = (now.tv_sec - meal.tv_sec) + 1e-6 * (now.tv_usec - meal.tv_usec);
	return (diff);
}

int	check_time(t_philo *philo)
{
	double	diff;

	diff = time_diff(philo);
	if (diff * 1000 > philo->envp->t_die)
		return (1);
	return (0);
}

long long	timestamp_ms(t_envph *envp)
{
	struct timeval	now;
	long long		diff;
	long long		time_1;
	long long		time_2;

	gettimeofday(&now, NULL);
	time_1 = (now.tv_sec - envp->t_start.tv_sec) * 1000LL;
	time_2 = (now.tv_usec - envp->t_start.tv_usec) / 1000LL;
	diff = time_1 + time_2;
	return (diff);
}

void	safe_print(t_philo *philo, const char *state)
{
	long long	ms;

	pthread_mutex_lock(&philo->envp->death_mutex);
	if (philo->envp->is_death)
	{
		pthread_mutex_unlock(&philo->envp->death_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->envp->print_mutex);
	ms = timestamp_ms(philo->envp);
	printf("%lld %d %s\n", ms, philo->id_philo, state);
	pthread_mutex_unlock(&philo->envp->print_mutex);
	pthread_mutex_unlock(&philo->envp->death_mutex);
}

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->envp->death_mutex);
	dead = philo->envp->is_death;
	pthread_mutex_unlock(&philo->envp->death_mutex);
	return (dead);
}
