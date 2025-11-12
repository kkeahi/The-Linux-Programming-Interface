#include <pthread.h>
#include <stdio.h>

struct thread_args {
    float* array;
    int index;
};

void* func(void* args)
{
    struct thread_args* casted = (struct thread_args*)args;
    int r = casted->index;
    float volume = 4.0 / 3.0 * 3.141592 * r * r * r;
    casted->array[r] = volume;

    return NULL;
}

int main()
{
    float volumes[100];
    struct thread_args args[100];
    pthread_t threads[100];

    for (int r = 0; r < 100; ++r)
    {
        args[r].index = r;
        args[r].array = volumes;

        pthread_t thread = {0};
        pthread_create(&threads[r], NULL, func, (void *) &args[r]);
    }

    for (int i; i < 100; ++i)
    {
        void* retval;
        pthread_join(threads[i], &retval);
    }

    printf("The volume of sphere, r = 57 is %f\n", volumes[57]);

    return 0;
}
