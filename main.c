#include "philo.h"

// philosopher routine function
static void *thread_routine(void *philo) {
    if (((struct s_info *)philo)->id % 2 == 1) {
        philo_think((struct s_info *)philo);
        ft_usleep(((struct s_info *)philo)->t_eat);
    }
    while (1) {
        eat((struct s_info *)philo);
        philo_sleep((struct s_info *)philo);
        philo_think((struct s_info *)philo);
    }
    return (NULL);
}
// err messages
static int error_manager(int code) {
    if (code == 1)
        printf("Error : Malloc error\n");
    else if (code == 2)
        printf("Error : Couldn't create a thread\n");
    return (0);
}

// Main 
int main(int argc, char **argv) {
    int i;
    t_philo *info;
    pthread_t *thread_id;


    info = (t_philo *)malloc(sizeof(t_philo));
    if (!info)
        return (error_manager(1));
    
    if (!parsing(argv, argc - 1, info))
        return (0);
    
    // pthread_t array allocation
    thread_id = (pthread_t *)malloc(info->n_philo * sizeof(pthread_t));
    if (!thread_id)
        return (error_manager(1));
    
    // init start time
    i = -1;
    info->start = ft_time();
    while (++i < info->n_philo) {
        info->philo[i].start = info->start;
        info->philo[i].last_meal = info->start;
        info->err = pthread_create(&thread_id[i], NULL, thread_routine, &info->philo[i]);
        if (info->err)
            return (error_manager(2));
    }
    
    // Freeing allocated memory for tid and running the monitor function
    free(thread_id);
    return (check_philos(info));
}
