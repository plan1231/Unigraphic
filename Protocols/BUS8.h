#ifndef BUS8_H
#define BUS8_H

#include "mbed.h"
#include "Protocols.h"
//#include "GraphicsDisplay.h"

/** Parallel 8bit interface
*/
class BUS8 : public Protocols
{
 public:

    /** Create a BUS8 display interface with scattered pins and 5 control pins
    *
    * @param buspins array of PinName to group as Bus
    * , i.e PinName buspins[8]={PC_0,PC_1,PC_2,PC_3,D9,D8,D7,D6};
    * @param CS pin connected to CS of display
    * @param reset pin connected to RESET of display
    * @param DC pin connected to data/command of display
    * @param WR pin connected to SDI of display
    * @param RD pin connected to RS of display 
    */ 
    BUS8(PinName* buspins, PinName CS, PinName reset, PinName DC, PinName WR, PinName RD);

protected:
  
    /** Send 8bit command to display controller 
    *
    * @param cmd: byte to send  
    *
    */   
    virtual void wr_cmd8(unsigned char cmd);
    
    /** Send 8bit data to display controller 
    *
    * @param data: byte to send   
    *
    */   
    virtual void wr_data8(unsigned char data);
    
    /** Send 2x8bit command to display controller 
    *
    * @param cmd: halfword to send  
    *
    */   
    virtual void wr_cmd16(unsigned short cmd);
    
    /** Send 2x8bit data to display controller 
    *
    * @param data: halfword to send   
    *
    */   
    virtual void wr_data16(unsigned short data);
    
    /** Send 16bit pixeldata to display controller 
    *
    * @param data: halfword to send   
    *
    */   
    virtual void wr_gram(unsigned short data);
    
    /** Send same 16bit pixeldata to display controller multiple times
    *
    * @param data: halfword to send
    * @param count: how many
    *
    */   
    virtual void wr_gram(unsigned short data, unsigned int count);
    
    /** Send array of pixeldata shorts to display controller
    *
    * @param data: unsigned short pixeldata array
    * @param lenght: lenght (in shorts)
    *
    */   
    virtual void wr_grambuf(unsigned short* data, unsigned int lenght);
    
    /** Read 16bit pixeldata from display controller (with dummy cycle)
    *
    * @param convert true/false. Convert 18bit to 16bit, some controllers returns 18bit
    * @returns 16bit color
    */ 
    virtual unsigned short rd_gram(bool convert);
    
    /** Read 4x8bit register data (with dummy cycle)
    * @param reg the register to read
    * @returns data as uint
    * 
    */ 
    virtual unsigned int rd_reg_data32(unsigned char reg);
    
    /** Read 3x8bit ExtendedCommands register data
    * @param reg the register to read
    * @returns data as uint
    * @note EXTC regs (0xB0 to 0xFF) are read/write registers, for Parallel mode directly accessible in both directions
    */ 
    virtual unsigned int rd_extcreg_data32(unsigned char reg, unsigned char SPIreadenablecmd);
    
    /** ILI932x specific, does a dummy read cycle, number of bits is protocol dependent
    * for PAR protocols: a signle RD bit toggle
    * for SPI8: 8clocks
    * for SPI16: 16 clocks
    */   
    virtual void dummyread ();
    
    /** ILI932x specific, select register for a successive write or read
    *
    * @param reg register to be selected
    * @param forread false = a write next (default), true = a read next
    * @note forread only used by SPI protocols
    */   
    virtual void reg_select(unsigned char reg, bool forread =false);
    
    /** ILI932x specific, write register with data
    *
    * @param reg register to write
    * @param data 16bit data
    */   
    virtual void reg_write(unsigned char reg, unsigned short data);
    
    /** ILI932x specific, read register
    *
    * @param reg register to be read
    * @returns 16bit register value
    */ 
    virtual unsigned short reg_read(unsigned char reg);
    
    /** HW reset sequence (without display init commands)   
    */
    virtual void hw_reset();
    
    /** Set ChipSelect high or low
    * @param enable 0/1   
    */
    virtual void BusEnable(bool enable);
  
   

private:

    BusInOut _bus;
    DigitalOut _CS; 
    DigitalOut _reset;
    DigitalOut _DC;
    DigitalOut _WR;
    DigitalOut _RD;
  
};
#endif