<?php

   function load_db(){
     $db_path=LKPHP_PATH.'/Libary/DataBase/myDataBase.php';
     if(!class_exists('myDataBase')){
          require($db_path);
     }
     return new MyDataBase();
   }
   function load_model($modelName){
   	$_Model_Path = LKPHP_PATH.'/MVC/Model/_Model.inc';//基类Model
   	if(!class_exists('_Model')){
         require($_Model_Path);
   	}
   	$_mdPath = LKPHP_PATH.'/MVC/Model/'.$modelName.'.inc';//基类Model

    if(!class_exists($modelName)){
    	require($_mdPath);
    }
   	return new $modelName();
   }

// the_XXX系列

/*
 * 获取get参数
 * 当$ispost是true是代表获取post参数 默认是false 
 */
function the_get($get_key,$ispost=false)
 {
 	 $parameters=$ispost?$_POST:$_GET;
     if(!isset($parameters[$get_key])) return "";
	 $str=$parameters[$get_key];
    //过滤危险字符、敏感字符通用函数
    //第一步：通过正则过滤掉我需要过滤的标记
     $farr = array(
    "/<(\/?)(script|i?frame|style|html|body|title|link|meta|\?|\%)([^>]*?)>/isU");
    //过滤类似 <script>  <style> <object>  <meta 等
     $str = preg_replace($farr,"",$str);
     $str=addslashes($str); //对单引号、双引号等预定义字符 前面加上反斜杠 如'变成\'
    
     //第二步 过滤敏感词汇
   
     $str=str_replace(explode(",", LKPHP_UNSAFEWORDS),"***",$str);
     return trim($str);
 }
 /*
  * 获取当前用户的IP地址，无参数
  */
 function the_ip()
 {
    if (getenv("HTTP_CLIENT_IP") && strcasecmp(getenv("HTTP_CLIENT_IP"), "unknown")) 
        $ip = getenv("HTTP_CLIENT_IP"); 
    else
        if (getenv("HTTP_X_FORWARDED_FOR") && strcasecmp(getenv("HTTP_X_FORWARDED_FOR"), "unknown")) 
            $ip = getenv("HTTP_X_FORWARDED_FOR"); 
        else
            if (getenv("REMOTE_ADDR") && strcasecmp(getenv("REMOTE_ADDR"), "unknown")) 
                $ip = getenv("REMOTE_ADDR"); 
            else
                if (isset ($_SERVER['REMOTE_ADDR']) && $_SERVER['REMOTE_ADDR'] && strcasecmp($_SERVER['REMOTE_ADDR'], "unknown")) 
                    $ip = $_SERVER['REMOTE_ADDR']; 
                else
                    $ip = "unknown"; 
    return ($ip); 
 }
 
 /*
  * 获取当前登录用户
  * 返回值是个model 如果用户没有登录则返回false
  */
 function the_user()
 {
	//可以使用cookie 也可以使用session
 	return isset($_COOKIE[LKPHP_USERCOOKIE])?json_decode($_COOKIE[LKPHP_USERCOOKIE]) :false;
 }
 
 //根据cacheKey或来获得缓存内容
function the_cache($cacheKey)
{
	//这里我们使用memcached
	return false;
}
?>
<?php
 //is_XX系列  如判断用户是否登录 字符串格式
 
 /*
  * 判断用户是否登录
  */
  function is_login()
 {
    //用户是否登录
     if(the_user()) return true;
     return false;
 }
  
  //判断字符串是否符合email格式 
 function is_email($email)
 {
 	return ereg("/^[a-z]([a-z0-9]*[-_\.]?[a-z0-9]+)*@([a-z0-9]*[-_]?[a-z0-9]+)+[\.][a-z]{2,3}([\.][a-z]{2})?$/i",$email);
 }
?>
<?php
  //set_XX系列，譬如更新缓存或者更新一个model
  
  //更新缓存
  function set_cache($cacheKey)
  {
  	
  }
  //更新一个model
  function set_model($model)
  {
  	
  }
  //设置当前登录用户
  function set_user($md,$time){
  	if($time<0){
            //代表注销
  		setcookie(LKPHP_USERCOOKIE,'',time()-3600,'/');
  	}else{
  		//代表登录成功
             setcookie(LKPHP_USERCOOKIE,json_encode($md),time()+$time,'/');//对对象进行json编码
  	}
  }
?>
