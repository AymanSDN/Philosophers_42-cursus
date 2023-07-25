#include "philo.h"
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if(!s)
		return(0);
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}


int	ft_atoi(char *str)
{
	long int	result = 0;

	if (!str || !*str)
	{
		printf("Error\n");
		return 0;
	}
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		printf("Error\n");
			return 0;
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str)
	{
		printf("Error\n");
		return 0;
	}
	if (0 < result && result <= INT_MAX)
		return (result);
	else
	{
        printf("Error: 0 < num <= MAX_INT\n");
		return 0;
	}
	return (1);
}
