/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:51:42 by junykim           #+#    #+#             */
/*   Updated: 2022/12/04 16:26:53 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

int	kill_mtx(t_philo_manager *manager, t_philo p)
{
	pthread_mutex_destroy(&manager->m_time);
	pthread_mutex_destroy(&manager->m_t_flag);
	pthread_mutex_destroy(&manager->m_fork_stat);
	if (p.must_eat_num != NONE)
		pthread_mutex_destroy(&manager->m_must_eat_flags);
	return (1);
}

static int	get_mtx(t_philo_manager *manager, t_philo p)
{
	if (pthread_mutex_init(&manager->m_time, NULL))
		return (FAIL);
	if (pthread_mutex_init(&manager->m_t_flag, NULL))
	{
		pthread_mutex_destroy(&manager->m_time);
		return (FAIL);
	}
	if (pthread_mutex_init(&manager->m_fork_stat, NULL))
	{
		pthread_mutex_destroy(&manager->m_time);
		pthread_mutex_destroy(&manager->m_t_flag);
		return (FAIL);
	}
	if (p.must_eat_num != NONE)
	{
		if (pthread_mutex_init(&manager->m_must_eat_flags, NULL))
		{
			pthread_mutex_destroy(&manager->m_time);
			pthread_mutex_destroy(&manager->m_t_flag);
			pthread_mutex_destroy(&manager->m_fork_stat);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

static int	init_fork_setting(t_philo_manager *manager, t_philo p)
{
	int	i;

	if (get_mtx(manager, p) == FAIL)
		return (FAIL);
	manager->m_fork = (pthread_mutex_t **)malloc(sizeof (pthread_mutex_t *)
			* p.philo_num);
	if (!manager->m_fork)
		return (kill_mtx(manager, p));
	i = 0;
	while (i < p.philo_num)
	{
		manager->m_fork[i] = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t));
		if (!manager->m_fork[i])
		{
			while (i--)
				free(manager->m_fork[i]);
			free(manager->m_fork);
			return (kill_mtx(manager, p));
		}
		i++;
	}
	return (SUCCESS);
}

/** static int	init_mtx_seg_b(t_philo_manager *manager, t_philo p, int i) */
/** { */
/**     manager->m_fork[i] = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t)); */
/**     if (!manager->m_fork[i]) */
/**     { */
/**         while (i--) */
/**             free(manager->m_fork[i]); */
/**         free(manager->m_fork); */
/**         return (kill_mtx(manager, p)); */
/**     } */
/**     return (SUCCESS); */
/** } */
/**  */
/** static int	init_mtx_seg_a(t_philo_manager *manager, t_philo p) */
/** { */
/**     if (get_mtx(manager, p) == FAIL) */
/**         return (FAIL); */
/**     manager->m_fork = (pthread_mutex_t **)malloc(sizeof (pthread_mutex_t *) */
/**             * p.philo_num); */
/**     if (!manager->m_fork) */
/**         return (kill_mtx(manager, p)); */
/**     return (SUCCESS); */
/** } */

int	init_mtx(t_philo_manager *manager, t_philo p)
{
	int	i;

	/** if (init_mtx_seg_a(manager, p)) */
	/**     return (FAIL); */
	init_fork_setting(manager, p);
	i = 0;
	while (i < p.philo_num)
	{
		/** if (init_mtx_seg_b(manager, p, i)) */
		/**     return (FAIL); */
		if (pthread_mutex_init(manager->m_fork[i], NULL) != SUCCESS)
		{
			while (i--)
			{
				pthread_mutex_destroy(manager->m_fork[i]);
				free(manager->m_fork[i]);
			}
			free(manager->m_fork);
			return (kill_mtx(manager, p));
		}
		i++;
	}
	return (SUCCESS);
}
