<style>
	table td {
		display: inline-block;
		width: 4.7px;
		height: 16px;
		margin: 0;
	}
	tr {
    display: block;
    width: 100%;
}
</style>
<table style="width:100%;">
<?php
	echo shell_exec("/var/www/html/led/main");
?>
</table>