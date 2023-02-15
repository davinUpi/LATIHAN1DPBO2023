<?php

    include "Program.php";
    include "Mahasiswa.php";

    $listMhs = array();
    # array yang akan menampung objek Mahasiswa

    $mainDriver = new Program();
    $listMhs = $mainDriver->readMhsFile();
    # listMhs diisi oleh objek2 Mahasiswa

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
    <!-- Bagian paling atas, berisi add-->
    <div class="sticky-top">
        <header class="d-flex p-3 flex-row justify-content-end nav-tabs flex-nowrap" id="mainNav">
            <div class="ml-2 d-block">
                <a href="form.php">
                    <button class="btn btn-primary"><i class="fa-solid fa-plus"></i></button>
                </a>
            </div>
        </header>
    </div>
    <!-- Bagian utama, menampilkan Mahasiswa-mahasiswa-->
    <div class="d-block ml-5">
        <main class="d-flex container flex-wrap flex-row justify-content-start m-5">
            <?php
                foreach($listMhs as $mhs){
            ?>
            <div class="card m-5">
                <img src="image/<?=$mhs->getImgPath()?>" alt="<?=$mhs->getName()?> image" class="card-image-top img-fluid img-thumbnail" style="
                        width: 234px;
                        height: 234px;
                        object-fit:cover;
                        object-position:50% 5%;
                        ">
                <div class="card-body">
                    <h5 class="card-title m-2">
                        <span class="d-inline-block text-truncate" style="max-width: 200px; color:black;">
                            <?=$mhs->getName()?>
                        </span>
                    </h5>
                    <p class="card-text m-2">
                        <span class="d-inline-block text-truncate" style="max-width: 200px; color:black;">
                            <?=$mhs->getNim()?>
                        </span>
                    </p>
                    <p class="card-text m-2">
                        <span class="d-inline-block text-truncate" style="max-width: 200px; color:black;">
                            <?=$mhs->getProdi()?>
                        </span>
                    </p>
                    <p class="card-text m-2">
                        <span class="d-inline-block text-truncate" style="max-width: 200px; color:black;">
                            <?=$mhs->getFakultas()?>
                        </span>
                    </p>
                </div>
                <div class="card-footer">
                    <div>
                        <!-- Tombol2: Tombol untuk mengedit dan menghapus mahasiswa-->
                        <a href="form.php?id=<?=$mhs->getId()?>" style="text-decoration: none;" class="mx-1">
                            <button class="btn btn-warning"><i class="fa-solid fa-wrench"></i></button>
                        </a>
                        <a href="delete.php?id=<?=$mhs->getId()?>" style="text-decoration: none;" class="mx-1">
                            <button class="btn btn-danger"><i class="fa-solid fa-trash"></i></button>
                        </a>
                    </div>
                </div>
            </div>
            <?php } ?>
        </main>
    </div>

    <script src="https://kit.fontawesome.com/13338d9b84.js" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
</body>
</html>