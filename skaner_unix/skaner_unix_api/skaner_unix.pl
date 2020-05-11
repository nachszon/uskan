#!/usr/bin/perl
#skaner.pl
#wersja 1.0
#Nachszon
#marzec 2017

#Skrypt przyjmuje i obs³uguje parametry przekazane stronê html
#Jest komponentem skanera sieciowego
#Skan odbywa siê wed³ug schematu:
#SprawdŸ ruch z hosta sourceHostString do hosta destinationHostString na porcie portString



use CGI
$query=new CGI;

#Wartoœci parametrów przyporz¹dkowane s¹ odpowiednio zmiennym:
#$sourceHostString - host Ÿródowy
#$destinationHostString - host docelowy
#$portString - port
$sourceHostString=$query->param('string_source_host');
$destinationHostString=$query->param('string_destination_host');
$portString=$query->param('string_port');


#weryfikacja poprawnosci przekazanych danych
#w parametrze odpowiadaj¹cym hostowi Ÿród³owemu
#Je¿eli parametr zawiera jeden z podanych w warunku if znaków
#zakoñcz dzia³anie skryptu z komunikatem b³êdu
if ($sourceHostString =~ /[\/@;,]/){

exec "source_host_errorskaner.sh";

exit;

}

#weryfikacja poprawnosci przekazanych danych
#w parametrze odpowiadaj¹cym hostowi docelowemu
#Je¿eli parametr zawiera jeden z podanych w warunku if znaków
#zakoñcz dzia³anie skryptu z komunikatem b³êdu
if ($destinationHostString =~ /[\/@;,]/){

exec "errorskaner.sh";

exit;

}

#weryfikacja poprawnosci przekazanych danych
#w parametrze odpowiadaj¹cym portowi
#Je¿eli parametr nie jest liczb¹
#zakoñcz dzia³anie skryptu z komunikatem b³êdu
unless ($portString =~ /^([+-]?)(?=\d|\.\d)\d*(\.\d*)?([Ee]([+-]?\d+))?$/){

	exec "errorskaner.sh";
	
	exit;

}

#Wykonanie skryptu shellowego z parametrami
#pobranymi ze strony html
my $executableFile='skaner.sh';

exec "$executableFile  $sourceHostString  $destinationHostString $portString"; 


print<<STOP;
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">

<html>
<head>
<META content="text/html; charset=iso-8859-2" http-equiv=content-type>
</META>

<body>

<div align="center">

<form name="Historia">
<input type="button" value="powrót" onClick="history.back()">
</form>

</div>
</body>

</html>

STOP


