#include <Keypad.h>
#include <Servo.h>

// Definisikan pin untuk servo
const int servoPin = 9;

// Buat objek servo
Servo lockServo;

// Definisikan keypad
const byte ROWS = 4; // empat baris
const byte COLS = 4; // empat kolom

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3}; // Sambungkan ke pin baris keypad
byte colPins[COLS] = {4, 5, 6, 7};     // Sambungkan ke pin kolom keypad

// Buat objek Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Set PIN yang benar
const String correctPIN = "1234"; // Ganti dengan PIN yang diinginkan
String inputPIN = "";

void setup() {
  lockServo.attach(servoPin);
  Serial.begin(9600);
  lock();  // Mulai dalam keadaan terkunci
  Serial.println("Sistem Kunci Pintar Siap");
  Serial.println("Masukkan PIN diikuti dengan # untuk membuka kunci");
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '#') {
      // Periksa PIN yang dimasukkan
      if (inputPIN == correctPIN) {
        Serial.println("PIN benar. Membuka kunci...");
        unlock();
      } else {
        Serial.println("PIN salah!");
        lock();
      }
      inputPIN = ""; // Hapus input setelah entri
    } else if (key == '*') {
      // Hapus input
      inputPIN = "";
      Serial.println("Input dibersihkan");
    } else {
      // Tambahkan tombol yang ditekan ke input
      inputPIN += key;
      Serial.print("*"); // Tampilkan input yang disembunyikan
    }
  }
}

// Fungsi untuk mengunci pintu
void lock() {
  lockServo.write(0);  // Anggap 0 adalah posisi terkunci
  Serial.println("Terkunci");
}

// Fungsi untuk membuka kunci pintu
void unlock() {
  lockServo.write(90); // Anggap 90 adalah posisi terbuka
  Serial.println("Terbuka");
}
