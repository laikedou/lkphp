<?php 
    include('lkphp.conf');
    //获取Controller参数
    $_controller = isset($_GET['controller'])?$_GET['controller']:'';
    //获取action
    $_action = isset($_GET['action'])?$_GET['action']:'';
    //如果传入的controller 为空或者在定义的自定义列表里面那么就终止程序向下执行 
    if($_controller === ''|| in_array($_controller,explode(',',LKPHP_FORBIDDEN_TYPE))) exit();
    error_reporting(E_ALL);//设定报错级别默认最高用于开发环境好调试错误
    require(LKPHP_PATH.'/Common/functions.inc');//加载公共函数库
    require(LKPHP_PATH.'MVC/Controller/_Master.inc');//加载Controller父类
    $_control_path = LKPHP_PATH.'MVC/Controller/'.$_controller.'.inc';//获取控制器类绝对地址
    if(!file_exists($_control_path)){
         exit();//判断是否存在此控制器类文件
    }
    require($_control_path);
    if (!class_exists($_controller)) {
        exit();//判断是否存在此类
    }
    $_init_controller = new $_controller();
    if (method_exists($_init_controller, $_action)) {
        $_init_controller->$_action();//如果控制器中存在此方法那么才进行执行
    }
    $_init_controller->run();
?>