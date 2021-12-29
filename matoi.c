
int	matoi(char *str, int *count)
{
	int	sign = 1;
	int	res = 0;
	int _count = 0;

	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		_count++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
		_count++;
	}
	if(res == 0 && *str == 'X')
	{
		*count = 1;	
		return sign;
	}
	*count = _count;
	return (res * sign);
}
