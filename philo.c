#include "philo.h"
void think(t_data *data)
{
    if(data->id % 2 == 1)
    {
	    printf("%lld %d is thinking\n", ft_get_time() - data->start, data->id);
        usleep(200);
    }
}
void *philo_routine(void *data)
{   
    while(1)
    {
        // sleep();
        // get_left_fork();
        // get_right_fork();
        // eat();
        // put_left_fork();
        // put_right_fork();
        think((struct s_data *)data);
    }
    return NULL;
}
int create_philosophers(t_ph *ph, t_data *data)
{
    pthread_t *tid = (pthread_t *)malloc(sizeof(pthread_t) * ph->n_philo);
    int i = 1;
    data->start = ft_get_time();
    while(i <= ph->n_philo)
    {
        ph->data[i].start = data->start;
        ph->data[i].last_meal = data->start;
        if (pthread_create(&tid[i], NULL, &philo_routine, &ph->data[i]))
            return(write(1, "Error: failed to create thread\n", 31), 0);
        pthread_join(tid[i], NULL);
        printf("creating Philosopher[%d]...\n", i);
        i++;
    }
    return 1;
}