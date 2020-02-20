
#include "basic_io.h"
#include "SD_Card.h"

int main(void)
{
  UINT16 i=0;
  UINT32 j=720;

  UINT16 Buffer0[256]={0};//256x16bits. 512Byte
  UINT16 Buffer1[256]={0};
  //PingPong Buffer
  //By Dee Zeng
  //Audio FIFO 512x16bits.(Audio ip changed)
  //when >256 or Buffer0,Buffer1 both not ready , read datas from SD card into buffers
  //when wrusedw < 256 ,write data to FIFO (Buffer0 -> Buffer1 -> Buffer0 loop)
  BYTE Buffer0_ready = 0;
  BYTE Buffer1_ready = 0;
  BYTE Buffer_status = 0;

  while(SD_card_init())
  usleep(50000);

  SD_Start_Multi_Read(j);
  while(1){

      if( (!IORD(AUDIO_0_BASE,0)) &&( ((!Buffer_status) && Buffer0_ready) || (Buffer_status && Buffer1_ready) ) )
      {   //PingPong Buffer -> FIFO
    	  if( (!Buffer_status) && Buffer0_ready){
    	    while(i<256)
    	    {
                IOWR(AUDIO_0_BASE,0,Buffer0[i++]);
                // 16bits {LSB,MSB}
                //.data({iDATA[7:0],iDATA[15:8]}),
                // recovery in AUDIO IP
            }
    	    Buffer0_ready = 0;
         	i = 0;
         	Buffer_status = 1;
    	  }else if(Buffer_status && Buffer1_ready){
    	    while(i<256)
    	    {
                IOWR(AUDIO_0_BASE,0,Buffer1[i++]);
            }
    	    Buffer1_ready = 0;
            i = 0;
         	Buffer_status = 0;
    	  }
       }else{ // SD Card -> PingPong Buffer

    	        if(!Buffer0_ready){
    	            SD_read_lba(Buffer0,j++);
    	            Buffer0_ready  =  1;
    	        }else if(!Buffer1_ready){
    	            SD_read_lba(Buffer1,j++);
    	            Buffer1_ready  =  1;
    	        }
       }

    if(j%64==0)
    {
      IOWR(LED_RED_BASE,0,Buffer0[0]);
      IOWR(LED_GREEN_BASE,0,Buffer1[0]);
    }

    IOWR(SEG7_DISPLAY_BASE,0,j); //7SEG display

    if((IORD(BUTTON_PIO_BASE,0)&0x02) == 0){ //press KEY1
       SD_Stop(); //CMD12 stop transmission
       j=720;
       SD_Start_Multi_Read(j); //CMD18 start multiple block read
       } //restart (you can try other value)
  }
 
  return 0;
}

//-------------------------------------------------------------------------


