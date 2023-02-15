<?php


class Program{
    #
    # Kelas yang menampung fungsi2 utama program
    # terutama yang berhubungan dengan file
    #
    private $filepath;
    # menampung alamat file penyimpanan
    private $numMhs;
    # menjadi id untuk para objek mahasiswa
    
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
}

?>