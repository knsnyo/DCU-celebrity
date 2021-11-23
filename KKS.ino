#define YEAR 107
#define MS 33
#define SLOT 100
#define FEVER 10000

int segment1[4] = {2, 3, 4, 5}; // 1자리
int segment2[4] = {6, 7, 8, 9}; // 10자리
int segment3[4] = {10, 11, 12, 13}; // 100자리

int button = 14;

int menu = 0;
int toggle_menu1 = 15;
int toggle_menu2 = 16;
int toggle_menu3 = 17;

int count = 0; // 나타낼 숫자
int i = 0;

bool btn_current, btn_previous = false;

unsigned long time_previous, time_current; // 시간 확인
unsigned long time_loop;

void setup() {
  // 핀모드 OUTPUT 설정
  for (int i = 0; i < 4; i++) {
    pinMode(segment1[i], OUTPUT);
    pinMode(segment2[i], OUTPUT);
    pinMode(segment3[i], OUTPUT);
  }
  //Serial.begin(9600);
}

void count_number() {
  time_previous = millis();
  while (true) {
    if (digitalRead(button)) {
      //Serial.println(String(i++) + "count_time()");
      delay(1000);
      break;
    }
    // 숫자 돌리기
    time_current = millis();
    if (MS <= time_current - time_previous) {
      time_previous = time_current;
      count += 1;
    }
    if (999 < count) {
      count = 0;
    }
    show_number(count);
  }
}

void show_number(int count) {
  int num3 = count / 100 % 10;
  int num2 = count / 10 % 10;
  int num1 = count % 10;
  for (int i = 0; i < 4; i += 1) {
    digitalWrite(segment1[i], num1 & (0x1 << i));
    digitalWrite(segment2[i], num2 & (0x1 << i));
    digitalWrite(segment3[i], num3 & (0x1 << i));
  }
}

void show_number1(int count){
  for (int i = 0; i < 4; i += 1) {
    digitalWrite(segment1[i], count & (0x1 << i));
  }
}

void show_number2(int count){
  for (int i = 0; i < 4; i += 1) {
    digitalWrite(segment2[i], count & (0x1 << i));
  }
}

void show_number3(int count){
  for (int i = 0; i < 4; i += 1) {
    digitalWrite(segment3[i], count & (0x1 << i));
  }
}

void show_void(int count){
  show_number1(count);
  show_number2(count);
  show_number3(count);
}

void show_result_number(int number) {
  time_previous = millis();
  while (true) {
    time_current = millis();
    // 3초 반복
    time_loop = time_current - time_previous;
    if (3000 <= time_loop) {
      break;
    }
    if (YEAR == number) {
      if (500 > time_loop) {
        show_number(number);
      } else if (1000 > time_loop) {
        show_void(15);
      } else if (1500 > time_loop) {
        show_number(number);
      } else if (2000 > time_loop) {
        show_void(15);
      } else if (2500 > time_loop) {
        show_number(number);
      } else {
        show_void(15);
      }
    } else {
      show_number(number);
    }
  }
}

void game1() {
  //Serial.println(String(i) + "game1()");
  delay(500);
  count_number();
  show_result_number(count);
}

void game2(){
  int result1, result2, result3;
  //Serial.println(String(i) + "game2()");
  time_previous = millis();
  while(true){
    show_number3(count);
    time_current = millis();
    if (SLOT <= time_current - time_previous) {
      time_previous = time_current;
      count += 1;
    }
    if (9 < count) {
      count = 0;
    }
    if(digitalRead(button)){
      result3 = count;
      break;
    }
  }
  delay(500);
  while(true){
    show_number2(count);
    time_current = millis();
    if (SLOT <= time_current - time_previous) {
      time_previous = time_current;
      count += 1;
    }
    if (9 < count) {
      count = 0;
    }
    if(digitalRead(button)){
      result2 = count;
      delay(50);
      break;
    }
  }
  delay(500);
  while(true){
    show_number1(count);
    time_current = millis();
    if (SLOT <= time_current - time_previous) {
      time_previous = time_current;
      count += 1;
    }
    if (9 < count) {
      count = 0;
    }
    if(digitalRead(button)){
      result1 = count;
      delay(50);
      break;
    }
  }
  delay(500);
  int result = 100 * result3 + 10 * result2 + result1;
  show_result_number(result);
}

void game3() {
  //Serial.println(String(i) + "game3()");
  time_previous = millis();
  while (true) {
    time_current = millis();
    if(FEVER <= time_current - time_previous){
      show_result_number(count);
      break;
    }
    if (YEAR == count) {
      show_result_number(count);
      break;
    }
    show_number(count);
    btn_current = digitalRead(button);
    if (btn_current) {
      if (false == btn_previous) {
        btn_previous = true;
         count += 1;
        //count = 107;
      }
      delay(10);
    } else {
      btn_previous = false;
    }
  }
}

void loop() {
  bool menu1 = digitalRead(toggle_menu1); // 0 = ON / 1 = OFF
  bool menu2 = digitalRead(toggle_menu2); // 0 = ON / 1 = OFF
  bool menu3 = digitalRead(toggle_menu3); // 0 = ON / 1 = OFF
  //Serial.println(menu3);
  if (0 == menu1) {
    menu = 1;
    show_number(1);
  } else if (0 == menu2) {
    menu = 2;
    show_number(2);
  }else if (0 == menu3){
    menu = 3;
    show_number(3);
  }else {
    show_number(0);
    menu = 0;
  }
  if(digitalRead(button)) {
    show_void(15);
    //Serial.println("button click");
    delay(1000);
    if (1 == menu) {
      game1();
    } else if (2 == menu) {
      game2();
    }else if (3 == menu){
      game3();
    }
  }
  /*
    count_number();
    show_result_number(count);
  */
  //game1();
  //game3();
  count = 0;
}
