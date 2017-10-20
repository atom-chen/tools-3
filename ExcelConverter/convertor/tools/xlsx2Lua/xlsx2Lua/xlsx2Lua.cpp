
/*
    ����xls / xlsx �ļ�������Ϊlua ��ʽ; 
*/





#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include "libxl.h"
#include <stdio.h>
#include <direct.h> //for create dircectory
#include <string>
#include <locale.h> //for string / wstring convert
#include <io.h>     //for access()


using namespace libxl;
using namespace std;


typedef enum{
    dType_none = 100,
    dType_int,
    dType_long,
    dType_string,
    dType_array,
    dType_group,
    dType_max
}dataType;

typedef struct{
    dataType type;
    std::string title;
    std::wstring wtitle;
}dataHead;



std::string luaPath;
std::string pbsPath;
std::wstring lang_name = std::wstring(L"Multi_lang.xlsx"); /*�����Ա�*/
std::wstring lang_type;
dataHead *headerInfo = NULL;

FILE *fp_sheetItemType = NULL; /* ��¼ÿ��sheet ҳ���ֶε���������*/

int row_index = 0;



/*
//�������ݶ�������Ҫ���б���ת��
char *wcs2char(const wchar_t *pwstr_in,  char *pcstr_out, size_t bufLen)  
{  
    int nlength=wcslen(pwstr_in); 
    int nbytes = WideCharToMultiByte( 0, 0, pwstr_in, nlength, NULL,0,NULL, NULL ); 
    if(nbytes > bufLen)
    {
        nbytes = bufLen;
    }
    
    WideCharToMultiByte( 0, 0, pwstr_in, nlength,  pcstr_out, nbytes, NULL,   NULL );  
    
    return pcstr_out ;  
}  

//ANSI -->UINICODE
wchar_t * char2wcs( const char* pcstr_in, wchar_t *pwstr_out, int bufLen)
{
    int nbytes = MultiByteToWideChar(CP_ACP, 0, pcstr_in, -1, NULL, 0);
    if (nbytes > bufLen)
    {
        nbytes = bufLen;
    }
    
    MultiByteToWideChar(CP_ACP, 0, pcstr_in, -1, pwstr_out, nbytes);
    
    return pwstr_out;
}
*/

bool isFileExist(std::string &fullPath)
{
    FILE *fp = fopen(fullPath.c_str(), "rb");
    if (fp)
    {
        fclose(fp);
        return true;
    }

    return false;
}


//�����locale stringͷ�ļ�, ʹ��setlocale
std::wstring string2wstring(const std::string str)
{
    unsigned len = str.size() * 2;// Ԥ���ֽ���
    setlocale(LC_CTYPE, "");     //������ô˺���
    wchar_t *p = new wchar_t[len];
    mbstowcs(p,str.c_str(),len);// ת��
    std::wstring str1(p);
    delete[] p;
    
    return str1;
}

std::string wstring2string(const std::wstring str)
{
    unsigned len = str.size() * 4;
    setlocale(LC_CTYPE, "");
    char *p = new char[len];
    wcstombs(p,str.c_str(),len);
    std::string str1(p);
    delete[] p;
    
    return str1;
}

//���ִ�"a,b,c; e,f,g"ת��Ϊ{ {array={a,b,c}}, {array={e,f,g}} } ��ʽ
std::string splitGroupString(std::string &str)
{
    std::string tmp;
    
    
    tmp += "{";

    if (str.length() > 0)
    {
        /*���ں���strtok() �ĵ�һ������pBuf  Ҫ����ָ���ǿɱ��, ����Ϊconst , ��������, �����������·�װ��*/
        int len = str.length() + 1;
        char *pBuf = (char *)malloc(len);
        memset(pBuf, 0, len);
        strcpy(pBuf, str.c_str());

        char * s = strtok(pBuf, ";");  
        int i=0;  
        while(s)  
        {  
           tmp += "{array = {";
           tmp += s;
           tmp += "}}";

            s = strtok(NULL, ";");  
            
            if (s)
            {
                tmp += ", ";
            }
        }
        
        free(pBuf);
    }
    
    tmp += "}";
    
    
    return tmp;
}


std::wstring getExtNameOfFile(std::wstring &fileName)
{
    std::wstring tmp;

    int pos = fileName.find(L".");
    if (pos != std::wstring::npos)
    {
        tmp = fileName.substr(pos);
    }
    
    return tmp;
}

