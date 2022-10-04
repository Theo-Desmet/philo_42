/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:06:00 by tdesmet           #+#    #+#             */
/*   Updated: 2022/10/04 08:32:22 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_start(t_data *data)
{
	int			i;

	i = 0;
	data->init_time = ft_get_time();
	while (i < data->args->nb_philo)
	{
		pthread_create(&data->philo[i]->philo,
			NULL, &ft_routine, data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->args->nb_philo)
	{
		pthread_join(data->philo[i]->philo, NULL);
		i++;
	}
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
	ft_start(data);
	ft_free_data(data);
	return (0);
}
