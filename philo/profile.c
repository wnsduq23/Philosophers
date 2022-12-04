/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:44:17 by junykim           #+#    #+#             */
/*   Updated: 2022/12/04 17:10:33 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_profile_seg_b(t_philo_profile *p, t_philo_manager *manager,
		t_philo *philo, int i)
{
	if (!i && philo->philo_num == 1)
	{
		p->fork_stat[1] = NULL;
		p->m_fork_slot[1] = NULL;
	}
	else if (i == philo->philo_num - 1)
	{
		p->fork_stat[1] = &manager->fork_stat[0];
		p->m_fork_slot[1] = manager->m_fork[0];
	}
	else
	{
		p->fork_stat[1] = &manager->fork_stat[i + 1];
		p->m_fork_slot[1] = manager->m_fork[i + 1];
	}
	p->m_time_adr = &manager->m_time;
	p->m_must_eat_flag = &manager->m_must_eat_flags;
	p->m_fork_stat = &manager->m_fork_stat;
	p->m_t_flag_adr = &manager->m_t_flag;
	p->manager_adr = manager;
}

static void	init_profile_seg_a(t_philo_profile *p, t_philo_manager *manager,
		t_philo *philo, int i)
{
	p->idx = i + 1;
	p->die_time = philo->die_time;
	p->eat_time = philo->eat_time;
	p->sleep_time = philo->sleep_time;
	p->eat_cnt = 0;
	p->must_eat_num = philo->must_eat_num;
	p->time_init_val = manager->time.tv_sec * 1000
		+ manager->time.tv_usec / 1000;
	p->time_adr = &manager->time;
	if (philo->must_eat_num != NONE)
		p->must_eat_flag = &(manager->must_eat_flags[i]);
	else
		p->must_eat_flag = NULL;
	p->t_flag_adr = &manager->t_flag;
	p->fork_stat[0] = &manager->fork_stat[i];
	p->m_fork_slot[0] = manager->m_fork[i];
}

void	init_profile(t_philo_manager *manager, t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->philo_num)
	{
		init_profile_seg_a(&manager->profile[i], manager, p, i);
		init_profile_seg_b(&manager->profile[i], manager, p, i);
		i++;
	}
}

static int	get_slots(t_philo_manager *manager, t_philo p)
{
	manager->must_eat_flags = (int *)malloc(sizeof(int) * p.philo_num);
	if (!manager->must_eat_flags)
		return (1);
	manager->profile = (t_philo_profile *)malloc(sizeof(t_philo_profile)
			* p.philo_num);
	if (!manager->profile)
	{
		free(manager->must_eat_flags);
		return (1);
	}
	manager->fork_stat = (int *)malloc(sizeof(int) * p.philo_num);
	if (!manager->fork_stat)
	{
		free(manager->profile);
		free(manager->must_eat_flags);
		return (1);
	}
	return (0);
}

int	init_manager(t_philo_manager *manager, t_philo p)
{
	int	i;

	manager->philo_num = p.philo_num;
	manager->t_flag = 0;
	if (get_slots(manager, p))
	{
		i = p.philo_num;
		while (i--)
		{
			pthread_mutex_destroy(manager->m_fork[i]);
			free(manager->m_fork[i]);
		}
		free(manager->m_fork);
		return (kill_mtx(manager, p));
	}
	i = 0;
	while (i < p.philo_num)
		manager->fork_stat[i++] = 1;
	i = 0;
	while (i < p.philo_num)
		manager->must_eat_flags[i++] = 0;
	return (0);
}
