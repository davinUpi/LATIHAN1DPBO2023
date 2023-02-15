<?php
class Mahasiswa {
    #
    # Kelas untuk menampung data2 Mahasiswa
    # Terdiri dari atribut id, name, nim, prodi, fakultas, dan imgPath
    # Semuanya dapat diakses dengan setter (memberi nilai) dan getter (mengambil nilai)
    #
    private $id;
    private $name;
    private $nim;
    private $prodi;
    private $fakultas;
    private $imgPath;

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
}
?>