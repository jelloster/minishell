/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motuomin <motuomin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:46:38 by motuomin          #+#    #+#             */
/*   Updated: 2024/11/04 16:06:40 by motuomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Function : color_code
 *
 * Returns the color code of given color enum
*/

static const char	*color_code(t_color color)
{
	if (color == RED)
		return ("\033[31m");
	else if (color == GREEN)
		return ("\033[31m");
	else if (color == YELLOW)
		return ("\033[33m");
	else if (color == BLUE)
		return ("\033[34m");
	else if (color == MAGENTA)
		return ("\033[35m");
	else if (color == CYAN)
		return ("\033[36m");
	return ("\033[0m");
}

/*
 * Function : print_in_color
 *
 * Prints a string (str) in a given color
*/

void	print_in_color(const char *str, t_color color)
{
	const char	*print_color;
	const char	*reset_color;

	print_color = color_code(color);
	reset_color = color_code(RESET);
	printf("%s%s%s", print_color, str, reset_color);
}

/*
 * Function : clear_terminal
 *
 * Clears the terminal
*/

void	clear_terminal(void)
{
	printf("\033[H\033[J");
}
