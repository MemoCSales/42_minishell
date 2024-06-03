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
	int		check;

	check = check_new_var(env_vars, main, new_var);
	if (check != -1)
		return (check);
	new_env_vars = allocate_and_copy(env_vars);
	if (!new_env_vars)
		return (1);
	if (add_and_duplicate(env_vars, new_var, new_env_vars))
	{
		cleanup_split(new_env_vars);
		return (1);
	}
	return (0);
}

int	check_new_var(t_env *env_vars, t_main *main, char *new_var)
{
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
	return (-1);
}

char	**allocate_and_copy(t_env *env_vars)
{
	char	**new_env_vars;

	new_env_vars = allocate_new_env_vars(env_vars);
	if (!new_env_vars)
		return (NULL);
	if (!copy_env_vars(env_vars, new_env_vars))
	{
		cleanup_split(new_env_vars);
		return (NULL);
	}
	return (new_env_vars);
}

int	add_and_duplicate(t_env *env_vars, char *new_var, char **new_env_vars)
{
	char	**old_new_vars;
	int		i;
	int		len;

	i = 0;
	while (new_env_vars[i] != NULL)
		i++;
	if (add_new_var(new_var, new_env_vars, i))
	{
		cleanup_split(new_env_vars);
		return (1);
	}
	len = count_new_env_elements(new_env_vars);
	old_new_vars = env_vars->env_vars;
	env_vars->env_vars = malloc((len + 1) * sizeof(char *));
	if (!env_vars->env_vars)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", 2);
		cleanup_split(new_env_vars);
		return (1);
	}
	duplicate_new_env_to_env(env_vars, new_env_vars, len);
	cleanup_split(new_env_vars);
	free(old_new_vars);
	return (0);
}

int	count_new_env_elements(char **new_env_vars)
{
	int	i;

	i = 0;
	while (new_env_vars[i] != NULL)
		i++;
	return (i);
}
