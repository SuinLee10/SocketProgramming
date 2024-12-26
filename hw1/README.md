# HW1(week1)
## TCP 기반 파일 다운로드 프로그램 구현 🚀

> **파일다운로드 프로그램** 클라이언트와 서버가 TCP 기반 소켓 연결을 사용하여 파일 목록과 정보를 write, read를 통해 소통할 수 있습니다. 
<hr>

### 기능 소개

### 1. 클라이언트가 서버에 접속 (TCP 이용)

- **설명:** 서버와 클라이언트는 서버의 포트 번호와 IP 를 통해 서버와 접속합니다.<br>
- **결과 화면:<br>**
<p>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/server_method.png" width = 80%><br>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/client_method.png" width = 80%><br>
</p>
<hr>

### 2. 서버 프로그램이 실행 중인 디렉토리의 모든 파일 목록을 클라이언트에게 전송

- **설명:** 서버와 클라이언트 소켓이 정상적으로 연결되면 서버는 클라이언트에게 실행 파일 디렉토리 내에 있는 파일 이름과 크기가 담긴 정보를 클라이언트에게 전달합니다.<br>
- **결과 화면:<br>**
<p>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/file_list_send.png" width = 80%><br>
</p>
<hr>

### 3. 클라이언트는 서버가 보내 온 목록을 보고 파일 하나를 선택

- **설명:** 클라이언트는 서버가 보낸 목록 중 한 파일을 선택하거나 Q(q)를 입력하여 프로그램을 종료할 수 있습니다.<br>
- **결과 화면:**<br>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/file_select_client.png" width = 80%><br>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/file_quit.png" width = 80%><br>
<hr>

### 4. 서버는 클라이언트가 선택한 파일을 클라이언트에게 전송

- **설명:** 서버는 클라이언트가 Q(q)를 입력하기 전까지 클라이언트가 선택한 파일 이름을 받고, 파일을 전송합니다. <br>
- **결과 화면:**<br>
  <p>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/server_get_filename.png" width = 80%><br>
<hr>

### 5. 전송된 파일은 클라이언트 프로그램이 실행 중인 디렉토리에 동일한 이름으로 저장됨.

- **설명:** 실행 중인 디렉토리에 파일이 정상적으로 저장되고 클라이언트는 감사의 메시지를 서버에 전송합니다. 
    - **결과 화면:**<br>
    <img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/sended_clnt.png" width = 80%><br>
<hr>

### 6. (2~5) 과정 반복
- **설명:** 클라이언트가 나가기(Q) 를 선택하기 전까지 위의 과정을 반복합니다.
- **결과 화면:**<br>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/server_result.png" width = 80%><br>
<img src="https://github.com/SuinLee10/SocketProgramming/blob/master/hw1/hw1_result_img/client_result.png" width = 80%><br>
  <br><hr>

