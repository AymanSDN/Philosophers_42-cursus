#include "philo.h"

int main(int ac, char **av)
{
    t_ph *ph = (t_ph *)malloc(sizeof(t_ph));
    t_data *data = (t_data *)malloc(sizeof(t_data));

    if(ac == 5 || ac == 6)
    {
        init_philosophers(ph, ac, av);
        each_philo_init(ph);
        create_philosophers(ph, data);
    }
    return(1);
}
