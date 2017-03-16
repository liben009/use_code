 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>   //ͷ�ļ�
 #include <assert.h>
 #include "get_cpu.h"
 
 int get_phy_mem(const pid_t p)
 {
    char file[64] = {0};//�ļ���
	
    FILE *fd;         //�����ļ�ָ��fd
    char line_buff[256] = {0};  //��ȡ�еĻ�����
    sprintf(file,"/proc/%d/status",p);//�ļ��е�11�а�����
  
    fprintf (stderr, "current pid:%d\n", p);                                                                                                  
    fd = fopen (file, "r"); //��R���ķ�ʽ���ļ��ٸ���ָ��fd
 
	//��ȡvmrss:ʵ�������ڴ�ռ��
    int i;
	char name[32];//�����Ŀ����
    int vmrss;//����ڴ��ֵ��С
    for (i = 0;i < VMRSS_LINE - 1;i++)
    {
        fgets (line_buff, sizeof(line_buff), fd);
    }
	//������15��
    fgets (line_buff, sizeof(line_buff), fd);//��ȡVmRSS��һ�е�����,VmRSS�ڵ�15��
    sscanf (line_buff, "%s %d", name,&vmrss);
    fprintf (stderr, "====%s��%d====\n", name,vmrss);
    fclose(fd);     //�ر��ļ�fd
    return vmrss;
}

 int get_rmem(pid_t p)
 {
    return get_phy_mem(p);
 }
 
 
 int get_total_mem()
 {
     char* file = "/proc/meminfo";//�ļ���
   
     FILE *fd;         //�����ļ�ָ��fd
     char line_buff[256] = {0};  //��ȡ�еĻ�����                                                                                                
     fd = fopen (file, "r"); //��R���ķ�ʽ���ļ��ٸ���ָ��fd

     //��ȡmemtotal:���ڴ�ռ�ô�С
     int i;
     char name[32];//�����Ŀ����
     int memtotal;//����ڴ��ֵ��С
     fgets (line_buff, sizeof(line_buff), fd);//��ȡmemtotal��һ�е�����,memtotal�ڵ�1��
     sscanf (line_buff, "%s %d", name,&memtotal);
     fprintf (stderr, "====%s��%d====\n", name,memtotal);
     fclose(fd);     //�ر��ļ�fd
     return memtotal;
 }
 
 float get_pmem(pid_t p)
 {
	 int phy = get_phy_mem(p);
	 int total = get_total_mem();
     float occupy = (phy*1.0)/(total*1.0);
	 fprintf(stderr,"====process mem occupy:%.6f\n====",occupy);
     return occupy;
 }
 
unsigned int get_cpu_process_occupy(const pid_t p)
{
    char file[64] = {0};//�ļ���
    process_cpu_occupy_t t;
  
    FILE *fd;         //�����ļ�ָ��fd
    char line_buff[1024] = {0};  //��ȡ�еĻ�����
    sprintf(file,"/proc/%d/stat",p);//�ļ��е�11�а�����

    fprintf (stderr, "current pid:%d\n", p);                                                                                                  
    fd = fopen (file, "r"); //��R���ķ�ʽ���ļ��ٸ���ָ��fd
    fgets (line_buff, sizeof(line_buff), fd); //��fd�ļ��ж�ȡ����Ϊbuff���ַ����ٴ浽��ʼ��ַΪbuff����ռ���

    sscanf(line_buff,"%u",&t.pid);//ȡ�õ�һ��
    char* q = get_items(line_buff,PROCESS_ITEM);//ȡ�ôӵ�14�ʼ����ʼָ��
    sscanf(q,"%u %u %u %u",&t.utime,&t.stime,&t.cutime,&t.cstime);//��ʽ����14,15,16,17��

    fprintf (stderr, "====pid%u:%u %u %u %u====\n", t.pid, t.utime,t.stime,t.cutime,t.cstime);
    fclose(fd);     //�ر��ļ�fd
    return (t.utime + t.stime + t.cutime + t.cstime);
} 

