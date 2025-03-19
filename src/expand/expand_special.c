/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:04:41 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 16:26:47 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_special_parameter(char *s)
{
	return (s[0] == '$' && s[1] == '?');
}

static void	append_num(char **dst, unsigned int last_status)
{
	if (last_status == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (last_status / 10 != 0)
		append_num(dst, last_status / 10);
	append_char(dst, '0' + (last_status % 10));
}

void	expand_special_parameter_str(char **dst, char **rest,
		char *ptr, t_shell *shell)
{
	if (!is_special_parameter(ptr))
		assert_error("Expand special parameter");
	ptr += 2;
	append_num(dst, shell->last_status);
	*rest = ptr;
}