bool getSheetRowsAndCols(Sheet *sheet, int &row_s, int &row_e,  int &col_s, int &col_e)
{
    row_s = sheet->firstRow();
    row_e = sheet->lastRow();    
    col_s = sheet->firstCol();
    col_e = sheet->lastCol();

    //calc valid rows, cols
    CellType type;                
    for (int i=col_s; i<=col_e; i++)
    {
        if (CELLTYPE_EMPTY==sheet->cellType(row_s, i) ||CELLTYPE_BLANK==sheet->cellType(row_s, i))
        {
            col_e = i > col_s ? i-1 : col_s;
            break;
        }
    }
    
    for (int i = row_s; i <= row_e; i++)
    {
        if (CELLTYPE_EMPTY==sheet->cellType(i, col_s) ||CELLTYPE_BLANK==sheet->cellType(i, col_s))
        {
            row_e = i > row_s ? i-1 : row_s;
            break;
        }
    }

    if( row_e <= row_s) 
    {
        return false;
    }

    return true;
}


dataHead* getSheetHeader(Sheet *sheet, int row_s,  int col_s, int col_e)
{
    const wchar_t *wstr;
    std::string sheetName = wstring2string(std::wstring(sheet->name()));;
    
    dataHead* outHead = new dataHead[col_e-col_s+1];

    for (int j=col_s; j<=col_e; j++)
    {
        wstr = sheet->readStr(row_s,  j);   //Ĭ�ϵ�1 ��Ϊ�ֶ���
        outHead[j].title = wstring2string(std::wstring(wstr));
        outHead[j].wtitle = std::wstring(wstr);
        
        wstr = sheet->readStr(row_s+1,  j); //Ĭ�ϵ�2 ��Ϊ�ֶ�����
        if (wstr)
        {
           char tmp[200] = {0};
            //sprintf(tmp, "%s", sheetName);
            
            if (wcscmp(wstr, L"int") == 0)
            {
                outHead[j].type = dType_int;
            }
            else if (wcscmp(wstr, L"long") == 0)
            {
                outHead[j].type = dType_long;
            }
            else if (wcscmp(wstr, L"string") == 0)
            {
                outHead[j].type = dType_string;
            }
            else if (wcscmp(wstr, L"array") == 0)
            {
                outHead[j].type = dType_array;
            }
            else if (wcscmp(wstr, L"group") == 0)
            {
                outHead[j].type = dType_group;
            }
            else
            {
                //cout << "Error: " << sheetName << "row, col" << row_s+1 << "," << j << endl;
                printf("wrong type :  %s, row, col:%d, %d \n", sheetName.c_str(), row_s+1, j);\
                delete []outHead;
                return NULL;
            }
        }
        else 
        {
            printf("Read Error:  %s, row, col:%d, %d, \n", sheetName.c_str(), row_s+1, j);
            delete []outHead;
            return NULL;
        }
    }

    return outHead;
}


bool writeCellToLuaFile(Sheet *sheet, dataHead *header, int row, int col, FILE *fp)
{
    std::string tmp;

    tmp = "\t\t" + header->title + " = ";


    switch (sheet->cellType(row, col))
    {
        case CELLTYPE_NUMBER:
            {
                char buf[32] = {0};
                itoa(sheet->readNum(row,  col), buf, 10);
                
                /*��������ʱ*/
                if (header->type == dType_string)
                {
                    tmp += ("\"" + std::string(buf) + "\"");
                }
                else if (header->type == dType_array)
                {
                    tmp += ("{" + std::string(buf) + "}");
                }
                else if (header->type == dType_group) 
                {
                    tmp += ("{{array = {" + std::string(buf) + "}}}");
                }
                else 
                {
                    tmp += std::string(buf);
                }
            }
            break;
            
        case CELLTYPE_STRING:
            if (header->type == dType_int ||header->type == dType_long)
            {
                tmp += wstring2string(std::wstring(sheet->readStr(row,  col))); 
            }
            else if (header->type == dType_array)
            {
                tmp += "{";
                tmp += wstring2string(std::wstring(sheet->readStr(row,  col))); 
                tmp += "}";
            }
            else if (header->type == dType_group)
            {
                tmp += splitGroupString(wstring2string(std::wstring(sheet->readStr(row,  col))));
            }
            else
            {
                tmp += "\"";
                tmp += wstring2string(std::wstring(sheet->readStr(row,  col))); /*�ִ����߶������(�Զ��Ÿ���)ʱ*/
                tmp += "\"";
            }
            break;

        case CELLTYPE_BOOLEAN:
            if (sheet->readBool(row,  col))
            {
                tmp += "true";
            }
            else 
            {
                tmp += "false";
            }
            break;
            
        case CELLTYPE_EMPTY:
        case CELLTYPE_BLANK:
            {   /*������ʱ*/
                if (header->type == dType_int ||header->type == dType_long)
                {
                    tmp += "0";
                }
                else if (header->type == dType_string)
                {
                     tmp += "\"\"";
                }
                else if (header->type == dType_array || header->type == dType_group)
                {
                     tmp += "{}";
                }
            }
            break;

        case CELLTYPE_ERROR:
            return false;
            break;
            
        default:
            break;
    }


    tmp += ",\n";
    if (fp)
    {
        fwrite(tmp.c_str(), tmp.length(), 1, fp);
        fflush(fp);
    }

    return true;
}


