<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "dbta";

$conn = mysqli_connect($servername, $username, $password, $dbname);

function query($query){
    global $conn;
    $result = mysqli_query($conn, $query);
    $rows = [];
    while ( $row = mysqli_fetch_assoc($result) ) {
        $rows [] = $row; //nambah element baru di array
    }
    return $rows; //simpen nilai variabel $rows
}

function search($keyword){
    global $conn;
    //the codes 5 lines below don't work lol
    $jumlahDataPerHalaman = 480;
    $jumlahData = count (query ("SELECT * FROM data"));
    $jumlahHalaman = ceil($jumlahData / $jumlahDataPerHalaman);
    $halamanAktif = ( isset($_GET['page']) ) ? $_GET['page'] : 1;
    $awalData = ($jumlahDataPerHalaman * $halamanAktif) - $jumlahDataPerHalaman;
    //        LIKE -> keyword buat nyari kata yang mirip
    //                kasih % di awal dan di akhir 'nama_variabel'
    //                tambah OR dibelakang biar pencariannya bisa utk beberapa kolom database
    $query = "SELECT * FROM data WHERE 
              dayStamp LIKE '%$keyword%' OR
              timeStamp LIKE '%$keyword%'
              LIMIT $awalData, $jumlahDataPerHalaman
              ";
    

    //memanggil fungsi query yang udh dibuat dalam variabel $query yang ada di fungsi ini
    return query ($query);
}
?>