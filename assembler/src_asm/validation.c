/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprotsen <sprotsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 13:43:04 by sprotsen          #+#    #+#             */
/*   Updated: 2017/07/01 13:43:06 by sprotsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head_asm.h"

int		command_checking(t_algo *lst)
{
	while (lst)
	{
		if (lst->content_size > 4000000000 && lst->content_size < 4000000017)
			return (FALSE);
		lst = lst->next;
	}
	ft_printf(RED"");
	write(2, "ERROR: file does not have any commands\n", 39);
	ft_printf("", RESET);
	return (TRUE);
}

int		check_symbol(t_algo *lst)
{
	char	*str;
	int		i;

	while (lst)
	{
		str = lst->origin;
		i = -1;
		while (str[++i])
		{
			if (str[i] > 127 || str[i] < 0 || (str[i] == SEPARATOR_CHAR
				&& str[i + 1] == SEPARATOR_CHAR) || (str[i + 1] == '\0'
				&& str[i] == SEPARATOR_CHAR))
			{
				ft_printf(RED"");
				write(2, "ERROR: Lexical error at:\n", 25);
				ft_printf("%s\n", lst->origin);
				ft_printf("Number line with error: %d\n"RESET, lst->length);
				return (TRUE);
			}
		}
		lst = lst->next;
	}
	return (FALSE);
}

int		validation(t_list *list, char *str, int fd)
{
	t_algo	*row;

	row = NULL;
	row = giving_len_for_each_list(list);
	delete_space(row);
	find_label(row);
	delete_space(row);
	if (find_name_and_comment(row, 0, 0) != 1)
		return (del_list_algo_false(&row));
	find_operations(row);
	if (command_checking(row))
		return (del_list_algo_false(&row));
	if (review_list_valid(row, 0, 0))
		return (del_list_algo_false(&row));
	if (!find_backslash_n(row, fd))
		return (del_list_algo_false(&row));
	clear_pieces_of_comment_in_line(row);
	if (check_symbol(row))
		return (del_list_algo_false(&row));
	if (next_validation(row))
		create_cor_file(row, str);
	del_list_algo(&row);
	return (TRUE);
}
