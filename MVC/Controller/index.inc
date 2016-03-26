<?php 
   class index extends _Master{
   	   function showindex(){
   	   	$this->setView('index');
   	   	//设置一些个变量 
   	   	$this->setVar('title','测试一下大家的灵活性！');
   	   	$userlist = array();
   	   	$userlist[] = array('username'=>'laike','usernickname'=>'kedou');
   	   	$userlist[] = array('username'=>'john','usernickname'=>'johnhack');
   	   	$userlist[] = array('username'=>'philip','usernickname'=>'philips');
   	   	$this->setVar('userlist',$userlist);
   	   }
   }
 ?>