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

// /// ADAPTATION OF THE PARSING FUNCTIONS TO THE MINISHELL
// t_list *create_main_structs(t_ast *ast)
// {
// 	t_list *cmdlist_node = ast->cmdlist;
// 	t_list *cmd_node;
// 	// t_list *redir_node;
// 	// t_list *token_node;
// 	t_list *main_structs = NULL;
// 	t_cmdlist *cmdlist;
// 	t_cmd *cmd;
// 	// t_redir *redir;
// 	t_main *main_struct;

// 	while (cmdlist_node)
// 	{
// 		cmdlist = (t_cmdlist *)cmdlist_node->content;
// 		cmd_node = cmdlist->commands;
// 		while (cmd_node)
// 		{
// 			cmd = (t_cmd *)cmd_node->content;
// 			main_struct = ft_calloc(1, sizeof(t_main));
// 			main_struct->tokens = cmd->tokens;
// 			main_struct->redirs = cmd->redirs;
// 			main_struct->separator = cmdlist->separator;
// 			ft_lstadd_back(&main_structs, ft_lstnew(main_struct));
// 			cmd_node = cmd_node->next;
// 		}
// 		cmdlist_node = cmdlist_node->next;
// 	}
// 	return (main_structs);
// }

// void print_main_structs(t_list *main_structs)
// {
// 	//need to print all the fields of the main struct: the output must be: Commands: char	*cmd; Flags: char	*flags; 
// 	//Args: char	**args; Tokens: t_list *tokens; Redirs: t_list *redirs; Separator: char *separator; FD: int fd[2]; PID: pid_t pid;

// 	t_list *main_node = main_structs;
// 	t_main *main;
	
// 	while (main_node)
// 	{
// 		main = (t_main *)main_node->content;
// 		printf("Commands: " );
// 		t_list *token_node = main->tokens;
// 		while (token_node)
// 		{
// 			char *token = (char *)token_node->content;
// 			printf("%s ", token);
// 			token_node = token_node->next;
// 		}
// 		printf("\n");
// 		t_list *flags	


// 	}
// }

// int main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;

// 	t_list *main_structs = create_main_structs(set_ast("ls -l | grep .txt"));
// 	print_main_structs(main_structs);

// 	t_list *main_node = main_structs;
// 	t_main *main;
// 	while (main_node)
// 	{
// 		main = (t_main *)main_node->content;
// 		printf("Command: ");
// 		t_list *token_node = main->tokens;
// 		while (token_node)
// 		{
// 			char *token = (char *)token_node->content;
// 			printf("%s ", token);
// 			token_node = token_node->next;
// 		}
// 		printf("\n");
// 		t_list *redir_node = main->redirs;
// 		while (redir_node)
// 		{
// 			t_redir *redir = (t_redir *)redir_node->content;
// 			printf("Redirection: %s %s\n", redir->type, redir->direction);
// 			redir_node = redir_node->next;
// 		}
// 		main_node = main_node->next;
// 	}
// 	return (0);
// }

// typedef struct s_main
// {
// 	char	*cmd;
// 	char	*flags;
// 	char	**args;
// 	int		fd[2];
// 	pid_t	pid;
// }			t_main;


// ////////////////////////////////////////////////////////////////////////////////////////////////////////
// /// PARSING TEST
// /// @brief a test for the above functions
// /// @param argc 
// /// @param argv 

// void print_ast(t_ast *ast)
// 		{
// 			t_list *cmdlist_node = ast->cmdlist;
// 			while (cmdlist_node)
// 			{
// 				t_cmdlist *cmdlist = (t_cmdlist *)cmdlist_node->content;
// 				t_list *cmd_node = cmdlist->commands;
// 				while (cmd_node)
// 				{
// 					t_cmd *cmd = (t_cmd *)cmd_node->content;
// 					printf("Command: ");
// 					t_list *token_node = cmd->tokens;
// 					while (token_node)
// 					{
// 						char *token = (char *)token_node->content;
// 						printf("%s ", token);
// 						token_node = token_node->next;
// 					}
// 					printf("\n");
// 					t_list *redir_node = cmd->redirs;
// 					while (redir_node)
// 					{
// 						t_redir *redir = (t_redir *)redir_node->content;
// 						printf("Redirection: %s %s\n", redir->type, redir->direction);
// 						redir_node = redir_node->next;
// 					}
// 					cmd_node = cmd_node->next;
// 				}
// 				cmdlist_node = cmdlist_node->next;
// 			}
// 		}
		
