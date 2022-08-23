/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 09:46:50 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/23 14:14:20 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	*ft_update_time(void *arg)
{
	long long	act_time;
	t_time		*time;

	time = (t_time*)arg;
	if (time->init_time > 0)
		act_time = ft_get_time() - time->init_time;
	return (0);
}
