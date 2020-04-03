Kelompok D02
- 5111840000120	-	Aflakah Nur Farhana
- 5111840000165	-	Muhammad Fikri Rabbani


**Soal 1**


**Soal 2**


**Soal 3**
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan

opsi `-f`

Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang user inginkan seperti contoh di atas.Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual, melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,maka dia akan disimpan dalam folder “Unknown”.

opsi `*`

Mengkategori seluruh file yang ada di working directory ketika menjalankan program C tersebut.

opsi `id`

Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).

Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau menggunakan `*` terdapat folder yang berisi file, maka file dalam folder tersebut tidak dihiraukan, cukup file pada 1 level saja.
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang menggunakan fork-exec dan system.

**Soal 4**

4a.Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).Tampilkan matriks hasil perkalian tadi ke layar.

4b.Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar.(Catatan!: gunakan shared memory).Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan format seperti matriks.Harus menggunakan Thread dalam penghitungan
faktorial)

4c.Buatlah program C ketiga dengan nama "4c.c". Program ini tidak memiliki hubungan terhadap program yang lalu.Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar IPC, Norland mengerjakannya dengan semangat.(Catatan! : Harus menggunakan IPC Pipes)