bool createLuaFile(Sheet *sheet, int row_s, int row_e, int col_s,  int col_e, dataHead *headerInfo)
{
    
    std::string sheetName;
    std::string tmp;
    
    sheetName = wstring2string(std::wstring(sheet->name()));
    printf("    convert sheet : %s\n", sheetName.c_str());
    
 
    //init data type for per col
    if ((headerInfo = getSheetHeader(sheet, row_s, col_s,  col_e)) == NULL)
    {   
        printf(" invalid file header type: %s\n ", sheetName.c_str());
        return false;
    }

    //create lua file.
    tmp = luaPath + "\\" + sheetName + ".lua";
    
    FILE *fp = fopen(tmp.c_str(), "w+");
    if (fp)
    {
        char buf[256] = {0};
        
        //header
        sprintf(buf, "local %sConfig = {\n", sheetName.c_str());
        fwrite(buf, strlen(buf), 1, fp);
        
        //read excell cells data
        for (int i=row_s+2; i<= row_e; i++)
        {
            fwrite("\t{\n", 3, 1, fp); 
            
            for (int j=col_s; j <= col_e; j++)
            {
                
                if (!writeCellToLuaFile(sheet, &headerInfo[j], i, j, fp))
                {
                    printf(" write file fail. \n");
                    break;
                }
            }
            
            fwrite("\t},\n", 4, 1, fp); 
        }

        //tail
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "}\n\nreturn %sConfig", sheetName.c_str());
        fwrite(buf, strlen(buf), 1, fp);
        
        fclose(fp);
    }
    
    return true; 
}

/*�����Ա���Ϊlua */
bool createLuaFileForMultiLan(std::wstring &fullpath)
{
    Book* book = NULL;
    int  row_s, row_e, col_s,  col_e;
    std::wstring ext = getExtNameOfFile(fullpath);
    

    if (ext.compare(L".xlsx") == 0) 
    {
        book = xlCreateXMLBook();
    }
    else if (ext.compare(L".xls") == 0)
    {
        book = xlCreateBook();
    }
    else 
    {
        return false;
    }

    
    if(book->load(fullpath.c_str()))
    {
        Sheet *sheet = book->getSheet(0);  
        std::string sheetName = wstring2string(std::wstring(sheet->name()));
        std::string luaName = luaPath + "\\" + sheetName + ".lua";
        
        if (!getSheetRowsAndCols(sheet, row_s, row_e, col_s,  col_e))
        {
            return false;
        }

                
         FILE *fp = fopen(luaName.c_str(), "w+");
        if (fp)
        {
            // get current language type .
            int selectedCol = 1;
            std::wstring lanType = std::wstring(sheet->readStr(0,  11));
            std::wstring tmp;
            for (int j=col_s+1; j<=col_e; j++)
            {
                tmp = std::wstring(sheet->readStr(0,  j));
                if (lanType.compare(tmp) == 0)
                {
                    selectedCol = j;
                    break;
                }
            }
                    
            fwrite("local lang = {\n", strlen("local lang = {\n"), 1, fp);
            //get row content for selected language type.
            std::string str;
            for (int i=row_s+1; i<= row_e; i++)
            {
                switch (sheet->cellType(i, selectedCol))
                {
                    case CELLTYPE_NUMBER:
                        {
                            char buf[32] = {0};
                            itoa(sheet->readNum(i,  selectedCol), buf, 10);
                            str = std::string(buf);
                        }
                        break;
                        
                   case CELLTYPE_STRING:
                        str = wstring2string(std::wstring(sheet->readStr(i,  selectedCol))); 
                        break;
                        
                   default:
                        break;
                }

                if (str.length() > 0)
                {
                    std::string content = wstring2string(std::wstring(sheet->readStr(i,  col_s))) + " = " + str + ",\n"; 
                    fwrite(content.c_str(), content.length(), 1, fp);
                }
            }

            fwrite("}\nreturn lang\n", strlen("}\nreturn lang\n"), 1, fp);
            fclose(fp);
        }
        
    }

    book->release();
}


