
int sum;
int *newLineBuffer;

void testA();

void testB();

void testC();

void dumbITOA(int number);

void newLine();

void newLine() {
  write(1, newLineBuffer, 1);
}


void dumbITOA(int number) {
  int i;
  int *buff;
  int tmp;
  int all;
  int div;
  all = 0;
  div = 100;
  tmp = number;
  buff = malloc(50);

  while (div != 0) {
    *(buff + all) = (tmp / div) + 48;
    tmp = tmp % div;
    div = div / 10;
    all = all + 1;
  }
  //*(buff + all) = ' ';
  write(1, buff, 10);
}

int main(int argc, int *argv) {

  newLineBuffer = malloc(12);
  *newLineBuffer = 10; //==newline
  *(newLineBuffer + 1) = ' ';

  write(1, "Start    ", 8);
  newLine();

  testA();
  //testB();
  //testC();
  //testD();
}

// with locking, the sum variable is incremented correctly
void testA() {
  int tmp;
  write(1, "TestA", 8);
  newLine();

  forkThread();
  forkThread();

  sum = 0;

  lock();

  yield();
  tmp = sum;
  // schedule other thread
  yield();

  tmp = tmp + 1;

  yield();

  sum = tmp;

  write(1, "+1 ascending number: ", 21);
  dumbITOA(sum);
  newLine();

  yield();

  unlock();

  yield();

  write(1, "sum: ", 5);
  dumbITOA(sum);
  newLine();
}

// without locking, the sum variable is not incremented correctly
void testB() {
  int tmp;

  write(1, "TestB", 8);
  newLine();

  forkThread();
  forkThread();

  sum = 0;

  tmp = sum;
  yield();
  tmp = tmp + 1;
  sum = tmp;

  dumbITOA(sum);
}

void testC() {
  int tid;
  int i;
  write(1, "TestC", 8);
  newLine();

  forkThread();

  tid = get_tid();

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

  tid = get_tid();

  // output the tid of both threads
  dumbITOA(tid);
}
