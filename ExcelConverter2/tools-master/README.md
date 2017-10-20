# tools
python tools

# excel_to_lua.py
首先需要安装xlrd的python插件，可以自行百度下载安装。
可以使用qiyu_drop.xlsx文件进行测试，格式如这个文件所示；使用方法
python excel_to_lua.py --your file name--

# loop_export_excel.py
遍历当前目录，将所有.xlsx和.xls文件导出成.lua文件，生成的文件放在该目录当中
需要修改里面的代码，才可以拷贝到你指定的目录，如下
                cmd = "cp " + lua_file + " ../src/config/" + lua_file
                os.system( cmd )
                cmd = "cp " + lua_file + " ../../server/config/" + lua_file
                os.system( cmd )

# manifest_export.py 
可以导出指定目录下的资源文件md5信息，生成cocos2dx内更新所需要的manifest文件
首先需要在目录中配置 version.manifest，导出函数会把version.manifest的信息复制到project.manifest
导出文件名称和导出的目录需要自己修改，如下
    src_dir = "src/"
    res_dir = "res/"

