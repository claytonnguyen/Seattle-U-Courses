<!-- db.php
     A PHP script to access the sailor database
     through MySQL
     -->
<html>
<head>
<title> Access the Exchange database with MySQL </title>
</head>
<body style="background: #eae2b7;">
<?php

// Connect to MySQL

$servername = "cssql.seattleu.edu";
$username = "user16";
$password = "1234";

// print $servername;

$conn = mysql_connect($servername, $username, $password);

if (!$conn) {
     print "Error - Could not connect to MySQL";
     exit;
}

// Select the movie database named test
$db = mysql_select_db("bw_db16", $conn);
if (!$db) {
    print "Error - Could not select the sailor database";
    exit;
}

$query = $_POST['query'];

if(!$query){
if(isset($_POST['formSubmit']) ){
  	$varTable = $_POST['formTable'];
  	$varAttribute = $_POST['formAttribute'];
  	$varMethod = $_POST['formMethod'];
	$varData1 = $_POST['formData1'];
	$varData2 = $_POST['formData2'];
	$varData3 = $_POST['formData3'];
	$varData4 = $_POST['formData4'];
	$varData5 = $_POST['formData5'];
	$varData6 = $_POST['formData6'];
	$varData7 = $_POST['formData7'];
	$varData8 = $_POST['formData8'];
	$varData9 = $_POST['formData9'];
	$varData10 = $_POST['formData10'];
	$varData11 = $_POST['formData11'];
	$varAttribute1 = $_POST['formAttribute1'];
	$varAttribute2 = $_POST['formAttribute2'];
	$varAttribute3 = $_POST['formAttribute3'];
	$varAttribute4 = $_POST['formAttribute4'];
	$varAttribute5 = $_POST['formAttribute5'];
	$varAttribute6 = $_POST['formAttribute6'];
	$varAttribute7 = $_POST['formAttribute7'];
	$varAttribute8 = $_POST['formAttribute8'];
	$varAttribute9 = $_POST['formAttribute9'];
	$varAttribute10 = $_POST['formAttribute10'];
	$varAttribute11 = $_POST['formAttribute11'];
	$varAttribute12 = $_POST['formAttribute12'];
  	$errorMessage = "";
		
	if($varTable == "Exchange"){
		if($varMethod == "Insert"){
			$query ="Insert into $varTable values ($varData1, $varData2, $varData3, $varData4);";
		}
		if($varMethod == "Update"){
			$query = "Update $varTable set $varAttribute1 = $varData1 where $varAttribute2 = $varData2 ;";
		}
		if($varMethod == "Delete"){
			$query ="Delete from $varTable where $varAttribute1 = $varData1;";
		}
		if($varMethod == "Count"){
			$query ="Select COUNT($varAttribute1) From $varTable;";
		}
		if($varMethod == "Sum"){
			$query ="Select SUM($varAttribute1) From $varTable;";
		}
		if($varMethod == "Average"){
			$query ="Select AVG($varAttribute1) From $varTable;";
		}
		if($varMethod == "Min"){
			$query ="Select MIN($varAttribute1) From $varTable;";
		}
		if($varMethod == "Max"){
			$query ="Select MAX($varAttribute1) From $varTable;";
		}
	}
	if($varTable == "ExchangeAccount"){
		if($varMethod == "Insert"){
			$query ="Insert into $varTable values ($varData1, $varData2, $varData3, $varData4, $varData5, $varData6, $varData7, $varData8, $varData9, $varData10, $varData11);";
		}
		if($varMethod == "Update"){
			$query = "Update $varTable set $varAttribute1 = $varData1 where $varAttribute2 = $varData2 ;";
		}
		if($varMethod == "Delete"){
			$query ="Delete from $varTable where $varAttribute1 = $varData 1;";
		}
		if($varMethod == "Count"){
			$query ="Select COUNT($varAttribute1) From $varTable;";
		}
		if($varMethod == "Sum"){
			$query ="Select SUM($varAttribute1) From $varTable;";
		}
		if($varMethod == "Average"){
			$query ="Select AVG($varAttribute1) From $varTable;";
		}
		if($varMethod == "Min"){
			$query ="Select MIN($varAttribute1) From $varTable;";
		}
		if($varMethod == "Max"){
			$query ="Select MAX($varAttribute1) From $varTable;";
		}
	}
	if($varTable == "BankAccount"){
		if($varMethod == "Insert"){
			$query ="Insert into $varTable values ($varData1, $varData2);";
		}
		if($varMethod == "Update"){
			$query = "Update $varTable set $varAttribute1 = $varData1 where $varAttribute2 = $varData2 ;";
		}
		if($varMethod == "Delete"){
			$query ="Delete from $varTable where $varAttribute1 = $varData 1;";
		}
		if($varMethod == "Count"){
			$query ="Select COUNT($varAttribute1) From $varTable;";
		}
		if($varMethod == "Sum"){
			$query ="Select SUM($varAttribute1) From $varTable;";
		}
		if($varMethod == "Average"){
			$query ="Select AVG($varAttribute1) From $varTable;";
		}
		if($varMethod == "Min"){
			$query ="Select MIN($varAttribute1) From $varTable;";
		}
		if($varMethod == "Max"){
			$query ="Select MAX($varAttribute1) From $varTable;";
		}
	}
	if($varTable == "Token"){
		if($varMethod == "Insert"){
			$query ="Insert into $varTable values ($varData1, $varData2, $varData3);";
		}
		if($varMethod == "Update"){
			$query = "Update $varTable set $varAttribute1 = $varData1 where $varAttribute2 = $varData2 ;";
		}
		if($varMethod == "Delete"){
			$query ="Delete from $varTable where $varAttribute1 = $varData 1;";
		}
		if($varMethod == "Count"){
			$query ="Select COUNT($varAttribute1) From $varTable;";
		}
		if($varMethod == "Sum"){
			$query ="Select SUM($varAttribute1) From $varTable;";
		}
		if($varMethod == "Average"){
			$query ="Select AVG($varAttribute1) From $varTable;";
		}
		if($varMethod == "Min"){
			$query ="Select MIN($varAttribute1) From $varTable;";
		}
		if($varMethod == "Max"){
			$query ="Select MAX($varAttribute1) From $varTable;";
		}
	}
	if($varTable == "BuyCrypto"){
		if($varMethod == "Insert"){
			$query ="Insert into $varTable values ($varData1, $varData2, $varData3, $varData4, $varData5, $varData6, $varData7);";
		}
		if($varMethod == "Update"){
			$query = "Update $varTable set $varAttribute1 = $varData1 where $varAttribute2 = $varData2 ;";
		}
		if($varMethod == "Delete"){
			$query ="Delete from $varTable where $varAttribute1 = $varData 1;";
		}
		if($varMethod == "Count"){
			$query ="Select COUNT($varAttribute1) From $varTable;";
		}
		if($varMethod == "Sum"){
			$query ="Select SUM($varAttribute1) From $varTable;";
		}
		if($varMethod == "Average"){
			$query ="Select AVG($varAttribute1) From $varTable;";
		}
		if($varMethod == "Min"){
			$query ="Select MIN($varAttribute1) From $varTable;";
		}
		if($varMethod == "Max"){
			$query ="Select MAX($varAttribute1) From $varTable;";
		}
	}
	if($varTable == "SellCrypto"){
		if($varMethod == "Insert"){
			$query ="Insert into $varTable values ($varData1, $varData2, $varData3, $varData4, $varData5, $varData6, $varData7);";
		}
		if($varMethod == "Update"){
			$query = "Update $varTable set $varAttribute1 = $varData1 where $varAttribute2 = $varData2 ;";
		}
		if($varMethod == "Delete"){
			$query ="Delete from $varTable where $varAttribute1 = $varData 1;";
		}
		if($varMethod == "Count"){
			$query ="Select COUNT($varAttribute1) From $varTable;";
		}
		if($varMethod == "Sum"){
			$query ="Select SUM($varAttribute1) From $varTable;";
		}
		if($varMethod == "Average"){
			$query ="Select AVG($varAttribute1) From $varTable;";
		}
		if($varMethod == "Min"){
			$query ="Select MIN($varAttribute1) From $varTable;";
		}
		if($varMethod == "Max"){
			$query ="Select MAX($varAttribute1) From $varTable;";
		}
	}

}
}

