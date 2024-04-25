/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:37:46 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/04/02 13:37:47 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_buildin(t_env *env_vars, char *new_var)
{
	int		i;
	int		j;
	char	**new_env_vars;
	char	*temp;
	char	**name;
	// char	**value;

	name = ft_split(new_var, '=');
	// value = ft_split(NULL, '=');
	if (!is_valid_var_name(name[0]))
	{
		ft_putstr_fd("export: not valid in this context: ", 2);
		ft_putstr_fd(name[0], 2);
		env_vars->status = 1;
	}

	if (check_duplicate(env_vars, new_var))
	{
		env_vars->status = 0;
		return;
	}
	i = 0;
	while (env_vars->env_vars[i] != NULL)
		i++;
	new_env_vars = malloc((i + 2) * sizeof(char *));
	if (!new_env_vars)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", 2);
		env_vars->status = 1;
		return ;
	}
	j = 0;
	while (j < i)
	{
		new_env_vars[j] = env_vars->env_vars[j];
		j++;
	}
	new_env_vars[i] = ft_strdup(new_var);
	if (!new_env_vars[i])
	{
		ft_putstr_fd("Error: Unable to duplicate string\n", 2);
		free(new_env_vars);
		env_vars->status = 1;
		return ;
	}
	if (ft_strchr(new_var, '=') == NULL)
	{
		temp = new_env_vars[i];
		new_env_vars[i] = ft_strjoin(new_env_vars[i], "=");
		free(temp);
		if (!new_env_vars[i])
		{
			ft_putstr_fd("Error allocating memory\n", 2);
			free(new_env_vars);
			env_vars->status = 1;
			return ;
		}
	}
	new_env_vars[i + 1] = NULL;
	free(env_vars->env_vars);
	env_vars->env_vars = new_env_vars;
	// env_buildin(env_vars);	//can delete later
	env_vars->status = 0;
}

int	check_duplicate(t_env *env_vars, char *new_var)
{
	int	i;

	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		if (ft_strncmp(env_vars->env_vars[i], new_var, ft_strlen(new_var)) == 0 \
			&& env_vars->env_vars[i][ft_strlen(new_var)] == '=')
		{
			free(env_vars->env_vars[i]);
			env_vars->env_vars[i] = ft_strdup(new_var);
			if(!env_vars->env_vars[i])
			{
				ft_putstr_fd("Error: Unable to duplicate string\n", STDERR_FILENO);
				env_vars->status = 1;
				return (0);
			}
			env_vars->status = 0;
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_valid_var_name(char *var)
{
	int	i;
	if (!var || !isalpha(var[0]) || ft_strchr(var, '='))
		return (0);
	i = 1;
	while (var[i])
	{
		if (!isalnum(var[i]) && (var[i] != '_' || var[i] != '-'))
			return (0);
		i++;
	}
	return (1);
}