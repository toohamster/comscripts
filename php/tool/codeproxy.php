<?php
header('Content-type: text/html;charset=utf-8');

if ( empty($_REQUEST['code']) || empty($_REQUEST['path']) )
{
	echo "请指定 code 和 path 两个参数";
	exit;
}

header("Location: {$_REQUEST['path']}", true, $_REQUEST['code']);