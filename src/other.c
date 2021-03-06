#include "../includes/fdf.h"

double	dtr(double degrees)
{
	return ((degrees) * M_PI / 180);
}

double	rtd(double radians)
{
	return ((radians) * 180 / M_PI);
}

int		base(int c, int base)
{
	char	*str;
	char	*str2;
	int		i;

	i = 0;
	str = "0123456789abcdef";
	str2 = "0123456789ABCDEF";
	while (i < base)
	{
		if (c == str[i] || c == str2[i])
			return (i);
		i++;
	}
	return (-1);
}

int		ft_atoi_base(const char *str)
{
	int str_base;
	int nb;
	int	i;

	nb = 0;
	i = 2;
	str_base = 16;
	while (base(str[i], str_base) != -1)
	{
		nb = nb * str_base;
		nb = nb + base(str[i], str_base);
		i++;
	}
	return (nb);
}
