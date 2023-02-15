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