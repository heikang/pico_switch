#if 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "hardware/uart.h"
#include "tusb.h"

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

#include "bsp/board.h"
#include "bsp/rp2040/board.h"
#endif


#include "lcd.h"
#include "img/lcdfont.h"
#include "img/github.h"
#include "img/ns.h"
#include "img/nga.h"

/******************************************************************************
  ����˵����LCD��������д�뺯��
  ������ݣ�dat  Ҫд��Ĵ�������
  ����ֵ��  ��
 ******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) 
{
	spi_write_blocking(spi_default, &dat, 1);
}

/******************************************************************************
  ����˵����LCDд������
  ������ݣ�dat д�������
  ����ֵ��  ��
 ******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
  ����˵����LCDд������
  ������ݣ�dat д�������
  ����ֵ��  ��
 ******************************************************************************/
void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
  ����˵����LCDд������
  ������ݣ�dat д�������
  ����ֵ��  ��
 ******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//   gpio_put(11, 0)//DC //д����
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//д����
}


/******************************************************************************
  ����˵����������ʼ�ͽ�����ַ
  ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
  y1,y2 �����е���ʼ�ͽ�����ַ
  ����ֵ��  ��
 ******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1+80);
		LCD_WR_DATA(y2+80);
		LCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
	else
	{
		LCD_WR_REG(0x2a);//�е�ַ����
		LCD_WR_DATA(x1+80);
		LCD_WR_DATA(x2+80);
		LCD_WR_REG(0x2b);//�е�ַ����
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//������д
	}
}

void LCD_Init(void)
{

	LCD_RES_Clr();//  gpio_put(10, 0)//RES //��λ
	sleep_ms(100);
	LCD_RES_Set();
	sleep_ms(100);

	LCD_BLK_Set();//�򿪱���
	sleep_ms(100);

	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	sleep_ms(120);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);
	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29); 
} 



/******************************************************************************
  ����˵������ָ�����������ɫ
  ������ݣ�xsta,ysta   ��ʼ����
  xend,yend   ��ֹ����
  color       Ҫ������ɫ
  ����ֵ��  ��
 ******************************************************************************/
uint16_t picbuf[115200/2];
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 

	for(i=0;i<(115200/2);i++)
		picbuf[i] = color;

	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//������ʾ��Χ

	spi_write_blocking(spi_default, (uint8_t *)picbuf, (xend-xsta)*(yend-ysta)*2);
#if 0
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA(color);
		}
	} 					  	    
#endif
}

/******************************************************************************
  ����˵������ָ��λ�û���
  ������ݣ�x,y ��������
  color �����ɫ
  ����ֵ��  ��
 ******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Address_Set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(color);
} 


/******************************************************************************
  ����˵��������
  ������ݣ�x1,y1   ��ʼ����
  x2,y2   ��ֹ����
  color   �ߵ���ɫ
  ����ֵ��  ��
 ******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
  ����˵����������
  ������ݣ�x1,y1   ��ʼ����
  x2,y2   ��ֹ����
  color   ���ε���ɫ
  ����ֵ��  ��
 ******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
  ����˵������Բ
  ������ݣ�x0,y0   Բ������
  r       �뾶
  color   Բ����ɫ
  ����ֵ��  ��
 ******************************************************************************/
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}


