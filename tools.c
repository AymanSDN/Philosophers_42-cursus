#include "philo.h"

// check whitespaces
static int escape_whitespaces(char c) {
    if (c == 32 || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == '\n')
        return (1);
    return (0);
}

// check if is digit
static int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

// Custom atoi function to convert string to integer
int ft_atoi(const char *str) {
    int i = 0;
    int j = 0;
    int sign = 1;

    while (escape_whitespaces(str[j]))
        j++;
    if (str[j] == '+' || str[j] == '-') {
        if (str[j] == '-')
            sign *= -1;
        j++;
    }
    while (ft_isdigit(str[j])) {
        i += str[j] - '0';
        j++;
        if (ft_isdigit(str[j]))
            i *= 10;
    }
    return (i * sign);
}

// custom usleep function to pause execution for a specified time
void ft_usleep(unsigned long long time) {
    unsigned long long sleep_time = ft_time();
    while (ft_time() - sleep_time != time)
        usleep(200);
}

// get current time in milliseconds
long long ft_time(void) {
    struct timeval timestamp;
    gettimeofday(&timestamp, NULL);
    return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}
