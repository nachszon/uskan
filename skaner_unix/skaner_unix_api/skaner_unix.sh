#!/bin/bash
#skaner.sh
#wersja 1.0
#Nachszon
#marzec 2017

#program wywo�uje agenta na ho�cie przerzutowym
#agent na ho�cie przerzutowym:
#-wywo�uje agenta na ho�cie �r�d�owym
#-przekazuje parametry  "host docelowy" oraz "port" do agenta na ho�cie �r�d�owym

printf "Content-type: text/html\n\n";




ssh user@remote_host "$path/skaner_unix_$1.sh" $2 $3



cat << STOP
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


