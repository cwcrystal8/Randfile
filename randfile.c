#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int check(int n, char * str){
  if(n == -1){
    printf("%s() return value: %s\n", str, strerror(errno));
    return 0;
  }
  return 1;
}

int generate_random(){
  int buf[1];

  int file_descriptor = open("/dev/random", O_RDONLY);

  int return_value = read(file_descriptor, buf, 4);
  int check_one = check(return_value, "read");

  return_value = close(file_descriptor);
  int check_two = check(return_value, "close");

  if(check_one && check_two){
    printf("%d\n", *buf);
    return *buf;
  }
  printf("Error generating random number\n");
}

int main(){

  printf("Generating random numbers:\n");
  int ary[10], i;
  for(i = 0; i < 10; i++){
    printf("\trandom %d: ", i);
    ary[i] = generate_random();
  }

  printf("Writing numbers to file...\n");
  int file_descriptor, return_value, *inc = ary;
  file_descriptor = open("newfile.txt", O_CREAT | O_WRONLY, 0777);
  return_value = write(file_descriptor, ary, sizeof(int) * 10);
  check(return_value, "write");
  return_value = close(file_descriptor);
  check(return_value, "close");

  printf("\nReading numbers from file...\n");
  file_descriptor = open("newfile.txt", O_RDONLY);
  int ary_two[10];
  return_value = read(file_descriptor, ary_two, sizeof(int) * 10);
  printf("\nVerification that written values were the same:\n");
  for(i = 0; i < 10; i++){
    printf("\trandom %d: %d\n", i, ary_two[i]);
  }
}
