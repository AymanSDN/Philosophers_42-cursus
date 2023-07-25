#ifndef PHILO_H
#define PHILO_H

#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>
typedef struct s_data
{
    int id;
    long long start;
    long long last_meal;
    int n_meals;
    int t_eat;
    int t_sleep;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *sync;
} t_data;

typedef struct s_ph
{
    long long start;
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int meals;
    pthread_mutex_t *forks;
    pthread_mutex_t sync;
    t_data *data;
}   t_ph;


// typedef enum s_state
// {
//     fork,
//     eat,
//     sleep,
//     tink,
//     die
// } t_state;

int	ft_strlen(char *s);
int	ft_isdigit(int c);

int	ft_atoi(char *str);

int init_philosophers(t_ph *ph, int ac, char **args);

int create_philosophers(t_ph *ph, t_data *data);

int each_philo_init(t_ph *ph);

long long	ft_get_time();

#endif