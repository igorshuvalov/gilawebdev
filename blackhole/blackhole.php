<?php /*

Title: Perishable Press Blackhole for Bad Bots
Description: Automatically trap and block bots that don't obey robots.txt rules
Project URL: http://perishablepress.com/press/2010/07/14/blackhole-bad-bots/
Author: Jeff Starr, aka perishable
Release: July 13th, 2010
Version: 1.2

Credits: The Blackhole includes customized/modified versions of these fine scripts:
 - Network Query Tool @ http://www.drunkwerks.com/docs/NetworkQueryTool/
 - Kloth.net Bot Trap @ http://www.kloth.net/internet/bottrap.php

License: Copyright (c) 2010 by Jeff Starr (aka perishable)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation 
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, 
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Usage: Visit Perishable Press for complete installation, configuration, and usage instructions:
http://perishablepress.com/press/2010/07/14/blackhole-bad-bots/

*/

if (phpversion() >= "4.2.0") {
	extract($_SERVER);
}
$badbot = 0; // set default value
$filename = DRUPAL_ROOT . "/blackhole/blackhole.dat"; // scan to prevent duplicates
$fp = fopen($filename, "r") or die("\t\t\t<p>Error opening file...</p>\n\t\t</div>\n\t</body>\n</html>");
while ($line = fgets($fp)) {
	if (!preg_match("/(googlebot|slurp|msnbot|teoma|yandex)/i", $line)) {
		$u = explode(" ", $line);
		if ($u[0] == $_SERVER['REMOTE_ADDR']) ++$badbot;
	}
}
fclose($fp);

// display message for bad bots
if ($badbot > 0) { // sleep(10); ?>
<!DOCTYPE html>
	<title>Access Denied</title>
	<h1>You have been banned from this domain</h1>
	<p>If you think there has been a mistake, send a message to 
		<a href="http://twitter.com/perishable" title="Perishable on Twitter">@perishable</a> 
		and we&rsquo;ll sort it out.
	</p>
</html>
<?php exit; } ?>