#define YEAR 107
#define MS 20

int segment1[4] = {2, 3, 4, 5}; // 1자리
int segment2[4] = {6, 7, 8, 9}; // 10자리
int segment3[4] = {10, 11, 12, 14}; // 100자리

int count = 0; // 나타낼 숫자

unsigned long time_previous, time_current; // 시간 확인
unsigned long time_loop;

void setup() {
  // 핀모드 OUTPUT 설정
  for (int i = 0; i < 4; i++){
    pinMode(segment1[i], OUTPUT);
    pinMode(segment2[i], OUTPUT);
    pinMode(segment3[i], OUTPUT);
  }
}

void show_number(){
  time_previous = millis();
  while (true) {
    // 숫자 돌리기
    time_current = millis();
    if (MS <= time_current - time_previous) {
      time_previous = time_current;
      count += 1;
    }
    if (999 < count) {
      count = 0;
    }
    int num1 = count / 100;
    int num2 = count / 10 % 10;
    int num3 = count % 10;
    for(int i = 0; i < 4; i += 1){
      digitalWrite(segment1[i], num1 & (0x1 << i));
      digitalWrite(segment2[i], num2 & (0x1 << i));
      digitalWrite(segment3[i], num3 & (0x1 << i));
    } 
  }
}

void loop() {
  show_number();
}


  /*
  // i : 0~9까지 숫자
  for (int i = 0; i < 10; i++) {
    // j : 0~3, A,B,C,D 핀
    for (int j = 0; j < 4; j++) {
      // A핀 0번째 비트
      // B핀 1번째 비트
      // C핀 2번째 비트
      // D핀 3번째 비트
      // 0x8은 1000(2) 이진수로 3번째 비트만 켜진 상태
      // X >> Y 연산은 숫자 X를 오른쪽으로 Y번 비트 시프트
      // ex) 8 >> 3은 이진수 1000이 3번 비트 시프트 0001으로 출력
      // j == 0, (0x1 << 0) == 0x1 (1)
      // j == 1, (0x1 << 1) == 0x2 (2)
      // j == 2, (0x1 << 2) == 0x4 (4)
      // j == 3, (0x1 << 3) == 0x8 (8)
      // i는 이진법으로 저장되어 있으므로
      // 위의 shift 결과와 and 연산을 통해 1,0 여부를 확인
      digitalWrite(segment[j], i & (0x1 << j));
    }
    delay(1000);
  }
  */  
