<?
//Header für jede PHP/-Datei
//Session starten, falls dies noch nicht passiert ist
if (!isset($_SESSION)){
	session_start();
}
header("Content-Type: text/html; charset=utf-8"); 
date_default_timezone_set('Europe/Berlin');
	
//Setup
function setup(){
	//Counter
	countAll();
	countDay();
}
//IP
function getIp(){
	if (! isset($_SERVER['HTTP_X_FORWARDED_FOR'])) {
		return $_SERVER['REMOTE_ADDR'];
	}
	return $_SERVER['HTTP_X_FORWARDED_FOR'];
}
//Counter
//Algemein
function countAll(){
	$path= $_SERVER["DOCUMENT_ROOT"]."/medien/counter/counter.txt";
	$datei = fopen($path,"r+");
		$counterstand = fgets($datei, 10);
		if(!isset($_SESSION['counter'])){
		   $counterstand++;
		   $_SESSION['counter'] = $counterstand;
		}	
		$counterstand++;
		rewind($datei);
		fwrite($datei, $counterstand);
	fclose($datei);
	return $counterstand;
}

//Tag
function countDay(){
	date_default_timezone_set('Europe/Berlin');
	$path= $_SERVER["DOCUMENT_ROOT"]."/medien/counter/day/".date("z").".txt";
	$datei = fopen($path,"c+");
	chmod($path,0600);
	$counterstand = fgets($datei, 10);
	rewind($datei);
	if($counterstand == ""){
		  $counterstand = 0;
	}
	if(!isset($_SESSION['counter'])){
		//Heute
		$counterstand++;
	}		
	fwrite($datei, $counterstand);
	fclose($datei);
	return $counterstand;
}

// IP-Log
function logIp(){
	$path= $_SERVER["DOCUMENT_ROOT"]."/medien/counter/ip.txt";
	$datei = fopen($path,"a+");
		$iptext = getIp().' - '.$_SESSION['counter'].' - '.time().' - '.$_SERVER['HTTP_REFERER'].' - '.$_SERVER["REQUEST_URI"];
		fwrite($datei, $iptext."\n");
	fclose($datei);
}

//Array ausgeben
function prar($array){
	echo '<pre>';
	print_r($array);
	echo '</pre>';
}
//Logs schreiben
function log_write($logtext, $subject = ''){
	// IP herausfinden
	$ip = getIp();
	$logdatei = fopen($_SERVER["DOCUMENT_ROOT"]."/log/log.txt", "a+");
	$logtext = $_SESSION['userdata']['id'].': '.$_SESSION['userdata']['user'].' | '.$ip.' | '.time().' | '.$logtext;
	fwrite($logdatei, $logtext."\n");
	fclose($logdatei);
	if($subject != ''){
		$log_subjectdatei = fopen($_SERVER["DOCUMENT_ROOT"]."/medien/log/".$subject.".txt", "a+");
		chmod($_SERVER["DOCUMENT_ROOT"]."/medien/log/".$subject.".txt", 0600);
		fwrite($log_subjectdatei, $logtext."\n");
		fclose($log_subjectdatei);
	}
	return false;
}
function timestamp($timestamp){
	return date("m.d.y - H:i:s", $timestamp);
}
function array_from_txt($src, $limit=25, $split=" - "){
	$src = $_SERVER["DOCUMENT_ROOT"].$src;
	if(file_exists($src)){
		$text = array_reverse(file($src));
		$i = 0;
		while($i < $limit){
			if($split != false){
				$return[$i] = explode($split, $text[$i]);
			} else{
				$return[$i] = $text[$i];
			}
			$i++;
		}
		return $return;
	}else{
		return false;
	}
}
function autolink($str, $attributes=array()) {
	$attrs = '';
	foreach ($attributes as $attribute => $value) {
		$attrs .= " {$attribute}=\"{$value}\"";
	}
	$str = ' ' . $str;
	$str = preg_replace(
		'`([^"=\'>])(((http|https|ftp)://|www.)[^\s<]+[^\s<\.)])`i',
		'$1<a href="$2"'.$attrs.'>$2</a>',
		$str
	);
	$str = substr($str, 1);
	$str = preg_replace('`href=\"www`','href="http://www',$str);
	// fügt http:// hinzu, wenn nicht vorhanden
	return $str;
}

function check_email($email) {
    if(!ereg("^[^@]{1,64}@[^@]{1,255}$", $email)) {
        return false;
    }
	$email_array = explode("@", $email);
	$local_array = explode(".", $email_array[0]);
	for ($i = 0; $i < sizeof($local_array); $i++) {
		if(!ereg("^(([A-Za-z0-9!#$%&'*+/=?^_`{|}~-][A-Za-z0-9!#$%&'*+/=?^_`{|}~\.-]{0,63})|(\"[^(\\|\")]{0,62}\"))$", $local_array[$i])) {
			return false;
		}
	}
    if(!ereg("^\[?[0-9\.]+\]?$", $email_array[1])) {
        $domain_array = explode(".", $email_array[1]);
        if(sizeof($domain_array) < 2) {
            return false;
        }
        for($i = 0; $i < sizeof($domain_array); $i++) {
            if(!ereg("^(([A-Za-z0-9][A-Za-z0-9-]{0,61}[A-Za-z0-9])|([A-Za-z0-9]+))$", $domain_array[$i])) {
                return false;
            }
        }
    }
    return true;
}  

