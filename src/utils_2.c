/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvet <gchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 13:18:37 by gchauvet          #+#    #+#             */
/*   Updated: 2025/09/24 15:21:22 by gchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	calculate_number(const char *nptr, int i)
{
	long int	n;

	n = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i] - '0');
		if (n > INT_MAX)
			return (0);
		i++;
	}
	return (n);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			s;
	long int	n;
	int			s2;

	i = 0;
	n = 0;
	s = 1;
	s2 = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = s * -1;
		i++;
		s2++;
	}
	if (s2 >= 2)
		return (0);
	n = calculate_number(nptr, i);
	return ((int)(n * s));
}
