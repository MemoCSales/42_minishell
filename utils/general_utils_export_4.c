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

int validate_var_name(char *var_name)
{
    int i;

    i = 0;
    if (!ft_isalpha(var_name[0]) && var_name[0] != '_')
        return (0);
    while (var_name[i] != '\0' && var_name[i] != '=')
    {
        if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int	check_command(t_main *main, char **error_message)
{
	if (ft_strncmp(main->cmd, "/", 1) == 0)
	{
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(main->cmd, 2);
		*error_message = ": Is a directory\n";
		return (126);
	}
    else if (ft_strncmp(main->cmd, "./", 2) == 0)
    {
        ft_putstr_fd("bash: ", 2);
        ft_putstr_fd(main->cmd, 2);
        *error_message = ": No such file o directory\n";
        return (126);
    }
	return (0);
}
