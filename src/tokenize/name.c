/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:03:05 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:03:56 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_alpha_underscore(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_underscore(char c)
{
	return (is_alpha_underscore(c) || ft_isdigit(c));
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_underscore(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_underscore(*s))
			return (false);
		s++;
	}
	return (true);
}