bool createProtoFile(std::string &sheetName, int col_s,  int col_e, dataHead *headerInfo)
{
    std::string fullPath = pbsPath + "\\" + sheetName +"Config"+ ".proto";
    std::string tmp;
    
    FILE *fp = fopen(fullPath.c_str(), "w+");
    if (fp)
    {
        tmp = "\nimport \"GroupTypeConfig.proto\"; \nmessage " + sheetName + "Config {\n";
        fwrite(tmp.c_str(), tmp.length(), 1, fp);
        
        for (int j=col_s; j <= col_e; j++)
        {
            char buf[32] = {0};
            itoa(j+1, buf, 10);
            
            switch(headerInfo[j].type)
            {
                case dType_int:
                case dType_long:
                    tmp = "\trequired int32 ";
                    break;
                    
                case dType_string:
                    tmp = "\trequired string ";
                    break;
                    
                case dType_array:
                    tmp = "\trepeated int32 ";
                    break;
                    
               case dType_group:
                    tmp = "\trepeated GroupTypeConfig ";
                    break;
               default:
                    break;
            }

            tmp += headerInfo[j].title + " = " + std::string(buf) + ";\n";
            fwrite(tmp.c_str(), tmp.length(), 1, fp);
            
        }
        
        fwrite("}\n", 2, 1, fp);
        fclose(fp);
    }
    
    return true;
}

bool parseXlsFile(std::wstring &fullpath)
{
    Book* book = NULL;
    bool result = true;
    int  row_s, row_e, col_s,  col_e;

    
    wprintf(L" parsing file : %s\n", fullpath.c_str());
    
    std::wstring ext = getExtNameOfFile(fullpath);

    if (ext.compare(L".xlsx") == 0) //(fileName.rfind(L".xlsx") != std::wstring::npos ) 
    {
        book = xlCreateXMLBook();
    }
    else if (ext.compare(L".xls") == 0)
    {
        book = xlCreateBook();
    }
    else 
    {
        return false;
    }


    if(book->load(fullpath.c_str()))
    {
        int sheetsCount = book->sheetCount();
        for (int index=0; index < sheetsCount; index++)
        {
            Sheet *sheet = book->getSheet(index);  
            if (sheet)
            { 
                std::string sheetName = wstring2string(std::wstring(sheet->name()));

                // 1. init rows & cols
                if (!getSheetRowsAndCols(sheet, row_s, row_e, col_s,  col_e))
                {
                    printf(" invalid file: %s\n", sheetName.c_str());
                    return false;
                }

                // 2. get header infos
                if ((headerInfo = getSheetHeader(sheet, row_s, col_s,  col_e)) == NULL)
                {   
                    printf(" invalid file header type: %s\n ", sheetName.c_str());
                    return false;
                }


                // 3. xls to lua
                if (!createLuaFile(sheet, row_s, row_e, col_s,  col_e, headerInfo))
                {
                    printf("create lua file fail, error code: %s\n", book->errorMessage());
                    result = false;
                    break;
                }
                
             /* 
                // 4. xls to proto 
                if (!createProtoFile(wstring2string(std::wstring(sheet->name())), col_s,  col_e, headerInfo))
                {
                    result = false;
                    break;
                }
            */
                
                if (headerInfo)
                {
                    delete []headerInfo;
                    headerInfo = NULL;
                }


                // 5. add sheet type to lua file.
                if (fp_sheetItemType)
                {
                    std::string str;
                    str = "\t" + sheetName + " = {\n";
                    fwrite(str.c_str(), str.length(), 1, fp_sheetItemType);
                    for (int j = col_s; j <= col_e; j++)
                    {
                        str = "\t\t\t\t" + wstring2string(std::wstring(sheet->readStr(row_s,  j))) +" = \"" + wstring2string(std::wstring(sheet->readStr(row_s+1,  j))) + "\",\n";
                        fwrite(str.c_str(), str.length(), 1, fp_sheetItemType);
                    }
                    str = std::string("\t},\n");
                    fwrite(str.c_str(), str.length(), 1, fp_sheetItemType);
                    fflush(fp_sheetItemType);
                }
            }
            else
            {
                printf(" open sheet fail, error code:  %s\n", book->errorMessage());
                result = false;
                break;
            } 
        } 

        book->release();
    }
    else 
    {
        printf(" open  xls/xlsx fail , error code : %s\n", book->errorMessage());
        result = false;
    }


    return result;
}

