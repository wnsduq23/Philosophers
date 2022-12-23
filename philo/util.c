/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junykim <junykim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:08:35 by junykim           #+#    #+#             */
/*   Updated: 2022/12/23 14:57:18 by junykim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*type is 1 : */
void	_error_msg(char *msg)
{
	write(0, msg, sizeof(msg));
}

void	free_mem(t_philo_manager *manager, t_philo args)
{
	int	i;

	i = 0;
	while (i < args.philo_num)
	{
		pthread_join(manager->profile[i].thr, NULL);
		i++;
	}
	kill_mtx(manager, args);
	i = 0;
	while (i < args.philo_num)
		free(manager->m_fork[i++]);
	free(manager->fork_stat);
	free(manager->m_fork);
	free(manager->profile);
	free(manager->must_eat_flags);
}

static int	outlier_check(unsigned int ret, int sign)
{
	if (ret > -INT_MIN && sign == -1)
		return (0);
	else if (ret > INT_MAX && sign == 1)
		return (-2);
	else
		return (ret * sign);
}

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	ret;
	size_t			i;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	ret = 0;
	while (('0' <= str[i] && str[i] <= '9'))
		ret = ret * 10 + (str[i++] - '0');
	ret = outlier_check(ret, sign);
	return (ret * sign);
}
