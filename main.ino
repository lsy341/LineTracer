#define IR2 A2   // 센서 2: 좌측 감지
#define IR4 A4   // 센서 4: 우측 감지
#define STBY 9   //모터드라이버 스탠바이 핀
#define AIN1 5
#define AIN2 6
#define PWMA 10
#define BIN1 7
#define BIN2 8
#define PWMB 11

const int threshold = 590; // 검정색 인식 임계값 (1주차에 여러분들이 찾은 센서값으로 변경)

void setup() {
//setup() 부분에 여러분들이 사용할 pinMode와 모터드라이버 활성화를 시켜주세요.
    pinMode(STBY, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);
    Serial.begin(9600);
}

void loop() {
  int IR2value = analogRead(IR2);
  int IR4value = analogRead(IR4);

  Serial.print("IR2value : ");
  Serial.println(IR2value);
  Serial.print("IR4value : ");
  Serial.println(IR4value);
  Serial.println("");


  //IR4만 검정이면 좌회전
  if (IR4value <= threshold && IR2value > threshold) {
    turn_left();
  }
  // IR2만 검정이면 우회전 
  else if (IR2value <= threshold && IR4value > threshold) {
    turn_right();
  }
  // 그 외의 경우 직진
  else {
    go_Motors();
  }
}

void turn_right(){ // 라인트레이서가 멈추는 함수를 지정합니다.
  // 좌회전을 위한 모터 제어 코드 삽입 (PWM50, PWM10 권장)
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 50);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 10);
}


void turn_left(){ // 라인트레이서가 멈추는 함수를 지정합니다.
  // 우회전을 위한 모터 제어 코드 삽입 (PWM50, PWM10 권장)
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 10);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 50);
}



void go_Motors(){ // 라인트레이서가 직진하는 함수를 지정합니다.
  //앞으로 직진하는 명령을 작성해주세요. (방향은 다를 수 있음 - HIGH, LOW 순서바꾸기)
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 100);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, 100);
}
