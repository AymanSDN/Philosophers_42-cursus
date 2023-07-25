#include "philo.h"
int	check_args(char **args)
{
    int i = 0, j = 0;

    while(args[i])
    {
        if (ft_strlen(args[i]) > 12)
        {
        printf("Error: 0 < num <= MAX_INT\n");
        return 0;
        }
        while(args[i][j])
        {
            if(!ft_isdigit(args[i][j]))
            {
                printf("Error: arguments must be only positive numbers");
                return 0;
            }
            j++;
        }
        i++;
    }
    return 1;

}
int	check_empty_arg(char **args)
{
	int		count;

	count = 0;
	while (args[count])
	{
		count++;
	}
	if (!count)
    {
		printf("Error: empty argument\n");
        return 0;
    }
    return 1;
}

int init_philosophers(t_ph *ph, int ac, char **args)
{
    int i = 0;
    check_args(args);
    check_empty_arg(args);
    ph->n_philo = ft_atoi(args[1]);
    printf("number of philosophers: [%d]\n", ph->n_philo);
    printf("number of forks: [%d]\n", ph->n_philo);
    ph->t_die = ft_atoi(args[2]);
    printf("time to die: [%d]\n", ph->t_die);
    ph->t_eat = ft_atoi(args[3]);
    printf("time to eat: [%d]\n", ph->t_eat);
    ph->t_sleep = ft_atoi(args[4]);
    printf("time to sleep: [%d]\n", ph->t_sleep);
    if(ac == 6)
        ph->meals = ft_atoi(args[5]);
    else
        ph->meals = -1;
    printf("number of times each philo must eat: [%d]\n", ph->meals);
    i = 0;
    ph->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ph->n_philo);
    while(i <  ph->n_philo)
    {
        pthread_mutex_init(&ph->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&ph->sync, NULL);  

    return 1;
}

int each_philo_init(t_ph *ph)
{
    memset((void *)ph, 0, sizeof(ph));
    ph->data = (t_data *)malloc(sizeof(t_data)* ph->n_philo);
    int i = 0;
    while(i < ph->n_philo)
    {
        ph->data[i].id = i +1;
        ph->data[i].t_eat =  ph->t_eat;
        ph->data[i].t_sleep =  ph->t_sleep;
        ph->data[i].right_fork = &ph->forks[i];
    printf("r_f[%d]\n", i);
        ph->data[i].left_fork = i - 1 >= 0 ? &ph->forks[i - 1] : &ph->forks[ph->n_philo - 1];
    printf("l_f[%d]\n", i - 1 >= 0 ? i - 1 : ph->n_philo - 1);
        ph->data[i].sync = &ph->sync;
        i++;
    }
    return 1;
}