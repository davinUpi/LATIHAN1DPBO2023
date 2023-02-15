# LATIHAN1DPBO2023

Saya Davin mengerjakan evaluasi LATIHAN1DPBO2023 dalam mata kuliah DPBO untuk keberkahanNya maka saya tidak melakukan kecurangan seperti yang telah dispesifikasikan. Aamiin.

Latihan praktikum dpbo 1

#SAYA MENGGUNAKAN PROGRAM PHP SEBAGAI CONTOH
Mengapa?
1. Paling terakhir yang saya bikin
2. Paling "bersih"
3. Paling jelas dan pendek awokowkoak

# Penjelasan Desain
 1. PHP
    a) Mahasiswa.php (Class)
    Merupakan sebuah kelas yang berisi data-data Mahasiswa sebagai atribut.
    Adapun atribut-atribut itu adalah id, nama, nim, prodi, fakultas, dan alamat gambar.
    Untuk saat ini, alamat gambar dipaksakan sama ("default.jpg").
    Semua atribut dapat diambil menggunakan getter.
    Semua atribut dapat diset menggunakan setter.
    Mahasiswa digunakan di dalam Program.php, index.php, delete.php, dan form.php
    
    Atribut:
    
##    
    private $id;
    private $name;
    private $nim;
    private $prodi;
    private $fakultas;
    private $imgPath;
<br>
    Metode:
    
##    
    public function __construct($id, $name, $nim, $prodi, $fakultas){
        $this->id = $id;
        $this->name = $name;
        $this->nim = $nim;
        $this->prodi = $prodi;
        $this->fakultas = $fakultas;
        $this->imgPath = "default.jpg";
        # tidak ada set foto, jadi pake yg default dulu
    }


    //Setter
    public function setId($input){
        $this->id = $input;
    }
    public function setName($input){
        $this->name = $input;
    }
    public function setNim($input){
        $this->nim = $input;
    }
    public function setProdi($input){
        $this->prodi = $input;
    }
    public function setFakultas($input){
        $this->fakultas = $input;
    }
    public function setImgPath($input){
        $this->imgPath;
    }

    // Getter
    public function getId(){
        return $this->id;
    }
    public function getName(){
        return $this->name;
    }
    public function getNim(){
        return $this->nim;
    }
    public function getProdi(){
        return $this->prodi;
    }
    public function getFakultas(){
        return $this->fakultas;
    }
    public function getImgPath(){
        return $this->imgPath;
    }
    
<br>     
     b) Program.php (Class)
     Merupakan kelas yang mengatasi pengolahan data.
     Untuk saat ini, fokus pada manajemen file.
     Terdapat beberapa metoda dan atribut 
     Kelas Program digunakan di index.php, form.php, dan delete.php <br>
     Atribut:
##      
      private $filepath;
      // menampung alamat file penyimpanan
      private $numMhs;
      // menjadi id untuk para objek mahasiswa
<br>      
      Metode: 
      
 ##
      public function __construct(){
          $this->filepath = "mahasiswa.dat";
          # inisialisasi file path
      }
      public function getNumMhs(){
          #
          # Mendapatkan jumlah mahasiswa yang ada
          #
          return $this->numMhs;
      }
       
      public function readMhsFile(){
        #
        # Mendapatkan data2 mahasiswa dari file
        #
        $file = @fopen($this->filepath, 'r');
        if($file){
            $listMhs = array();
            foreach(file($this->filepath) as $line){
                $this->numMhs++;
                $datas = explode(' ', $line);
                array_push($listMhs, new Mahasiswa($this->numMhs,$datas[0], $datas[1], $datas[2], $datas[3]));
            }
            fclose($file);
            return $listMhs;
        }
    }
    
    public function writeMhsFile($listMhs){
        #
        # Menuliskan data2 mahasiswa ke sebuah file
        #
        $file = @fopen($this->filepath, "w");
        if($file){
            foreach($listMhs as $mhs){
                $name = $mhs->getName();
                $nim = $mhs->getNim();
                $prodi = $mhs->getProdi();
                $fakultas = $mhs->getFakultas();
                $data = $name . " " . $nim . " " . $prodi . " " . $fakultas;
                fwrite($file, $data);
            }
            fclose($file);
        }
    }
