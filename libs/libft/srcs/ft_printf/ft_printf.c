/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:39:18 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 16:55:16 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_printf.h>

int	ft_print(va_list ap, t_options *option)
{
	int		ret;
	char	spec;

	ret = 0;
	spec = option->spec;
	if (spec == 'c')
		ret = ft_print_c(va_arg(ap, int), option);
	else if (spec == '%')
		ret = ft_print_c('%', option);
	else if (spec == 's')
		ret = ft_print_str(va_arg(ap, char *), option);
	else if (spec == 'd' || spec == 'i')
		ret = ft_print_nbr(va_arg(ap, int), option);
	else if (spec == 'x' || spec == 'X' || spec == 'u')
		ret = ft_print_nbr(va_arg(ap, unsigned int), option);
	else if (spec == 'p')
		ret = ft_print_nbr(va_arg(ap, unsigned long long), option);
	return (ret);
}

void	zero_logic(t_options *option, char format)
{
	option->spec = format;
	if ((option->negative == 1 || option->precision > -1)
		&& option->spec != '%')
		option->zero = 0;
}

int	parse_format(va_list ap, char *format)
{
	int			i;
	int			ret;
	t_options	*option;

	i = 0;
	ret = 0;
	option = malloc(sizeof(t_options) * 1);
	if (!(option))
		return (-1);
	while (format[i] != '\0')
	{
		while (format[i] != '%' && format[i] != '\0')
			ret += ft_putchar(format[i++]);
		if (format[i] == '%')
		{
			init(option);
			while (format[++i] != '\0' && !(ft_strchr(SPEC, format[i])))
				check_flags(ap, format, option, i);
			zero_logic(option, format[i++]);
			ret += ft_print(ap, option);
		}
	}
	free(option);
	return (ret);
}

/*
 * L'entree de fonction, on appel tout de suite la fonction parse_format()
*/

int	ft_printf(const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = parse_format(ap, (char *)format);
	va_end(ap);
	return (ret);
}
