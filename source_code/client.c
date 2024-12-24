//클라이언트가 서버에 접속
//클라이언트는 서버가 보내온 목록을 보고 파일 하나를 선택
//클라이언트 프로그램이 실행중인 디렉토리에 동일한 이름으로 저장
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
#define CHAR_SIZE 256

typedef struct{
    char filename[CHAR_SIZE];
    unsigned long file_sz;
}pkt_t;

void error_handling(char *message);

int main(int argc, char *argv[]){
    int sd;
    FILE *fp;
    
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_adr;
    if(argc != 3){
        printf("Usage: %s <IP><port>\n", argv[0]);
        exit(1);
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if(sd == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");
   
    while(1){
        printf("------ File list from server ------ \n");
        int file_count;
        
        read(sd, &file_count, sizeof(file_count));
        for(int i = 0; i < file_count; i++ ){
            pkt_t recv_packet; 
            read(sd, &recv_packet, sizeof(pkt_t));
            printf("File Name: %s (Size: %lu bytes)\n", recv_packet.filename, recv_packet.file_sz);
        }

        char str[CHAR_SIZE];
        printf("\nEnter the file name (or Q to quit) >> ");
        scanf("%s", str);

        if(!strcmp(str, "Q") || !strcmp(str, "q")){
            printf("Bye!\n");
            close(sd);
            return 0;
        }
        write(sd, str, strlen(str) + 1);
        
        fp = fopen(str, "wb");
        while((read_cnt = read(sd, buf, BUF_SIZE)) > 0)
            fwrite((void*)buf, 1, read_cnt, fp);
        
        printf("Received file data successfully\n");
        fclose(fp);
    }
    close(sd);
    
    return 0;
}
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}