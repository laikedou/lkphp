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
?>