if($query){

// Clean up the given query (delete leading and trailing whitespace)
trim($query);

// remove the extra slashes
$query = stripslashes($query);


// handle HTML special characters
$query_html = htmlspecialchars($query);
// print "<p> <b> The query is: </b> " . $query_html . "</p>";


// Execute the query
$result = mysql_query($query);
if (!$result) {
	print "<button onclick='history.go(-1);' style='background-color: #7f5539; border: none; border-radius: 10px; color: white; margin-top: 10px; margin-left: 30px; padding: 10px 20px; text-align: center; text-decoration: none; display: grid; justify-content: center; margin: 25px auto; font-size: 16px; font-family: monospace;'> Back </button>";
    print "Error - the query could not be executed";
    $error = mysql_error();
    print "<p>" . $error . "</p>";
    exit;
}


// Get the first row
$row = mysql_fetch_array($result);

// Get the number of rows in the result
$num_rows = mysql_num_rows($result);

// Get the number of fields in the rows
$num_fields = mysql_num_fields($result);

// Display back button
print "<button onclick='history.go(-1);' style='background-color: #7f5539; border: none; border-radius: 10px; color: white; margin-top: 10px; margin-left: 30px; padding: 10px 20px; text-align: center; text-decoration: none; display: grid; justify-content: center; margin: 25px auto; font-size: 16px; font-family: monospace;'> Back </button>";


// Display the results in a table
print "<table border='border' style='padding-top: 12px;
  padding-bottom: 12px;
  text-align: center;
  background-color: #d4a373;
  color: #432818; margin: 25px auto;
  padding: 8px; border: 10px solid #432818;
  width: 80%; border-radius: 10px;'><caption> <h2 style='font-size: 33px;'> Query Results </h2> </caption>";
print "<tr align = 'center'>";

// border: 1px solid #432818;  border-collapse: collapse;


// Produce the column labels
$keys = array_keys($row);
for ($index = 0; $index < $num_fields; $index++)
    print "<th>" . $keys[2 * $index + 1] . "</th>";

print "</tr>";

// Output the values of the fields in the rows
for ($row_num = 0; $row_num < $num_rows; $row_num++) {

    print "<tr align = 'center'>";
    $values = array_values($row);

    for ($index = 0; $index < $num_fields; $index++){
        $value = htmlspecialchars($values[2 * $index + 1]);
        print "<td>" . $value . "</td> ";
    }

    print "</tr>";
    $row = mysql_fetch_array($result);


}

print "</table>";
print "<div style='margin: 50px auto; text-align: center;'>";
print "<p style='font-size: 15px;'> Number of rows = $num_rows </p><br />";
print "<p style='font-size: 15px;'> Number of fields = $num_fields </p><br />";
print "</div>";

}
mysql_close($conn);
?>
</body>
</html>
