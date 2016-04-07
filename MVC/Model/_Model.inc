<?php 
   abstract class _Model{
      public $_view_name ='';
      public $_id = 0;
      public $_id_key='id';//主键的字段名

      function load($where=''){ 

      	if($this->_view_name === ''||$this->_id === 0) return;
      	$vars = get_object_vars($this);
      	$sql ='';
      	foreach ($vars as $key => $value) {

      		if(trim($value) === ''){

      			if($sql !== ''){
      				$sql .=',';
      			}
      			$sql .=$key;
      		}
      	}

      	
      	if($sql === '') return;
      	$sql = 'select '.$sql.' from '.$this->_view_name.' where ';
      	if($where === ''){
      		$sql.=$this->_id_key.'='.$this->_id;
      	}else{
      		$sql .= $where;
      	}
      	$db = load_db();
      	$ret = $db->execForArray($sql);
      	if($ret && count($ret) ===1){
      		$ret = $ret[0];
      		$var_keys = array_keys($vars);
      		foreach ($ret as $key => $value) {
      			 if(in_array($key,$var_keys)){
      			 	$this->$key = $value;
      			 }
      		}
      	}

      }

   }
 ?>