#include <pthread.h>

struct rwlock {
    pthread_mutex_t lock;
    pthread_cond_t read;
    pthread_cond_t write;
    unsigned readers;
    unsigned writers;
    unsigned read_waiters;
    unsigned write_waiters;
};

void reader_lock(struct rwlock *self) {
    pthread_mutex_lock(&self->lock);
    if(self->writers || self->write_waiters) {
        self->read_waiters++;
        do {
            pthread_cond_wait(&self->read, &self->lock);
        } while(self->writers || self->write_waiters);
        self->read_waiters--;
    }
    self->readers++;
    pthread_mutex_unlock(&self->lock);
}

void reader_unlock(struct rwlock *self) {
    pthread_mutex_lock(&self->lock);
    self->readers--;
    if(self->write_waiters) {
        pthread_cond_signal(&self->write);
    }
    pthread_mutex_unlock(&self->lock);
}

void writer_lock(struct rwlock *self) {
    pthread_mutex_lock(&self->lock);
    if(self->readers || self->writers) {
        self->write_waiters++;
        do {
            pthread_cond_wait(&self->write, &self->lock);
        } while(self->readers || self->writers);
        self->write_waiters--;
    }
    self->writers = 1;
    pthread_mutex_unlock(&self->lock);
}

void writer_unlock(struct rwlock *self) {
    pthread_mutex_lock(&self->lock);
    self->writers = 0;
    if(self->write_waiters) {
        pthread_cond_signal(&self->write);
    } else if(self->read_waiters) {
        pthread_cond_broadcast(&self->read);
    }
    pthread_mutex_unlock(&self->lock);
}

void rwlock_init(struct rwlock *self) {
    self->readers = 0;
    self->writers = 0;
    self->read_waiters = 0;
    self->write_waiters = 0;
    pthread_mutex_init(&self->lock, NULL);
    pthread_cond_init(&self->read, NULL);
    pthread_cond_init(&self->write, NULL);
}
