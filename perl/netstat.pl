###################################
### author: www.ttlsa.com ###
### QQ群: 39514058 ###
### E-mail: service@ttlsa.com ###
###################################
use strict;
use Data::Dumper;
use WWW::Curl::Easy;
 
if(!@ARGV){
 print "Usaging: $0 url\n";
 print "For example: $0 www.ttlsa.com\n";
 exit;
}
 
my $curl = new WWW::Curl::Easy;
open my $response_body,">/dev/null";
$curl->setopt(CURLOPT_HEADER,1);
$curl->setopt(CURLOPT_URL, $ARGV[0]);
$curl->setopt(CURLOPT_WRITEDATA,\$response_body);
$curl->perform;
my $err = $curl->errbuf;
if(!$err){
 my $st = &getTime;
 my $http_code = $curl->getinfo(CURLINFO_RESPONSE_CODE);
 my $http_dns_time = $curl->getinfo(CURLINFO_NAMELOOKUP_TIME);
 my $http_conn_time = $curl->getinfo(CURLINFO_CONNECT_TIME);
 #my $http_APP_time = $curl->getinfo(CURLINFO_APPCONNECT_TIME);
 my $http_PRE_TRAN_time = $curl->getinfo(CURLINFO_PRETRANSFER_TIME);
 my $http_START_TRAN_time = $curl->getinfo(CURLINFO_STARTTRANSFER_TIME);
 my $http_TOTAL_time = $curl->getinfo(CURLINFO_TOTAL_TIME);
 my $http_SIZE_DOWN = $curl->getinfo(CURLINFO_SIZE_DOWNLOAD);
 my $http_SPEED_DOWN = $curl->getinfo(CURLINFO_SPEED_DOWNLOAD);
 
 printf "local_time: %s, http_code: %d, dns_time: %.3fms, conn_time: %.3fms, pre_tran_time: %.3fms, start_tran_time: %.3fms, total_time: %.3fms, size_download: %dB, speed_download: %dB/s",($st,$http_code,$http_dns_time,$http_conn_time,$http_PRE_TRAN_time,$http_START_TRAN_time,$http_TOTAL_time,$http_SIZE_DOWN,$http_SPEED_DOWN);
 write;
 
 format STDOUT_TOP=
 站点各类响应时间明细-@||
 $%
 =========================
 +---------------------+------+-------------+--------------+--------------------------+------------------------+-------------+-----------+------------+
 | 本地时间 | 状态 | DNS解析时间 | 建立连接时间 | 从建立连接到准备传输时间 |从建立连接到开始传输时间| 整个过程时间| 下载数据量|平均下载速度|
 +---------------------+------+-------------+--------------+--------------------------+------------------------+-------------+-----------+------------+
 .
 
 format STDOUT=
 |@<<<<<<<<<<<<<<<<<<<<| @<<<<| @<<<<<<<<<<<| @<<<<<<<<<<<<| @<<<<<<<<<<<<<<<<<<<<<<<<| @<<<<<<<<<<<<<<<<<<<<<<| @<<<<<<<<<<<| @<<<<<<<<<| @<<<<<<<<<<|
 $st,$http_code,$http_dns_time."ms",$http_conn_time."ms",$http_PRE_TRAN_time."ms",$http_START_TRAN_time."ms",$http_TOTAL_time."ms",$http_SIZE_DOWN."B",$http_SPEED_DOWN."B/s"
 +---------------------+------+-------------+--------------+--------------------------+------------------------+--------------+----------+------------+
 .
}else{
 print "Error: $err\n";
}
 
sub getTime()
{
 my @time=(localtime)[5,4,3,2,1,0];
 $time[0]+=1900;
 $time[1]+=1;
 return sprintf("%04u-%02u-%02u %02u:%02u:%02u",@time);
}