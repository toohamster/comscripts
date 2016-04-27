<?php
/**
 * 简单的加密/解密 实现
 */
class SimpleEncrypt
{

	/**
	 * 用于加密的code
	 * @var string
	 */
	private $code = 'kenxu!@#';

	function __construct($code)
	{
		if ( !empty($code) ) $this->code = trim($code);
	}

	/**
	 * 创建加密__hash__ 通过时间戳判断有效期
	 * 
     * @param  string $str 待加密的串
	 * @param  bool $expired_destruct 过期自毁标识
	 * 
	 * @return array
	 */
    function encrypt($str, $expired_destruct=false)
    {
    	$et = time();
        $ed = intval($expired_destruct) == 0 ? 0 : 1;
    	$hash = SimpleEncryptDes::instance($this->code)->encrypt("{$str}_{$ed}{$et}");
        return array(
        		'et'	=> $et,		// 生成时间
        		'hash'	=> $hash, 	// 生成的hash串
        	);
    }

    /**
     * 解密 __hash__
     * 
     * @param string  $hash 需要解密的字符
     * @param int $time 有效期
     * 
     * @return array
     */
    function decrypt($hash, $time = 600)
    {
    	$dt = time();
        $str = SimpleEncryptDes::instance($this->code)->decrypt($hash);
        $arr  = explode("_",$str);

        $tc = count($arr);
        if ( $tc > 1 )
        {
        	$eta = $arr[$tc - 1];
            $len = strlen($str) - strlen("_{$eta}");

            $ed = intval(substr( $eta, 0,1));
            $et = substr( $eta, 1);            

        	return array(
        			'str'	=> substr($str, 0, $len), // 原文
        			'expired'	=> $dt > ($et + $time) ? 1 : 0,// 是否过期
                    'ed'    => $ed, // 过期自毁标识
        			'et'	=> $et,	// 生成时间
        			'dt'	=> $dt,// 解析时间
        		);

        }

        return false;
    }

}

/**
 * DES加密, 为了保证java和object-c 跨平台的兼容性必须是8位
 */
class SimpleEncryptDes
{
	
	private function __construct($secret_key)
    {
        $this->_secret_key = trim($secret_key);
    }

    /**
     * 获取 特定加密对象
     * 
     * @param  string $code
     * 
     * @return SimpleEncryptDes
     */
    static function instance($code)
    {
    	static $its = array();
    	
    	if(empty($code) || strlen($code) != 8)
        {
            throw new Exception(sprintf('fail, deskey非法 code=%s', $code));
        }

    	if ( empty($its[$code]) )
    	{
    		$its[$code] = new self( $code );
    	}

    	return $its[$code];
    }

    function encrypt($string)
    {
        $ivs=array(0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF);
        $iv = '';

        foreach ($ivs as $s)
        {
            $iv .= chr($s);
        }

        $size   = mcrypt_get_block_size(MCRYPT_DES, MCRYPT_MODE_CBC );  
        $string = $this->_pkcs5Pad ( $string, $size );  

        $data =  mcrypt_encrypt(MCRYPT_DES, $this->_secret_key, $string, MCRYPT_MODE_CBC, $iv);
        return base64_encode($data);
    }

    function decrypt($string)
    {
        $ivs=array(0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF);
        $iv = '';
        foreach ($ivs as $s)
        {
            $iv .= chr($s);
        }

        $result = mcrypt_decrypt(MCRYPT_DES, $this->_secret_key, base64_decode($string), MCRYPT_MODE_CBC, $iv);
        $result = $this->_pkcs5Unpad( $result );
        return $result;
    }

    private function _pkcs5Pad($text, $blocksize)
    {
        $pad = $blocksize - (strlen( $text ) % $blocksize);  
        return $text . str_repeat( chr( $pad ), $pad );  
    }  
  
    private function _pkcs5Unpad($text)
    {  
        $pad = ord( $text {strlen ( $text ) - 1} );  
        if ($pad > strlen( $text ))  return false;  
        if (strspn( $text, chr( $pad ), strlen( $text ) - $pad ) != $pad)  
            return false;  
        return substr( $text, 0, - 1 * $pad );  
    }
}
