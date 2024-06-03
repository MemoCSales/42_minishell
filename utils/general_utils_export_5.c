/* ************************************************************************** */
/*                                                                            */
/*   general_utils_export.c     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	duplicate_new_env_to_env(t_env *env_vars, char **new_env_vars, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		env_vars->env_vars[i] = ft_strdup(new_env_vars[i]);
		if (!env_vars->env_vars[i])
		{
			ft_putstr_fd("Error: Unable to duplicate string\n", STDERR_FILENO);
			while (i-- > 0)
				free(env_vars->env_vars[i]);
			free(env_vars->env_vars);
			env_vars->env_vars = NULL;
			cleanup_split(new_env_vars);
			return ;
		}
		i++;
	}
	env_vars->env_vars[len] = NULL;
}

int	get_name_length(char *new_var)
{
	char	*name;
	int		len;

	name = ft_strchr(new_var, '=');
	if (name != NULL)
		len = name - new_var;
	else
		len = ft_strlen(new_var);
	return (len);
}
