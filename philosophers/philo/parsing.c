/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutumur <aoutumur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:00:43 by aoutumur          #+#    #+#             */
/*   Updated: 2025/05/08 10:45:32 by aoutumur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* contains_only_digits:
*	Checks if a string contains only digits 0 - 9.
*	Returns true if the string only contains digits.
*	Returns false if the string contains a character that is not a digit.
*/
int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/* integer_atoi:
*	Converts a digit-only string into a positive integer.
*	Returns the converted number between 0 and INT MAX.
*	Returns -1 if the converted number exceeds INT MAX.
*/
int	ft_atoi(char *str)
{
	unsigned long long int	number;
	int						i;

	i = 0;
	number = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
	return ((int)number);
}

/* is_valid_input:
*	Checks if all required arguments are valid
*	digits only, which does not exceed INT MAX.
*	Also checks if number of philosophers is valid (between 1 & MAX_PHILOS).
*	Returns true if all arguments are valid, false if one of them is invalid.
*/
int	is_valid_input(int argc, char **argv)
{
	int	i;
	int	number;

	i = 1;
	while (i < argc)
	{
		if (!is_only_digits(argv[i]))
			return (printf(ERR_NOT_DIGIT, i), 0);
		number = ft_atoi(argv[i]);
		if (number == -1)
			return (printf(ERR_INVALID_INT), 0);
		if (argc == 6 && ft_atoi(argv[5]) <= 0)
		{
			printf("Error: num_of_times_philosopher_must_eat must be > 0\n");
			return (0);
		}
		if (i == 1 && (number < 1 || number > MAX_PHILOS))
			return (printf(ERR_PHILO_MAX, MAX_PHILOS), 0);
		i++;
	}
	return (1);
}
