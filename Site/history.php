<script type="text/javascript">
    $(function () {
        $('#container').highcharts({
            title: {
                text: 'Sample Home Data',
                style: {
                    color: '#2191C0',
                    fontWeight: 'bold'
                }
            },
            xAxis: {
                tickInterval: 250
            },
            yAxis: { // left y axis
                title: {
                    style: {
                        color: '#2191C0',
                        fontWeight: 'bold'
                    },
                    text: 'Function results'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            legend: {
                align: 'left',
                verticalAlign: 'top',
                y: 50,
                x: 70,
                floating: true,
                borderWidth: 0
            },
            tooltip: {
                shared: true,
                crosshairs: true
            },
            	
            series: [{
                data :[<?php echo join($data, ',') ?>],
                color: '#2191C0'
            }]
        });
    });

</script>
<div id="container" style="min-width: 1500px; height: 500px; margin: 0 auto"></div>