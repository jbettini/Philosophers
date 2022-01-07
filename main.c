/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:28:31 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/07 18:15:45 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int main(int ac, char **av)
{
    t_simul simul;
    t_philo *philo;

    if (ac != 5 && ac != 6)
        return(write(2, "Invalid number of argument\n", 27));
    else if (project_init(&simul, &av[1]))
        return (write(2, "Initialising error\n", 19));
    philo = simul.philo;
}