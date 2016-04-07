<?php
 require("adodb.inc.php");
 class myDataBase 
 {
    //数据库处理类
    
    public $_dbAddr="localhost"; //数据库服务器IP 
    public $_dbName="onethink"; //数据库名
    public $_dbUser="root"; //用户名
    public $_dbPwd="root";//密码
    public $_dbType='mysqli';
   
    public $_db=false; //内部实例化过后的数据库连接对象
    
    
    
    function myDataBase($dbtype='mysqli') // __construct
    {
        $this->_dbType = $dbtype ? $dbtype :'mysqli';
        //写一些数据库  connect 过程 
        $this->initConnect();
    }
    function __destruct() //析构函数
    {
         if($this->_db && $this->_db->IsConnected())
         {
            $this->_db->disconnect();
            unset($this->_db);
         }
    }
    function initConnect()
    {
      switch ($this->_dbType) {
        case 'mysqli':
          //mysql 连接方式
          //sqlserver和oracle略有不同，后面再讲
          $this->_db=NewADOConnection("mysqli");//php5 之后的增强版驱动
          $this->_db->connect($this->_dbAddr,$this->_dbUser,$this->_dbPwd,$this->_dbName);
          $this->_db->Query("set names utf8"); //客户端编码
          $this->_db->SetFetchMode(ADODB_FETCH_ASSOC);  //执行查询 返回的数组的key 就是字段名
          break;
        case 'mssql':
          $this->_db=NewADOConnection("mssqlnative");//php5 之后的增强版驱动
          $this->_db->connect($this->_dbAddr,$this->_dbUser,$this->_dbPwd,$this->_dbName);
          break;
        case 'oracle':
          //使用oracle数据库
          
          break;
        default:
          //使用
          break;
      }
        
		
    }
    
    function execForNothing($sql)// 执行一个sql语句，不返回任何值
    {
         $this->_db->Execute($sql);
    }
    function execForArray($sql)
    {
        //执行一个sql语句 ，返回类型是数组
       
        $result=$this->_db->Execute($sql);
      
        if($result)
        {
            $returnArray=array();
            while(!$result->EOF)
            {
                $returnArray[]=$result->fields;
                $result->MoveNext();
            }
            return  $returnArray;
        }
        else
            return  false;
          
        
    }
    function execForOne($sql)
    {
      //执行一个sql语句 ，返回 单列字符串
       
       $result=$this->_db->GetOne($sql); //adodb的函数，来获取单个值
      return $result;
    }
    function execForTrac($sqllist,$resulttype) //用事务 来执行
    {
        
        //$sqllist 参数 是sql数组
        $type=array("none","string","array","int"); //返回类型
        if(!in_array($resulttype,$type)) return false;
        if(count($sqllist)==0) return false;
        $this->_db->BeginTrans(); //开启事务
        $sqlindex=0;
        $ret=false;
        foreach($sqllist as $sql)
        {
            
          
            if($sqlindex==(count($sqllist)-1)) //最后一个语句 需要根据返回类型来做不同的处理
            {
                 if($resulttype=="none")
                 {
                      $this->_db->Execute($sql);
                 }
                  else if($resulttype=="array")
                  {
                    $ret=$this->execForArray($sql);
                  }
                  else if($resulttype=="int" || $resulttype=="string")
                  {
                 
                    $ret=$this->execForOne($sql);
                  }
					else
					{
						 $ret=$this->execForArray($sql);
					}
                   
            }
            else
            $this->_db->Execute($sql);
            $sqlindex++;
        }
        if($ret){
          $this->_db->CommitTrans();
        }else{
          $this->_db->RollbackTrans();
        }
        return $ret;
    }
    
 }
 


?>