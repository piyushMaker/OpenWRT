#include <stdio.h>
#include <time.h>
#include <unistd.h> 
int main()
{
while(1){
   time_t T= time(NULL);
    struct  tm tm = *localtime(&T);
   

   printf("System Date is: %02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    printf("System Time is: %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
 
sleep(2);	
}
}
