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

int	export_builtin(t_env *env_vars, char *new_var)
{
	int		i;
	int		j;
	char	**new_env_vars;
	char	*temp;
	char	**name;

	if (new_var == NULL)
	{
		i = 0;
		while (env_vars->env_vars[i]  != NULL)
		{
			printf("declare -x %s\n", env_vars->env_vars[i]);
			i++;
		}
		return (0);
	}
	name = ft_split(new_var, '=');
	if (name[0] == NULL || !is_valid_var_name(name[0]))
	{
		printf("Export builtin\n");
		// ft_putstr_fd("miniℍΞLL: not a valid identifier\n", 2);
		env_vars->status = 1;
		return (env_vars->status);
	}
	if ((name[0][ft_strlen(name[0]) - 1] == ' ')  || (name[1] && name[1][0] == ' '))
	{
		ft_putstr_fd("bash: export: '=': nor a valid identifier", 2);
		free(name);
		return (1);
	}
	if (!is_valid_var_name(name[0]))
	{
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (check_duplicate(env_vars, new_var))
	{
		return (0);
	}
	i = 0;
	while (env_vars->env_vars[i] != NULL)
		i++;
	new_env_vars = malloc((i + 2) * sizeof(char *));
	if (!new_env_vars)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", 2);
		return (1);
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
			free(new_env_vars);
			return (1);
		}
	}
	new_env_vars[i + 1] = NULL;
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
		if (ft_strncmp(env_vars->env_vars[i], new_var, len) == 0 && env_vars->env_vars[i][len] == '=')
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
	printf("dsfdsafasd");
	if (!var || !ft_isalpha(var[0]) || ft_strchr(var, '=') || ft_isdigit(var[0]))
	{
		printf("Is valid first char\n");
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
			printf("Is valid remaining chars\n");
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
	printf("ISVALIR\n");
	if (!is_valid_first_char(var))
		return (0);
	if (!is_valid_remaining_chars(var))
		return (0);
	if (!is_all_uppercase(var))
		return (0);
	return (1);
}
