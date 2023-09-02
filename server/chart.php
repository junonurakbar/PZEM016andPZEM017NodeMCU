<?php 
require_once ("functions.php");
$Pac = "Pac";
$Pdc = "Pdc";
$Eac = "Eac";
$Edc = "Edc";

$query = query ("SELECT dayStamp, timeStamp, Pac, Pdc, Eac, Edc FROM data WHERE
                 $Pac <> 0 OR
                 $Pdc <> 0 OR
                 $Eac <> 0 OR
                 $Edc <> 0
                ");

$labels = array();
$dataPointsPac = array();
$dataPointsPdc = array();
$dataPointsEac = array();
$dataPointsEdc = array();

foreach ($query as $row){
    $labels[] = $row['dayStamp'];   //
    $dataPointsPac[] = $row['Pac'];
    $dataPointsPdc[] = $row['Pdc'];
}

// var_dump($labels);
// var_dump($dataPoints);

?>

<!DOCTYPE html>
<html>
<head>
    <title>Grafik</title>
</head>
<body>
    <div style="width: 80%; margin: auto;">
        <canvas id="grafikData"></canvas>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script>
        // Convert PHP data to JavaScript variables
        var labels = <?php echo json_encode($labels); ?>;
        var dataPointsPac = <?php echo json_encode($dataPointsPac); ?>;
        var dataPointsPdc = <?= json_encode($dataPointsPdc); ?>
        // var dataPointsEac = <?= json_encode($dataPointsEac); ?>
        // var dataPointsEdc = <?= json_encode($dataPointsEdc); ?>
        console.log(labels);

        // Create the chart using Chart.js
        var ctx = document.getElementById('grafikData').getContext('2d');
        var chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: labels,
                datasets: [{
                    label: 'Pac',
                    data: dataPointsPac, 
                    backgroundColor: 'rgba(0, 123, 255, 0.5)',
                    borderColor: 'rgba(0, 123, 255, 1)',
                    borderWidth: 1
                },{
                    label: 'Pdc',
                    data: dataPointsPdc,
                    backgroundColor: 'rgba(255, 99, 132, 0.5)',
                    borderColor: 'rgba(255, 99, 132, 1)',
                    borderWidth: 1
                }
                ]
            },
            options: {
                responsive: true,
                scales: {
                    y: {
                        beginAtZero: true
                    }
                }
            }
        });
    </script>
</body>
</html>
