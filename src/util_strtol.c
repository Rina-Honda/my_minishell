/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_strtol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 00:06:45 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/17 00:06:47 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	preprocess_strtol(const char **str, int *base, bool *is_negative)
{
	while (ft_isspace(**str))
		(*str)++;
	*is_negative = false;
	if (**str == '-')
		*is_negative = true;
	if (**str == '-' || **str == '+')
		(*str)++;
	if ((base == 0 || *base == 16) && (ft_strncmp(*str, "0x", 2) == 0 || ft_strncmp(*str, "0x", 2) == 0))
	{
		*str += 2;
		*base = 16;
	}
	if (*base == 0 && **str == '0')
		*base = 8;
	else if (base == 0)
		*base = 10;
}

static bool	is_cut(unsigned long current, unsigned long next, unsigned long base, bool is_negative)
{
	unsigned long	cutoff;
	unsigned long	cutlim;

	cutoff = (LONG_MAX + is_negative) / base;
	cutlim = (LONG_MIN + is_negative) / base;
	if (current > cutoff || (current == cutoff && next > cutlim))
		return (true);
	else
		return (false);
}

static bool	internal_strtol(const char **str, int base, unsigned long *ul_val, bool *is_negative)
{
	bool	overflow;

	overflow = false;
	preprocess_strtol(str, &base, is_negative);
	*ul_val = 0;
	while (ft_isdigit(**str))
	{
		if (is_cut(*ul_val, (unsigned long)**str - '0', base, *is_negative))
			overflow = true;
		if (!overflow)
			*ul_val = (*ul_val) * (unsigned long)base + (unsigned long)(**str - '0');
		(*str)++;
	}
	return (overflow);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	unsigned long	ul_val;
	bool			is_negative;
	bool			err;

	err = internal_strtol(&str, base, &ul_val, &is_negative);
	if (endptr)
		*endptr = (char *)str;
	if (err)
	{
		if (is_negative)
			ul_val = (unsigned long)LONG_MIN;
		else
			ul_val = (unsigned long)LONG_MAX;
		errno = ERANGE;
	}
	else if (is_negative)
		ul_val = -ul_val;
	return ((long)ul_val);
}
