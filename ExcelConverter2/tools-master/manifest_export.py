#coding=utf-8

import os
import os.path
import sys
import hashlib
import json

def GetFileMd5(strFile):
    file = None
    bRet = False
    strMd5 = ""
    try:
        file = open(strFile, "rb")
        md5 = hashlib.md5()
        strRead = ""
        while True:
            strRead = file.read(4096)
            if not strRead:
                break
            md5.update(strRead)
            #read file finish
        bRet = True
        strMd5 = md5.hexdigest()
    except:
        bRet = False
    finally:
        if file:
            file.close()
    return [bRet, strMd5]

def md5_walk_dir(dir, assets):
    file_count = 0
    for filename in os.listdir(dir):
        if filename.startswith('~') or filename.startswith('.'): #这里需要忽略隐藏目录和隐藏文件
            continue
        filepath = os.path.join(dir, filename)
        if os.path.isdir(filepath):
            file_count = file_count + md5_walk_dir(filepath, assets)
        elif os.path.isfile(filepath):
            result = GetFileMd5(filepath)
            if result[0] == True:
                file_info = {}
                assets[filepath] = file_info
                file_info["md5"] = result[1]
                # print(result[1], filepath)
                file_count = file_count + 1
            else:
                print("get md5 error", filepath)
    return file_count

def load_manifest(filepath):
    file = open(filepath, "rb")
    str = file.read()
    dict = json.loads(str)
    return  dict

def save_manifest(filepath, dict):
    file = open(filepath, "wb")
    dump_str = json.dumps(dict, sort_keys=True, separators=(',',':'))
    file.write(dump_str)
    print("save file: "+filepath)
    print("total dump_str: byte", len(dump_str))

def create_project_manifest():
    version = load_manifest("version.manifest")
    project = {}
    project["engineVersion"] = version["engineVersion"]
    project["packageUrl"] = version["packageUrl"]
    project["remoteManifestUrl"] = version["remoteManifestUrl"]
    project["remoteVersionUrl"] = version["remoteVersionUrl"]
    project["version"] = version["version"]
    project["searchPaths"] = version["searchPaths"]
    assets = {}
    project["assets"] = assets
    src_dir = "src/"
    res_dir = "res/"
    total_count = 0
    total_count = total_count + md5_walk_dir(src_dir, assets)
    total_count = total_count + md5_walk_dir(res_dir, assets)
    print("total file: ", total_count)
    save_manifest("project.manifest", project)
    return  project

create_project_manifest()


