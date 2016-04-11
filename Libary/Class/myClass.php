<?php 
       /**
       * 虚拟注入类实现
       */
       class myClass
       {
       	    var $xmlContent="";
       	    var $funcList = array();
       	
	       	function myClass($xmlname)
	       	{
               $xmlurl = LKPHP_PATH.'Libary/Class/'.$xmlname.'.xml';
               
               $this->xmlContent = file_get_contents($xmlurl);
               $this->loadXml();
	       	}
	       	function loadXml(){
	       		$conf = (array)simplexml_load_string($this->xmlContent);
	       		
	       		foreach ($conf['func'] as $func) {
	       			$this->funcList[strval($func->name)] = array(
	       				 'sql'=>strval($func->sql),
	       				 'description'=>strval($func->description),
	       				 'resultType'=>strval($func->resultType)
	       				);
	       		}

	       	}
	       	function getSqlByParams($sql,$funcParams){
	       		if(!$funcParams || count($funcParams) === 0) return $sql;
	       		$index = 0;
	       		foreach ($funcParams as $p) {
	       			$sql = str_replace('#{'.$index.'}',$p,$sql);
	       			$index++;
	       		}
	       		return $sql;
	       	}
	       	function __call($funcName,$funcParams){
	       		//echo '执行了'.$funcName.'但是这个方法没有定义，因此本函数来接管';
	       		if(array_key_exists($funcName,$this->funcList)){
	       			$db = load_db();
	       			$sql = $this->funcList[$funcName]['sql'];
	       			if(explode(';',$sql)>1){
                         $sqls = explode(';',$sql);
                         $sqlList = array();
                         foreach ($sqls as $s) {
                         	$s = $this->getSqlByParams($s,$funcParams);//过滤参数
                         	$s = str_replace(array('\n',PHP_EOL,'\t'),'',$s);
                         	$sqlList[] = $s;
                         }
                         //这里要直接使用事务进行执行
                         return $db->execForTrac($sqlList,$this->funcList[$funcName]['resultType']);
	       			}
	       			$sql = $this->getSqlByParams($sql,$funcParams);
	       			switch ($this->funcList[$funcName]['resultType']) {
	       				case 'array':
	       					return $db->execForArray($sql);
	       					break;
	       				case 'int':
	       				    return intval($db->execForOne($sql));
	       				case 'string':
	       				    return strval($db->execForOne($sql));
	       				default:
	       					//默认使用返回数组的方式
	       					return $db->execForArray($sql);
	       					break;
	       			}
	       			
	       		}
	       	}

       }
 ?>