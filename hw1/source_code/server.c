//TCP이용
//서버프로그램이 실행중인 디렉토리의 모든 파일 목록(파일 이름, 파일 크기)을 클라이언트에게 전송
//서버는 클라이언트가 선택한 파일을 클라이언트에게 전송
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUF_SIZE 30

typedef struct{
    char filename[256];
    unsigned long file_sz;
}pkt_t;

void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sd, clnt_sd;
    char buf[BUF_SIZE];
    char clnt_request[BUF_SIZE];
    int read_cnt;
    DIR *dir;
    struct dirent *entry;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    //소켓 연결
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sd == -1) 
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    if(listen(serv_sd, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    if(clnt_sd == -1)
        error_handling("accept() error");
    
    while(1){
        //file 이름 크기 리스트에 담기
        dir = opendir(".");
        if(!dir){
            error_handling("opendir() error");
            exit(1);
        }

        int file_count = 0; 
        pkt_t * packet = NULL;
        while((entry = readdir(dir)) != NULL){
            if(entry->d_name[0] == '.')
                continue;

            packet = realloc(packet, sizeof(pkt_t)*(file_count + 1));
            //using packet 
            pkt_t *send_pkt = &packet[file_count];
            memset(send_pkt, 0, sizeof(pkt_t));
            strncpy(send_pkt->filename, entry->d_name, sizeof(send_pkt->filename)-1);
        
            struct stat file_info;
            stat(entry->d_name, &file_info);
            send_pkt->file_sz = file_info.st_size;

            file_count++;
        }
        closedir(dir);

        //파일 총 갯수 보내기
        write(clnt_sd, &file_count, sizeof(file_count));

        printf("========================\n");
        //파일 이름 사이즈 struct 단위로 보내기 
        for(int i = 0; i < file_count; i++){
            write(clnt_sd, &packet[i], sizeof(pkt_t));  
            printf("Sending File Information: %s (size: %lu bytes)\n", packet[i].filename, packet[i].file_sz);
        }
        printf("========================\n");

        //클라이언트에서 요청한 파일 이름 읽기
        read(clnt_sd, clnt_request, BUF_SIZE);
        int send_file_sz;
        struct stat send_info;
        stat(clnt_request, &send_info);
        send_file_sz = send_info.st_size;
        
        write(clnt_sd, &send_file_sz, sizeof(send_file_sz));

        if(!strcmp(clnt_request, "Q") || !strcmp(clnt_request, "q")){
            printf("Bye!\n");
            free(packet);
            close(clnt_sd);
            close(serv_sd);
            return 0;
        }
        
        printf("Request file name from client: %s\n", clnt_request);

        //해당 파일 전송
        FILE *fp;
        fp = fopen(clnt_request, "rb");

        while(1){
            read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
            if(read_cnt < BUF_SIZE){
                write(clnt_sd, buf, read_cnt);
                break;
            }write(clnt_sd, buf, BUF_SIZE);
        }
        printf("\nSended File %s successfully!!\n", clnt_request);
        
        read(clnt_sd, buf, BUF_SIZE);
        printf("Message from client: %s\n", buf);

        fclose(fp);
        free(packet);
    }

    close(clnt_sd);
    close(serv_sd);

    return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}