////////////// TEST MAIN WITH EXAMPLES ALREADY SETTED
// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
//     const char *test_cases[] = {
//         "ls -l",
//         "echo Hello, World!",
//         "cat file.txt",
//         "ls -l | grep .txt",
//         "cat < input.txt > output.txt",
//         "ls -l; echo Done",
//         "command_does_not_exist",
//         "ls -l && echo Success || echo Failure",
//         "ls -l > output.txt 2> error.txt",
//         "cat file.txt | grep keyword | wc -l",
//         // "ls -l; echo Done &",
//         "ls -l && echo Success && echo More Success",
//         "ls -l || echo Failure || echo More Failure",
//         "command1; command2; command3",
//         // "command1 & command2 & command3",
//         "command1 && command2 && command3",
//         "command1 || command2 || command3",
//         "command1 | command2 | command3",
//         "command1 > output.txt",
//         "command1 2> error.txt",
//         "command1 > output.txt 2> error.txt",
//         "command1 < input.txt",
//         "command1 < input.txt > output.txt",
//         "command1 < input.txt 2> error.txt",
//         "command1 < input.txt > output.txt 2> error.txt",
//         NULL
//     };

//     for (int i = 0; test_cases[i] != NULL; i++)
//     {
//         const char *string = test_cases[i];
//         t_ast *ast = set_ast(string);
//         if (ast)
//         {
//             printf("AST created successfully for test case %d: %s\n", i, string);
//             print_ast(ast);
//         }
//         else
//         {
//             printf("Failed to create AST for test case %d: %s\n", i, string);
//         }
//     }

//     return 0;
// }

// cc parser.c parse_utils.c -L../libft/ -lft -Wall -Wextra -Werror && ./a.out


// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	return(0);
// }


// Function to convert AST to an array of arrays
void ast_to_array(t_ast *ast, int *index, char **array) {
    if (ast == NULL || *index >= 1000) {
        return;
    }

    // Traverse the command list linked list
    t_list *current_cmdlist = ast->cmdlist;
    while (current_cmdlist != NULL) {
        t_cmdlist *cmdlist = (t_cmdlist *)current_cmdlist->content;

        // Traverse the command linked list within the command list
        t_list *current_cmd = cmdlist->commands;
        while (current_cmd != NULL) {
            t_cmd *cmd = (t_cmd *)current_cmd->content;

            // Store command tokens in array
            t_list *current_token = cmd->tokens;
            while (current_token != NULL) {
                char *token = (char *)current_token->content;
                array[*index] = token;
                (*index)++;
                current_token = current_token->next;
            }

            // Traverse the redirections linked list within the command
            t_list *current_redir = cmd->redirs;
            while (current_redir != NULL) {
                t_redir *redir = (t_redir *)current_redir->content;

                // Store redirection type and direction in array
                array[*index] = redir->type;
                (*index)++;
                array[*index] = redir->direction;
                (*index)++;

                current_redir = current_redir->next;
            }
// printf("separator: %s\n", cmdlist->separator);
			// array[*index] = cmdlist->separator;
			// (*index)++;
            current_cmd = current_cmd->next;
        }
        current_cmdlist = current_cmdlist->next;
    }
}

int main(int argc, char **argv) {
	(void)argc;
	argv[1] = "cat index.txt | ls -l && echo Success || echo Failure";
	printf("STRING: %s\n\n", argv[1]);
    // Assuming you have already constructed your AST
    t_ast *ast = set_ast(argv[1]); // Replace with your function to construct the AST

    // Define an array to store the AST elements
    char *array[1000];
    int index = 0;

    // Convert AST to array
    ast_to_array(ast, &index, array);

    // Print the array (for demonstration)
    printf("Array representation of AST:\n");
    for (int i = 0; i < index; i++) {
        printf("%s\n", array[i]);
    }

    return 0;
}