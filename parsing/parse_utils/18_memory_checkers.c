/* ************************************************************************** */
/*                                                                            */
/*   15_handle_variables_1.c        ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*my_malloc(size_t size)
{
	void	*result;

	result = malloc(size);
	printf("Allocated %zu bytes at address %p\n", size, result);
	return (result);
}

void	my_free(void *ptr)
{
	printf("Freed memory at address %p\n", ptr);
	free(ptr);
}
//Custom Memory Allocator
// typedef struct Allocation {
//     void* address;
//     size_t size;
// } Allocation;

// Allocation allocations[1000];  // Increase this if necessary
// int allocation_count = 0;

// void* my_malloc(size_t size) {
//     void* result = malloc(size);
//     allocations[allocation_count].address = result;
//     allocations[allocation_count].size = size;
//     allocation_count++;
//     return result;
// }

// void my_free(void* ptr) {
//     for (int i = 0; i < allocation_count; i++) {
//         if (allocations[i].address == ptr) {
//             allocations[i].address = NULL;
//             allocations[i].size = 0;
//             break;
//         }
//     }
//     free(ptr);
// }