/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:19:58 by ltammie           #+#    #+#             */
/*   Updated: 2020/01/15 01:18:53 by sauron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int c)
{
	unsigned char sym;

	sym = (unsigned char)c;
	if (sym == '\n' || sym == '\t' || sym == '\v' || sym == '\r'
	|| sym == '\f' || sym == ' ')
		return (1);
	return (0);
}
