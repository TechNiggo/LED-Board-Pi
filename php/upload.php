<?php
//Session starten, falls dies noch nicht passiert ist
session_set_cookie_params(10800);
if (!isset($_SESSION)){
	session_start();
}
$_SESSION['counter']="-1";
$upload_folder = '../../medien/upload/'; //Das Upload-Verzeichnis
$filename = pathinfo($_FILES['datei']['name'], PATHINFO_FILENAME);
$extension = strtolower(pathinfo($_FILES['datei']['name'], PATHINFO_EXTENSION));
 
 
//Überprüfung der Dateiendung
$allowed_extensions = array('bmp');
if(!in_array($extension, $allowed_extensions)) {
 die("Ung&uuml;ltige Dateiendung. Nur bmp-Dateien sind erlaubt");
}
 
//Überprüfung der Dateigröße
$max_size = 500*1024; //500 KB
if($_FILES['datei']['size'] > $max_size) {
 die("Bitte keine Dateien gr&ouml;ßer 500kb hochladen");
}
 
//Überprüfung dass das Bild keine Fehler enthält
/*if(function_exists('exif_imagetype')) { //Die exif_imagetype-Funktion erfordert die exif-Erweiterung auf dem Server
 $allowed_types = array(IMAGETYPE_PNG, IMAGETYPE_JPEG, IMAGETYPE_GIF);
 $detected_type = exif_imagetype($_FILES['datei']['tmp_name']);
 if(!in_array($detected_type, $allowed_types)) {
 die("Nur der Upload von Bilddateien ist gestattet");
 }
}*/
 
//Pfad zum Upload
$new_path = $upload_folder.$filename.'.'.$extension;
 
//Neuer Dateiname falls die Datei bereits existiert
if(file_exists($new_path)) { //Falls Datei existiert, hänge eine Zahl an den Dateinamen
 $id = 1;
 do {
 //$new_path = $upload_folder.$filename.'_'.$id.'.'.$extension;
 $new_path = $upload_folder.$id.'.'.$extension;
 $id++;
 } while(file_exists($new_path));
}
 
//Alles okay, verschiebe Datei an neuen Pfad
move_uploaded_file($_FILES['datei']['tmp_name'], $new_path);
// Kopiere die Datei immer zum seleben Pfad
copy ($new_path, $upload_folder.'aktuell.'.$extension);
//echo 'Bild erfolgreich hochgeladen: <a href="'.$new_path.'">'.$new_path.'</a><br />Bild erfolgreich kopiert: <a href="'.$upload_folder.'aktuell.'.$extension.'">'.$upload_folder.'aktuell.'.$extension.'</a><br />';
echo 'Bild erfolgreich hochgeladen und kopiert<br /><a href="#" onclick="bildAnzeigen();">Bild neuladen...</a>';
// in Log schreiben
$log_datei = fopen("../log/upload.txt","a+");
$log = $_SESSION['counter'].' - '.time().' - '.$filename.' - '.$_FILES['datei']['size'].' - ';//.$id;
fwrite($log_datei, $log."\n");
//echo '<a href="./">Zur&uuml;ck"</a>';
?>