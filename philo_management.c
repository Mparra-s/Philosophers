/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   council_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:52:08 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/16 16:12:52 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*initializate_council(t_philo *council, t_envph *envp)
{
	int	i;

	i = 0;
	council = malloc(sizeof(t_philo) * envp->n_philo);
	if (!council)
		return (NULL);
	envp->philo_crew = council;
	while (i < envp->n_philo)
	{
		council[i].id_philo = i + 1;
		council[i].envp = envp;
		council[i].has_eaten = 0;
		gettimeofday(&council[i].time_eat, NULL);
		i++;
	}
	return (council);
}

int	create_council(t_philo *crew)
{
	int	i;

	i = 0;
	while (i < crew->envp->n_philo)
	{
		if (pthread_create(&crew[i].thread, NULL, schedule, &crew[i]) != 0)
		{
			perror("Error a la hora de generar el hilo");
			while (--i >= 0)
				pthread_join(crew[i].thread, NULL);
			return (0);
		}
		i++;
	}
	return (1);
}

void	dissolve_council(t_philo *council)
{
	int	i;

	i = 0;
	while (i < council->envp->n_philo)
	{
		pthread_join(council[i].thread, NULL);
		i++;
	}
	return ;
}

void	congregate_council(t_envph *envp)
{
	int		i;
	t_philo	*council;

	i = 0;
	council = NULL;
	council = initializate_council(council, envp);
	if (!council)
		return ;
	if (!create_mutex(council))
	{
		check_errors(envp, council);
		return ;
	}
	if (!create_council(council))
	{
		destroy_mutex(council);
		check_errors(envp, council);
		return ;
	}
	if (create_monitor(envp, council) != 0)
		return ;
	dissolve_council(council);
	pthread_join(envp->monitor, NULL);
	destroy_mutex(council);
	free(council);
}

int	create_monitor(t_envph *envp, t_philo *council)
{
	if (pthread_create(&envp->monitor, NULL,
			monitor_routine, (void *)envp) != 0)
	{
		perror("Error creando monitor");
		dissolve_council(council);
		destroy_mutex(council);
		check_errors(envp, council);
		return (1);
	}
	return (0);
}
