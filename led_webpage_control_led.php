<?php
$ledStatus = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["fname"])) {
        $ledStatus = $_POST["fname"];
        if (empty($ledStatus)) {
            $ledStatus = "";
        } else {
            echo "Last time you clicked was: $ledStatus";
        }
    }
}

$myfile = fopen("results.txt", "w") or die("Unable to open file!");
fwrite($myfile, $ledStatus);
fclose($myfile);
?>
