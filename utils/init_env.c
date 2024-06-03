/* ************************************************************************** */
/*                                                                            */
/*   init_env.c                 ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(t_env *env_vars, char **env)
{
	int	num_vars;

	num_vars = 0;
	if (env[0] != NULL)
	{
		while (env[num_vars] != NULL)
			num_vars++;
	}
	else
		num_vars = 3;
	env_vars->env_vars = (char **)malloc((num_vars + 1) * sizeof(char *));
	if (!env_vars->env_vars)
	{
		env_vars->status = -1;
		return ;
	}
	if (env[0] != NULL)
		duplicating_env_vars(env_vars, env, num_vars);
	else
		set_default_env_vars(env_vars);
	env_vars->env_vars[num_vars] = NULL;
	env_vars->status = 0;
}

void	duplicating_env_vars(t_env *env_vars, char **env, int num_vars)
{
	int	i;

	i = 0;
	while (i < num_vars)
	{
		env_vars->env_vars[i] = ft_strdup(env[i]);
		i++;
	}
}

void	set_default_env_vars(t_env *env_vars)
{
	int	i;

	i = 0;
	env_vars->env_vars[i] = ft_strdup("PWD=/home/mcruz-sa/Documents \
									/GIT_minishell");
	i++;
	env_vars->env_vars[i] = ft_strdup("SHLVL=1");
	i++;
	env_vars->env_vars[i] = ft_strdup("_=usr/bin/env");
	i++;
}

void	check_env(t_env *env_vars)
{
	int	i;

	if (env_vars->status == 0)
	{
		i = 0;
		while (env_vars->env_vars[i] != NULL)
		{
			printf("%s\n", env_vars->env_vars[i]);
			i++;
		}
		i = 0;
		while (env_vars->env_vars[i] != NULL)
		{
			free(env_vars->env_vars[i]);
			i++;
		}
		free(env_vars->env_vars);
	}
	else
		printf("Error initializaing environment variables\n");
}

char	*ft_strdup_minishell(char *s1)
{
	char	*ns;
	size_t	i;

	i = 0;
	if (s1 == NULL)
	{
		ns = malloc(1);
		if (ns)
			ns[0] = '\0';
		return (ns);
	}
	ns = (char *)malloc(ft_strlen(s1) + 1);
	if (!(ns))
		return (NULL);
	while (s1[i])
	{
		ns[i] = s1[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
