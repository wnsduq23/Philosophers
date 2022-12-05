/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:23:09 by junykim           #+#    #+#             */
/*   Updated: 2022/12/05 22:06:27 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork(t_philo_profile *p, struct timeval *time,
		__uint64_t *time_stamp)
{
	*p->fork_stat[0] = 0;
	*p->fork_stat[1] = 0;
	pthread_mutex_unlock(p->m_fork_stat);
	if (!is_termination(p))
	{
		pthread_mutex_lock(p->m_fork_stat);
		*p->fork_stat[0] = 1;
		*p->fork_stat[1] = 1;
		pthread_mutex_unlock(p->m_fork_stat);
		return (1);
	}
	get_time(p, time, NULL, time_stamp);
	pthread_mutex_lock(p->m_fork_slot[0]);
	printf("%llums %i has taken a fork.\n", *time_stamp, p->idx);
	pthread_mutex_lock(p->m_fork_slot[1]);
	printf("%llums %i has taken a fork.\n", *time_stamp, p->idx);
	pthread_mutex_unlock(p->m_t_flag_adr);
	return (0);
}

static int	gne_sleep(t_philo_profile *p, struct timeval *time)
{
	__uint64_t	time_stamp;
	int			think_time;

	get_time(p, time, &p->r_sleep, &time_stamp);
	if (!is_termination(p))
		return (1);
	printf("%llums %i is sleeping\n", time_stamp, p->idx);
	pthread_mutex_unlock(p->m_t_flag_adr);
	if (p->eat_time + p->sleep_time > p->die_time)
	{
		usleep_check(p, time, p->die_time - p->eat_time);
		return (1);
	}
	usleep_check(p, time, p->sleep_time);
	get_time(p, time, &p->r_think, &time_stamp);
	if (!is_termination(p))
		return (1);
	printf("%llums %i is thinking\n", time_stamp, p->idx);
	pthread_mutex_unlock(p->m_t_flag_adr);
	if (p->manager_adr->philo_num % 2)
		think_time = (p->eat_time * 2 - p->sleep_time);
	else
		think_time = 0;
	usleep_check(p, time, think_time);
	return (0);
}

static int	grab_eat_sleep(t_philo_profile *p, struct timeval *time)
{
	__uint64_t		time_stamp;

	if (!is_termination(p))
		return (unlock_fork(p));
	pthread_mutex_unlock(p->m_t_flag_adr);
	get_time(p, time, &p->r_eat, &time_stamp);
	if (!is_termination(p))
		return (unlock_fork(p));
	printf("%llums %i is eating\n", time_stamp, p->idx);
	p->eat_cnt++;
	pthread_mutex_unlock(p->m_t_flag_adr);
	if (p->eat_cnt == p->must_eat_num)
	{
		pthread_mutex_lock(p->m_must_eat_flag);
		*p->must_eat_flag = 1;
		pthread_mutex_unlock(p->m_must_eat_flag);
	}
	usleep_check(p, time, p->eat_time);
	unlock_fork(p);
	return (gne_sleep(p, time));
}

static int	routine_seg(t_philo_profile *p, struct timeval *time,
		__uint64_t *time_stamp)
{
	if (!is_fork_available(p))
	{
		if (take_fork(p, time, time_stamp))
			return (1);
		if (grab_eat_sleep(p, time))
			return (1);
	}
	else
	{
		pthread_mutex_unlock(p->m_fork_stat);
		usleep(100);
	}
	return (0);
}

void	*routine(void *philo_info)
{
	t_philo_profile	*p;
	__uint64_t		time_stamp;

	p = (t_philo_profile *)philo_info;
	if (!(p->m_fork_slot[1]))
		return (kill_single_philo(p, p->time_adr));
	get_time(p, p->time_adr, &p->r_eat, &time_stamp);
	if (!early_death(p, p->time_adr))
		return (0);
	if (p->manager_adr->philo_num % 2)// 짝수명이면 
	{
		if (p->idx == p->manager_adr->philo_num)// 이거 꼭 해야함 ? 왜?
			usleep_check(p, p->time_adr, p->eat_time * 2);
		else if (p->idx % 2) // 철학자가 짝수번째면
			usleep_check(p, p->time_adr, 1);
	}
	else if (p->idx % 2) // 홀수명이면
		usleep_check(p, p->time_adr, p->eat_time);
	while (is_termination(p))
	{
		pthread_mutex_unlock(p->m_t_flag_adr);
		if (routine_seg(p, p->time_adr, &time_stamp))
			return (0);
	}
	return (0);
}
