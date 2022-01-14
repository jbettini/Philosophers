/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:28:31 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/14 03:32:18 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free_exit(t_simul *simul, int mod)
{
    int i;

    i = -1;
    while (++i < simul->param.philo_nb && mod)
        pthread_join(simul->philo[i].thread, NULL);
    i = -1;
    while (++i < simul->param.philo_nb)
        pthread_mutex_destroy(&(simul->fork[i]));
    free(simul->fork);
    free(simul->philo);
}

void    *the_dining(void *philo_tmp)
{
    t_philo *philo;

    philo = (t_philo *)philo_tmp;
    while (all_is_alive(philo->simul->philo, philo->simul->param.philo_nb))
    {
        printf("%lld\n", philo->simul->start);
    }
    return (NULL);
}

int start_dining(t_simul *simul)
{
    int i;

    i = -1;
    simul->start = get_time();
    while (++i < simul->param.philo_nb)
    {
        if (pthread_create(&(simul->philo[i].thread), NULL, &the_dining, &(simul->philo[i])))
            return (1);
    }
    return (0);
}

int main(int ac, char **av)
{
    t_simul simul;
    int     ret;

    if (ac != 5 && ac != 6)
        return(write(2, "Invalid number of argument\n", 27));
    else 
    {
        ret = project_init(&simul, &av[1]);
        if (ret)
        {
            if (ret == 3)
                free(simul.fork);
            return (write(2, "Initialising error\n", 19));
        }
        if (start_dining(&simul))
        {
            free_exit(&simul, 0);
            return (write(2, "Thread create error\n", 21));
        }
        else
            free_exit(&simul, 1);
    }
    system("leaks philo");
    return (0);
}