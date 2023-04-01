#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock { /* TODO: implement the structure */
   pthread_mutex_t wrlock;
   pthread_cond_t cond;
   int type;
   int noReader;
} pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_init(rw->wrlock);
   pthread_cond_init(rw->cond);
   rw->type = 0;
   rw->noReader = 0;
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   if(rw->type == 0 && rw->noReader == 0 ){
      rw->type = 1;
      pthread_mutex_lock(rw->wrlock);
   }
   else{
   }
}


static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */

    return 0;
}

static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */

    return 0;
}

