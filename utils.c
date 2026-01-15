/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:23:54 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/19 10:54:40 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_limit(long num)
{
	long	temp;

	temp = num;
	if (temp < INT_MIN || temp > INT_MAX)
		return (0);
	return (1);
}

long	ft_atol(const char *nptr)
{
	long	num;
	int		i;
	int		sign;

	sign = 1;
	num = 0;
	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr [i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != '\0')
	{
		num = 10 * num + (nptr[i] - '0');
		i++;
	}
	ft_limit (sign * num);
	return (sign * num);
}

void	init_var(t_envph *var, char **argv, int argc)
{
	var->n_philo = ft_atol(argv[1]);
	if (!is_digit(argc, argv))
		return ;
	if (var->n_philo < 1 || var->n_philo > INT_MAX)
	{
		printf("Número inválido de filósofos");
		return ;
	}
	var->t_die = ft_atol(argv[2]);
	var->t_eat = ft_atol(argv[3]);
	var->t_sleep = ft_atol(argv[4]);
	if (var->t_die <= 0 || var->t_eat < 0 || var->t_sleep < 0
		|| var->t_die > INT_MAX || var->t_eat > INT_MAX
		|| var->t_sleep > INT_MAX)
	{
		printf("Argumentos inválidos");
		return ;
	}
	var->total_meal = 0;
	var->is_death = 0;
	if (argc == 5)
		var->n_eat = -1;
	else
		var->n_eat = ft_atol(argv[5]);
	gettimeofday(&var->t_start, NULL);
}

t_envph	*get_var(char **argv, int argc)
{
	t_envph	*var;

	var = malloc(sizeof(t_envph) * 1);
	if (!var)
		return (NULL);
	init_var(var, argv, argc);
	return (var);
}

int	is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] > 47 && argv[i][j] < 58))
			{
				printf("Argumento inválido");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
