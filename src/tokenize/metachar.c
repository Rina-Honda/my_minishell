/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:01:38 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:02:21 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_metachar(char c)
{
	if (is_blank(c))
		return (true);
	return (c && ft_strchr("|&;()<> \t\n", c));
}

bool	is_metachar_notblank(char c)
{
	return (c && ft_strchr("|&;()<>", c));
}