/*��xls �ļ���string �浽excel ��*/
bool parseXlsFileForString(std::wstring &fullpath,  Sheet *sheet_lang)
{
    Book* book = NULL;
    bool result = true;
    int  row_s, row_e, col_s,  col_e;
    std::wstring tmp;    
    wchar_t buf[64];
    
    wprintf(L" parsing file : %s\n", fullpath.c_str());
    
    std::wstring ext = getExtNameOfFile(fullpath);

    if (ext.compare(L".xlsx") == 0) //(fileName.rfind(L".xlsx") != std::wstring::npos ) 
    {
        book = xlCreateXMLBook();
    }
    else if (ext.compare(L".xls") == 0)
    {
        book = xlCreateBook();
    }
    else 
    {
        return false;
    }
    
    
    if(book->load(fullpath.c_str()))
    {
        int sheetsCount = book->sheetCount();
        for (int index=0; index < sheetsCount; index++)
        {
            Sheet *sheet = book->getSheet(index);  
            if (sheet)
            { 
                std::string sheetName = wstring2string(std::wstring(sheet->name()));

                // 1. init rows & cols
                if (!getSheetRowsAndCols(sheet, row_s, row_e, col_s,  col_e))
                {
                    printf(" invalid file: %s\n", sheetName.c_str());
                    return false;
                }

                // 2. get header infos
                if ((headerInfo = getSheetHeader(sheet, row_s, col_s,  col_e)) == NULL)
                {   
                    printf(" invalid file header type: %s\n ", sheetName.c_str());
                    return false;
                }

                // 3. find string to excel file 
                for (int j=col_s; j <=col_e; j++)
                {
                    if (headerInfo[j].type == dType_string)
                    {
                        for (int i=row_s+2; i<= row_e; i++)
                        {
                            memset(buf, 0, sizeof(buf));
                            wsprintf(buf, L"_%d", i-row_s-1);
                            tmp = std::wstring(sheet->name()) +L"_" + headerInfo[j].wtitle + std::wstring(buf);
                            
                            sheet_lang->writeStr(row_index, 0, tmp.c_str());
                            
                            switch (sheet->cellType(i, j))
                            {
                                case CELLTYPE_NUMBER:
                                    memset(buf, 0, sizeof(buf));
                                    wsprintf(buf, L"\"%d\"", sheet->readNum(i,  j));
                                    sheet_lang->writeStr(row_index, 1, buf);
                                    break;
                                    
                                case CELLTYPE_STRING:
                                    tmp = L"\"" + std::wstring(sheet->readStr(i,  j)) + L"\"";
                                    sheet_lang->writeStr(row_index, 1, tmp.c_str());
                                    break;
                                    
                                default:
                                    //sheet_lang->writeBlank(row_index, 1);
                                    break;
                            }

                            row_index++;
                        }
                    }
                }
                
                
                if (headerInfo)
                {
                    delete []headerInfo;
                    headerInfo = NULL;
                }

            }
            else
            {
                printf(" open sheet fail, error code:  %s\n", book->errorMessage());
                result = false;
                break;
            } 
        } 

        book->release();
    }
    else 
    {
        printf(" open  xls/xlsx fail , error code : %s\n", book->errorMessage());
        result = false;
    }


    return result;
}

