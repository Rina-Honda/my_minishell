/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msawada <msawada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 23:12:42 by rhonda            #+#    #+#             */
/*   Updated: 2025/03/23 21:46:03 by msawada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_underscore(s[1]));
}

void	expand_variable_str(char **dst, char **rest, char *ptr, t_shell *shell)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (!name)
		fatal_error("ft_calloc");
	if (*ptr != '$')
		assert_error("Expected dollar sign");
	ptr++;
	if (!is_alpha_underscore(*ptr))
		assert_error("Variable must starts with alpha or underscore.");
	append_char(&name, *ptr++);
	while (is_alpha_num_underscore(*ptr))
		append_char(&name, *ptr++);
	value = ft_getenv(name, shell);
	free(name);
	if (value)
	{
		while (*value)
			append_char(dst, *value++);
	}
	*rest = ptr;
}