<br>    
    c) index.php
    PHP hanya berisi pengisian array dengan data-data dari file
    
##
    <?php

    include "Program.php";
    include "Mahasiswa.php";

    $listMhs = array();
    # array yang akan menampung objek Mahasiswa

    $mainDriver = new Program();
    $listMhs = $mainDriver->readMhsFile();
    # listMhs diisi oleh objek2 Mahasiswa

    ?>
<br>
    d) form.php <br>
    PHP yang berisi pengolahan input untuk mengubah atau menambahkan mahasiswa baru <br>
    Kode: 
 
 ##
    <?php

    include "Program.php";
    include "Mahasiswa.php";

    $listMhs = array();
    $driver = new Program();
    $listMhs = $driver->readMhsFile();

    $id = $name = $nim = $prodi = $fakultas = $imgPath = "";
    $errName = $errNim = $errProdi = $errFakultas = "";
    # untuk menampilkan value dalam input dan juga menampilkan error bila ada

    $curMhs = "";
    #untuk menampung mahasiswa yang diubah datanya (bila mengubah data)

    if(isset($_GET["id"])){
        #
        # Bila form digunakan untuk mengedit data Mahasiswa
        #
        $id = $_GET["id"];
        foreach($listMhs as $mhs){
            if ($id == $mhs->getId()){
                $curMhs = $mhs;
                break;
            }
        }

        $name = $curMhs->getName();
        $nim = $curMhs->getNim();
        $prodi = $curMhs->getProdi();
        $fakultas = $curMhs->getFakultas();
        $imgPath = $curMhs->getImgPath();
    }

    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        #
        # Ketika form telah diisi, diproses sehingga
        # dapat membuat objek Mahasiswa baru. Hasilnya
        # disimpan pada sebuah fiile
        #
        
        if(isset($_POST["id"])){
            $id = $_POST["id"];
        }

        if(empty($_POST["name"]) ){
            #
            # nama harus diisi dan juga tidak memiliki spasi
            #
            $errName = "Name is required";
         }
         else if(strrpos($_POST['name'], ' ')){
            $errName = "Must not contain spaces!";
         }
         else{
             $name = htmlspecialchars(trim($_POST["name"]));
         }
         
         if(empty($_POST["nim"])){
            #
            # nim harus diisi dan juga tidak memiliki spasi
            #
             $errNim = "Nim is required";
         }
         else if(strrpos($_POST['nim'], ' ')){
            $errNim = "Must not contain spaces!";
         }
         else{
             $nim = htmlspecialchars(trim($_POST["nim"]));
         }
 
         if(empty($_POST["prodi"])){
            #
            # prodi harus diisi dan juga tidak memiliki spasi
            #
             $errProdi = "Prodi is required";
         }
         else if(strrpos($_POST['prodi'], ' ')){
            $errProdi = "Must not contain spaces!";
         }
         else{
             $prodi = htmlspecialchars(trim($_POST["prodi"]));
         }
         
         if(empty($_POST["fakultas"])){
            #
            # fakultas harus diisi dan juga tidak memiliki spasi
            #
             $errFakultas = "Fakultas is required";
         }
         else if(strrpos($_POST['fakultas'], ' ')){
            $errFakultas = "Must not contain spaces!";
         }
         else{
             $fakultas = htmlspecialchars(trim($_POST["fakultas"]));
         }

         if(
            empty($errName) &&
            empty($errNim) &&
            empty($errProdi) &&
            empty($errFakultas)
         ){
            #
            # Bila semua data lengkap dan sesuai persyaratan
            # commit change atau add (sesuai pilihan)
            #
            if(empty($id)){
                #
                # Bila tidak ada id, berarti menambahkan Mahasiswa baru
                # (Id baru didapatkan di sini)
                #
                array_push($listMhs, new Mahasiswa($driver->getNumMhs(), $name, $nim, $prodi, $fakultas));
            }else{
                #
                # Bila ada id, mencari Mahasiswa dengan id tersebut
                # Lalu mengupdate nilai atribut-atributnya
                #
                foreach($listMhs as $mhs){
                    if ($id == $mhs->getId()){
                        $curMhs = $mhs;
                        break;
                    }
                }
                $curMhs->setName($name);
                $curMhs->setNim($nim);
                $curMhs->setProdi($prodi);
                $curMhs->setFakultas($fakultas);
            }
            $driver->writeMhsFile($listMhs);
            # save ke file

            header('Location: index.php');
         }
    }
      ?>


