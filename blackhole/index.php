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

*/ ?>
<!DOCTYPE html>
	<title>Welcome to Blackhole!</title>
	<style>
		body {
			font: 14px/1.5 Helvetica, Arial, sans-serif;
			background-color: #851507; color: #fff;
			}
			#blackhole { margin: 20px auto; width: 700px; }
			pre {
				background-color: #B34334;
				white-space: pre-line;
					-webkit-border-radius: 10px;
					-khtml-border-radius: 10px;	
					-moz-border-radius: 10px;
				border-radius: 10px;
				padding: 20px;
				}
			a { color: #fff; }
	</style>
	<body>
		<div id="blackhole">
			<h1>You have fallen into a trap!</h1>
			<p>This site&rsquo;s <a href="http://example.com/robots.txt">robots.txt</a> file explicitly forbids your presence at this location. 
				The following Whois data will be reviewed carefully. If it is determined that you suck, you will be banned from this site. 
				If you think this is a mistake, <em>now</em> is the time to <a href="http://example.com/contact/">contact me</a>.</p>

<?php // customized version of Network Query Tool http://www.shat.net/php/nqt/
if (phpversion() >= "4.2.0") {
	extract($_POST);
	extract($_GET);
	extract($_SERVER);
	extract($_ENV);
	}
$target = $REMOTE_ADDR;
function arin($target) {
	global $msg, $target;
	$server = "whois.arin.net";
	if (!$target = gethostbyname($target)) {
		$msg .= "Can't IP Whois without an IP address.";
	} else {
		if (! $sock = fsockopen($server, 43, $num, $error, 20)) {
			unset($sock);
			$msg .= "Timed-out connecting to $server (port 43).";
		} else {
			fputs($sock, "$target\n");
			while (!feof($sock))
			$buffer .= fgets($sock, 10240); 
			fclose($sock);
		}
		if (eregi("RIPE.NET", $buffer)) {
			$nextServer = "whois.ripe.net";
		} else if (eregi("whois.apnic.net", $buffer)) {
			$nextServer = "whois.apnic.net";
		} else if (eregi("nic.ad.jp", $buffer)) {
			$nextServer = "whois.nic.ad.jp";
			$extra = "/e"; // suppress JaPaNIC character output
		} else if (eregi("whois.registro.br", $buffer)) {
			$nextServer = "whois.registro.br";
		}
		if ($nextServer) {
			$buffer = "";
			message("Deferred to specific whois server: $nextServer...");
			if (! $sock = fsockopen($nextServer, 43, $num, $error, 10)) {
				unset($sock);
				$msg .= "Timed-out connecting to $nextServer (port 43)";
			} else {
				fputs($sock, "$target$extra\n");
				while (!feof($sock))
				$buffer .= fgets($sock, 10240);
				fclose($sock);
			}
		}
		$msg .= nl2br($buffer);
	}
	$msg = trim(ereg_replace('#', '', strip_tags($msg)));
	message($msg);
}
// execute message function
function message($msg) {
	global $msg, $target;
	$timestamp = time();
	echo "\t\t\t" . "<h3>Your IP Address is " . $target . "</h3>" . "\n";
	echo "\t\t\t" . "<pre>WHOIS Lookup for " . $target . "\n" . date("l, F jS Y @ H:i:s", $timestamp) . "\n\n" . $msg . "</pre>" . "\n";
	flush();
}
// check target validity | bugfix
if ((!$target) || (!preg_match("/^[\w\d\.\-]+\.[\w\d]{1,4}$/i", $target))) { 
	message("Error: You did not specify a valid target host or IP.");
	exit;
}
// whois lookup
arin($target);

// modified version of http://www.kloth.net/internet/bottrap.php
$badbot = 0; // set default value
$filename = "blackhole.dat"; // scan to prevent duplicates
$fp = fopen($filename, "r") or die("\t\t\t<p>Error opening file...</p>\n\t\t</div>\n\t</body>\n</html>");
while ($line = fgets($fp)) {
	$u = explode(" ", $line);
	if ($u[0] == $_SERVER['REMOTE_ADDR']) ++$badbot;
}
fclose($fp);

// if bot is unique, send email and log entry
if ($badbot == 0) { // check for unlisted bot
	global $msg, $target;
	$tmestamp  = time();
	$datestamp = date("l, F jS Y @ H:i:s", $tmestamp);
	$sender    = "email@example.com";
	$recipient = "email@example.com";
	$subject   = "Bad Bot Alert!";
	$message   = $datestamp . "\n\n";
	$message  .= "URL Request: " . $_SERVER['REQUEST_URI'] . "\n";
	$message  .= "IP Address: " . $_SERVER['REMOTE_ADDR'] . "\n";
	$message  .= "User Agent: " . $_SERVER['HTTP_USER_AGENT'] . "\n\n";
	$message  .= "Whois Lookup: " . "\n";
	$message  .= "\n" . $msg . "\n";
	mail($recipient, $subject, $message, "From: $sender"); // send email

	$fp = fopen($filename, 'a+'); // append to blackhole.dat
	fwrite($fp, $_SERVER['REMOTE_ADDR'] ." - ". $_SERVER['REQUEST_METHOD'] ." - ". $_SERVER['SERVER_PROTOCOL'] ." - ". $datestamp ." - ". $_SERVER['HTTP_USER_AGENT'] ."\n");
	fclose($fp);
} ?>

			<p><a href="http://perishablepress.com/press/2010/07/14/blackhole-bad-bots/" title="Blackhole for Bad Bots">Blackhole v1.2</a></p>
		</div>
	</body>
</html>