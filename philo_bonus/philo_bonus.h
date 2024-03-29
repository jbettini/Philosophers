/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:18:05 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/01 00:03:02 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>

# define DIE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4

typedef struct s_param
{
	int	philo_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	eat_nb;
}				t_param;

typedef struct s_philo
{
	int				number;
	int				left_fork;
	int				right_fork;
	int				eat_time;
	int				all_eat;
	int				last_meal;
	struct s_simul	*simul;
	pid_t			pid;
	pthread_t		death;
}				t_philo;

typedef struct s_simul
{
	int				life;
	long long		start;
	t_param			param;
	t_philo			*philo;
	pthread_t		stop_eat;
	sem_t			*end;
	sem_t			*fork;
	sem_t			*log;
	sem_t			*feed;
	sem_t			*meal;
}				t_simul;

int			parent(t_philo *philo);
int			ft_sem_init(char *name, sem_t *sem, int param);
void		the_dining(t_philo *philo, t_simul *simul);
void		*the_dead(void *simul);
int			start_dining(t_simul *simul);
void		take_fork(t_simul *simul, t_philo *philo);
void		eat(t_simul *simul, t_philo *philo);
void		sleep_n_think(t_simul *simul, t_philo *philo);
int			project_init(t_simul *simul, char **param);
int			init_philo(t_simul *simul);
int			init_mutex(t_simul *simul);
int			init_param(t_param *param, char **arg);
int			check_param(t_param *param);
long long	get_time(void);
void		spin_sleep(long long ms);
int			ft_atoi(const char *str);
int			eat_and_life(t_philo *philo, int len);
void		print_log(t_philo *philo, long long time_pass, int flg);
void		free_exit(t_simul *simul, t_philo *philo);
void		ft_sem_destroy(char *name, sem_t *sem);
void		one(t_simul *simul, t_philo *philo);

#endif
