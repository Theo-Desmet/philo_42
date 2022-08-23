/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdesmet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:41:47 by tdesmet           #+#    #+#             */
/*   Updated: 2022/08/23 08:29:48 by tdesmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_is_int(const char *nptr)
{
	int			i;
	long long	result;
	int			neg;

	i = 0;
	neg = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	result *= neg;
	if (result > 2147483647 || result < -2147483648)
		return (0);
	return (1);
}

int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_is_signed_int(int argc, char **argv)
{
	int			i;
	int	temp;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			return (ft_putstr("Error, negative argument\n"), 0);
		if (ft_strlen(argv[i]) > 10)
			return (ft_putstr("Error, argument not integer\n"), 0);
		if (!ft_is_int(argv[i]))
			return (ft_putstr("Error, argument not integer\n"), 0);
		if (!ft_check_digit(argv[i]))
			return (ft_putstr("Error, argument non digit character\n"), 0);
		if (argv[i][0] == 0)
			return (ft_putstr("Error, please dont use 0\n"), 0);
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	if (argc < 5)
		return (ft_putstr("Error, too few argument"), 0);
	if (argc > 6)
		return (ft_putstr("Error, too many argument"), 0);
	if (!ft_check_is_signed_int(argc, argv))
		return (0);
	return (1);
}

t_args	*ft_get_args(t_data *data, int argc, char **argv)
{
	data->args = malloc(sizeof(t_args));
        if (!data->args)
                return (NULL);
	data->args->nb_philo = ft_atoi(argv[1]);
	data->args->time_live = ft_atoi(argv[2]);
	data->args->time_eat = ft_atoi(argv[3]);
	data->args->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->args->iter = ft_atoi(argv[5]);
	else
		data->args->iter = -1;
	return (data->args);
}
