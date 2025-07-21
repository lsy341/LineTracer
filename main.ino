#define AIN2 6
#define PWMA 10
#define BIN1 7
#define BIN2 8
#define PWMB 11

const int threshold = 700;  // 검은색 인식 임계값
int baseSpeed = 200;        // 기본 속도
int minSpeed = 10;          // 최소 속도 보장

// PID 변수 설정
float Kp = 60.0;  // 에러값에 비례, 속력을 바꾸는 메인임
float Ki = 0.3;  // 이전 에러와 현재 에러의 차이에 비례, 변화를 추구
float Kd = 2.5;  // 변화에 저항

int lastError = 0;  // 이전 오차
int integral = 0;   // 적분값

void setup() {
  ADCSRA = (ADCSRA & B11111000) | 0x04;
    pinMode(STBY, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    digitalWrite(STBY, HIGH);
    Serial.begin(115200);
}

// 가중 평균을 사용한 error 계산 함수
int getError() {
    int weights[7] = {-3, -2, -1, 0, 1, 2, 3};  // 센서 위치에 따른 가중치
    int sumWeights = 0;
    int sumValues = 0;

    int sensorValues[7] = {
        analogRead(IR1),
        analogRead(IR2),
        analogRead(IR3),
        analogRead(IR4),
        analogRead(IR5),
        analogRead(IR6),
        analogRead(IR7)
    };

    for (int i = 0; i < 7; i++) {
        if (sensorValues[i] < threshold) {  // 검은색 감지 시
            sumWeights += weights[i];
            sumValues++;
        }
    }

    if (sumValues == 0) return lastError;  // 검은색을 감지하지 못하면 마지막 오차 유지

    return sumWeights / sumValues;
}

void loop() {
    int error = getError();  // 가중 평균 기반 오차 계산

    // PID 제어 계산
    integral += error;
    int derivative = error - lastError;
    int correction = Kp * error + Ki * integral + Kd * derivative;

    lastError = error;
    Serial.println(error);

    // PID 보정된 속도
    int leftSpeed = constrain(baseSpeed + correction, minSpeed, 255);
    int rightSpeed = constrain(baseSpeed - correction, minSpeed, 255);

    driveMotors(leftSpeed, rightSpeed);

    delay(50);
  
}

// 모터 제어 함수 (코드 간소화)
void driveMotors(int leftSpeed, int rightSpeed) {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, leftSpeed);

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, rightSpeed);
}
