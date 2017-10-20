#coding=utf-8
import os
import os.path


def readfile(dir):
    for filename in os.listdir(dir):
        if filename.startswith('~') or filename.startswith('.'): #这里需要忽略隐藏目录和隐藏文件
            continue
        filepath = os.path.join(dir, filename)
        if os.path.isdir(filepath):
            readfile(filepath)
        elif os.path.isfile(filepath):
            name,ext = os.path.splitext(filename)
            # print(name,ext)
            if ext == ".xlsx" or ext == ".xls":
                print 'export file : ' + filepath   # + ' begin'
                # print 'export file ' + filename
                lua_file = name + '.lua'
                cmd = "python excel_to_lua.py " + filename + " " + lua_file
                # print cmd
                os.system( cmd )
                # print 'export file : ' + filepath + ' successed'
                cmd = "cp " + lua_file + " ../src/config/" + lua_file
                os.system( cmd )
                cmd = "cp " + lua_file + " ../../server/config/" + lua_file
                os.system( cmd )
                # print 'copy file : ' + lua_file + ' successed'

export_dir = "."
readfile(export_dir)