/******************************************************************************
  ����˵������ʾ�����ַ�
  ������ݣ�x,y��ʾ����
  num Ҫ��ʾ���ַ�
  fc �ֵ���ɫ
  bc �ֵı���ɫ
  sizey �ֺ�
mode:  0�ǵ���ģʽ  1����ģʽ
����ֵ��  ��
 ******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //���ù��λ�� 
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==12)temp=ascii_1206[num][i];		       //����6x12����
		else if(sizey==16)temp=ascii_1608[num][i];		 //����8x16����
		else if(sizey==24)temp=ascii_2412[num][i];		 //����12x24����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//�ǵ���ģʽ
			{
				if(temp&(0x01<<t))LCD_WR_DATA(fc);
				else LCD_WR_DATA(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//����ģʽ
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//��һ����
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
  ����˵������ʾ�ַ���
  ������ݣ�x,y��ʾ����
 *p Ҫ��ʾ���ַ���
 fc �ֵ���ɫ
 bc �ֵı���ɫ
 sizey �ֺ�
mode:  0�ǵ���ģʽ  1����ģʽ
����ֵ��  ��
 ******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
  ����˵������ʾ����
  ������ݣ�m������nָ��
  ����ֵ��  ��
 ******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
  ����˵������ʾ��������
  ������ݣ�x,y��ʾ����
  num Ҫ��ʾ��������
  len Ҫ��ʾ��λ��
  fc �ֵ���ɫ
  bc �ֵı���ɫ
  sizey �ֺ�
  ����ֵ��  ��
 ******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 

		}
		LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 

/******************************************************************************
  ����˵������ʾ��λС������
  ������ݣ�x,y��ʾ����
  num Ҫ��ʾС������
  len Ҫ��ʾ��λ��
  fc �ֵ���ɫ
  bc �ֵı���ɫ
  sizey �ֺ�
  ����ֵ��  ��
 ******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{
	uint8_t t,temp,sizex;
	uint16_t num1;
	sizex=sizey/2;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
			t++;
			len+=1;
		}
		LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
}


/******************************************************************************
  ����˵������ʾͼƬ
  ������ݣ�x,y�������
  length ͼƬ����
  width  ͼƬ���
  pic[]  ͼƬ����
  ����ֵ��  ��
 ******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);

	spi_write_blocking(spi_default, pic, length*width*2);
#if 0
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}
#endif
}

void LCD_ShowPicture16(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint16_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);

	spi_write_blocking(spi_default, (uint8_t*)pic, length*width*2);
}


uint16_t sx = 0;
uint16_t sy = 0;
uint16_t sn = 0;

void ps(const uint8_t *p)
{
	char buf[5] = {0};
	sprintf(buf, "%3d", sn);
	LCD_ShowString(sx,sy, buf, BLACK, LIGHTBLUE, 16, 0);
	LCD_ShowString(sx+40,sy, p, BLACK, LIGHTBLUE, 16, 0);
	sy += 20;

	if((sy+20) > 240){
		LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
		sy = 0;
	}

	sn++;
	if(sn > 100)
		sn = 0;
}

void pn(uint32_t num)
{
	char buf[5] = {0};
	sprintf(buf, "%3d", sn);
	LCD_ShowString(sx,sy, buf, BLACK, LIGHTBLUE, 16, 0);
	LCD_ShowIntNum(sx+40,sy,num, 15, BLACK, LIGHTBLUE,16);
	sy += 20;

	if((sy+20) > 240){
		LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
		sy = 0;
	}

	sn++;
	if(sn > 100)
		sn = 0;
}

void Calc_Fps(void)
{
	int i;
	int start_ms;
	int end_ms;
	int dt;
	int fps;
	char buf[10] = {0};

	start_ms = board_millis();

	for(i=0;i<200;i++){
		//LCD_Fill(0,0,LCD_W,LCD_H,BLUE);
		LCD_ShowPicture(0,0,240,240,gImage_ns);
	}

	end_ms = board_millis();

	LCD_Fill(0,0,LCD_W,LCD_H,GREEN);

	dt = end_ms - start_ms;
	pn(dt);

	dt = dt/1000;
	fps = 200/dt;
	pn(fps);
}

void screen(void)
{
	int i;

	LCD_Init();
	//Calc_Fps();

	while(1){
		LCD_ShowPicture16(0,0,240,240,gImage_github);
		sleep_ms(2000);
		LCD_ShowPicture16(0,0,240,240,gImage_nga);
		sleep_ms(2000);
		LCD_ShowPicture16(0,0,240,240,gImage_ns);
		sleep_ms(2000);
	}
}
