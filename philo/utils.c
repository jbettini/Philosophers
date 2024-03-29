/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:56:51 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/01 00:16:41 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	res;
	int	i;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg -= 2;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * neg);
}

int	all_eat_time(t_philo *philo, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (philo[i].eat_time < philo->simul->param.eat_nb)
			return (0);
	}
	return (1);
}

int	eat_and_life(t_philo *philo, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (philo[i].life == 0)
			return (1);
	}
	if (all_eat_time(philo, philo->simul->param.philo_nb) \
		&& philo->simul->param.eat_nb != -42)
		return (2);
	return (0);
}

void	print_log(t_philo *philo, long long time_pass, int flg)
{
	long long	time;

	if (!eat_and_life(philo->simul->philo, philo->simul->param.philo_nb))
	{
		pthread_mutex_lock(&(philo->simul->log));
		time = time_pass - philo->simul->start;
		if (flg == EAT)
			printf("%lld %d is eating\n", time, philo->number + 1);
		else if (flg == SLEEP)
			printf("%lld %d is sleeping\n", time, philo->number + 1);
		else if (flg == THINK)
			printf("%lld %d is thinking\n", time, philo->number + 1);
		else if (flg == FORK)
			printf("%lld %d has taken a fork\n", time, philo->number + 1);
		pthread_mutex_unlock(&(philo->simul->log));
	}	
	else if (eat_and_life(philo->simul->philo, \
				philo->simul->param.philo_nb) == 1)
	{
		pthread_mutex_lock(&(philo->simul->log));
		time = time_pass - philo->simul->start;
		if (flg == DIE)
			printf("%lld %d died\n", time, philo->number + 1);
	}
}

void	free_exit(t_simul *simul, int mod)
{
	int	i;

	i = -1;
	while (++i < simul->param.philo_nb && mod)
		pthread_join(simul->philo[i].thread, NULL);
	i = -1;
	while (++i < simul->param.philo_nb)
		pthread_mutex_destroy(&(simul->fork[i]));
	free(simul->fork);
	free(simul->philo);
}
