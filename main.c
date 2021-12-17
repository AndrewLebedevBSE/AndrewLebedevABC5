#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


struct hotel{
    int rub200;
    int rub400;
    int rub600;
};

struct hotel h = (struct hotel){.rub200 = 10, .rub400 = 10, .rub600 = 5};

pthread_mutex_t lock;
int money;

void* visitHotel(){
    pthread_mutex_lock(&lock);
    printf("Client %d came with %d RUB.\n", getpid(), money);

    if (money >= 600 && h.rub600 > 0){
        printf("Client has taken a place for 600 rub: room #%d\n", (11 - h.rub600));
        h.rub600--;
    } else if (money >= 400 && h.rub400 > 0){
        printf("Client has taken a place for 400 rub: room #%d\n", (11 - h.rub400));
        h.rub400--;
    } else if (money >= 200 && h.rub200 > 0){
        printf("Client has taken a place for 200 rub: room #%d\n", (11 - h.rub200));
        h.rub200--;
    } else printf("Client left the hotel.\n");
    printf("Hotel:\t600RUB rooms: %d, 400RUB rooms: %d, 200RUB rooms: %d\n",
           h.rub600, h.rub400, h.rub200);
    pthread_mutex_unlock(&lock);
    return 0;
}

int main() {
    printf("Enter number of possible guests:\n");
    int guests;
    scanf("%d", &guests);
    while (guests < 0){
        printf("Wrong number of guests!\nEnter number of possible guests:\n");
        scanf("%d", &guests);
    }
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < guests; ++i) {
        pthread_t t;
        money = rand() % 1000;
        int a = pthread_create(&t, NULL, &visitHotel, NULL);
        if (a != 0)
            printf("Cant create thread!\n");
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
