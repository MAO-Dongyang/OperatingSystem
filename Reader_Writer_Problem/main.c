#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t wrt;
sem_t mutex;

int readcount = 0;
int i;

void *reader(void *arg) {
  sem_wait(&mutex);
  ++readcount;
  if (readcount == 1) {
    sem_wait(&wrt);
  }
  sem_post(&mutex);
  printf("reader is being performed - %d\n", readcount);
  sleep(1);
  sem_wait(&mutex);
  --readcount;
  if (readcount == 0) {
    sem_post(&wrt);
  }
  sem_post(&mutex);
}

void* writer(void* arg) {
  sem_wait(&wrt);
  printf("writing is being performed \n");
  sleep(1);
  sem_post(&wrt);
}

int main(int argc, char *argv[]) {
  pthread_t tid[2];
  sem_init(&mutex, 0, 1);
  sem_init(&wrt, 0, 1);
  pthread_create(&tid[0], NULL, writer, NULL);
  for(i=0;i<4;++i) {
    pthread_create(&tid[1], NULL, reader, NULL);
  }
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  sem_destroy(&mutex);
  sem_destroy(&wrt);
  return 0;
}
