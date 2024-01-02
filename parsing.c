#include "philo.h"

// error messages based on error codes and arguments
static int err_message(int code, int args_num) {
    if (!code)
        printf("Error : Incorrect number of arguments (expected 4) got %d\n", args_num);
    else if (code == 1) {
        printf("Error : All arguments must be numbers.\n");
        printf("Format : n_philoophers t_die t_eat t_sleep [number_of_times_each_philosopher_must_eat]\n");
    } else if (code == 2)
        printf("Error : None of the parameters can be less or equal to 0\n");
    else if (code == 3)
        printf("Error : Malloc error\n");
    return (0);
}


static int ft_isdigit(int c) {
    return (c >= '0' && c <= '9');
}

// init data for philos
static void initialise_data(t_philo *target) {
    int i;

    i = -1;
    while (++i < target->n_philo)
        pthread_mutex_init(&target->forks[i], NULL);
    pthread_mutex_init(&target->sync, NULL);
    i = -1;
    while (++i < target->n_philo) {
        target->philo[i].id = i + 1;
        if (!i)
            target->philo[i].left_fork = &target->forks[target->n_philo - 1];
        else
            target->philo[i].left_fork = &target->forks[i - 1];
        target->philo[i].right_fork = &target->forks[i];
        target->philo[i].sync = &target->sync;
        target->philo[i].t_eat = target->t_eat;
        target->philo[i].t_sleep = target->t_sleep;
        target->philo[i].last_meal = 0;
        target->philo[i].eating_time = 0;
    }
}

// load info into struct from  arguments
static void load_info_to_struct(char **args, t_philo *target) {
    target->n_philo = ft_atoi(args[0]);
    target->t_die = ft_atoi(args[1]);
    target->t_eat = ft_atoi(args[2]);
    target->t_sleep = ft_atoi(args[3]);
    if (args[4]) {
        target->nbr_meals = ft_atoi(args[4]);
        target->philo_eaft_time = TRUE;
    } else {
        target->nbr_meals = 1;
        target->philo_eaft_time = FALSE;
    }
    target->forks = (pthread_mutex_t *)malloc(target->n_philo * sizeof(pthread_mutex_t));
    target->philo = (struct s_info *)malloc(target->n_philo * sizeof(struct s_info));
    if (!target->forks || !target->philo)
        return;
    initialise_data(target);
}

// Function to parse arguments and init struct
int parsing(char **args, int args_num, t_philo *target) {
    int i;
    int j;

    if (args_num < 4 || args_num > 5)
        return (err_message(0, args_num));
    i = 0;
    while (++i < args_num + 1) {
        j = -1;
        while (args[i][++j])
            if (!ft_isdigit(args[i][j]))
                return (err_message(1, 0));
    }
    load_info_to_struct(args + 1, target);
    if (target->nbr_meals <= 0 || target->n_philo <= 0 ||
        target->t_die <= 0 || target->t_eat <= 0 || target->t_sleep <= 0)
        return (err_message(2, 0));
    if (!target->forks || !target->philo)
        return (err_message(3, 0));
    return (1);
}