<br>
    e) delete.php <br>
    delete.php digunakan untuk menghapus mahasiswa. <br>
    kode:<br>
    
    
    <?php

    include "Program.php";
    include "Mahasiswa.php";

    $listMhs = array();
    $driver = new Program();
    $listMhs = $driver->readMhsFile();

    if(isset($_GET['id'])){
        $id = $_GET["id"];
        $curMhs;
        foreach($listMhs as $mhs){
            if ($id == $mhs->getId()){
                $curMhs = $mhs;
                break;
            }
        }
        if(isset($curMhs)){
            $idx = array_search($curMhs, $listMhs);
            array_splice($listMhs, $idx, 1);
            $driver->writeMhsFile($listMhs);
        }

    }
    header('Location: index.php');
     ?>
  
2. HTML <br>
    a) index.php
      index.php berisi halaman muka, yaotu halaman yang menampilkan semua kartu Mahasiswa.
      terdapat opsi untuk menambahkan Mahasiswa baru denan cara menekan tombol [+] di pojok kanan atas.
      Setiap kartu terdiri dari gambar profil, identitas (nama, nim, prodi, fakultas), dan tombol untuk mengedit 
      ataupun menghapus kartu mahasiswa tersebut. Untuks saat ini, belum ada pop-up konfirmasi penghapusan
      
      ![Screenshot (465)](https://user-images.githubusercontent.com/100902319/219044751-e636f742-62c3-4342-bcd3-ff443e17afd8.png)
      
      Tombol untuk menambahkan mahasiswa adalah tombol biru di pojok atas kanan.
      
      Tombol untuk mengubah data mahasiswa adalah tombol kuing pada kartu mahasiswa.
      
      Tombol untuk menghapus mahasiswa adalah tombol merah pada kartu mahasiswa
      
      
      
      b) form.php
      form.php berisi sebuah formulir yang dapat diakses apabila menekan tombol [+] untuk menambahkan
      mahasiswa baru atau tombol untuk mengedit data mahasiswa. Bila untuk mengedit, formulir akan terisi
      dengan data-data mahasiswa yang ingin diubah.
      
      Bila form digunakan untuk menambahkan mahasiswa baru:
      
      ![Screenshot (466)](https://user-images.githubusercontent.com/100902319/219045527-19537025-17bc-4e3f-a1fa-d8ebd79a2900.png)

      Bila form digunakan untuk mengedit mahasiswa baru: (hint, lihat url)
      
      ![Screenshot (469)](https://user-images.githubusercontent.com/100902319/219045674-05f015c7-dd58-4e73-b135-044314eeb754.png)

# Penjelasan alur
  
  mengakses Indeks
  
  1. Pengguna mengakses index.php
  2. Ketika mengakses, program memuat data-data Mahasiswa dari file ke dalam array
  3. program mampilkan data-data setiap mahasiswa dalam bentuk kartu
  
  ![Screenshot (465)](https://user-images.githubusercontent.com/100902319/219046799-31d4d39f-c411-4141-9d12-21ef9da69453.png)

  Menambahkan mahasiswa baru
  
  1. Pengguna menekan tombol biru di pojok kanan atas halaman indeks
  2. Pengguna diantarkan ke form.php
  3. Ketika pengguna mengakses form.php, program memuat data-data mahasiswa dari file ke dalam array
  4. Pengguna mengisi formulir sesuai dengan ketentuan
  5. Bila sudah, pengguna menekan tombol submit yang akan mengirimkan POST ke form.php
  6. Program akan menangkap POST
  7. program melakukan pengecekan atas input pengguna
  8. Bila ada yang tidak sesuai, akan menampilkan error. Pengguna harus mengisi ulang
  9. Bila sudah sesuai, program membuat objek Mahasiswa baru dan memasukkannya ke dalam array
  10. Array disalin ke dalam file
  11. File ditutup
  12. Kembalikan pengguna ke index.php
  
  ![Screenshot (466)](https://user-images.githubusercontent.com/100902319/219048148-2d72d1bc-ab18-4394-9945-a188e22793ef.png)

![Screenshot (467)](https://user-images.githubusercontent.com/100902319/219048175-7a14960a-053f-47be-8f94-26135355ebde.png)

![Screenshot (468)](https://user-images.githubusercontent.com/100902319/219048213-bed3ab46-5250-444f-8ce8-9a4335c9f068.png)

  Mengubah data mahasiswa
  
  1. Pengguna menekan tombol kuning pada kartu Mahasiswa yang ingin diubah.
  2. Program mengantarkan pengguna ke form.php dengan mengirimkan GET berupa id Mahasiswa tersebut.
  3. Program memuat data-data mahasiswa dari file ke dalam array
  3. Program akan menangkap GET berisi id.
  4. Program mencari Mahasiswa dengan id tersebut di dalam array
  5. Formulir akan terisi dengan data-data mahasiswa dengan id yang ditangkap dari GET
  6. Pengguna mengubah data-data yang diinginkan sesuai dengan persyaratan
  7. Pengguna menekan tombol submit yang akan mengirimkan POST ke form.php
  8. Program menangkap POST
  9. Kali ini, POST berisi masukkan pengguna dan juga id Mahasiswa yang diubah
  10. program melakukan pengecekan atas input pengguna
  11. Bila ada yang tidak sesuai, akan menampilkan error. Pengguna harus mengisi ulang
  12. Bila sudah sesuai, program membuat objek Mahasiswa baru dan memasukkannya ke dalam array
  13. Array disalin ke dalam file
  14. File ditutup
  15. Kembalikan pengguna ke index.php
  
  ![Screenshot (468)](https://user-images.githubusercontent.com/100902319/219049778-b2419ae4-c1f1-4410-b32d-99ffbef469f1.png)

![Screenshot (469)](https://user-images.githubusercontent.com/100902319/219049970-a502280e-f7b8-4b4c-90cb-40f07f216c87.png)

![Screenshot (470)](https://user-images.githubusercontent.com/100902319/219050009-6febd378-0fd1-4cb1-8016-db9a7de9586f.png)

  Menghapus mahasiswa
  
  1. Pengguna menekan tombol merah pada kartu mahasiswa yang ingin dihapus
  2. Program akan mengirimkan GET berupa id ke delete.php
  3. Program menangkap GET berisikan id mahasiswa yang ingin dihapus
  4. Program memuat data-data mahasiswa dari file ke dalam array
  5. Program mencari mahasiswa yang ingin dihapus di dalam array
  6. Bila ketemu, hapus Mahasiswa tersebut dari array
  7. Array disalin ke dalam file
  8. File ditutup
  9. Kembalikan pengguna ke index.php 
  
  ![Screenshot (470)](https://user-images.githubusercontent.com/100902319/219050723-c31139ac-7fc3-4ba6-bb14-9b0cf4b5ff07.png)

![Screenshot (471)](https://user-images.githubusercontent.com/100902319/219050748-384400ff-2cff-4f4c-ace5-ac5693d23667.png)
