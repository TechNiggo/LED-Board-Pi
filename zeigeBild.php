<style>
	table td {
		display: inline-block;
		height: 7.196px;
		width: 7.196px;
		margin: 0;
	}
	tr {
		display: block;
		width: 100%;
	}
	table {
		background: #444;
		margin: 0 auto;
	}
</style>
<table>
<?php
	echo shell_exec("/var/www/html/led/main");
?>
</table>