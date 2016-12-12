
int sum;

void testA();
void testB();
void testC();
void testD();

int main(int argc, int *argv) {
    //testA();
    //testB();
    //testC();
    testD();
}

// with locking, the sum variable is incremented correctly
void testA() {
    int tmp;

    forkThread();
    forkThread();

    sum = 0;

    lock();
    tmp = sum;
    // schedule other thread
    yield();
    tmp = tmp + 1;
    sum = tmp;
    unlock();

    output(sum);

}

// without locking, the sum variable is not incremented correctly
void testB() {
    int tmp;

    forkThread();
    forkThread();

    sum = 0;

    tmp = sum;
    yield();
    tmp = tmp + 1;
    sum = tmp;

    output(sum);
}

void testC() {
    int tid;
    int i;

    tid = forkThread();

    lock();
    // if we are the "parent" of the new thread, we do some work. The new thread is blocked until the parent
    // is done and releases the lock, i.e., it cannot make progress during that time.
    // if the new thread is scheduled first after its creation however, it can aquire the lock, release it again and terminate.
    if (tid != 0) {
        i = 0;
        while (i < 1000000) {
            i = i + 1;
        }
    }
    unlock();

    // output the tid of both threads
    output(get_tid());
}
