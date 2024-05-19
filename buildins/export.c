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
	if (ft_strncmp(new_var, "=", 1) == 0 || (name[0] == NULL
			&& !is_valid_var_name(name[0])) || !is_valid_var_name(name[0])
		|| check_duplicate(env_vars, new_var))
		return (0);
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

int	export_builtin(t_env *env_vars, t_main *main, char *new_var)
{
	char	**new_env_vars;
	int		i;

	if (new_var == NULL)
	{
		print_env_vars(env_vars);
		return (0);
	}
	if (main->args[1] != NULL)
		return (0);
	if (!validate_new_var(env_vars, new_var))
		return (1);
	new_env_vars = allocate_new_env_vars(env_vars);
	if (!new_env_vars)
		return (1);
	copy_env_vars(env_vars, new_env_vars);
	i = 0;
	while (new_env_vars[i] != NULL)
		i++;
	if (add_new_var(new_var, new_env_vars, i))
		return (1);
	free(env_vars->env_vars);
	env_vars->env_vars = new_env_vars;
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

int	is_valid_first_char(char *var)
{
	if (!var || !ft_isalpha(var[0]) || ft_strchr(var, '=')
		|| ft_isdigit(var[0]))
	{
		print_invalid_identifier(var);
		return (0);
	}
	return (1);
}

int	is_valid_remaining_chars(char *var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && (var[i] != '_' || var[i] != '-'))
		{
			print_invalid_identifier(var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	is_all_uppercase(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isupper(var[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_var_name(char *var)
{
	if (!is_valid_first_char(var))
		return (0);
	if (!is_valid_remaining_chars(var))
		return (0);
	if (!is_all_uppercase(var))
		return (0);
	return (1);
}
