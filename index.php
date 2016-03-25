<?php 
    include('lkphp.conf');
    //获取Controller参数
    $controller = isset($_GET['controller'])?$_GET['controller']:'';
    //获取action
    $action = isset($_GET['action'])?$_GET['action']:'';
    //如果传入的controller 为空或者在定义的自定义列表里面那么就终止程序向下执行 
    if($controller === ''|| in_array($controller,explode(',',LKPHP_FORBIDDEN_TYPE))) exit();
    error_reporting(E_ALL);//设定报错级别默认最高用于开发环境好调试错误
    include(LKPHP_PATH.'/Common/functions.inc');//加载公共函数库
    include(LKPHP_PATH.'MVC/Controller/_Master.inc');//加载Controller父类
    include(LKPHP_PATH.'MVC/Controller/'.$controller.'.inc');//加载特定的controller类
    $_init_controller = new $controller();
    $_init_controller->$action();
?>