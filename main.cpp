
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "xxtea.cpp"

#define CAMP(x) strcmp(command,x)==0

int main(int argc, char * argv[]){

    FILE *fp;   //�ļ�ָ��
    char *command; //��ѹ����
    char *sign;char *key; //xxtea ������Ҫ��sign��key
    char *inf;char *outf; //�����ļ�������ļ�
    unsigned char *buf, *data; //�ļ���ȡ
    int keyl,signl;//sign��key�ĳ���
    int renl;//��������ֵ
    int fileNameSize;//�ļ�������
    unsigned long lenth;//�ļ���С
    if(argc<5){
             printf("luatool - a tool for reengineering Android apk files \nwith cocos2dx-lua xxtea \nCopyright 2018 Blacat Recycler<recyclerblacat@gmail.com> \nusage:luatool d[ecode] <file_lua> <sign> <key>\nusage:luatool b[uild] <file_lua> <sign> <key>\n");
        return 0;
    }
    command = argv[1];
        if(CAMP("D")||CAMP("d")){//����
            inf=argv[2];
            fileNameSize=strlen(inf);
            outf=(char *)malloc(fileNameSize+strlen(".lua"));
            strcpy(outf,inf);
            strcat(outf,".lua");//��Ӻ�׺
            sign=argv[3];
            key=argv[4];
            keyl=strlen(key);
            signl=strlen(sign);

        }else if(CAMP("B")||CAMP("b")){//�ؽ�
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
    fseek(fp,0L,SEEK_END);//ָ���ļ�ĩβ
    lenth=ftell(fp);//��ȡ�ļ�������
    rewind(fp);//����ָ���ļ���ͷ
    buf=(unsigned char *)malloc(lenth);
    fread(buf,lenth,1,fp);
    fclose(fp);
    if(CAMP("D")||CAMP("d")){//���������
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
    }else if(CAMP("B")||CAMP("b")){//�ؽ������
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
