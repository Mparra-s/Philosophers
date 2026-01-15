/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:40:52 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/19 10:29:01 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_philo *council)
{
	int	i;

	i = 0;
	if (!council || !council->envp)
		return (0);
	while (i < council->envp->n_philo)
	{
		pthread_mutex_destroy(&council[i].fork);
		pthread_mutex_destroy(&council[i].last_meal);
		i++;
	}
	pthread_mutex_destroy(&council->envp->death_mutex);
	pthread_mutex_destroy(&council->envp->print_mutex);
	return (1);
}

void	init_mutex(t_philo *council)
{
	int	i;

	i = 0;
	while (i < council->envp->n_philo)
	{
		if (pthread_mutex_init(&council[i].fork, NULL) != 0
			|| pthread_mutex_init(&council[i].last_meal, NULL) != 0)
		{
			printf ("Error al inicializar el mutex\n");
			while (--i >= 0)
			{
				pthread_mutex_destroy(&council[i].fork);
				pthread_mutex_destroy(&council[i].last_meal);
			}
			return ;
		}
		i++;
	}
}

int	create_mutex(t_philo *council)
{
	init_mutex(council);
	if (pthread_mutex_init(&council->envp->death_mutex, NULL) != 0)
	{
		destroy_var(council);
		return (0);
	}
	if (pthread_mutex_init(&council->envp->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&council->envp->death_mutex);
		destroy_var(council);
		return (0);
	}
	return (1);
}

void	destroy_var(t_philo *council)
{
	int	i;

	i = 0;
	printf("Error al inicializar el mutex\n");
	while (i < council->envp->n_philo)
	{
		pthread_mutex_destroy(&council[i].fork);
		pthread_mutex_destroy(&council[i].last_meal);
		i++;
	}
}
