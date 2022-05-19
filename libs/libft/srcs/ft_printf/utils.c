/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabir <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:37:38 by hsabir            #+#    #+#             */
/*   Updated: 2022/01/06 16:56:14 by hsabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_printf.h>

// Initializing the structure
void	init(t_options *option)
{
	option->negative = 0;
	option->zero = 0;
	option->width = 0;
	option->precision = -1;
	option->spec = 0;
	option->nbr_base = 10;
	option->sign = 1;
}

void	check_flags(va_list ap, char *format, t_options *option, int i)
{
	if (format[i] == '0' && option->width == 0 && option->precision == -1)
		option->zero = 1;
	else if (format[i] == '-')
		option->negative = 1;
	else if (format[i] == '.')
		option->precision = 0;
	else if (ft_isdigit(format[i]) || format[i] == '*')
		width_precision(ap, format, option, i);
}

void	width_precision(va_list ap, char *format, t_options *option, int i)
{
	if (ft_isdigit(format[i]))
	{
		if (option->precision == -1)
			option->width = option->width * 10 + format[i] - 48;
		else
			option->precision = option->precision * 10 + format[i] - 48;
	}
	else if (format[i] == '*')
	{
		if (option->precision == -1)
		{
			option->width = va_arg(ap, int);
			if (option->width < 0)
			{
				option->negative = 1;
				option->width *= -1;
			}
		}
		else
			option->precision = va_arg(ap, int);
	}	
}

// Length of a number
int	ft_nbrlen(unsigned long long nbr, t_options *option)
{
	int	i;

	if (nbr == 0 && option->precision != 0)
		return (1);
	i = 0;
	while (nbr)
	{
		i++;
		nbr /= option->nbr_base;
	}
	return (i);
}

char	*ft_baseset(char spec)
{
	if (spec == 'u' || spec == 'd' || spec == 'i')
		return ("0123456789");
	else if (spec == 'x' || spec == 'p')
		return ("0123456789abcdef");
	else if (spec == 'X')
		return ("0123456789ABCDEF");
	return (0);
}
