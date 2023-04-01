#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock { /* TODO: implement the structure */
   pthread_mutex_t mutex;
   pthread_cond_t cond;
   int type;
   int readerCount;
   int seq;
} pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_init(&(rw->mutex), NULL);
   pthread_cond_init(&(rw->cond), NULL);
   rw->type = 0;
   rw->readerCount = 0;
   rw->seq = 0;
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   
   pthread_mutex_lock(&(rw->mutex));
   while(rw->type == 1 || rw->readerCount > 1 ){
      // is writing or is more than 1 reader
      printf("Type %d, reader count %d", rw->type, rw->readerCount);
      pthread_cond_wait(&(rw->cond), &(rw->mutex));
   }
   rw->type = 1;
   
}


static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   
   rw->type = 0;
   rw->seq++;
   pthread_cond_broadcast(&(rw->cond));
   pthread_mutex_unlock(&(rw->mutex));
}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_lock(&(rw->mutex));
   while(rw->type != 0){// is writing
      pthread_cond_wait(&(rw->cond), &(rw->mutex));
   }
   rw->type = 0;
   rw->readerCount++;
   pthread_mutex_unlock(&(rw->mutex));

   return rw->seq;
}

static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_lock(&(rw->mutex));
   rw->type = 0;
   rw->readerCount--;
   pthread_cond_broadcast(&(rw->cond));
   pthread_mutex_unlock(&(rw->mutex));
   return rw->seq;
}

