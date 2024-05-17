/* ************************************************************************** */
/*                                                                            */
/*   main.c                     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_main	*main_var;
	t_env	env_var;

	(void)argc;
	(void)argv;
	main_var = NULL;
	init_env(&env_var, env);
	main_loop(env_var, main_var);
	// check_env(&env_var);
	return (0);
}

// int main() {
//     char line[256];
//     int numStrings;

//     while (1) {
//         printf("Enter a string (or 'exit' to quit): ");
//         fgets(line, sizeof(line), stdin);

//         // Remove trailing newline
//         line[strcspn(line, "\n")] = 0;

//         // Exit if the user entered "exit"
//         if (strcmp(line, "exit") == 0) {
//             break;
//         }

//         char **strings = extract_strings(line, &numStrings);

//         if (strings) {
//             replace_with_placeholder(line);

//             printf("Modified line: %s\n", line);
//             printf("Strings between quotes:\n");
//             for (int i = 0; strings[i]; ++i) {
//                 printf("%d: %s\n", i + 1, strings[i]);
//                 free(strings[i]); // Free allocated memory
//             }
//             free(strings);
//         }
//     }

//     return 0;
// }

// int main() {
//     char line[1024];

//     while (1) {
//         printf("Enter a string (or 'quit' to exit):");
//         fgets(line, sizeof(line), stdin);

//         // Remove trailing newline
//         line[strcspn(line, "\n")] = 0;

//         if (strcmp(line, "quit") == 0) {
//             break;
//         }

//         char* quoted_strings = process_line(line);
//         if (quoted_strings != NULL) {
//             printf("Quoted strings:%s\n", quoted_strings);
//             free(quoted_strings);
//         }
//     }

//     return 0;
// }

// int	main (void)
// {
// 	char	*line;
// 	char	*result;

// 	// line = "echo $PWD";
// 	while (1)
// 	{
// 		line = readline("\033[1;31mψΨ:\033[0m");
// 		if (!line)
// 		{
// 			printf("Error: readline\n");
// 			continue ;
// 		}
// 		result = prepare_line(line);
// 		if (result != NULL)
// 		{
// 			printf("Prepared line:%s\n", result);
// 			free(result);
// 		}
// 		else
// 		{
// 			printf("Error preparing line.\n");
// 		}
// 		free(line);
// 	}
// 	return (0);
// }