bool findAndConvertExcelFiles(std::wstring &path, std::wstring &extName)
{
    bool result = true;
    HANDLE hFile;
    WIN32_FIND_DATA findData;
    std::wstring strTemp;
    std::wstring ext;
    
    strTemp = path;
    strTemp +=  L"*.*";

    hFile = FindFirstFile(strTemp.c_str(), &findData);
    while (hFile != INVALID_HANDLE_VALUE)
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)// is directory 
        {
            if(findData.cFileName[0] != _T('.')) //�ų�. ��.. �ļ���
            {
                //�������·��
                strTemp = path;
                strTemp += std::wstring(findData.cFileName);
                strTemp +=   L"\\";

                findAndConvertExcelFiles(strTemp, extName); //�ݹ���ҵ�ǰĿ¼���ļ�
            }
        }
        else
        {
            strTemp = std::wstring(findData.cFileName); 
            wprintf(L"=========%s\n", findData.cFileName);
            if (strTemp.compare(lang_name) == 0)    /*�����Ա�*/
            {
                createLuaFileForMultiLan(path+strTemp);
            }
            else
            {
                if (extName.compare(getExtNameOfFile(strTemp)) == 0 )
                {
                    if (!parseXlsFile(path+strTemp))
                    {
                        result = false;
                        break;
                    }
                }
            }
        }

        if(!FindNextFile(hFile, &findData))
        {
            break;
        }
    }
    
    return result;
}


/*������xlsx �е�string �����һ��excel ��, �������Է���ʹ��*/
bool findAllStringToExcel(std::wstring &path, std::wstring &extName,  Sheet *sheet_lang)
{
    bool result = true;
    HANDLE hFile;
    WIN32_FIND_DATA findData;
    std::wstring strTemp;
    std::wstring ext;
    
    
    strTemp = path;
    strTemp +=  L"*.*";
    
    hFile = FindFirstFile(strTemp.c_str(), &findData);
    while (hFile != INVALID_HANDLE_VALUE)
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)// is directory 
        {
            if(findData.cFileName[0] != _T('.')) //�ų�. ��.. �ļ���
            {
                //�������·��
                strTemp = path;
                strTemp += std::wstring(findData.cFileName);
                strTemp +=   L"\\";

                findAllStringToExcel(strTemp, extName, sheet_lang); //�ݹ���ҵ�ǰĿ¼���ļ�
            }
        }
        else
        {
            strTemp = std::wstring(findData.cFileName); 
            if (strTemp.compare(lang_name) != 0)    /* ֻ��Գ������Ա��������excel ����е���string */
            {
                if (extName.compare(getExtNameOfFile(strTemp)) == 0 )
                {
                    if (!parseXlsFileForString(path+strTemp, sheet_lang))
                    {
                        result = false;
                        break;
                    }
                }
            }
        }

        if(!FindNextFile(hFile, &findData))
        {
            break;
        }
    }
    
    
    return result;
}


bool createMultiLanExcel(std::wstring &xlsPath)
{

    Book *book_lang = xlCreateXMLBook();
    Sheet *sheet_lang = book_lang->addSheet(L"lang");
        
    printf(" find all string into excel...\n");
    
    sheet_lang->writeStr(0, 0, L"id");
    sheet_lang->writeStr(0, 1, L"ch");
    sheet_lang->writeStr(0, 10, L"��ǰѡ��");
    sheet_lang->writeStr(0, 11, L"ch");
    
    row_index = 1;
    
    if ( !findAllStringToExcel(xlsPath, std::wstring(L".xlsx"), sheet_lang))
    {
        return false;
    }

    if ( !findAllStringToExcel(xlsPath, std::wstring(L".xls"), sheet_lang))
    {
        return false;
    }        


    xlsPath += lang_name;
    wprintf(L" output multi-lan xlsx path = %s\n", xlsPath.c_str());
    book_lang->save(xlsPath.c_str());
    book_lang->release();
    
    return true;
}


#if 1  /*����Ŀ¼������xls ��xlsx �ļ���ת��*/

