/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:48:04 by junykim           #+#    #+#             */
/*   Updated: 2022/12/04 15:58:43 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* write, read, usleep */
# include <unistd.h>

/* malloc, free */
# include <stdlib.h>

/* waitpid, wait */
# include <sys/wait.h>

/* memset */
# include <string.h>

/* printf */
# include <stdio.h>

/* pthread~ */
# include <pthread.h>

/* gettimeofday */
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define SUCCESS 0
# define FAIL 1
# define NONE -1

typedef struct s_philo_manager t_philo_manager;

typedef struct s_philo_profile
{
	int				idx;
	struct timeval	r_eat;
	struct timeval	r_sleep;
	struct timeval	r_think;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_cnt;
	int				must_eat_num;
	__uint64_t		time_init_val;
	struct timeval	*time_adr;
	pthread_mutex_t	*m_time_adr;
	int				*must_eat_flag;
	pthread_mutex_t	*m_must_eat_flag;
	int				*t_flag_adr;
	pthread_mutex_t	*m_t_flag_adr;
	int				*fork_stat[2];
	pthread_mutex_t	*m_fork_stat;
	pthread_mutex_t	*m_fork_slot[2];
	pthread_t		thr;
	t_philo_manager	*manager_adr;
}	t_philo_profile;

struct s_philo_manager
{
	int				philo_num;
	t_philo_profile	*profile;
	struct timeval	time;
	pthread_mutex_t	m_time;
	int				t_flag;
	pthread_mutex_t	m_t_flag;
	int				*must_eat_flags;
	pthread_mutex_t	m_must_eat_flags;
	int				*fork_stat;
	pthread_mutex_t	m_fork_stat;
	pthread_mutex_t	**m_fork;
};

typedef struct s_philo
{
	int	philo_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	must_eat_num;
}		t_philo;

// ================================
//				init.c
// ================================
int		init_philo(t_philo *p, char **av);

// ================================
//			profile.c
// ================================
void	init_profile(t_philo_manager *manager, t_philo *args);
int		init_manager(t_philo_manager *manager, t_philo args);

// ================================
//			mtx.c
// ================================
int		kill_mtx(t_philo_manager *manager, t_philo p);
int		init_mtx(t_philo_manager *manager, t_philo p);

// ================================
//			thread.c
// ================================
void		*routine(void *philo_info);

// ================================
//			thread_util.c
// ================================
void	get_time(t_philo_profile *p, struct timeval *time, \
		struct timeval *dest, __uint64_t *time_stamp);
void	usleep_check(t_philo_profile *p, struct timeval *time, int targ_time);
int		unlock_fork(t_philo_profile *p);
void	*kill_single_philo(t_philo_profile *p, struct timeval *time);
int		is_fork_available(t_philo_profile *p);

// ================================
//			thread_early_death.c
// ================================
int		early_death(t_philo_profile *p, struct timeval *time);

// ================================
//			thread_util2.c
// ================================
int		is_termination(t_philo_profile *p);
int		is_flags_all_up(int *must_eat_flags, int philo_num);

// ================================
//			util.c
// ================================
void	free_mem(t_philo_manager *manager, t_philo p);
int		init_philo(t_philo *p, char **av);
void	_error_msg(char *msg);
int		ft_atoi(const char *str);
#endif
