
-- 注意 package.path 一般存放lua的环境变量; package.cpath 一般存放 c 库
package.path = package.path..";.\\tools\\pbc\\?.lua;.\\lua_utf8\\?.lua"
package.cpath = package.cpath..";.\\tools\\pbc\\?.dll" --用于加载 protobufc.dll 在


require("protobuf") --该lua文件里面第一行代码 local c = require "protobufc" 会调用到 protobufc.dll 





-- 获取当前脚本的路径
local cdObj = io.popen("cd")
local currentPath = cdObj:read("*all"):sub(1,-2)
cdObj:close()

-- pbs & lua 路径
local PBS_PATH = currentPath.."/pbs/"
local LUA_PATH = currentPath.."/lua_utf8/"
local DATA_PATH = currentPath.."/data/"


local NAME_COMMON_PROTO = "GroupTypeConfig"
local NAME_ALL_IN_ONE_PROTO = "AllConfig"
local NAME_ALL_PBS = "AllPbsName"
local VERSION_NAME = "version"

-- 所有已转换的 sheet 字段类型
local allSheetsType = require("_SheetItemTypeMap")
local multi_lang = require("lang")     --多语言表, 语言选择在Multi_lang.xlsx 里设定

-- data版本号由 getVersion.bat 自动生成导入到 _Version.lua中
-- local dataVersion = require("_Version")  




-- 每个 xls sheet 对应一个proto
local function createSheetProto(sheetName, sheetInfo)
  local pathName = PBS_PATH..sheetName.."Config.proto"
  local fp = assert( io.open(pathName, "w+"))
  fp:write(string.format("import \"%s.proto\";\n",NAME_COMMON_PROTO))
  fp:write(string.format("message %sConfig {\n",sheetName))

  if sheetInfo ~= nil then 
    local i = 0
    for k, v in pairs(sheetInfo) do
      i = i + 1

      if v == "int" then
        fp:write(string.format("\trequired int32 %s = %d;\n",k,i))
      elseif v == "string" then
        fp:write(string.format("\trequired string %s = %d;\n",k,i))
      elseif v == "array" then
        fp:write(string.format("\trepeated int32 %s = %d;\n",k,i))
      elseif v == "group" then
        fp:write(string.format("\trepeated %s %s = %d;\n",NAME_COMMON_PROTO,k,i))
      else
        assert(false, "Invalid type:"..v..",sheetName:"..sheetName..",item:"..k)
      end
    end
  end

  fp:write("}\n")
  fp:close()
end

-- 创建所有proto, 并将所有proto合并成一个proto,注意单个proto成员id不能超过125左右,否则可能会编译不过
-- 此时可以分成几个proto, 做好映射即可
local function createAllProto() 
  print("=== create all proto")

  -- 1. create common type proto 
  local pathName = PBS_PATH..NAME_COMMON_PROTO..".proto"
  local fp1 = assert( io.open(pathName, "w+"))
  fp1:write("message ".. NAME_COMMON_PROTO.."{\n\trepeated int32 array = 1;\n}\n" )
  fp1:close() 

  -- 2.create every sheet proto
  for sheetName, sheetInfo in pairs(allSheetsType) do 
    createSheetProto(sheetName, sheetInfo)
  end 

  -- 3.make all in one proto 
  local pathName2 = PBS_PATH..NAME_ALL_IN_ONE_PROTO..".proto"
  local fp2 = assert( io.open(pathName2, "w+"))  
  for sheetName, sheetInfo in pairs(allSheetsType) do 
    fp2:write(string.format("import \"%sConfig.proto\";\n",sheetName))
  end 
  fp2:write(string.format("message %s {\n",NAME_ALL_IN_ONE_PROTO))
  local i = 0 
  for sheetName, sheetInfo in pairs(allSheetsType) do 
    i = i + 1 
    fp2:write(string.format("\trepeated %sConfig %s = %d;\n",sheetName, string.lower(sheetName), i))
  end 
  fp2:write("}\n")
  fp2:close() 

  -- 4. 将所有sheet对应的pb名存起来,供客户端和服务器初始化数据时用来注册pb
  local pathName3 = PBS_PATH..NAME_ALL_PBS..".proto"
  local fp3 = assert( io.open(pathName3, "w+"))  
  fp3:write(string.format("\nmessage %s {\n",NAME_ALL_PBS))
  fp3:write("\trepeated string all_sheets = 1;\n")
  fp3:write("}\n")
  fp3:close() 
