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

void	print_env_vars(t_env *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		printf("declare -x %s\n", env_vars->env_vars[i]);
		i++;
	}
}

int	validate_new_var(t_env *env_vars, char *new_var)
{
	char	**name;

	if (ft_strncmp(new_var, "=", 1) == 0)
	{
		ft_putstr_fd("miniℍΞLL: export: '=': not a valid identifier\n", 2);
		return (0);
	}
	name = ft_split(new_var, '=');
	if ((name[0] == NULL
			&& !is_valid_var_name(name[0])) || !is_valid_var_name(name[0])
		|| check_duplicate(env_vars, new_var))
	{
		cleanup_split(name);
		return (0);
	}
	cleanup_split(name);
	return (1);
}

char	**allocate_new_env_vars(t_env *env_vars)
{
	int		i;
	char	**new_env_vars;

	i = 0;
	while (env_vars->env_vars[i] != NULL)
		i++;
	new_env_vars = malloc((i + 2) * sizeof(char *));
	if (!new_env_vars)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", 2);
		exit(EXIT_FAILURE);
	}
	return (new_env_vars);
}

void	copy_env_vars(t_env *env_vars, char **new_env_vars)
{
	int	j;

	j = 0;
	while (env_vars->env_vars[j] != NULL)
	{
		new_env_vars[j] = env_vars->env_vars[j];
		j++;
	}
}

int	add_new_var(char *new_var, char **new_env_vars, int i)
{
	char	*temp;

	new_env_vars[i] = ft_strdup(new_var);
	if (!new_env_vars[i])
	{
		ft_putstr_fd("Error: Unable to duplicate string\n", 2);
		free(new_env_vars);
		return (1);
	}
	if (ft_strchr(new_var, '=') == NULL)
	{
		temp = new_env_vars[i];
		new_env_vars[i] = ft_strjoin(new_env_vars[i], "=");
		free(temp);
		if (!new_env_vars[i])
		{
			ft_putstr_fd("Error allocating memory\n", 2);
			cleanup_split(new_env_vars);
			return (1);
		}
	}
	new_env_vars[i + 1] = NULL;
	return (0);
}
