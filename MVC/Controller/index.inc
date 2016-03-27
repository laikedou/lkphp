<?php 
   class index extends _Master{
   	   function showindex(){
   	   	$this->setView('index');
   	   	//设置一些个变量 
   	   	$this->setVar('title','测试一下大家的灵活性！');
                    $md = load_model('UserModel');
                    $md->user_id = 3;
                    $md->user_name='laike';
                    $md->user_email='lake1355@qq.com';
                    $md->user_pass='test';
                    set_user($md,3600);

                    if(is_login()){
                       $this->setVar('userState','当前用户是：'.the_user()->user_name);
                    }else{
                        $this->setVar('userState','当前用户未登录');
                    }
   	   }
   }
 ?>