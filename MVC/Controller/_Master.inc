<?php 
  //所有controller的父类 抽象类 
  abstract class _Master{
     var $_view='index';//模板名称
     var $_vars = array();
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
     function run(){
     	//解包变量
        extract($this->_vars);
     	//加载头部模板
     	include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.LKPHP_VIEWHEADER.'.'.LKPHP_EXTENSION);
     	include($this->getView());//加载模板body
     	include(LKPHP_PATH.'/MVC/View/'.LKPHP_VIEWPATH.'/'.LKPHP_VIEWFOOTER.'.'.LKPHP_EXTENSION);//尾部
     }
  }
 ?>