
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "xxtea.cpp"

#define CAMP(x) strcmp(command,x)==0

int main(int argc, char * argv[]){

    FILE *fp;   //文件指针
    char *command; //解压命令
    char *sign;char *key; //xxtea 加密需要的sign和key
    char *inf;char *outf; //输入文件和输出文件
    unsigned char *buf, *data; //文件读取
    int keyl,signl;//sign和key的长度
    int renl;//函数返回值
    int fileNameSize;//文件名长度
    unsigned long lenth;//文件大小
    if(argc<5){
             printf("luatool - a tool for reengineering Android apk files \nwith cocos2dx-lua xxtea \nCopyright 2018 Blacat Recycler<recyclerblacat@gmail.com> \nusage:luatool d[ecode] <file_lua> <sign> <key>\nusage:luatool b[uild] <file_lua> <sign> <key>\n");
        return 0;
    }
    command = argv[1];
        if(CAMP("D")||CAMP("d")){//解析
            inf=argv[2];
            fileNameSize=strlen(inf);
            outf=(char *)malloc(fileNameSize+strlen(".lua"));
            strcpy(outf,inf);
            strcat(outf,".lua");//添加后缀
            sign=argv[3];
            key=argv[4];
            keyl=strlen(key);
            signl=strlen(sign);

        }else if(CAMP("B")||CAMP("b")){//重建
            inf=argv[2];
            fileNameSize=strlen(inf);
            outf=(char *)malloc(fileNameSize-strlen(".lua"));
            strncpy(outf,inf,fileNameSize-strlen(".lua"));
            outf[fileNameSize-strlen(".lua")]='\0';
            sign=argv[3];
            key=argv[4];
            keyl=strlen(key);
            signl=strlen(sign);
        }
        else{
            printf("cannot find this command\n");return 0;
        }
    if((fp=fopen(inf,"rb"))==NULL){
        printf("cannot read file!\n");
        return -1;
    }
    fseek(fp,0L,SEEK_END);//指向文件末尾
    lenth=ftell(fp);//获取文件流长度
    rewind(fp);//重新指回文件开头
    buf=(unsigned char *)malloc(lenth);
    fread(buf,lenth,1,fp);
    fclose(fp);
    if(CAMP("D")||CAMP("d")){//解析的情况
        data=xxtea_decrypt((buf+signl),(xxtea_long)lenth-signl,(unsigned char *)key,(xxtea_long)keyl,(xxtea_long *)&renl);
        if(data==NULL){
		printf("%s decrypt fail\n",inf);
		return -1;
        }

        if((fp=fopen(outf,"wb+"))==0){
                printf("%s",outf);
        printf("cannot write file!\n");
        return -1;
        }

        fwrite(data,renl,1,fp);
        fclose(fp);
    }else if(CAMP("B")||CAMP("b")){//重建的情况
        data=xxtea_encrypt(buf,(xxtea_long)lenth,(unsigned char *)key,(xxtea_long)keyl,(xxtea_long*)&renl);
        if(data==NULL){
		printf("%s encrypt fail\n",inf);
		return -1;
        }
        if((fp=fopen(outf,"w+"))==0){
            printf("cannot write file!\n");
            return -1;
        }
        fwrite(sign,signl,1,fp);
        fclose(fp);

        if((fp=fopen(outf,"ab+"))==0){
        printf("write failed!\n");
        return -1;
        }

        fwrite(data,renl,1,fp);
        fclose(fp);

    }


    return 0;
}
