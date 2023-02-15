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
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
</head>
<body>
    <div class="wrapper m-5">
        <h2>Mahasiswa Form</h2>
        <p>Please fill this form to create a new Mahasiswa.</p>
        <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="post">
            <div class="form-group">
                <label>Nama</label>
                <input type="text" name="name" class="form-control <?php echo (!empty($errName)) ? 'is-invalid' : ''; ?>" value="<?php echo $name; ?>">
                <span class="invalid-feedback"><?php echo $errName; ?></span>
            </div>
            <div class="form-group">
                <label>Nim</label>
                <input type="text" name="nim" class="form-control <?php echo (!empty($errNim)) ? 'is-invalid' : ''; ?>" value="<?php echo $nim; ?>">
                <span class="invalid-feedback"><?php echo $errNim; ?></span>
            </div>
            <div class="form-group">
                <label>Program Studi</label>
                <input type="text" name="prodi" class="form-control <?php echo (!empty($errProdi)) ? 'is-invalid' : ''; ?>" value="<?php echo $prodi; ?>">
                <span class="invalid-feedback"><?php echo $errProdi; ?></span>
            </div>
            <div class="form-group">
                <label>Fakultas</label>
                <input type="text" name="fakultas" class="form-control <?php echo (!empty($errFakultas)) ? 'is-invalid' : ''; ?>" value="<?php echo $fakultas; ?>">
                <span class="invalid-feedback"><?php echo $errProdi; ?></span>
            </div>
            <input type="hidden" name="id" id="hiddenField" value="<?php echo $id ?>" />
            <div class="form-group">
                <input type="submit" class="btn btn-primary" value="Submit">
                <input type="reset" class="btn btn-secondary ml-2" value="Reset">
            </div>
        </form>
    </div>
    <script src="https://kit.fontawesome.com/13338d9b84.js" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
</body>
</html>