/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:47:41 by junykim           #+#    #+#             */
/*   Updated: 2022/12/05 20:26:29 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_threads(t_philo args, t_philo_profile *profile)
{
	int	i;

	i = 0;
	while (i < args.philo_num)
	{
		if (pthread_create(&(profile[i].thr), NULL,
				routine, &(profile[i])) < 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
int	main(int ac, char **av)
{
	t_philo			philo;
	t_philo_manager	manager;

	if((ac != 5 && ac != 6) || init_philo(&philo, av) == FAIL)
	{
		_error_msg("invalid input\n");
		return (1);
	}
	if (init_mtx(&manager, philo) != SUCCESS)
		return (1);
	if (init_manager(&manager, philo) != SUCCESS)
		return (1);
	gettimeofday(&manager.time, NULL);
	init_profile(&manager, &philo);
	if (get_threads(philo, manager.profile) != SUCCESS)
	{
		free_mem(&manager, philo);
		return (1);
	}
	free_mem(&manager, philo);
	return (0);
}
