/**
  ECAN Generated Driver  File

  @Company
    Microchip Technology Inc.

  @File Name
    ecan.c

  @Summary
    This is the generated driver implementation for the ECAN driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for CAN.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.12.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00
*/


/**
  Section: Included Files
*/

#include <xc.h>
#include "ecan.h"
// �rne?in, ecan.c i�inde global de?i?kenlerin tan?mlar?:
uint8_t VehicleSpeed;
bool SpeedInfoReceived = false; // Varsay?lan de?erini ayarlad?m

// Fonksiyon prototipleri ve tan?mlar? ecan.h dosyas?na eklenmeli

static void (*WakeUpInterruptHandler)(void);

/**
    Local Functions
*/  
static uint32_t convertReg2ExtendedCANid(uint8_t tempRXBn_EIDH, uint8_t tempRXBn_EIDL, uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL);
static uint32_t convertReg2StandardCANid(uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL);
static void convertCANid2Reg(uint32_t tempPassedInID, uint8_t canIdType, uint8_t *passedInEIDH, uint8_t *passedInEIDL, uint8_t *passedInSIDH, uint8_t *passedInSIDL);

static void WakeUpDefaultInterruptHandler(void) {}

void ECAN_Initialize(void)
{
    CANCON = 0x80;
    while (0x80 != (CANSTAT & 0xE0)); // wait until ECAN is in config mode
    
    /**
    Mode 0
    */
    ECANCON = 0x00;
    
    /**
    Initialize CAN I/O
    */
    CIOCON = 0x20;
    
    /**
    Mask and Filter definitions
    ........................................................    
    CAN ID		ID Type		Mask				Filter		Buffer    
    ........................................................    
    ........................................................
    */
 
/**    
    Initialize Receive Masks
*/   
    RXM0EIDH = 0x00;
    RXM0EIDL = 0x00;
    RXM0SIDH = 0x00;
    RXM0SIDL = 0x00;
    RXM1EIDH = 0x00;
    RXM1EIDL = 0x00;
    RXM1SIDH = 0x00;
    RXM1SIDL = 0x00;
 
    /**
    Initialize Receive Filters
    */   
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x00;
    RXF0SIDL = 0x00;
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x00;
    RXF1SIDL = 0x00;
    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0x00;
    RXF2SIDL = 0x00;
    RXF3EIDH = 0x00;
    RXF3EIDL = 0x00;
    RXF3SIDH = 0x00;
    RXF3SIDL = 0x00;
    RXF4EIDH = 0x00;
    RXF4EIDL = 0x00;
    RXF4SIDH = 0x00;
    RXF4SIDL = 0x00;
    RXF5EIDH = 0x00;
    RXF5EIDL = 0x00;
    RXF5SIDH = 0x00;
    RXF5SIDL = 0x00;

    /**
    Initialize CAN Timings
    */
    
  	/**
        Baud rate: 500kbps
        System frequency: 8000000
        ECAN clock frequency: 8000000
        Time quanta: 8
        Sample point: 1-1-4-2
        Sample point: 75%
	*/ 
    
    BRGCON1 = 0x00;
    BRGCON2 = 0x98;
    BRGCON3 = 0x01;
    
    ECAN_SetWakeUpInterruptHandler(WakeUpDefaultInterruptHandler);
    PIR5bits.WAKIF = 0;
    PIE5bits.WAKIE = 1;
    
    CANCON = 0x00;
    while (0x00 != (CANSTAT & 0xE0)); // wait until ECAN is in Normal mode   
    
}
/**
  Section: CAN APIs
*/

void CAN_sleep(void) 
{
    CANCON = 0x20; // request disable mode
    while ((CANSTAT & 0xE0) != 0x20); // wait until ECAN is in disable mode   
    //Wake up from sleep should set the CAN module straight into Normal mode

}

