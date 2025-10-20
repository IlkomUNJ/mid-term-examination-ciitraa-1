1. Setelah menganalisis kode, ditemukan bahwa window size yang digunakan adalah 3x3 piksel. Ini dapat dilihat pada matriks 3x3 yang dibuat.

2. Pola-pola window yang mengindikasikan segment:
    1 1 1   0 0 0   0 0 0   (horizontal)
    0 0 0   1 1 1   0 0 0
    0 0 0   0 0 0   1 1 1

    1 0 0   0 1 0   0 0 1   (vertikal)
    1 0 0   0 1 0   0 0 1
    1 0 0   0 1 0   0 0 1
    
    1 0 0   0 0 1   (diagonal)
    0 1 0   0 1 0
    0 0 1   1 0 0

untuk 1 berarti ada warnanya
untuk 0 warna putih/latar

3. Berdasarkan temuan nomor 1 dan 2, saya mencoba membuat program deteksi yang menggambar persegi kecil berwarna ungu sebagai penanda. Saya menambahkan operator perbandingan di CustomMatrix.h untuk membandingan dua objek agar menentukan apakah keduanya sama atau tidak. Lalu Saya membuat vektor baru di drawingcanvas.h untuk menyimpan titik-titik segmen yang terdeteksi. Kemudian saya memodifikasi drawing.cpp pada bagian segmentDetection (menyesuaikan dengan window pattern pada no2) dan paintEvent untuk menggambar persegi warna ungunya. Tidak lupa juga menambahkan penghapus penanda ungu jika button clear digunakan.

link AI:
Perplexity saya ngedown dan tidak bisa dibuka kembali pak, jadi link untuk perplexitynya tidak ada. Saya izin mengirimkan link gemini ai yang saya tanyakan sama dengan di perplexity pak. Terima kasih pak.

https://gemini.google.com/share/687158ca7444