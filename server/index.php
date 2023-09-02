<?php // memanggil file koneksi.php untuk koneksi ke database
  require_once "functions.php";
  //buat pagination
  //                                    LIMIT index_awal, berapa_data_ditampilkan
  $jumlahDataPerHalaman = 150;
  //            count : hitung berapa elemen dalam sebuah array 
  $jumlahData = count (query ("SELECT * FROM data"));
  //var_dump($jumlahData); -> int(jumlah_data_di_DB_ada_brp_baris)

  //membulatkan bilangan pecahan di PHP: round(bulat ke terdekat), floor(bulat ke bawah), ceil(bulat ke atas)
  $jumlahHalaman = ceil($jumlahData / $jumlahDataPerHalaman);

  //halaman aktif: utk menentukan sedang di halaman berapa
  //tentukan dulu apakah baru masuk page/belum, pakai operator ternary
  // (kondisi) ? nilai_true : nilai_false ; -> masukin ke variabel
  $halamanAktif = ( isset($_GET['page']) ) ? $_GET['page'] : 1;

  //bikin variabel baru lagi utk menentukan awal index dari LIMIT query
  $awalData = ($jumlahDataPerHalaman * $halamanAktif) - $jumlahDataPerHalaman;

  $sql = query ("SELECT * FROM data ORDER BY id DESC LIMIT $awalData, $jumlahDataPerHalaman");

  //jika tombol cari di klik
  if ( isset($_POST["search"]) ){
      //cari data berdasarkan keyword yang dimasukkan
      //       search(dapat_data_dari_variabel)
      $sql = search($_POST["keyword"]);
  }
?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!--refresh page every 60 seconds
    <meta http-equiv="refresh" content="60">
	-->
    
    <title>Last Year Project</title>
  </head>

  <body>
    <style>
      #wntable {
        border-collapse: collapse;
        width: 90%;
    
      }

      #wntable td, #wntable th {
        border: 1px solid #ddd;
        padding: 8px;
      }

      #wntable tr:nth-child(even){background-color: #f2f2f2;}

      #wntable tr:hover {background-color: #ddd;}

      #wntable th {
        padding-top: 12px;
        padding-bottom: 12px;
        text-align: left;
        background-color: #00A8A9;
        color: white;
      }
    </style>

    <div id="cards" class="cards" align="center">
        <h1> Pentago Last Year Project</h1>

        <!--bikin form pencarian -->
        <form action="" method="post">
            <!-- autofocus: input akan otomatis aktif ketika buka halaman-->
            <!-- autocomplete="off": hapus history pencarian-->
            <input type="text" name="keyword" size="30" placeholder="Search Data" autofocus autocomplete="off">
            <button type="submit" name="search" >Enter</button>
            <br>
        </form>

        <!-- bikin pagination -->
        <!-- bikin previous page pake &lt : lambang dari less than -->
        <!-- atau pake laquo << -->
        <?php if($halamanAktif > 1) : ?>    
            <a href="?page=<?=$halamanAktif-1; ?>">&lt</a>
        <?php endif;?>

        <?php for($i=1; $i<=$jumlahHalaman; $i++) : ?>
            <?php if ($i == $halamanAktif) : ?>
                <a href="?page=<?=$i; ?>"style="font-weight:bold; color: red;" > <?=$i; ?></a>
            <?php else : ?> 
                <a href="?page=<?=$i; ?>"> <?=$i; ?></a>
            <?php endif; ?>
        <?php endfor; ?>
        <!-- bikin previous page pake &gt : lambang dari greater than -->
        <!-- atau pake raquo >> -->
        <?php if($halamanAktif < $jumlahHalaman) : ?>    
            <a href="?page=<?=$halamanAktif+1; ?>">&gt</a>
        <?php endif;?>

        <table id="wntable">
        <tr>
          <th>No</th>
          <th>Tanggal</th>
          <th>Waktu</th>
          <th>Vac [V]</th>
          <th>Iac [A]</th>
          <th>Pac [W]</th>
          <th>Eac [Wh]</th>
          <th>Vdc [V]</th>
          <th>Idc [A]</th>
          <th>Pdc [W]</th>
          <th>Edc [Wh]</th>
        </tr>
        <?php

        // $sql = mysqli_query($conn, "SELECT * FROM data_server ORDER BY dayStamp DESC, timeStamp DESC");

          $no = 1; // mewakili data dari nomor 1
          foreach ($sql as $row) { // fetch query yang sesuai ke dalam array
            echo '
            <tr>
              <td>'.$no.'</td>
              <td>'.$row['dayStamp'].'</td>
              <td>'.$row['timeStamp'].'</td>
              <td>'.$row['Vac'].'</td>
              <td>'.$row['Iac'].'</td>
              <td>'.$row['Pac'].'</td>
              <td>'.$row['Eac'].'</td>
              <td>'.$row['Vdc'].'</td>
              <td>'.$row['Idc'].'</td>
              <td>'.$row['Pdc'].'</td>
              <td>'.$row['Edc'].'</td>
            </tr>
            ';
            $no++; // mewakili data kedua dan seterusnya
          }
        
        ?>
      </table>
    </div>
  </body>
</html>