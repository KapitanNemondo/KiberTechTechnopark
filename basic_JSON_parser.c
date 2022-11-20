#include <stdio.h>

#define DEV_VERSION

//#define DEBUG_CASOS

#define JSON_MAX_LEN 100

#define COMAND_ERROR -1
#define COMAND_STOP 0
#define COMAND_FORWARD 1
#define COMAND_BACKWARD 2
#define COMAND_LEFT 3
#define COMAND_RIGHT 4

char jsonBuf[JSON_MAX_LEN];

char* strFind (char* str, char* subStr){
    int subStrLen = 0;
    int curChar;
    while (subStr[subStrLen]!=0)
    {
        subStrLen++;
    }
    
    
    while (*str != 0)
    {
        if (*str==*subStr)
        {
            curChar=1;
            str++;
            while (curChar<subStrLen && *str != 0)
            {
                if (*str != subStr[curChar])
                {
                    break;
                }
                str++;
                curChar++;
            }
            if (curChar == subStrLen)
            {
                return str-subStrLen;
            }
            
        }
        str++;
    }
    return NULL;    
}

int parseComand(char* inStr, int* comand, float* time)
{
    char comandStr[]="cmd";
    char valStr[]="val";
    char* buf;
    buf = strFind(inStr,comandStr);
    if (buf==NULL) return -1;
    buf +=(3+3);

    #ifdef DEV_VERSION
    printf("%c\n",*buf);
    #endif
    

    switch (*buf)
    {
    case 's':
        *comand=COMAND_STOP;
        return 0;
        break;
    case 'f':
        *comand=COMAND_FORWARD;
        break;
    case 'b':
        *comand=COMAND_BACKWARD;
        break;
    case 'l':
        *comand=COMAND_LEFT;
        break;
    case 'r':
        *comand=COMAND_RIGHT;
        break;
    default:
        *comand=COMAND_ERROR;
        return -1;
        break;
    }
    
    buf = strFind(inStr,valStr);
    if (buf==NULL) return -1;
    buf +=(3+3);

    #ifdef DEV_VERSION
    printf("%c\n",*buf);
    #endif

    float ret=0;
    while (*buf!='.')
    {
        ret*=10;
        ret+=*buf-'0';
        buf++;
    }
    buf++;
    float tmp=1;
    while (*buf!='\"')
    {
        tmp/=10;
        ret+=(*buf-'0')*tmp;
        buf++;
    }
    *time=ret;
    #ifdef DEV_VERSION
    printf("%f",ret);
    #endif

    #ifdef DEBUG_CASOS
    fprintf(stderr,"com:%d val:%f",*comand,ret);
    #endif

    return 0;
}

int main(){
    printf("hi\n");
    char testStr[]="{\"cmod\":\"forward\", \"val\":\"15.05\"}";
    int com;
    float time;
    int res;
    res = parseComand(testStr, &com, &time);
    #ifdef DEV_VERSION
    printf("%d",res);
    #endif
    return res;
}
