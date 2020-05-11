#!/usr/bin/perl
#skaner.pl
#wersja 1.0
#Nachszon
#marzec 2017

#Skrypt przyjmuje i obs�uguje parametry przekazane stron� html
#Jest komponentem skanera sieciowego
#Skan odbywa si� wed�ug schematu:
#Sprawd� ruch z hosta sourceHostString do hosta destinationHostString na porcie portString



use CGI
$query=new CGI;

#Warto�ci parametr�w przyporz�dkowane s� odpowiednio zmiennym:
#$sourceHostString - host �r�dowy
#$destinationHostString - host docelowy
#$portString - port
$sourceHostString=$query->param('string_source_host');
$destinationHostString=$query->param('string_destination_host');
$portString=$query->param('string_port');


#weryfikacja poprawnosci przekazanych danych
#w parametrze odpowiadaj�cym hostowi �r�d�owemu
#Je�eli parametr zawiera jeden z podanych w warunku if znak�w
#zako�cz dzia�anie skryptu z komunikatem b��du
if ($sourceHostString =~ /[\/@;,]/){

exec "source_host_errorskaner.sh";

exit;

}

#weryfikacja poprawnosci przekazanych danych
#w parametrze odpowiadaj�cym hostowi docelowemu
#Je�eli parametr zawiera jeden z podanych w warunku if znak�w
#zako�cz dzia�anie skryptu z komunikatem b��du
if ($destinationHostString =~ /[\/@;,]/){

exec "errorskaner.sh";

exit;

}

#weryfikacja poprawnosci przekazanych danych
#w parametrze odpowiadaj�cym portowi
#Je�eli parametr nie jest liczb�
#zako�cz dzia�anie skryptu z komunikatem b��du
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
<input type="button" value="powr�t" onClick="history.back()">
</form>

</div>
</body>

</html>

STOP


