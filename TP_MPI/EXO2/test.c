#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main()
{
char buf[4096];
char *tmp;
int r;
char * mess = "Message envoyé par ";
int rang=10;
sprintf(buf,"%s %d",mess, rang);
printf("buf = %s\n", buf);
sscanf(buf, "%s %d",&tmp, &r ); 
printf("le rang est %d\n", r);


}
