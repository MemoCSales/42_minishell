/* *************************************************************************** */
/*                                                                             */
/*                                                           ::     :::::      */
/*   parse_utils.c                                         :+:    :+:  :+:     */
/*                                                       +:+ +:+       +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>             +#+ +:+      +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>  +#+  +#+     +#+          */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#              */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr        */
/*                                                                             */
/* *************************************************************************** */

#include "../minishell.h"

t_main	*initialize_main(t_main *main_var)
{
	main_var = (t_main *)malloc(sizeof(t_main));
	if (!main_var)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	main_var->cmd = NULL;
	main_var->flags = NULL;
	main_var->args = NULL;
	main_var->fd[0] = 0;
	main_var->fd[1] = 1;
	main_var->pid = 0;
	return (main_var);
}