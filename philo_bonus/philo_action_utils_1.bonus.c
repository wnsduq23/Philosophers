/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_utils_1.bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:53:13 by junykim           #+#    #+#             */
/*   Updated: 2022/12/23 14:52:31 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*kill_single_philo(t_philo_profile *p, t_philo_manager *manager)
{
	__uint64_t		time_stamp;
	struct timeval	*time;

	time = &manager->time;
	usleep_check(manager, p->die_time);
	gettimeofday(time, NULL);
	time_stamp = time->tv_sec * 1000
		+ time->tv_usec / 1000 - manager->time_init_val;
	printf("%llu 1 died\n", time_stamp);
	exit(0);
}

void	usleep_check(t_philo_manager *manager, int targ_time)
{
	__uint64_t	time_stamp;
	__uint64_t	r_time;

	if (!targ_time)
		return ;
	get_time(manager, NULL, &r_time);
	while (1)
	{
		usleep(500);
		get_time(manager, NULL, &time_stamp);
		if (time_stamp >= (__uint64_t)(targ_time + r_time))
			break ;
	}
}

void	get_time(t_philo_manager *manager, struct timeval *dest,
		__uint64_t *time_stamp)
{
	struct timeval	*time;

	time = &manager->time;
	sem_wait(manager->time_sem);
	gettimeofday(time, NULL);
	if (dest)
		*dest = *time;
	if (time_stamp)
		*time_stamp = time->tv_sec * 1000 + time->tv_usec / 1000
			- manager->time_init_val;
	sem_post(manager->time_sem);
}

static void	check_death(t_philo_profile *p, t_philo_manager *manager)
{
	__uint64_t		time_stamp;

	get_time(manager, NULL, &time_stamp);
	if (time_stamp + manager->time_init_val > (__uint64_t)(p->die_time
		+ p->r_eat.tv_sec * 1000 + p->r_eat.tv_usec / 1000))
	{
		printf("%llu %i died\n", time_stamp, p->idx);
		exit (0);
	}
}

void	is_termination(t_philo_profile *p, t_philo_manager *manager)
{
	sem_wait(manager->termination_sem);
	sem_wait(manager->print_sem);
	check_death(p, manager);
	sem_post(manager->print_sem);
	sem_post(manager->termination_sem);
}
