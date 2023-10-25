/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picarlie <picarlie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:34:40 by picarlie            #+#    #+#             */
/*   Updated: 2023/10/25 14:34:40 by picarlie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	printf_char(char c)
{
	return (write(1, &c, 1));
}

int	printf_string(char *str)
{
	int	count_printed;

	count_printed = 0;
	while (*str)
	{
		if (printf_char(str) < 0)
			return (-1);
		str++;
		count_printed++;
	}
	return (count_printed);
}

int	printf_number(long int nb, char *base, int count_printed)
{
	int	len_base;
	int	check;

	len_base = ft_strlen(base);
	if (nb < 0)
	{
		check = write(1, '-', 1);
		if (check < 0)
			return (check);
		return (printf_number(nb, base, ++count_printed));
	}
	if (nb > len_base)
	{
		check = printf_number(nb / len_base, base, count_printed);
		if (check < 0)
			return (check);
		return (printf_number(nb % len_base, base, count_printed + check));
	}
	check = write(1, &base[nb], 1);
	if (check < 0)
		return (check);
	return (count_printed + check);
}

int	redirect(va_list ap, char c)
{
	int	check;

	check = 0;
	if (c == 'c')
		check = printf_char(ap);
	if (c == 's')
		check = printf_string(ap);
	if (c == 'p')
		//check = printf_s(ap);
	if (c == 'd')
		check = printf_number(ap, "0123456789", 0);
	if (c == 'i')
		check = printf_number(ap, "0123456789", 0);
	if (c == 'u')
		check = printf_number(ap, "0123456789", 0);
	if (c == 'x')
		check = printf_number(ap, "0123456789abcdef", 0);
	if (c == 'X')
		check = printf_number(ap, "0123456789ABCDEF", 0);
	if (check == -1 || !check)
		return (-1); // NILLS ????????????????
	return (check);
}

int	ft_printf(const char *input, ...)
{
	va_list	ap;
	int	count_printed;
	int	check;

	count_printed = 0;
	va_start(ap, input);
	while (*input)
	{
		if (*input != '%' || (*input == '%' && *(++input) == '%'))
			check = write(1, input, 1);
		else
		{
			input++;
			check = redirect(ap, *format);
			va_arg(ap);
		}
		if (check < 0)
			return (check);
		count_printed += check;
	}
	va_end(ap);
	return (count_printed);
}

#include <stdio.h>

int	main ()
{
	int	count_printed;
	char	*str = "Test";
	int	deci = -10;
	unsigned int	unsign = 10;

	count_printed = ft_printf("Hello wolrd \nc : %c\ns : %s\np : %p\nd : %d\ni : %i\nu : %u\n
	x : %x\nX : %X\n%% : %%\n", 'c', str, str, , deci, deci, unsign, deci, deci);
	ft_printf("count_printed : %d\n", count_printed);
	count_printed = printf("Hello wolrd \nc : %c\ns : %s\np : %p\nd : %d\ni : %i\nu : %u\n
	x : %x\nX : %X\n%% : %%\n", 'c', str, str, , deci, deci, unsign, deci, deci);
	printf("count_printed : %d\n", count_printed);
	return (0);
}