end 

local function registProto(name)
  local pathName = PBS_PATH..name..".pb"
  local fp = assert(io.open(pathName,"rb"), "Can not load pb file:"..pathName)
  local buffer = fp:read "*a"
  fp:close()
  protobuf.register(buffer)
  print("register pb: "..name)
end

local function registAllProto()
  registProto(NAME_COMMON_PROTO)
  for sheetName, sheetInfo in pairs(allSheetsType) do 
    registProto(sheetName.."Config")
  end 
  registProto(NAME_ALL_IN_ONE_PROTO)
  registProto(NAME_ALL_PBS) 
end 

-- 针对单个excel 作内部类型校验
local function checkData(sheetName, data)

  local msgInfo = allSheetsType[sheetName]
  for k, infoData in pairs(data) do   --针对每个proto结构数据进行检查
    for member, menberVal in pairs(infoData) do --检查proto各字段数据

      if msgInfo[member] == "array" then 
        assert(type(menberVal)=="table", string.format("error in %s , %s", sheetName, member))
        for m, v in pairs(menberVal) do 
          assert(type(v) == "number", string.format("invalid number in: %s , %s, index %d", sheetName, member, k))
        end 

      elseif msgInfo[member] == "group" then 
        assert(type(menberVal)=="table", string.format("error in %s , %s", sheetName, member))
        for m, v in pairs(menberVal) do 
          assert(type(v.array)=="table", string.format("error in %s , %s", sheetName, member, k))
          for key, val in pairs(v.array) do 
            assert(type(val) == "number", string.format("invalid number in group: %s , %s, index %d", sheetName, member, k))
          end 
        end 

      elseif msgInfo[member] == "int" then 
        assert(type(menberVal) == "number", string.format("invalid number in: %s , %s, index %d", sheetName, member, k))

      elseif msgInfo[member] == "string" then 
        assert(type(menberVal) == "string", string.format("invalid number in: %s , %s, index %d", sheetName, member, k))
        -- 从多语言lua文件中获取相应的字串
        local index = sheetName.."_"..member.."_"..k 
        if multi_lang[index] then 
          data[k][member] = multi_lang[index] 
        end 

      else 
        assert(0, string.format("invalid type: %s, %s", sheetName, member))
      end 
    end 
  end 

  return data 
end 

-- 各个sheet表之间的数据关联检查, 一般会有个map表,这里暂时未处理.
local function checkDataBetweenSheets(all_config_data)

end 

local function createData()
  local all_config_data = {}

  -- 1. 将版本号也一并存到data里
  -- all_config_data[VERSION_NAME] = dataVersion 

  -- 2. 获取各个表的数据
  for sheetName, sheetInfo in pairs(allSheetsType) do 
    local data = require(sheetName)
    data = checkData(sheetName, data)
    all_config_data[string.lower(sheetName)] = data 
  end 

  -- 3. 检查表与表之间的数据关联
  checkDataBetweenSheets(all_config_data)

  -- 4. 将所有数据封装成一个data文件
  local buff = protobuf.encode(NAME_ALL_IN_ONE_PROTO, all_config_data)
  local dataName = DATA_PATH.."all_config_data.data"
  local fp = assert(io.open(dataName,"wb+"))
  fp:write(buff)
  fp:close()

  -- 5. 将所有pb名字保存到一个data文件供客户端/服务器端解析pb时使用.
  local pbsName = {}
  table.insert(pbsName, NAME_COMMON_PROTO)
  -- table.insert(pbsName, NAME_ALL_PBS)
  for sheetName, sheetInfo in pairs(allSheetsType) do 
    table.insert(pbsName, sheetName.."Config")
  end 
  table.insert(pbsName, NAME_ALL_IN_ONE_PROTO)

  local buff2 = protobuf.encode(NAME_ALL_PBS, {all_sheets = pbsName})
  local path = DATA_PATH..NAME_ALL_PBS..".data"
  local fp2 = assert(io.open(path,"wb+"))
  fp2:write(buff2) 
  fp2:close() 
end 


local function make()
  -- 创建proto文件
  createAllProto()

  -- 将proto生成pb和cc/h文件
  os.execute(currentPath.."/CreatePbs.bat")
  os.execute(currentPath.."/createC++.bat")

  -- 注册pb
  registAllProto()
  
  -- 封装成data
  createData()
end 


make()
