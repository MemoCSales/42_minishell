/* *************************************************************************** */
/*                                                                             */
/*                                                           ::     :::::      */
/*   parser.c                                              :+:    :+:  :+:     */
/*                                                       +:+ +:+       +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>             +#+ +:+      +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>  +#+  +#+     +#+          */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#              */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr        */
/*                                                                             */
/* *************************************************************************** */

#include "../minishell.h"

t_redir	*set_redir(const char *string, int *position)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
    if (string[*position] == '<')
    {
        redir->type[0] = string[(*position)++];
        redir->type[1] = '\0';
    }
    else if (!ft_strncmp(&string[*position], ">>", 2))
    {
        ft_strncpy(redir->type, (char *)&string[*position], 2);
        redir->type[2] = '\0';
        *position += 2;
    }
    else if (string[*position] == '>')
    {
        redir->type[0] = string[(*position)++];
        redir->type[1] = '\0';
    }
	ft_jump_spaces(string, position);
	redir->direction = set_token(string, position);
	return (redir);
}

char	*set_token(const char *string, int *position)
{
	char	*token;
	int		position_start;

	position_start = *position;
	while (string[*position] && !ft_istoken_separator(string[*position]))
	{
		if (ft_isquote(string[*position]))
			ft_jump_quotes(string, position);
		else if (string[*position])
			(*position)++;
	}
	token = ft_substr(string, position_start, *position - position_start);
	if (!token)
		return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
	return (token);
}

t_cmd	*set_cmd(const char *string, int *position)
{
	t_cmd	*cmd;
	t_list	*added_node;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
	while (string[*position] && !ft_iscmd_separator(string[*position]))
	{
		if (string[*position] != '>' && string[*position] != '<')
		{
			added_node = ft_lstnew((void *)set_token(string, position));
			if (!added_node)
				return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
			ft_lstadd_back(&cmd->tokens, added_node);
		}
		else if (string[*position] == '>' || string[*position] == '<')
		{
			added_node = ft_lstnew((void *)set_redir(string, position));
			if (!added_node)
				return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
			ft_lstadd_back(&cmd->redirs, added_node);
		}
		ft_jump_spaces(string, position);
	}
	return (cmd);
}

t_cmdlist	*set_cmdlist(const char *string, int *position)
{
	t_cmdlist	*cmdlist;
	t_list		*cmd;

	cmdlist = ft_calloc(1, sizeof(t_cmdlist));
	if (!cmdlist)
		return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
	while (string[*position] && !ft_iscmdlist_separator(&string[*position]))
	{
		ft_jump_spaces(string, position);
		cmd = ft_lstnew((void *)set_cmd(string, position));
		if (!cmd)
			return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
		ft_lstadd_back(&cmdlist->commands, cmd);
		if (string[*position] == '|' && string[*position + 1] != '|')
			(*position)++;
	}
	cmdlist->separator = get_cmdlist_separator(string, position);
	return (cmdlist);
}

t_ast	*set_ast(const char *string)
{
	t_ast	*ast;
	t_list	*cmdlist;
	int		position;

	ast = ft_calloc(1, sizeof(t_ast));
	if (!ast)
		return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
	position = 0;
	while (string[position])
	{
		ft_jump_spaces(string, &position);
		cmdlist = ft_lstnew((void *)set_cmdlist(string, &position));
		if (!cmdlist)
			return (NULL); // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
		ft_lstadd_back(&ast->cmdlist, cmdlist);
	}
	return (ast);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PARSING TEST
/// @brief a test for the above functions
/// @param argc 
/// @param argv 

void print_ast(t_ast *ast)
		{
			t_list *cmdlist_node = ast->cmdlist;
			while (cmdlist_node)
			{
				t_cmdlist *cmdlist = (t_cmdlist *)cmdlist_node->content;
				t_list *cmd_node = cmdlist->commands;
				while (cmd_node)
				{
					t_cmd *cmd = (t_cmd *)cmd_node->content;
					printf("Command: ");
					t_list *token_node = cmd->tokens;
					while (token_node)
					{
						char *token = (char *)token_node->content;
						printf("%s ", token);
						token_node = token_node->next;
					}
					printf("\n");
					t_list *redir_node = cmd->redirs;
					while (redir_node)
					{
						t_redir *redir = (t_redir *)redir_node->content;
						printf("Redirection: %s %s\n", redir->type, redir->direction);
						redir_node = redir_node->next;
					}
					cmd_node = cmd_node->next;
				}
				cmdlist_node = cmdlist_node->next;
			}
		}
		

////////////// TEST MAIN WITH EXAMPLES ALREADY SETTED
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
    const char *test_cases[] = {
        "ls -l",
        "echo Hello, World!",
        "cat file.txt",
        "ls -l | grep .txt",
        "cat < input.txt > output.txt",
        "ls -l; echo Done",
        "command_does_not_exist",
        "ls -l && echo Success || echo Failure",
        "ls -l > output.txt 2> error.txt",
        "cat file.txt | grep keyword | wc -l",
        // "ls -l; echo Done &",
        "ls -l && echo Success && echo More Success",
        "ls -l || echo Failure || echo More Failure",
        "command1; command2; command3",
        // "command1 & command2 & command3",
        "command1 && command2 && command3",
        "command1 || command2 || command3",
        "command1 | command2 | command3",
        "command1 > output.txt",
        "command1 2> error.txt",
        "command1 > output.txt 2> error.txt",
        "command1 < input.txt",
        "command1 < input.txt > output.txt",
        "command1 < input.txt 2> error.txt",
        "command1 < input.txt > output.txt 2> error.txt",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++)
    {
        const char *string = test_cases[i];
        t_ast *ast = set_ast(string);
        if (ast)
        {
            printf("AST created successfully for test case %d: %s\n", i, string);
            print_ast(ast);
        }
        else
        {
            printf("Failed to create AST for test case %d: %s\n", i, string);
        }
    }

    return 0;
}

// cc parser.c parse_utils.c -L../libft/ -lft -Wall -Wextra -Werror && ./a.out