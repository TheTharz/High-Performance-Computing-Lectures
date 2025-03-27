#include <pthread.h>
#include <stdio.h>

void* thread_function(void* arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_attr_t attr;
    size_t stack_size;

    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr, &stack_size);
    printf("Stack size: %zu bytes\n", stack_size);
    
    pthread_create(&thread, &attr, thread_function, NULL);
    pthread_join(thread, NULL);
    return 0;
}
