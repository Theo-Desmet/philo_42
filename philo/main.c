/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:06:00 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/12 09:48:38 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_start(t_data *data)
{
	int			i;

	i = 0;
	data->init_time = ft_get_time();
	while (i < data->args->nb_philo)
	{
		if (pthread_create(&data->philo[i]->philo,
				NULL, &ft_routine, data->philo[i]))
		{
			data->dead = 1;
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->args->nb_philo)
	{
		if (pthread_join(data->philo[i]->philo, NULL))
		{
			data->dead = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!ft_check_args(argc, argv))
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data = ft_memset(data, 0, sizeof(t_data));
	if (!ft_init(data, argc, argv))
		return (ft_free_data(data), 0);
	if (ft_start(data))
		usleep (5000);
	ft_free_data(data);
	return (0);
}