unsigned int get_user_cpu_process_occupy(const pid_t p)
{
    char file[64] = {0};//�ļ���
    process_cpu_occupy_t t;
  
    FILE *fd;         //�����ļ�ָ��fd
    char line_buff[1024] = {0};  //��ȡ�еĻ�����
    sprintf(file,"/proc/%d/stat",p);//�ļ��е�11�а�����

    fprintf (stderr, "current pid:%d\n", p);                                                                                                  
    fd = fopen (file, "r"); //��R���ķ�ʽ���ļ��ٸ���ָ��fd
    fgets (line_buff, sizeof(line_buff), fd); //��fd�ļ��ж�ȡ����Ϊbuff���ַ����ٴ浽��ʼ��ַΪbuff����ռ���

    sscanf(line_buff,"%u",&t.pid);//ȡ�õ�һ��
    char* q = get_items(line_buff,PROCESS_ITEM);//ȡ�ôӵ�14�ʼ����ʼָ��
    sscanf(q,"%u",&t.utime);//��ʽ����14��

    fprintf (stderr, "====pid%u:%u %u %u %u====\n", t.pid, t.utime);
    fclose(fd);     //�ر��ļ�fd
	
    return t.utime;
}

unsigned int get_cpu_total_occupy()
{
	 FILE *fd;         //�����ļ�ָ��fd
 	 char buff[1024] = {0};  //����ֲ�����buff����Ϊchar���ʹ�СΪ1024
     total_cpu_occupy_t t;
                                                                                                              
     fd = fopen ("/proc/stat", "r"); //��R���ķ�ʽ��stat�ļ��ٸ���ָ��fd
     fgets (buff, sizeof(buff), fd); //��fd�ļ��ж�ȡ����Ϊbuff���ַ����ٴ浽��ʼ��ַΪbuff����ռ���
     /*�����ǽ�buff���ַ������ݲ���format��ת��Ϊ���ݵĽ��������Ӧ�Ľṹ����� */
     char name[16];//��ʱ��������ַ���
     sscanf (buff, "%s %u %u %u %u", name, &t.user, &t.nice,&t.system, &t.idle);
     
	 fclose(fd);     //�ر��ļ�fd
     return (t.user + t.nice + t.system + t.idle);
}
 

 float get_pcpu(pid_t p)
 {
	 unsigned int totalcputime1,totalcputime2;
     unsigned int procputime1,procputime2;
	 unsigned int procusertime1, procusertime2;
	 procputime1 = get_user_cpu_process_occupy(p);
     totalcputime1 = get_cpu_total_occupy();
     procputime1 = get_cpu_process_occupy(p);
     usleep(500000);//�ӳ�500����
	 procputime2 = get_user_cpu_process_occupy(p);
     totalcputime2 = get_cpu_total_occupy();
     procputime2 = get_cpu_process_occupy(p);
	 float pid_user_cpu = 100.0 * (procusertime2 - procusertime1) / (totalcputime2 - totalcputime1);
     float pcpu = 100.0*(procputime2 - procputime1)/(totalcputime2 - totalcputime1);
     fprintf(stderr,"====pcpu:%.6f =====user_pcpu:%.6f\n====",pcpu, pid_user_cpu);
     return pcpu;
}


const char* get_items(const char* buffer,int ie)
{
	assert(buffer);
    char* p = buffer;//ָ�򻺳���
    int len = strlen(buffer);
    int count = 0;//ͳ�ƿո���
    if (1 == ie || ie < 1)
    {
		return p;
    }

	int i;

    for (i=0; i<len; i++)
    {
        if (' ' == *p)
		{
	        count++;
            if (count == ie-1)
			{
				p++;
                break;
			}
	   }
		p++;
    }
 
	return p;

}

int main(int argc, char *argv[])
{	
	int ret = -1;
	
	if (argc < 2)
	{
		return ret;
	}

	pid_t p = atoi(argv[1]);
	float pcpu = get_pcpu(p);
	float prem = get_pmem(p);
	return 0;
} 
