/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 04:45:36 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/17 04:46:54 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_fork(t_simul *simul, t_philo *philo)
{
    if (philo->number % 2)
    {
        pthread_mutex_lock(&(simul->fork[philo->right_fork]));
        print_log(philo, get_time(), FORK);
        pthread_mutex_lock(&(simul->fork[philo->left_fork]));
        print_log(philo, get_time(), FORK);
    }
    else
    {
        pthread_mutex_lock(&(simul->fork[philo->left_fork]));
        print_log(philo, get_time(), FORK);
        pthread_mutex_lock(&(simul->fork[philo->right_fork]));
        print_log(philo, get_time(), FORK);
    }
}

void    eat(t_simul *simul, t_philo *philo)
{
    pthread_mutex_lock(&(simul->meal));
    print_log(philo, get_time(), EAT);
    philo->eat_time++;
    philo->last_meal = get_time();
    pthread_mutex_unlock(&(simul->meal));
    spin_sleep(simul->param.time_to_eat);
    pthread_mutex_unlock(&(simul->fork[philo->left_fork]));
    pthread_mutex_unlock(&(simul->fork[philo->right_fork]));
}

void    sleep_n_think(t_simul *simul, t_philo *philo)
{
   print_log(philo, get_time(), SLEEP); 
   spin_sleep(simul->param.time_to_sleep);
   print_log(philo, get_time(), THINK);
   usleep(100);
}