int _tmain(int argc, _TCHAR* argv[])
{
    std::string tmp;
    std::wstring xlsPath;
    
/*
    char *dd = "D:\\hlb\\xlsx2Lua\\Debug\\";
    //create directory    
    tmp = std::string(dd) + "convertor";
    _mkdir(tmp.c_str());
    luaPath = tmp + "\\lua";
    _mkdir(luaPath.c_str());

    pbsPath = tmp + "\\pbs";
    _mkdir(pbsPath.c_str());
*/

    for (int i=1; i<argc; i++)
    {
        wprintf(L"para_%d  : %s\n", i, argv[i]);
    }

    if (argc <= 1)
    {
        printf(" pls input paras...");
        return 1;
    }
    
    /*---------------------------------------------------------------------------------*/
    /* ������:  ���������ݱ��е�string  ���������ͬһ��excel ���� */
    if (argc == 2) //export all string to one excel
    {
        xlsPath = std::wstring(argv[1]);
        createMultiLanExcel(xlsPath);

        return 0;
    }
    /*---------------------------------------------------------------------------------*/



    
    luaPath = wstring2string(std::wstring(argv[1]));
    pbsPath = wstring2string(std::wstring(argv[2]));
    xlsPath = std::wstring(argv[3]);

    /*
        //��������Ա��������ȴ���
        tmp = wstring2string(xlsPath + lang_name);
        if (!isFileExist(tmp))
        {
            if (!createMultiLanExcel(xlsPath))
            {
                goto ERROR1;
            }
        }
    */


    /*������excel �ļ�����Ϊlua */

    /*
        // 1. create group type of proto
        tmp = pbsPath + "\\GroupTypeConfig.proto";
        FILE *fp = fopen(tmp.c_str(), "w+");
        if (fp)
        {
            tmp.assign("\nmessage GroupTypeConfig {\n\trepeated int32 array = 1;\n}\n");
            fwrite(tmp.c_str(), tmp.length(), 1, fp);
            fclose(fp);
        }
    */

    // 2. ��������ӳ���, ��lua �����´��ʹ��
    tmp = luaPath + "\\" +  "_SheetItemTypeMap.lua";
    fp_sheetItemType = fopen(tmp.c_str(), "w+");
    if (fp_sheetItemType)
    {
        std::string str("local SheetItemTypeMap = {\n");
        fwrite(str.c_str(), str.length(), 1, fp_sheetItemType); 
        //fflush(fp_sheetItemType);
    }    

    //===========================================
    // 3. ��xls/xlsx ����ת��lua �ļ��洢
    if ( !findAndConvertExcelFiles(xlsPath, std::wstring(L".xlsx")))
    {
        goto ERROR1;
    }

    if ( !findAndConvertExcelFiles(xlsPath, std::wstring(L".xls")))
    {
        goto ERROR1;
    }
    //===========================================

   
    if (fp_sheetItemType)
    {
        std::string str("}\nreturn SheetItemTypeMap\n");
        fwrite(str.c_str(), str.length(), 1, fp_sheetItemType); 
        fclose(fp_sheetItemType);
    }

    
    //printf("\n============ SUCCESS ================\n");
    
    //system("pause"); 
    return 0;
    
    
ERROR1:
    printf("\n============ FAIL !!!! ================\n");
    //system("pause"); 
    
    return 1;
}


#else  /*���ⲿ����ÿ��excel  �ļ���·����ת��*/

int _tmain(int argc, _TCHAR* argv[])
{
    std::string tmp;
    std::wstring xlsPath;

/*
    for (int i=1; i<argc; i++)
    {
        wprintf(L"para_%d  : %s\n", i, argv[i]);
    }
*/

    if (argc != 4)
    {
        printf(" wrong input para !!!!!!");
        return 1;
    }

    
    luaPath = wstring2string(std::wstring(argv[1]));
    pbsPath = wstring2string(std::wstring(argv[2]));
    xlsPath = argv[3];
    

    //������proto , �����������ɵ�proto ����. ������ļ��������򴴽�.
    tmp = pbsPath + "\\GroupTypeConfig.proto";
    if (access(tmp.c_str(), 0) != 0)
    {
        FILE *fp = fopen(tmp.c_str(), "w+");
        if (fp)
        {
            tmp.assign("\nmessage GroupTypeConfig {\n\trepeated int32 array = 1;\n}\n");
            fwrite(tmp.c_str(), tmp.length(), 1, fp);
            fclose(fp);
        }
    }
    

    if (!parseXlsFile(xlsPath))
    {
        //goto ERROR1;
        return 1;
    }
    
/*
    printf("\n============ SUCCESS ================\n");
    //system("pause"); 
    return 0;
    
    
ERROR1:
    printf("\n============ FAIL !!!! ================\n");
    //system("pause"); 
    
    return 1;
*/
    
    return 0;
}



#endif

