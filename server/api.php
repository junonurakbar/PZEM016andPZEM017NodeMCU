<?php

require("koneksi.php");

// Database configuration
// $servername = "localhost";
// $username = "root";
// $password = "";
// $dbname = "dbta";

// Create a new MySQLi object
// $conn = new mysqli($servername, $username, $password, $dbname);

// Check the connection
// if ($conn->connect_error) {
//     die("Connection failed: " . $conn->connect_error);
// }

// Retrieve the JSON data from the request
$jsonData = file_get_contents('php://input');

// Decode the JSON data
$data = json_decode($jsonData, true);

// Check if the data is valid
if ($data !== null) {
    // Perform any necessary processing and validation on the data
    //PZEM-016
    $dayStamp = $data["dayStamp"];
    $timeStamp = $data["timeStamp"];
    $Vac = $data["Vac"];
    $Iac = $data["Iac"];
    $Pac = $data["Pac"];
    $Eac = $data["Eac"];
    //PZEM-017
    $Vdc = $data["Vdc"];
    $Idc = $data["Idc"];
    $Pdc = $data["Pdc"];
    $Edc = $data["Edc"];

    // Prepare and execute the SQL query to insert the data into the database
    $stmt = $conn->prepare("INSERT INTO data (dayStamp, timeStamp, Vac, Iac, Pac, Eac, Vdc, Idc, Pdc, Edc) 
                            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    $stmt->bind_param("ssssssssss", $dayStamp, $timeStamp, $Vac, $Iac, $Pac, $Eac, $Vdc, $Idc, $Pdc, $Edc);
    $stmt->execute();

    // Close the statement
    $stmt->close();

    // Send a response back to the Arduino
    http_response_code(200);
    echo "Data received and stored successfully.";
} else {
    // Invalid JSON data
    http_response_code(400);
    echo "Invalid JSON data.";
}

// Close the database connection
$conn->close();

?>
