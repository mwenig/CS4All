//used for simple integer output in range [0 - 99];

int* newLineBuffer;

void dumbITOA(int number);
void newLine();
void boxedThreadFork();
void boxedThreadFork1();

void newLine(){
  write(1, newLineBuffer, 1);
}

void boxedThreadFork(){
  int someTmp;
  int *moreTmp;

  moreTmp = malloc(12);
  someTmp = 22222;

  boxedThreadFork1();
}

void boxedThreadFork1(){
  int someTmp;
  int *moreTmp;

  moreTmp = malloc(10);
  someTmp = 88;

  forkThread();

  dumbITOA(someTmp);
  newLine();
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
  int id;
  int local;
  int *all;
  int *sub;

  newLineBuffer = malloc(12);
  *newLineBuffer = 10; //==newline
  *(newLineBuffer + 1) = ' ';

  newLine();

  local = 0;
  all = malloc(20);
  *all = 100;
  //forkThread();

  boxedThreadFork();

  sub = malloc(20);
  *sub = 40;

  local = local + 1;
  *all = *all + 1;
  *sub = *sub + 1;

  write(1, "local ", 6);
  dumbITOA(local);
  write(1, "sub ", 4);
  dumbITOA(*sub);
  write(1, "all ", 4);
  dumbITOA(*all);
  newLine();

  yield();

  forkThread();

  local = local + 1;
  *all = *all + 1;
  *sub = *sub + 1;

  write(1, "local ", 6);
  dumbITOA(local);
  write(1, "sub ", 4);
  dumbITOA(*sub);
  write(1, "all ", 4);
  dumbITOA(*all);
  newLine();
}