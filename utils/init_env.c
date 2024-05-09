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
	int	i;

	num_vars = 0;
	while (env[num_vars] != NULL)
		num_vars++;
	env_vars->env_vars = (char **)malloc((num_vars + 1) * sizeof(char *));
	if (!env_vars->env_vars)
	{
		env_vars->status = -1;
		return ;
	}
	i = 0;
	while (i < num_vars)
	{
		env_vars->env_vars[i] = ft_strdup(env[i]);
		i++;
	}
	env_vars->env_vars[i] = NULL;
	env_vars->status = 0;
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
		ns = "";
		return (ns);
	}
	ns = (char *) malloc(ft_strlen(s1) + 1);
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