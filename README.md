# dining_philosophers

Решение проблемы обедающих философов. philo_one - потоки и мьютексы, philo_two - потоки и семафоры, philo_three - процессы и семафоры.

Собрать проект: make, 

Запустить программу: ./philo_* number_of_philosophers time_to_dietime_to_eat time_to_sleep \[number_of_times_each_philosopher_must_eat]

1. \* - номер философов
2. number_of_philosophers - количество философов
3. time_to_dietime_to_eat - время в милисекундах которое философы могут жить без еды
4. time_to_sleep - время в милисекундах, которое спят философы
5. number_of_times_each_philosopher_must_eat - опциональный аргумент, количество раз, сколько должен поесть каждый из философов, чтобы симуляция закончилась
