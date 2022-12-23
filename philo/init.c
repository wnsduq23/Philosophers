/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:17:19 by junykim           #+#    #+#             */
/*   Updated: 2022/12/23 14:53:45 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *p, char **av)
{
	p->philo_num = ft_atoi(av[1]);
	p->die_time = ft_atoi(av[2]);
	p->eat_time = ft_atoi(av[3]);
	p->sleep_time = ft_atoi(av[4]);
	if (av[5])
		p->must_eat_num = ft_atoi(av[5]);
	else
		p->must_eat_num = NONE;
	if (p->philo_num < 1 || p->die_time < 1 \
			|| p->eat_time < 1 || p->sleep_time < 1 \
			|| p->must_eat_num < -1)
		return (FAIL);
	return (SUCCESS);
}
