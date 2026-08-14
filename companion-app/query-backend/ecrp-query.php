<?php
// ecrp-query.php
// Upload ke hosting Ahmad Store lu, terus samain URL-nya di
// www/index.html (variabel QUERY_BACKEND_URL).
//
// Cara kerja: SA-MP pakai protokol query khusus lewat UDP (bukan HTTP),
// jadi app mobile gak bisa langsung nanya ke server game. Script PHP
// ini yang jadi jembatan: dia yang ngomong UDP ke server SA-MP, lalu
// balikin hasilnya sebagai JSON biasa yang gampang dibaca app.

header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *'); // biar app mobile boleh fetch

$serverIp = '217.216.111.75';
$serverPort = 7034;
$timeoutSec = 2;

function sampQuery(string $ip, int $port, string $opcode, float $timeout) {
    $socket = @fsockopen("udp://$ip", $port, $errno, $errstr, $timeout);
    if (!$socket) return null;
    stream_set_timeout($socket, (int)$timeout);

    $packet = "SAMP" . chr((int)explode('.', $ip)[0]) . chr((int)explode('.', $ip)[1])
             . chr((int)explode('.', $ip)[2]) . chr((int)explode('.', $ip)[3])
             . chr($port & 0xFF) . chr(($port >> 8) & 0xFF) . $opcode;

    fwrite($socket, $packet);
    $response = fread($socket, 2048);
    fclose($socket);
    return $response;
}

$start = microtime(true);
$infoResponse = sampQuery($serverIp, $serverPort, 'i', $timeoutSec);
$pingMs = round((microtime(true) - $start) * 1000);

if ($infoResponse === null || strlen($infoResponse) < 11) {
    echo json_encode(['online' => false]);
    exit;
}

// Format paket 'i' (server info) dari SA-MP:
// header(11 byte) + password(1) + players(2) + maxplayers(2)
// + len(4) + hostname + gamemode_len(4) + gamemode + lang_len(4) + lang
$offset = 11;
$data = substr($infoResponse, $offset);

$password = ord($data[0]);
$players  = unpack('v', substr($data, 1, 2))[1];
$maxPlayers = unpack('v', substr($data, 3, 2))[1];

echo json_encode([
    'online' => true,
    'players' => $players,
    'maxplayers' => $maxPlayers,
    'password' => (bool)$password,
    'ping' => $pingMs,
]);
