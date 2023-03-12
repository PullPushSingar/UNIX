#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>






int main()
{
    char buf[5],polecenie[5];
    int status,child = 0;
    while(1)
    {
        printf("Podaj polecenie do wykonania [d,s,x,e,q]:\n");
        fgets(buf,sizeof(buf),stdin);
        sscanf(buf, "%s", polecenie);
        if (polecenie[0] != 'q')
        {
                if((child =  fork()) == 0)
                {
                        printf("Tu potomek pid=%d\n", getpid());
                        switch (polecenie[0])
                        {
                                case 'd' :
                                        execlp("date", "date",NULL);
                                        break;
                                case 's' :
                                        execlp("sh", "sh",NULL);
                                        break;
                                case 'x' :
                                        execlp("xclock", "xclock", "-update", "1",NULL);
                                        break;
                                case 'e' :
                                        system("x=`zenity --file-selection`; xedit $x");
                                        break;
                                default :
                                        printf("Wpisano zla litere:\n");
                                        break;
                        }

                        exit(0);
                }

        }
        if ((buf[0] == 's') || (buf[0] == 'd'))
        {
                waitpid(child,&status,0);
        }
        while(1)
        {
                child = waitpid(0,NULL,WNOHANG);
                if (child <= 0)
                {
                        break;
                }

        }
        switch (polecenie[0])
        {
                case 'q':
                        return 0;
                break;
        }
    }
}