<?php 
   class index extends _Master{
   	   function showindex(){
   	      //测试下数据库操作
          /*
          $db = load_db();

          $newslist=$db->execForArray('select * from onethink_action');
          header('Content-Type:text/html;charset=utf8');
          foreach ($newslist as $value) {
          	 echo '标题：'.$value['title'].' 标注：'.$value['remark'].'<br/>';
          }*/
   	   	  include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/index.php');

   	   	  //最新使用Model
   	   	  // $user = load_model('UserModel');
   	   	  // $user->_view_name = 'onethink_ucenter_member';
   	   	  // $user->_id = 1;
   	   	  // $user->load();
          
          $db = load_db();
          
          $sql[] = "insert into onethink_ucenter_member(username,password,email) values('laikedoud','0931e5bac9c74449eb14fcdbe4223d3c','laike13545@qq.com')";
          $sql[] = 'select LAST_INSERT_ID() into @newuserid';
          $sql[] ="insert into onethink_member(last_login_time,nickname,qq) values(@newuserid,'laikedou','924462390')";
          $sql[] = 'select @newuserid';
          $userid =$db->execForTrac($sql,'int');
          exit('当前用户ID是：'.$userid);

   	   	 

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