//setup
countAll();
countDay();
//prar($_SESSION);

// Ende Functions.php


/*


error_reporting(E_ALL ^  E_NOTICE); 

ob_start(); 
header("Content-Type: text/html; charset=utf-8"); 
// Alles
$datei = fopen("./medien/counter/counter.txt","r+");
$counterstand = fgets($datei, 10);
// IP
if (! isset($_SERVER['HTTP_X_FORWARDED_FOR'])) {
$ip = $_SERVER['REMOTE_ADDR'];
}
else {
$ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
}
$ip_datei = fopen("./medien/counter/ip.txt","a+");
//Heute
date_default_timezone_set('Europe/Berlin');
$datei2 = fopen("./medien/counter/day/".date("z").".txt","c+");
chmod("./medien/counter/day/".date("z").".txt",0600);
$counterstand2 = fgets($datei2, 10);
   if($counterstand2 == ""){
   $counterstand2 = 0;
   }
if(!isset($_SESSION['counter']) and !isset($_GET['alarm'])){
   $counterstand++;
   rewind($datei);
   fwrite($datei, $counterstand);
   //Heute
   $counterstand2++;
   $_SESSION['counter'] = $counterstand;
}
   // IP
   $iptext = $ip.' - '.$_SESSION['counter'].' - '.time().' - '.$_SERVER['HTTP_REFERER'].' - '.$_SERVER["REQUEST_URI"];
   fwrite($ip_datei, $iptext."\n");
//Heute 
   rewind($datei2);
   fwrite($datei2, $counterstand2);
fclose($datei);
fclose($datei2);
$rel = '';
//$rel = $_SERVER["REQUEST_URI"];
if($_GET['qr'] == 1){
	$rel .= '&rel=QR1';
}
if($_GET['qr'] == 2 or $_GET['qr'] == 4 or $_GET['qr'] == 5){
	$rel .= '&autoplay=true';
}
if($_GET['test']){
$rel = './1.7'.$rel;
}
else {
$rel = './0.2'.$rel;
}
?>
<html lang="de">
	<head>
		<style type="text/css">
			body, html{
				margin:0px;
				height:100%;
			}
			body#body::-webkit-scrollbar { 
			display: none; 
			}
		</style>
		<title>
			<? if(isset($_GET['rel'])){ echo $_GET['rel'].' - '; } ?>LED-Board
		</title>
		<meta CHARSET="utf-8" />
		<meta http-equiv="language" content="Deutsch" />
		<meta http-equiv="X-UA-Compatible" content="IE=edge" />
		<meta name="google-site-verification" content="Axt4g_aEnqN9QOaIaHitZj3f9s-EIrZDDG8AxFIvHiI" />
		<meta name='author'      content='Nico Herkner' />
		<meta name="date" content="2017-07-20" />
		<!--<meta name="viewport" content="user-scalable=no, width=325px" />-->
		<meta name="apple-mobile-web-app-capable" content="yes" />
		<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
		<link rel="apple-touch-icon" href="./medien/logo/applelogo60.png" />
		<link rel="apple-touch-icon" sizes="76x76" href="./medien/logo/applelogo76.png" />
		<link rel="apple-touch-icon" sizes="120x120" href="./medien/logo/applelogo120.png" />
		<link rel="apple-touch-icon" sizes="152x152" href="./medien/logo/applelogo152.png" />
		<? 
		if($_GET['rel']){
		echo '<meta id="view" name="viewport"   content="width=1250px, initial-scale=1.0, maximum-scale=3.5" />';
		}
		else {
			echo '<meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0, user-scalable=no" />';
		}
		?>
		<meta name='publisher'   content='Siemens' />
		<meta name='copyright'   content='Siemens' />
		<meta name='keywords'	 content='Siemens, Ausbildung, LED, Board, LED-Board, FPGA' />
		<meta name="description" content=""/>
		<meta name='robots'      content='INDEX, NOFOLLOW' />
		<link rel="icon" href="./medien/logo/favicon.ico" type="image/x-icon" />
	</head>
	<body id="body">
		<form style="display:none;">
			<?				
			if($_SERVER['HTTP_REFERER']){
				echo '<input type="hidden" name="url" value="'.$_SERVER['HTTP_REFERER'].'" />';
			}
			?>
		</form>
		<iframe src="<? echo $rel; ?>" style="height: 100%; width: 100%; border:none; overflow:auto;" />
	
	</body>
</html> */?>