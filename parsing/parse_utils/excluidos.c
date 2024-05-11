/* ************************************************************************** */
/*                                                                            */
/*   excluidos.c                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

// void	ft_erase_quotes(char *tkn)
// {
// 	int	i;
// 	int	double_q_flag;
// 	int	single_q_flag;

// 	i = 0;
// 	double_q_flag = 0;
// 	single_q_flag = 0;
// 	while (tkn[i])
// 	{
// 		if (tkn[i] == '"' && single_q_flag == 0)
// 		{
// 			double_q_flag = !double_q_flag;
// 			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
// 			continue ;
// 		}
// 		else if (tkn[i] == '\'' && double_q_flag == 0)
// 		{
// 			single_q_flag = !single_q_flag;
// 			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
// 			continue ;
// 		}
// 		i++;
// 	}
// }