<html>
	<head>
		<meta charset="UTF-8" />
		<link rel="stylesheet" href="./css/style.css" />
		<script src="./js/jquery.js"></script>
		<script type="text/javascript" src="./js/jquery.form.js"></script>
		<script>
			$(document).ready(function(){
				/* Hier der jQuery-Code */
				bildAnzeigen();
			});
			function bildAnzeigen(){
					div_width = $("#wrapper").width()/250;
					//alert(div_width);
					$("#load").load("./php/time.php", function(){
						$("#anzeige table").load("./php/bild.php", function(){
							$("#anzeige td").height(div_width).width(div_width).css("margin", "0" + 0*div_width*0.2);
							$("#anzeige table").width(div_width*176*1.4);
							$("#anzeige td").click(function(){
								$(this).fadeTo(2000,0);
							});
						});
					});
			}
			function fileUpload(form, result){
				$(result).html('').html('<img style="margin-top: 6px; margin-bottom: -13px;" src="./img/loading.gif" /><br /><br />Wird hochgeladen...');
				$(form).ajaxForm({target: result},bildAnzeigen()).submit(function(){
					bildAnzeigen();
				});
				
			}
			function neuesBild(input_name){
				$("form " + input_name).attr("value", "neues Bild ausw&auml;len...");
			}
			function gpioStatus(delay=25000){
				$("#gpioStatus").load("./php/gpioStatus.php").before("Hallo");
				setInterval(function(){
					$("#gpioStatus").load("./php/gpioStatus.php");
				
				}, delay);
			}
		</script>
		<title></title>
	</head>
	<body>
		<div id="outer-wrapper">
			<div id="wrapper">
				<div id="load"></div>
				<div id="anzeige"><table border="0"></table></div>
				<hr />
				<h1 onclick="bildAnzeigen();" style="cursor: pointer;">Bild (.bmp) hochladen</h1>
				<form action="./php/upload.php" id="bmp_upload" method="post" enctype="multipart/form-data" onsubmit="neuesBild('#bild');">
					<input id="bild" form="bmp_upload" value="Bild ausw&auml;len..." type="file" name="datei" onchange="fileUpload('#bmp_upload', '#form_result'); $('#bmp_upload').submit();"/><br /><br />
					<input type="submit" form="bmp_upload" value="Upload Bild" onclick="fileUpload('#bmp_upload', '#form_result');"><br/>
				</form>
				<div id="form_result"></div>
				<br />
				
				<!--<div id="gpioStatus"><span href="#" onclick="gpioStatus();">GPIO-Status laden</span></div>-->
			</div>
		</div>	
	</body>
</html>