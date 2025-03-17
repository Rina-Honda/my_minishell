/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhonda <rhonda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 00:05:13 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/18 00:42:16 by rhonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = {">>", "<<", "||", "&&",
		";;", ">", "<", "&", ";", "(", ")", "|", "\n"};
	size_t				i;
	char				*operator;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (starts_with(line, operators[i]))
		{
			operator = ft_strdup(operators[i]);
			if (!operator)
				fatal_error("ft_strdup");
			*rest = line + ft_strlen(operator);
			return (new_token(operator, TK_OP));
		}
		i++;
	}
	assert_error("Unexpected operator");
}
