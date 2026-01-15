/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparra-s <mparra-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:07:47 by mparra-s          #+#    #+#             */
/*   Updated: 2025/09/19 11:32:39 by mparra-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_envph
{
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor;
	struct s_philo	*philo_crew;
	struct timeval	t_start;
	int				is_death;
	int				n_philo;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				n_eat;
	int				total_meal;
}	t_envph;

typedef struct s_philo
{
	struct s_envph	*envp;
	struct timeval	time_eat;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
	int				id_philo;
	int				has_eaten;
}	t_philo;

long long	timestamp_ms(t_envph *envp);
t_philo		*initializate_council(t_philo *council, t_envph *envp);
t_envph		*get_var(char **argv, int argc);
long		ft_atol(const char *nptr);
int			ft_limit(long num);
int			destroy_mutex(t_philo *council);
int			create_mutex(t_philo *council);
int			check_death(t_philo *philo);
int			check_time(t_philo *philo);
int			create_council(t_philo *council);
int			philo_check_death(t_philo *philo, int ms);
int			philo_eat(t_philo *philo);
int			philo_check_solo(t_philo *philo);
int			is_digit(int argc, char **argv);
int			create_monitor(t_envph *envp, t_philo *council);
int			check_total_meals(t_envph *monitor);
int			monitor_death(t_envph *monitor, t_philo *philo, double diff);
void		check_errors(t_envph *envp, t_philo *council);
void		check_death_monitor(t_envph *monitor, t_philo *philo);
void		philo_one(t_philo *philo);
void		*monitor_routine(void *arg);
void		init_var(t_envph *var, char **argv, int argc);
void		init_mutex(t_philo *council);
void		dissolve_council(t_philo *council);
void		congregate_council(t_envph *envp);
void		*schedule(void *arg);
void		philo_sleep(t_philo *philo);
void		destroy_var(t_philo *council);
void		select_forks(t_philo *philo, int fork_l, int fork_r);
void		print_fork(t_philo *philo);
void		print_eat(t_philo *philo);
void		count_meals(t_philo	*philo);
void		print_sleep(t_philo *philo);
void		print_thinking(t_philo *philo);
void		print_death(t_philo *philo);
void		safe_print(t_philo *philo, const char *state);
double		time_diff(t_philo *philo);

#endif
