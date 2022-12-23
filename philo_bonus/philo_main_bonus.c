/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:53:25 by junykim           #+#    #+#             */
/*   Updated: 2022/12/23 14:52:35 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static int	check_must_eat_sem(t_philo_manager *manager)
{
	int	i;

	i = manager->args.philo_num;
	sem_wait(manager->print_sem);
	while (i--)
	{
		sem_post(manager->print_sem);
		sem_wait(manager->must_eat_sem);
		sem_wait(manager->print_sem);
	}
	return (0);
}

static int	get_pcs(t_philo_manager *manager,
	t_philo_args args, t_philo_profile *profile)
{
	int		child_count;
	pid_t	pid;

	child_count = args.philo_num;
	while (child_count)
	{
		profile->idx++;
		pid = fork();
		if (pid == -1)
			return (1);
		else if (!pid)
			routine(manager, profile);
		child_count--;
		manager->pid_arr[child_count] = pid;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_args	args;
	t_philo_manager	manager;
	t_philo_profile	p;

	if ((argc != 5 && argc != 6) || prep_args(&args, argv))
	{
		printf("invalid args\n");
		return (0);
	}
	if (init_manager(&manager, args))
		return (1);
	init_profile(&p, args);
	p.manager_adr = &manager;
	if (get_pcs(&manager, args, &p))
		return (free_mem(&manager));
	if (manager.must_eat_sem)
		check_must_eat_sem(&manager);
	else
		waitpid(-1, NULL, 0);
	kill_all(manager.pid_arr, args.philo_num);
	free_mem(&manager);
	return (0);
}
