# Philosophers

A simulation of the dining philosophers problem using pthreads in C:
- simulates philosophers sitting at a table, thinking, eating, and sleeping
- each philosopher needs two forks to eat. forks are shared with neighbors
- the program avoids deadlocks and starvation using mutexes and careful fork handling

## Build and usage

Build the project:

    cd philo
    make

Run the simulation:

    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

- `number_of_philosophers`: how many philosophers (and forks) at the table (1–200)
- `time_to_die`: time in ms before a philosopher dies if they don't eat
- `time_to_eat`: time in ms a philosopher spends eating
- `time_to_sleep`: time in ms a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): simulation ends when each philosopher has eaten this many times

For example:

    ./philo 5 800 200 200
