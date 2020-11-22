const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>

<head>
	<title>Big Green House </title>
	<!--For offline ESP graphs see this tutorial https://circuits4you.com/2018/03/10/esp8266-jquery-and-ajax-web-server/ -->
	<script src = "https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>	
	<style>
	canvas{
		-moz-user-select: none;
		-webkit-user-select: none;
		-ms-user-select: none;
	}

	/* Data Table Styling */
	#dataTable {
	  font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
	  border-collapse: collapse;
	  width: 100%;
	}

	#dataTable td, #dataTable th {
	  border: 1px solid #ddd;
	  padding: 8px;
	}

	#dataTable tr:nth-child(even){background-color: #f2f2f2;}

	#dataTable tr:hover {background-color: #ddd;}

	#dataTable th {
	  padding-top: 12px;
	  padding-bottom: 12px;
	  text-align: left;
	  background-color: #4CAF50;
	  color: white;
	}
	</style>
</head>

<body>
    <div style="text-align:center;"><b>Team Delta</b><br>Big Green House</div>
    <div class="chart-container" position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
	<table id="dataTable">
	  <tr><th>Time</th><th>Power</th></tr>
	</table>
</div>
<br>
<br>	

<script>
//Graphs visit: https://www.chartjs.org
var values = [];
var timeStamp = [];
function showGraph()
{
    for (i = 0; i < arguments.length; i++) {
    	values.push(arguments[i]);    
    }

    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,	//Bottom Labeling
            datasets: [{
                label: "Power usage",
                fill: true,	//Try with true
                backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                borderColor: 'rgba( 243, 156, 18 , 1)',	//Graph Line Color
                data: values,
            }],
        },
        options: {
            title: {
                    display: true,
                    text: "Power"
                },
            maintainAspectRatio: false,
            elements: {
            line: {
                    tension: 0.5 //Smoothening (Curved) of data lines
                }
            },
            scales: {	
                    yAxes: [{
                        ticks: {
							maxTicksLimit: 5,
                            beginAtZero:true
                        }
                    }]
            }
        }
    });

}


var data = [
   [values],
   [timeStamp],
   ['Moo', 'Reindeer Hunter']
];
 

 function download_csv() {
    var i;
	var csv = 'Power,Time\n';
	for (i of  values) {
	csv +=  values[i] + "," + timeStamp[i] + ",\n";
 }
 
    console.log(csv);
    var hiddenElement = document.createElement('a');
    hiddenElement.href = 'data:text/csv;charset=utf-8,' + encodeURI(csv);
    hiddenElement.target = '_blank';
    hiddenElement.download = 'people.csv';
    hiddenElement.click();
}
 
// function download_csv() {
    // var csv = 'Name,Title\n';
    // data.forEach(function(row) {
            // csv += row.join(',');
            // csv += "\n";
    // });
 
    // console.log(csv);
    // var hiddenElement = document.createElement('a');
    // hiddenElement.href = 'data:text/csv;charset=utf-8,' + encodeURI(csv);
    // hiddenElement.target = '_blank';
    // hiddenElement.download = 'people.csv';
    // hiddenElement.click();
// }
//On Page load show graphs
window.onload = function() {
	console.log(new Date().toLocaleTimeString());
	showGraph();
};

//Ajax script to get ADC voltage at every 5 Seconds 
//Read This tutorial https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/

setInterval(function() {
  // Call a function repetatively with 5 Second interval
  getData();
}, 500); //5000mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     //Push the data in array
	var time = new Date().toLocaleTimeString();
	var ADCValue = this.responseText; 
      values.push(ADCValue);
      timeStamp.push(time);
      showGraph();	//Update Graphs
	//Update Data Table	
	  var table = document.getElementById("dataTable");
	  var row = table.insertRow(1);	//Add after headings
	  var cell1 = row.insertCell(0);
	  var cell2 = row.insertCell(1);
	  cell1.innerHTML = time;
	  cell2.innerHTML = ADCValue;
    }
  };
  xhttp.open("GET", "readPOWER", true);	//Handle readADC server on ESP8266
  xhttp.send();
}

</script>
<button onclick="download_csv()">Download CSV</button> 

</body>

</html>

)=====";