uint8_t CAN_transmit(uCAN_MSG *tempCanMsg) {
    uint8_t tempEIDH = 0;
    uint8_t tempEIDL = 0;
    uint8_t tempSIDH = 0;
    uint8_t tempSIDL = 0;

    uint8_t returnValue = 0;

    if (TXB0CONbits.TXREQ != 1) 
    {
        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB0EIDH = tempEIDH;
        TXB0EIDL = tempEIDL;
        TXB0SIDH = tempSIDH;
        TXB0SIDL = tempSIDL;
        TXB0DLC  = tempCanMsg->frame.dlc;
        TXB0D0   = tempCanMsg->frame.data0;
        TXB0D1   = tempCanMsg->frame.data1;
        TXB0D2   = tempCanMsg->frame.data2;
        TXB0D3   = tempCanMsg->frame.data3;
        TXB0D4   = tempCanMsg->frame.data4;
        TXB0D5   = tempCanMsg->frame.data5;
        TXB0D6   = tempCanMsg->frame.data6;
        TXB0D7   = tempCanMsg->frame.data7;

        TXB0CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
        
    } 
    else if (TXB1CONbits.TXREQ != 1) 
    {

        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB1EIDH = tempEIDH;
        TXB1EIDL = tempEIDL;
        TXB1SIDH = tempSIDH;
        TXB1SIDL = tempSIDL;
        TXB1DLC  = tempCanMsg->frame.dlc;
        TXB1D0   = tempCanMsg->frame.data0;
        TXB1D1   = tempCanMsg->frame.data1;
        TXB1D2   = tempCanMsg->frame.data2;
        TXB1D3   = tempCanMsg->frame.data3;
        TXB1D4   = tempCanMsg->frame.data4;
        TXB1D5   = tempCanMsg->frame.data5;
        TXB1D6   = tempCanMsg->frame.data6;
        TXB1D7   = tempCanMsg->frame.data7;

        TXB1CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    } 
    else if (TXB2CONbits.TXREQ != 1) 
    {

        convertCANid2Reg(tempCanMsg->frame.id, tempCanMsg->frame.idType, &tempEIDH, &tempEIDL, &tempSIDH, &tempSIDL);

        TXB2EIDH = tempEIDH;
        TXB2EIDL = tempEIDL;
        TXB2SIDH = tempSIDH;
        TXB2SIDL = tempSIDL;
        TXB2DLC  = tempCanMsg->frame.dlc;
        TXB2D0   = tempCanMsg->frame.data0;
        TXB2D1   = tempCanMsg->frame.data1;
        TXB2D2   = tempCanMsg->frame.data2;
        TXB2D3   = tempCanMsg->frame.data3;
        TXB2D4   = tempCanMsg->frame.data4;
        TXB2D5   = tempCanMsg->frame.data5;
        TXB2D6   = tempCanMsg->frame.data6;
        TXB2D7   = tempCanMsg->frame.data7;

        TXB2CONbits.TXREQ = 1; //Set the buffer to transmit		
        returnValue = 1;
    }

    return (returnValue);
}

uint8_t CAN_receive(uCAN_MSG *tempCanMsg) {
    uint8_t returnValue = 0;

    //check which buffer the CAN message is in
    if (RXB0CONbits.RXFUL != 0) { //CheckRXB0
        if ((RXB0SIDL & 0x08) == 0x08) { //If Extended Message
            //message is extended
            tempCanMsg->frame.idType = (uint8_t) dEXTENDED_CAN_MSG_ID_2_0B;
            tempCanMsg->frame.id = convertReg2ExtendedCANid(RXB0EIDH, RXB0EIDL, RXB0SIDH, RXB0SIDL);
        } else {
            //message is standard
            tempCanMsg->frame.idType = (uint8_t) dSTANDARD_CAN_MSG_ID_2_0B;
            tempCanMsg->frame.id = convertReg2StandardCANid(RXB0SIDH, RXB0SIDL);
        }

        tempCanMsg->frame.dlc = RXB0DLC;
        tempCanMsg->frame.data0 = RXB0D0;
        tempCanMsg->frame.data1 = RXB0D1;
        tempCanMsg->frame.data2 = RXB0D2;
        tempCanMsg->frame.data3 = RXB0D3;
        tempCanMsg->frame.data4 = RXB0D4;
        tempCanMsg->frame.data5 = RXB0D5;
        tempCanMsg->frame.data6 = RXB0D6;
        tempCanMsg->frame.data7 = RXB0D7;

        

        RXB0CONbits.RXFUL = 0;
        returnValue = 1;
    } else if (RXB1CONbits.RXFUL != 0) { //CheckRXB1
        // Ayn? i?lemler RXB1 i�in de tekrarlan?yor
        if ((RXB1SIDL & 0x08) == 0x08) { //If Extended Message
            tempCanMsg->frame.idType = (uint8_t) dEXTENDED_CAN_MSG_ID_2_0B;
            tempCanMsg->frame.id = convertReg2ExtendedCANid(RXB1EIDH, RXB1EIDL, RXB1SIDH, RXB1SIDL);
        } else {
            tempCanMsg->frame.idType = (uint8_t) dSTANDARD_CAN_MSG_ID_2_0B;
            tempCanMsg->frame.id = convertReg2StandardCANid(RXB1SIDH, RXB1SIDL);
        }

        tempCanMsg->frame.dlc = RXB1DLC;
        tempCanMsg->frame.data0 = RXB1D0;
        tempCanMsg->frame.data1 = RXB1D1;
        tempCanMsg->frame.data2 = RXB1D2;
        tempCanMsg->frame.data3 = RXB1D3;
        tempCanMsg->frame.data4 = RXB1D4;
        tempCanMsg->frame.data5 = RXB1D5;
        tempCanMsg->frame.data6 = RXB1D6;
        tempCanMsg->frame.data7 = RXB1D7;

        

        RXB1CONbits.RXFUL = 0;
        returnValue = 1;
    }
    return (returnValue);
}



