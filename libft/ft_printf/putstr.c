/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:03:20 by mirsella          #+#    #+#             */
/*   Updated: 2022/11/27 21:52:12 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_print_char(t_formatoptions *fo, unsigned char c) {
  if (fo->dash) {
    count_bytes(&fo->byteswrotes, ft_putchar_fd(c, fo->fd));
    while (fo->width-- > 1)
      count_bytes(&fo->byteswrotes, ft_putchar_fd(' ', fo->fd));
  } else {
    while (fo->width-- > 1)
      count_bytes(&fo->byteswrotes, ft_putchar_fd(' ', fo->fd));
    count_bytes(&fo->byteswrotes, ft_putchar_fd(c, fo->fd));
  }
}

void ft_print_string(t_formatoptions *fo, char *s) {
  int i;
  int precision;

  i = 0;
  if (s == NULL)
    s = "(null)";
  if (fo->precision == -1)
    fo->precision = ft_strlen(s);
  precision = fo->precision;
  if (fo->dash) {
    while (precision-- > 0 && s[i])
      count_bytes(&fo->byteswrotes, ft_putchar_fd(s[i++], fo->fd));
    while (fo->width-- > ft_llmin(fo->precision, (int)ft_strlen(s)))
      count_bytes(&fo->byteswrotes, ft_putchar_fd(' ', fo->fd));
  } else {
    while (fo->width-- > ft_llmin(fo->precision, (int)ft_strlen(s)))
      count_bytes(&fo->byteswrotes, ft_putchar_fd(' ', fo->fd));
    while (precision-- > 0 && s[i])
      count_bytes(&fo->byteswrotes, ft_putchar_fd(s[i++], fo->fd));
  }
}
