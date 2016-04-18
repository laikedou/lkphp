<?php 
  //所有controller的父类 抽象类 
  abstract class _Master{
     var $_view='index';//模板名称
     var $_vars = array();
     var $_cachetime=0;//缓存时间
     function setView($viewName){
         $this->_view = $viewName;
     }
     function getView(){
     	return LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.$this->_view.'.'.LKPHP_EXTENSION;
     }
     function setVar($varName,$varValue){
         //设置变量
        $this->_vars[$varName] = $varValue;
     }
     function hasVarCache(){
        if(the_cache($this->_view)){
            return true;
        }
        return false;
     }
     function run(){
     	
        //解包变量
        if($this->_cachetime > 0){
            $getVars_cache = the_cache($this->_view);
            if($getVars_cache){
                echo '<b>这是从memcache中获取的数据</b><br/>';
                extract($getVars_cache);
            }else{
                //同时要设置缓存
                set_cache($this->_view,$this->_vars,0,$this->_cachetime);
                extract($this->_vars);
            }
        }else{
            extract($this->_vars);
        }
        extract($this->_vars);
        if(LKPHP_IS_OPEN_FILE_CACHE){
            //这里我们要讲写入缓冲区
            $tpl='';
            ob_start();
            //加载头部模板
            include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.LKPHP_VIEWHEADER.'.'.LKPHP_EXTENSION);
            include($this->getView());//加载模板body
            include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.LKPHP_VIEWFOOTER.'.'.LKPHP_EXTENSION);//尾部
            $tpl = ob_get_contents();
            
            ob_clean();
            $file_name = md5($_SERVER['REQUEST_URI']);
            $cache_file='Cache/'.$file_name;
            if(file_exists($cache_file)){
                echo  file_get_contents($cache_file);
            }else{
                file_put_contents($cache_file,$tpl);
                echo $tpl;
            }
        }else{
            //加载头部模板
            include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.LKPHP_VIEWHEADER.'.'.LKPHP_EXTENSION);
            include($this->getView());//加载模板body
            include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.LKPHP_VIEWFOOTER.'.'.LKPHP_EXTENSION);//尾部
        }

     }
     //魔术方法
    function __get($p){
        $c=load_class($p);
        return $c;
    }
  }
 ?>