uint8_t CAN_messagesInBuffer(void) 
{
    uint8_t messageCount = 0;
    if (RXB0CONbits.RXFUL != 0) //CheckRXB0
    {
        messageCount++;
    }
    if (RXB1CONbits.RXFUL != 0) //CheckRXB1
    {
        messageCount++;
    }

    return (messageCount);
}

uint8_t CAN_isBusOff(void) 
{
    uint8_t returnValue = 0;

    //COMSTAT bit 5 TXBO: Transmitter Bus-Off bit
    //1 = Transmit error counter > 255
    //0 = Transmit error counter less then or equal to 255

    if (COMSTATbits.TXBO == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

uint8_t CAN_isRXErrorPassive(void) 
{
    uint8_t returnValue = 0;

    //COMSTAT bit 3 RXBP: Receiver Bus Passive bit
    //1 = Receive error counter > 127
    //0 = Receive error counter less then or equal to 127

    if (COMSTATbits.RXBP == 1) {
        returnValue = 1;
    }
    return (returnValue);
}

uint8_t CAN_isTXErrorPassive(void) 
{
    uint8_t returnValue = 0;

    //COMSTAT bit 4 TXBP: Transmitter Bus Passive bit
    //1 = Transmit error counter > 127
    //0 = Transmit error counter less then or equal to 127

    if (COMSTATbits.TXBP == 1) 
    {
        returnValue = 1;
    }
    return (returnValue);
}

/**
Internal functions
*/


static uint32_t convertReg2ExtendedCANid(uint8_t tempRXBn_EIDH, uint8_t tempRXBn_EIDL, uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL) 
{
    uint32_t returnValue = 0;
    uint32_t ConvertedID = 0;
    uint8_t CAN_standardLo_ID_lo2bits;
    uint8_t CAN_standardLo_ID_hi3bits;

    CAN_standardLo_ID_lo2bits = (uint8_t)(tempRXBn_SIDL & 0x03);
    CAN_standardLo_ID_hi3bits = (uint8_t)(tempRXBn_SIDL >> 5);
    ConvertedID = (uint32_t)(tempRXBn_SIDH << 3);
    ConvertedID = ConvertedID + CAN_standardLo_ID_hi3bits;
    ConvertedID = (ConvertedID << 2);
    ConvertedID = ConvertedID + CAN_standardLo_ID_lo2bits;
    ConvertedID = (ConvertedID << 8);
    ConvertedID = ConvertedID + tempRXBn_EIDH;
    ConvertedID = (ConvertedID << 8);
    ConvertedID = ConvertedID + tempRXBn_EIDL;
    returnValue = ConvertedID;    
    return (returnValue);
}

static uint32_t convertReg2StandardCANid(uint8_t tempRXBn_SIDH, uint8_t tempRXBn_SIDL) 
{
    uint32_t returnValue = 0;
    uint32_t ConvertedID;
    //if standard message (11 bits)
    //EIDH = 0 + EIDL = 0 + SIDH + upper three bits SIDL (3rd bit needs to be clear)
    //1111 1111 111
    ConvertedID = (uint32_t)(tempRXBn_SIDH << 3);
    ConvertedID = ConvertedID + (uint32_t)(tempRXBn_SIDL >> 5);
    returnValue = ConvertedID;
    return (returnValue);
}

static void convertCANid2Reg(uint32_t tempPassedInID, uint8_t canIdType, uint8_t *passedInEIDH, uint8_t *passedInEIDL, uint8_t *passedInSIDH, uint8_t *passedInSIDL) 
{
    uint8_t wipSIDL = 0;

    if (canIdType == dEXTENDED_CAN_MSG_ID_2_0B) {

        //EIDL
        *passedInEIDL = 0xFF & tempPassedInID; //CAN_extendedLo_ID_TX1 = &HFF And CAN_UserEnter_ID_TX1
        tempPassedInID = tempPassedInID >> 8; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 >> 8

        //EIDH
        *passedInEIDH = 0xFF & tempPassedInID; //CAN_extendedHi_ID_TX1 = &HFF And CAN_UserEnter_ID_TX1
        tempPassedInID = tempPassedInID >> 8; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 >> 8

        //SIDL
        //push back 5 and or it
        wipSIDL = 0x03 & tempPassedInID;
        tempPassedInID = tempPassedInID << 3; //CAN_UserEnter_ID_TX1 = CAN_UserEnter_ID_TX1 << 3
        wipSIDL = (0xE0 & tempPassedInID) + wipSIDL;
        wipSIDL = (uint8_t)(wipSIDL + 0x08); // TEMP_CAN_standardLo_ID_TX1 = TEMP_CAN_standardLo_ID_TX1 + &H8
        *passedInSIDL = (uint8_t)(0xEB & wipSIDL); //CAN_standardLo_ID_TX1 = &HEB And TEMP_CAN_standardLo_ID_TX1

        //SIDH
        tempPassedInID = tempPassedInID >> 8;
        *passedInSIDH = 0xFF & tempPassedInID;
    } 
    else //(canIdType == dSTANDARD_CAN_MSG_ID_2_0B)
    {
        *passedInEIDH = 0;
        *passedInEIDL = 0;
        tempPassedInID = tempPassedInID << 5;
        *passedInSIDL = 0xFF & tempPassedInID;
        tempPassedInID = tempPassedInID >> 8;
        *passedInSIDH = 0xFF & tempPassedInID;
    }
}

void ECAN_SetWakeUpInterruptHandler(void (*handler)(void))
{
    WakeUpInterruptHandler = handler;
}

void ECAN_WAKI_ISR(void)
{
    WakeUpInterruptHandler();
    PIR5bits.WAKIF = 0;
}

// PID sorgulama ve cevap i?leme fonksiyonlar?

void ECAN_Send_VehicleSpeed_Request(void) {
    uint8_t can_tx_data[8] = {0x02, 0x01, 0x0D, 0x55, 0x55, 0x55, 0x55, 0x55};
    ECAN_SetTxMsgId(0x7DF); // �rnek ID
    ECAN_SetTxMsgDLC(8);    // Veri uzunlu?u
    for (uint8_t i = 0; i < 8; i++) {
        ECAN_SetTxData(i, can_tx_data[i]);
    }
    ECAN_Transmit();
}

uint8_t ECAN_ReceiveVehicleSpeed(void) {
    uint8_t can_rx_data[8];
    if (ECAN_ReceiveMsg()) {
        for (uint8_t i = 0; i < 8; i++) {
            can_rx_data[i] = ECAN_GetRxData(i);
        }
        if (can_rx_data[1] == 0x41 && can_rx_data[2] == 0x0D) {
            VehicleSpeed = can_rx_data[3];
            SpeedInfoReceived = true;
            return VehicleSpeed;
        }
    }
    SpeedInfoReceived = false;
    return 0;
}

// Yeni eklenen fonksiyonlar:
void ECAN_SetTxMsgId(uint32_t id) {
    // Tx mesaj ID'sini ayarlay?n
    TXB0SIDH = (id >> 3) & 0xFF; // SIDH (�st 8 bit)
    TXB0SIDL = (id << 5) & 0xE0; // SIDL (alt 3 bit)
}

void ECAN_SetTxMsgDLC(uint8_t dlc) {
    // Tx mesaj veri uzunlu?unu ayarlay?n
    TXB0DLC = dlc & 0x0F; // DLC'nin ilk 4 bitini kullan?n
}

void ECAN_SetTxData(uint8_t index, uint8_t data) {
    // Tx veri byte'?n? ayarlay?n
    switch (index) {
        case 0: TXB0D0 = data; break;
        case 1: TXB0D1 = data; break;
        case 2: TXB0D2 = data; break;
        case 3: TXB0D3 = data; break;
        case 4: TXB0D4 = data; break;
        case 5: TXB0D5 = data; break;
        case 6: TXB0D6 = data; break;
        case 7: TXB0D7 = data; break;
    }
}

void ECAN_Transmit(void) {
    // Mesaj? CAN hatt?na g�nderin
    TXB0CONbits.TXREQ = 1; // ?letim iste?ini ba?lat?n
}

bool ECAN_ReceiveMsg(void) {
    // CAN hatt?ndan mesaj al?m? kontrol edin
    return RXB0CONbits.RXFUL; // RX buffer doluysa true d�ner
}

uint8_t ECAN_GetRxData(uint8_t index) {
    // Rx veri byte'?n? d�nd�r�n
    uint8_t data = 0;
    switch (index) {
        case 0: data = RXB0D0; break;
        case 1: data = RXB0D1; break;
        case 2: data = RXB0D2; break;
        case 3: data = RXB0D3; break;
        case 4: data = RXB0D4; break;
        case 5: data = RXB0D5; break;
        case 6: data = RXB0D6; break;
        case 7: data = RXB0D7; break;
    }
    return data;
}

