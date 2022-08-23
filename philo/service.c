/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 11:04:32 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/23 11:58:26 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_calc_time_to_think(t_data *data)
{
	int	live;
	int	eat;
	int	sleep;

	live = data->args->time_live;
	eat = data->args->time_eat;
	sleep = data->args->time_sleep;
	if (live - eat - sleep - 10 < 10)
		return (10);
	else
		return (live - eat - sleep - 10);
}

int	ft_calc_service(t_data *data)
{
	int	eat;
	int	think;
	int	i;

	i = 1;
	eat = data->args->time_eat;
	think = data->time_think;
	while (think - (eat * i) > eat)
		i++;
	return (i);
}
