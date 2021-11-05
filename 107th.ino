#define YEAR 107
int button = 14;
boolean button_state = false; // button 상태
unsigned long time_previous, time_current; 
int current_number = 0;
bool btn_current, btn_previous = false;

// 0에서 9까지 숫자 표현을 위한
// 세그먼트 a, b, c, d, e, f, g, dp의 패턴
byte patterns[] = {
  0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6
};
int digit_select_pin[] = {66, 67, 68, 69}; // 자릿수 선택 핀
// 7세그먼트 모듈 연결 핀 ‘a, b, c, d, e, f, g, dp’ 순서
int segment_pin[] = {58, 59, 60, 61, 62, 63, 64, 65};
int count = 0;
int SEGMENT_DELAY = 5; // 숫자 표시 사이의 시간 간격

void setup(){
  for (int i = 0; i < 4; i++) { // 자릿수 선택 핀을 출력으로 설정
    pinMode(digit_select_pin[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) { // 세그먼트 제어 핀을 출력으로 설정
    pinMode(segment_pin[i], OUTPUT);
  }
  time_previous = millis(); // 시작시간
  Serial.begin(9600);
}

// 해당 자리에 숫자 하나를 표시하는 함수
void show_digit(int pos, int number) { // (위치, 출력할 숫자)
  for (int i = 0; i < 4; i++) {
    if (i + 1 == pos) // 해당 자릿수의 선택 핀만 LOW로 설정
      digitalWrite(digit_select_pin[i], LOW);
    else // 나머지 자리는 HIGH로 설정
      digitalWrite(digit_select_pin[i], HIGH);
  }
  for (int i = 0; i < 8; i++) {
    boolean on_off = bitRead(patterns[number], 7 - i);
    digitalWrite(segment_pin[i], on_off);
  }
}

// 4자리 7세그먼트 표시 장치에 4자리 숫자를 표시하는 함수
void show_4_digit(int number) {
  number = number % 10000; // 4자리로 제한
  int thousands = number / 1000; // 천 자리
  number = number % 1000;
  int hundreads = number / 100; // 백 자리
  number = number % 100;
  int tens = number / 10; // 십 자리
  int ones = number % 10; // 일 자리
  show_digit(1, thousands);
  delay(SEGMENT_DELAY);
  show_digit(2, hundreads);
  delay(SEGMENT_DELAY);
  show_digit(3, tens);
  delay(SEGMENT_DELAY);
  show_digit(4, ones);
  delay(SEGMENT_DELAY);
}

void loop(){
  time_current = millis(); // 현재시간
  current_number = time_current - time_previous; // 0 ~ 9999
  show_4_digit(current_number);
  if(current_number > 999){
    time_previous = time_current;
  }
  // 버튼 눌렸을 때
  btn_current = digitalRead(button);
  // Serial.print(btn_current);
  if(btn_current){
    Serial.print("prev : ");
    Serial.println(time_previous);
    Serial.print("current : ");
    Serial.println(time_current);
    int loop_time = time_current;    
    if(btn_previous == false){
      Serial.println(loop_time);
      Serial.println("버튼 눌림");
      btn_previous = true;      
      while(true){
        loop_time = millis();
        show_4_digit(current_number);
        if(loop_time - time_current > 3000){ break;}
      }
    }
    delay(50);
  }else{
    btn_previous = false;
  }
}
