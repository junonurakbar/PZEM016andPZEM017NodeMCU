<?php
// Retrieve the JSON data from the request
$jsonData = file_get_contents('php://input');

// Decode the JSON data
$data = json_decode($jsonData, true);

// Check if the JSON data is valid
if ($data === null) {
    echo "Invalid JSON data";
    exit;
}

// Database connection settings
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "dbta";

// Create a new PDO instance
try {
    $conn = new PDO("mysql:host=$servername;dbname=$dbname", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
    exit;
}

// Prepare the SQL statement
$sql = "INSERT INTO data (dayStamp, timeStamp, Vac, Iac, Pac, Eac, Vdc, Idc, Pdc, Edc) 
                  VALUES (:dayStamp, :timeStamp, :Vac, :Iac, :Pac, :Eac, :Vdc, :Idc, :Pdc, :Edc)";
$stmt = $conn->prepare($sql);

// Iterate over each JSON object and insert the data into the database
foreach ($data as $obj) {
    // Bind the values to the parameters in the SQL statement
    $stmt->bindParam(':dayStamp', $obj['dayStamp']);
    $stmt->bindParam(':timeStamp', $obj['timeStamp']);
    $stmt->bindParam(':Vac', $obj['Vac']);
    $stmt->bindParam(':Iac', $obj['Iac']);
    $stmt->bindParam(':Pac', $obj['Pac']);
    $stmt->bindParam(':Eac', $obj['Eac']);
    $stmt->bindParam(':Vdc', $obj['Vdc']);
    $stmt->bindParam(':Idc', $obj['Idc']);
    $stmt->bindParam(':Pdc', $obj['Pdc']);
    $stmt->bindParam(':Edc', $obj['Edc']);

    // Execute the statement
    $stmt->execute();
}

// Close the database connection
$conn = null;

// Return a response
echo "Data inserted successfully";
?>
