/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:18:46 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/25 10:21:04 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct	s_format
{
	int			min_width;
	int			precision;
}				t_format;

int				ft_parse_width(const char *str, t_format *format)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		format->min_width = format->min_width * 10 + str[i++] - '0';
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int				ft_parse_precision(const char *str, t_format *format)
{
	int	i;

	i = 0;
	if (str[i++] != '.')
	{
		format->precision = -1;
		return (0);
	}
	format->precision = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		format->precision = format->precision * 10 + str[i++] - '0';
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int				ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				ft_nbrlen_base(int nbr, int baselen)
{
	int				i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr)
	{
		i++;
		nbr /= baselen;
	}
	return (i);
}

int				ft_unbrlen_base(unsigned int nbr, int baselen)
{
	int				i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i++;
	while (nbr)
	{
		i++;
		nbr /= baselen;
	}
	return (i);
}

int				ft_putflags(t_format *format, int negative)
{
	int	i;
	int	ret;

	i = 0;
	while (i++ < format->min_width)
		write(1, " ", 1);
	ret = i;
	if (negative)
	{
		ret++;
		write(1, "-", 1);
	}
	i = 0;
	while (i++ < format->precision)
		write(1, "0", 1);
	return (i + ret - 2);
}

int				ft_putnbr_base(unsigned int nbr, char *base, int len)
{
	int	i;

	i = 0;
	if (nbr >= (unsigned int)len)
		i += ft_putnbr_base(nbr / (unsigned int)len, base, len);
	write(1, &base[nbr % len], 1);
	return (i + 1);
}

int				ft_print_dec(t_format *format, va_list args)
{
	int				nbr;
	int				len;
	int				negative;
	unsigned int	u_nbr;

	nbr = va_arg(args, int);
	u_nbr = nbr;
	negative = 0;
	if (nbr < 0)
	{
		u_nbr = -nbr;
		negative = 1;
	}
	len = ft_nbrlen_base(nbr, 10) - (format->precision == 0 && nbr == 0);
	format->precision -= len - (nbr < 0);
	if (format->precision < 0)
		format->precision = 0;
	format->min_width -= format->precision + len;
	if (format->min_width < 0)
		format->min_width = 0;
	if (len == 0)
		return (ft_putflags(format, 0));
	return (ft_putflags(format, negative) +
			ft_putnbr_base(u_nbr, "0123456789", 10));
}

int				ft_print_hex(t_format *format, va_list args)
{
	int				len;
	unsigned int	nbr;

	nbr = (unsigned int)va_arg(args, int);
	len = ft_unbrlen_base(nbr, 16) - (format->precision == 0 && nbr == 0);
	format->precision -= len - (nbr < 0);
	if (format->precision < 0)
		format->precision = 0;
	format->min_width -= format->precision + len;
	if (format->min_width < 0)
		format->min_width = 0;
	if (len == 0)
		return (ft_putflags(format, 0));
	return (ft_putflags(format, 0) +
			ft_putnbr_base(nbr, "0123456789abcdef", 16));
}

int				ft_putnstr(char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
		write(1, &str[i++], 1);
	return (i);
}

int				ft_print_string(t_format *format, va_list args)
{
	int		len;
	char	*str;

	str = va_arg(args, char*);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (format->precision >= 0 && len > format->precision)
		len = format->precision;
	format->precision = 0;
	format->min_width -= len;
	if (format->min_width < 0)
		format->min_width = 0;
	return (ft_putflags(format, 0) + ft_putnstr(str, len));
}

int				ft_print_identifier(const char *str, t_format *format, va_list args)
{
	if (str[0] == 'd')
		return (ft_print_dec(format, args));
	else if (str[0] == 'x')
		return (ft_print_hex(format, args));
	else if (str[0] == 's')
		return (ft_print_string(format, args));
	return (-1);
}

int				ft_parse_format(const char *str, int *i, va_list args)
{
	int			ret;
	t_format	format;

	format.min_width = 0;
	format.precision = -1;
	ret = ft_parse_width(&str[*i], &format);
	if (ret == -1)
		return (-1);
	*i += ret;
	ret = ft_parse_precision(&str[*i], &format);
	if (ret == -1)
		return (-1);
	*i += ret;
	if (str[*i] == '\0')
		return (-1);
	return (ft_print_identifier(&str[(*i)++], &format, args));
}

int				ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	int		ret;
	va_list	args;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i += 1;
			ret = ft_parse_format(str, &i, args);
			if (ret == -1)
				return (-1);
			len += ret - 1;
		}
		else
			write(1, &str[i++], 1);
		len++;
	}
	va_end(args);
	return (len);
}
