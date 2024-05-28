/* ************************************************************************** */
/*                                                                            */
/*   17_syntax_error.c              ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int is_metacharacter(char* token) {
//     return strcmp(token, "|") == 0 || strcmp(token, ";") == 0 || strcmp(token, "&") == 0 ||
//            strcmp(token, "(") == 0 || strcmp(token, ")") == 0 || strcmp(token, "<") == 0 ||
//            strcmp(token, ">") == 0;
// }

// void check_syntax(char* command) {
//     char* token = strtok(command, " ");
//     int last_was_meta = 0;

//     while (token != NULL) {
//         if (is_metacharacter(token)) {
//             if (last_was_meta) {
//                 printf("Syntax error: unexpected token '%s'\n", token);
//                 return;
//             }
//             last_was_meta = 1;
//         } else {
//             last_was_meta = 0;
//         }
//         token = strtok(NULL, " ");
//     }

//     if (last_was_meta) {
//         printf("Syntax error: unexpected token at end\n");
//         return;
//     }

//     printf("No syntax errors.\n");
// }

// int main() {
//     char command[100];
//     printf("Enter a command: ");
//     fgets(command, 100, stdin);
//     command[strcspn(command, "\n")] = 0;  // Remove trailing newline
//     check_syntax(command);
//     return 0;
// }