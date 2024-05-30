/* ************************************************************************** */
/*                                                                            */
/*   export.c                   ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_builtin(t_env *env_vars, t_main *main, char *new_var)
{
	char	**new_env_vars;
	int		i;
	int		len;

	if (new_var == NULL)
	{
		print_env_vars(env_vars);
		return (0);
	}
	if (main->args[1] != NULL)
		return (0);
	if (!validate_var_name(new_var))
	{
		print_invalid_identifier(new_var);
		return (1);
	}
	if (!validate_new_var(env_vars, new_var))
		return (0);
	new_env_vars = allocate_new_env_vars(env_vars);
	if (!new_env_vars)
		return (1);
	copy_env_vars(env_vars, new_env_vars);
	i = 0;
	while (new_env_vars[i] != NULL)
		i++;
	if (add_new_var(new_var, new_env_vars, i))
		return (1);
	len = 0;
	while (new_env_vars[len] != NULL)
		len++;
	env_vars->env_vars = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		env_vars->env_vars[i] = ft_strdup(new_env_vars[i]);
		if (!env_vars->env_vars[i])
		{
			ft_putstr_fd("Error: Unable to duplicate string\n", STDERR_FILENO);
			cleanup_split(new_env_vars);
			return (1);
		}
		i++;
	}
	env_vars->env_vars[len] = NULL;
	return (0);
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

int	replace_env_var(t_env *env, char *new_var, int i)
{
	free(env->env_vars[i]);
	env->env_vars[i] = ft_strdup(new_var);
	if (!env->env_vars[i])
	{
		ft_putstr_fd("Error: Unable to duplicate string\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	check_duplicate(t_env *env_vars, char *new_var)
{
	int	i;
	int	len;

	len = get_name_length(new_var);
	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		if (ft_strncmp(env_vars->env_vars[i], new_var, len) == 0
			&& env_vars->env_vars[i][len] == '=')
		{
			return (replace_env_var(env_vars, new_var, i));
		}
		i++;
	}
	return (0);
}

void	print_invalid_identifier(char *var)
{
	ft_putstr_fd("miniℍΞLL: export: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
}
