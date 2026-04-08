// Definisi Pin
const int pinSensor = A0;
const int pinRelay  = 8;
const int pinLED    = 2;

// Kalibrasi (Ubah angka ini berdasarkan hasil Serial Monitor kamu)
const int NILAI_KERING = 1000; // Nilai saat sensor di udara/tanah kering
const int NILAI_BASAH  = 300;  // Nilai saat sensor di tanah basah/air

// Ambang Batas dalam Persen
int batasSiramPersen = 30; // Pompa nyala jika kelembapan di bawah 30%

void setup() {
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLED, OUTPUT);
  pinMode(pinSensor, INPUT);
  
  digitalWrite(pinRelay, HIGH); // Matikan pompa di awal
  digitalWrite(pinLED, LOW);
  
  Serial.begin(9600);
  Serial.println("Sistem Monitoring Kelembapan (%) Dimulai");
}

void loop() {
  // Baca nilai mentah dari sensor
  int nilaiMentah = analogRead(pinSensor);
  
  // Ubah nilai mentah ke persentase
  // Map: (nilai, dari_bawah, dari_atas, ke_bawah, ke_atas)
  int kelembapanPersen = map(nilaiMentah, NILAI_KERING, NILAI_BASAH, 0, 100);
  
  // Batasi agar nilai tetap di antara 0-100%
  kelembapanPersen = constrain(kelembapanPersen, 0, 100);

  // Tampilkan di Serial Monitor
  Serial.print("Nilai Mentah: ");
  Serial.print(nilaiMentah);
  Serial.print(" | Kelembapan: ");
  Serial.print(kelembapanPersen);
  Serial.println("%");

  // Logika Penyiraman
  if (kelembapanPersen < batasSiramPersen) {
    Serial.println("KONDISI: Tanah Kering. Pompa ON!");
    digitalWrite(pinRelay, LOW);  // Nyalakan Pompa
    digitalWrite(pinLED, HIGH);   // Nyalakan LED
    delay(5000);                  // Siram selama 5 detik
  } else {
    Serial.println("KONDISI: Tanah Cukup Air. Pompa OFF.");
    digitalWrite(pinRelay, HIGH); // Matikan Pompa
    digitalWrite(pinLED, LOW);    // Matikan LED
  }

  delay(2000); // Tunggu 2 detik sebelum pembacaan berikutnya
}